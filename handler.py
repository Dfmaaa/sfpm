import ctypes as caccess
import common
import config


def handle(x: list) -> None:
    clib = caccess.CDLL("lib/sfpm.so")
    command = x
    if command[0] == "help" and len(command) == 1:
        print(common.help_msg)
    if command[0] == "list" or command[0]=="group-list":
        src_dic=dict()
        code=common.PKG_LS if command[0]=="list" else common.PKG_GRP
        src_file=open(config.SOURCES)
        sources=src_file.read().split("\n")
        counter=1
        for line in sources:
            kv=line.split(" ")
            if len(kv)!=4:
                print(f"Error in line {counter} of {config.SOURCES}.")
                return
            src_dic.update(kv[0],kv[0:])
            counter=counter+1
        if len(command)==1:
            #passing all sources to package_list()
            for entry in src_dic.keys():
                print(f"Source: {entry}:",end="\n\t")
                clib.package_code(src_dic[entry][0],src_dic[entry][1],code,src_dic[entry][3])
        else:
            #assuming user listed specific sources    
            source_list=command[0:] 
            for entry in source_list:
                print(f"Source: {entry}:",end="\n\t")
                clib.package_code(src_dic[entry][0],src_dic[entry][1],code,src_dic[entry][3])
    
