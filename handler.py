import ctypes as caccess

def handle(x:list) -> None:
    lib=caccess.CDLL("lib/sfpm.so")
    command=x
