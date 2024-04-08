from fastapi import FastAPI, HTTPException
from pymongo import MongoClient
from pymongo.errors import DuplicateKeyError
import json

app = FastAPI()

# Conexión a la base de datos MongoDB
client = MongoClient("mongodb://localhost:27017/")
db = client["usuariosdb"]
collection = db["usuarios"]

# Registrar usuarios en MongoDB desde el archivo JSON
with open("users.json", "r") as file:
    usuarios = json.load(file)
    try:
        collection.insert_many(usuarios)
    except DuplicateKeyError:
        pass  # Ignorar si los usuarios ya existen en la base de datos


@app.get("/validar_usuario")
async def validar_usuario(usuario: str, clave: str):
    user = collection.find_one({"usuario": usuario, "clave": clave})
    if user:
        return {"mensaje": "Usuario válido"}
    else:
        raise HTTPException(status_code=401, detail="Usuario no válido")
