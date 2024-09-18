from wespdisp import *
import datetime
import time

d = wDisplay("192.168.0.108")
d.setSize(2)

while True:
    ctime = datetime.datetime.now()
    ftime = ctime.strftime("%H:%M:%S")
    d.clear()
    d.setCursor(0, 16)
    d.println(ftime)
    d.update()