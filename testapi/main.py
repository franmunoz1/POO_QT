from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from pymongo import MongoClient
from werkzeug.security import check_password_hash

# Conectar a MongoDB Atlas
client = MongoClient('mongodb+srv://franmunoz2501:<password>@poo.kq1obxp.mongodb.net/')
db = client['Usuarios']
users_collection = db['usuarios']

app = FastAPI()

class User(BaseModel):
    usuario: str
    clave: str

@app.post("/validar_usuario/")
async def validar_usuario(user: User):
    # Buscar usuario en la base de datos
    db_user = users_collection.find_one({"usuario": user.usuario})
    if db_user and check_password_hash(db_user['clave'], user.clave):
        nombre_completo = f"{db_user['nombre']}::{db_user['apellido']}"
        return {"mensaje": nombre_completo}
    else:
        raise HTTPException(status_code=401, detail="denegado")

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
