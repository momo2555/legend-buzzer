#!/usr/bin/env python

import asyncio
from websockets.client import connect


server = None
    
async def connect_to_server():
    global server
    server = await connect("ws://localhost:2225")

async def sending():
    while 1:
        await server.send("wesh la mif")
        await asyncio.sleep(1)

async def receiving():
    while 1: 
        data = await server.recv()
        print(data)

async def main():
    await connect_to_server()
    await asyncio.gather(sending(), receiving())

asyncio.run(main())