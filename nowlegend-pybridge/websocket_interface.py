import logging
import asyncio

from websockets.client import connect


SERVER_URI = "ws://localhost:2225"


class WebsocketInterface:
    def __init__(self):
        self.__receive_message_callback = None
        self.__logger = logging.getLogger("pybridge")
        
    async def connect(self):
        self.__server : connect = await connect(SERVER_URI)
        self.__logger.info(f"Wbsocket connection opened : {self.__server.open}")
        #await self.write_websocket("je suis trop fort !! \n")

    async def read_websocket(self):
        self.__logger.info("Start websocket reading coroutine")
        while 1:
            data = await self.__server.recv()
            await self.__receive_message_callback(data)

    async def write_websocket(self, data : str):
        await self.__server.send(data)

    def set_receive_callback(self, callback):
        self.__receive_message_callback = callback

    
    

        