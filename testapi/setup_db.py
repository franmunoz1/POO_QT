from pymongo import MongoClient
from werkzeug.security import generate_password_hash

# Conectar a MongoDB Atlas
client = MongoClient('mongodb+srv://franmunoz2501:Lourdes31@poo.kq1obxp.mongodb.net/')
db = client['Usuarios']
users_collection = db['usuarios']

# Insertar algunos usuarios
users = [
    {
        "nombre": "Juan",
        "apellido": "Carlos",
        "usuario": "juan123",
        "clave": generate_password_hash("password1")
    },
    {
        "nombre": "Maria",
        "apellido": "Gomez",
        "usuario": "maria456",
        "clave": generate_password_hash("password2")
    }
]

# Insertar usuarios en la colección
users_collection.insert_many(users)
print("Usuarios insertados correctamente.")
