from wespdisp import wDisplay
import time

d = wDisplay("192.168.0.109", port=80, debug=True)
d.setup(x=0, y=0, size=1) # checking display availability, clearing display, setting font size and text position
d.println("test") # printing something
d.setCursor(0, 16) # setting cursor position
d.println("BIG TEST", 2) # setting size with print function (also works with print)
for i in range(10):
    d.print(".", 1) # printing dot for 10 times
    time.sleep(0.5)
d.clear() # clearing display
d.setCursor(0, 0) # setting cursor position again
d.println("end of test", 1) # printing final message

#removegcc14