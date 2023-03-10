import sys
import os
import handler as core
import common
import config
#This will prevent keyboard interrupt tracebacks.
def suppress_keyboard_interrupt() -> None:
    previous_hook=sys.excepthook
    def dummy_hook(type,value,tbk):
        if type!=KeyboardInterrupt:
            sys.excepthook=previous_hook
        else:
            pass
    sys.excepthook=dummy_hook

if __name__!="__main__":
    print("This module must not be imported. Exiting.")
    sys.exit(1)

suppress_keyboard_interrupt()
check=0;
for x in sys.argv:
    for y in common.commands:
        if x==y:
            check+=1
        if check>1:
            print("More than one command is not allowed at a time.")
            sys.exit(1)

if check==0:
    print(common.help_msg)
    sys.exit(0)
os.chdir(config.WD_D)
core.handle(sys.argv[0:])