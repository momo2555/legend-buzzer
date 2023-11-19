import json
import logging 
import threading
import asyncio

import serial


SERIAL_PORT = "/dev/ttyUSB0"
BAUDRATE = 115200


class SerialInterface:
    def __init__(self, seiral_port, baudrate):
        self.__serial = serial.Serial(seiral_port, baudrate)
        self.__receive_data_callback = None
        self.__logger = logging.getLogger("pybridge")
        self.__queue = asyncio.Queue()
        self.__loop = asyncio.get_event_loop()
    
    def set_receive_callback(self, callback):
        self.__receive_data_callback = callback

    def read_thread(self):
        self.__logger.info("Start serial reading thread")
        while True:
            try:
                data = self.__serial.read_until(b"\n").decode()
                if len(data) > 0 and data[0] == "R":
                    data = data[1:]
                    json_data = json.loads(data)
                    asyncio.run_coroutine_threadsafe(self.__queue.put(json_data), self.__loop)
            except Exception as e:
                self.__logger.warning(f"Error reading serial : {e}")
    
    async def read_serial(self):
        read_thread = threading.Thread(target=self.read_thread)
        read_thread.daemon = True
        read_thread.start()

        self.__logger.info("Start serial reading coroutine")
        while True:
            data = await self.__queue.get()
            await self.__receive_data_callback(data)

    async def write_data(self, data : bytes):
        self.__serial.write(data)
