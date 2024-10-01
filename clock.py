from wespdisp import * # another example of this library using
import subprocess
import datetime
import time

d = wDisplay("192.168.0.9", debug=True)
d.setSize(3)

while True:
    ctime = datetime.datetime.now()
    ftime = ctime.strftime("%H:%M")
    d.clear()
    d.setCursor(0, 16)
    d.print(ftime, 3)
    d.print("MCK", 2)
    d.setCursor(0, 40)
    result = subprocess.check_output(['playerctl', 'metadata', 'title']).decode().strip()
    d.println(result, 1)
    result = subprocess.check_output(['playerctl', 'metadata', 'artist']).decode().strip().replace("и", "&")
    d.println(result, 1)
    d.update()
    time.sleep(1)
