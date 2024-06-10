from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from pymongo import MongoClient

app = FastAPI()

# Conectar a MongoDB
client = MongoClient('localhost', 27017)
db = client['POO']
collection = db['Usuarios']

# Modelo de datos para la solicitud de validación
class Usuario(BaseModel):
    usuario: str
    clave: str

@app.post("/validar_usuario")
async def validar_usuario(usuario: Usuario):
    # Añadir impresión de depuración
    print(f"Buscando usuario: {usuario.usuario} con clave: {usuario.clave}")
    
    user = collection.find_one({"usuario": usuario.usuario, "clave": usuario.clave})
    
    # Añadir impresión de depuración
    print(f"Resultado de la consulta: {user}")
    
    if user:
        nombre_completo = f"{user['nombre']} {user['apellido']}::Ponce"
        return {"mensaje": nombre_completo}
    else:
        raise HTTPException(status_code=401, detail="denegado")

# Ejecutar el servidor con: uvicorn nombre_archivo:app --reload
