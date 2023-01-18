import ctypes as caccess
import common


def handle(x: list) -> None:
    clib = caccess.CDLL("lib/sfpm.so")
    command = x
    if command[0] == "help" and len(command) == 1:
        print(common.help_msg)
    
