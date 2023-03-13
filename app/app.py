
import motor.motor_asyncio
import pydantic
import datetime
from datetime import datetime

from pydantic import BaseModel
from fastapi.middleware.cors import CORSMiddleware
from typing import Optional
from fastapi import FastAPI, Request, HTTPException, status
from fastapi.responses import Response
from bson import ObjectId
from httpx import request

app = FastAPI()

class data(BaseModel):
   temp: float
   sunset:str
   fanspeed: bool
   brightness: bool

class info():
   temeperature: Optional[float] = None
   fanspeed: Optional[bool]=None
   sunset:Optional[str]=None
   brightness: Optional[bool]=None


origins = [
    "192.168.0.7"
    "https://ecse-sunset-api.onrender.com"
]



app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

client=motor.motor_asyncio.AsyncIOMotorClient("mongodb+srv://Tombraider77:Iamnotarobot17@cluster0.ylqnn6l.mongodb.net/?retryWrites=true&w=majority")

db = client.lab6

pydantic.json.ENCODERS_BY_TYPE[ObjectId]=str

app.put("/api/temperature",status_code= 204)
async def temp_data(temp_request: Request):
     
   
    temperature_obj = await temp_request.json()
    temp_find = await db["state"].find_one({"temperature": "tempature_obj"})

    
    new_temp= await db["state"].find_one({"temperature":"temperature_obj"})

   return new_temp

now = datetime.now()

current_time = now.strftime("%H:%M:%S")
print("Current Time =", current_time)

@app.get("/api/state")



