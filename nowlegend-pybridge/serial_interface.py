import json
import logging 

import serial


SERIAL_PORT = "/dev/ttyUSB0"
BAUDRATE = 115200


class SerialInterface:
    def __init__(self, seiral_port, baudrate):
        self.__serial = serial.Serial(seiral_port, baudrate)
        self.__receive_data_callback = None
        self.__logger = logging.getLogger("pybridge")
    
    def set_receive_callback(self, callback):
        self.__receive_data_callback = callback
        
        
    async def read_serial(self):
        self.__logger.info("Start serial reading coroutine")
        while 1:
            try:
                data = self.__serial.read_until(b"\n").decode()
                if data[0] == "R":
                    data = data[1:]
                    json_data = json.loads(data)
                    await self.__receive_data_callback(json_data)
            except Exception as e:
                self.__logger.warning(f"Error reading serial : {e}")
                
    
    async def write_data(self, data : bytes):
        self.__serial.write(data)
        pass
