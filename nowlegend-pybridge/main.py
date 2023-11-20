#!/usr/bin/env python
import logging
import asyncio
import json

from serial_interface import SerialInterface, SERIAL_PORT, BAUDRATE
from websocket_interface import WebsocketInterface


serial_itf : SerialInterface = None
websocket_itf : WebsocketInterface = None

def _init_logger():
    logger = logging.getLogger("pybridge")
    logger.setLevel(logging.INFO)

    formatter = logging.Formatter('[%(asctime)s] [%(name)s] [%(levelname)s] : %(message)s')
    ch = logging.StreamHandler()
    ch.setLevel(logging.INFO)
    ch.setFormatter(formatter)

    logger.addHandler(ch)

async def _serial_receive_callback(json_data):
    global websocket_itf
    await websocket_itf.write_websocket(json.dumps(json_data))

async def _websocket_receive_callback(data : str):
    global serial_itf
    data = "R" + data + "\n"
    await serial_itf.write_data(data.encode())

async def main():
    global serial_itf
    global websocket_itf

    _init_logger()
    logger = logging.getLogger("pybridge")
    logger.info("Start of the program")

    serial_itf = SerialInterface(SERIAL_PORT, BAUDRATE)
    serial_itf.set_receive_callback(_serial_receive_callback)

    websocket_itf = WebsocketInterface()
    websocket_itf.set_receive_callback(_websocket_receive_callback)
    await websocket_itf.connect()
    
    await asyncio.gather(websocket_itf.read_websocket(), serial_itf.read_serial())

if __name__ == "__main__":
    asyncio.run(main())
    