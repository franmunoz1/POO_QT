from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from pymongo import MongoClient
from bson import ObjectId
from typing import List

app = FastAPI()

# Conectar a MongoDB
client = MongoClient('localhost', 27017)
db = client['POO']
collection = db['Usuarios']

# Modelo de datos para la solicitud de validación
class Usuario(BaseModel):
    usuario: str
    clave: str

# Modelo de datos para la respuesta de usuarios
class UsuarioOut(BaseModel):
    id: str
    usuario: str
    nombre: str
    apellido: str

# Modelo de datos para agregar un usuario
class NuevoUsuario(BaseModel):
    usuario: str
    clave: str
    nombre: str
    apellido: str

@app.post("/validar_usuario")
async def validar_usuario(usuario: Usuario):
    # Añadir impresión de depuración
    print(f"Buscando usuario: {usuario.usuario} con clave: {usuario.clave}")
    
    user = collection.find_one({"usuario": usuario.usuario, "clave": usuario.clave})
    
    # Añadir impresión de depuración
    print(f"Resultado de la consulta: {user}")
    
    if user:
        nombre_completo = f"{user['nombre']}::{user['apellido']}"
        return {"mensaje": nombre_completo}
    else:
        raise HTTPException(status_code=401, detail="denegado")

@app.get("/usuarios", response_model=List[UsuarioOut])
async def obtener_usuarios():
    usuarios = []
    for user in collection.find():
        usuarios.append({
            "id": str(user["_id"]),
            "usuario": user["usuario"],
            "nombre": user["nombre"],
            "apellido": user["apellido"]
        })
    return usuarios

@app.delete("/usuarios/{usuario}")
async def delete_usuario(usuario: str):
    result = collection.delete_one({"usuario": usuario})
    
    if result.deleted_count == 1:
        return {"mensaje": "Usuario eliminado correctamente"}
    else:
        raise HTTPException(status_code=404, detail="Usuario no encontrado")

@app.post("/usuarios")
async def agregar_usuario(nuevo_usuario: NuevoUsuario):
    # Verificar si el usuario ya existe
    if collection.find_one({"usuario": nuevo_usuario.usuario}):
        raise HTTPException(status_code=400, detail="El usuario ya existe")
    
    # Insertar el nuevo usuario en la base de datos
    resultado = collection.insert_one(nuevo_usuario.dict())
    
    # Devolver el ID del nuevo usuario
    return {"id": str(resultado.inserted_id)}

# Ejecutar el servidor con: uvicorn nombre_archivo:app --reload
