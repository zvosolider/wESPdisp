import requests
import re

class wDisplay:
    def __init__(self, ip:str, port:int=80, debug:bool=False):
        self.url = f"http://{ip}:{port}"
        self.debug = debug
        self.port = port
        self.ip = ip
        self.size = 0


    def setup(self, x:int=0, y:int=0, size:int=1):
        if self.debug: print(f"connecting to {self.ip}")
        req = requests.get(url=f"{self.url}")
        if req.text == f"display {self.ip} is ready" and self.debug:
            print(f"display {self.ip} is ready")
        self.clear()
        self.setCursor(x, y)
        self.setSize(size)
        self.size = size


    def println(self, text:str, size:int=-1):
        if size > -1 and size != self.size:
            self.setSize(size)
        data = { "text": text }
        req = requests.post(url=f"{self.url}/println", data=data)
        if self.debug and req.status_code == 200:
            print(f"printed {text}")


    def print(self, text:str, size:int=-1):
        if size > -1 and size != self.size:
            self.setSize(size)
        data = { "text": text }
        req = requests.post(url=f"{self.url}/print", data=data)
        if self.debug and req.status_code == 200:
            print(f"printed {text}")


    def clear(self):
        req = requests.post(url=f"{self.url}/clear")
        if self.debug and req.status_code == 200:
            print("cleared")

    
    def invert(self):
        req = requests.post(url=f"{self.url}/invert")
        if self.debug and req.status_code == 200:
            print("inverted")


    def setCursor(self, x:int=0, y:int=0):
        data = { "x": str(x), "y": str(y) }
        req = requests.post(url=f"{self.url}/setCursor", data=data)
        if self.debug and req.status_code == 200:
            print(f"cursor set to {x},{y}")
    

    def setSize(self, size:int):
        data = { "size": str(size) }
        req = requests.post(url=f"{self.url}/setSize", data=data)
        self.size = size
        if self.debug and req.status_code == 200:
            print(f"font size set to {size}")


    def upload(self, text:str):
        pattern = r'\(?(\d+)\)?\[?(\d+)?;?(\d+)?\]?:(.+)'
        for line in text.split("\n"):
            match = re.match(pattern, line)
            size = int(match.group(1)) if match.group(1) else None
            x = int(match.group(2)) if match.group(2) else None
            y = int(match.group(3)) if match.group(3) else None
            tx = match.group(4)

            if size: self.setSize(size)
            if x and y: self.setCursor(x, y)
            self.println(tx)


    def setColor(self, color:str="white"): # black or white
        data = { "color": color }
        req = requests.post(url=f"{self.url}/setColor", data=data)
        if self.debug and req.status_code == 200:
            print(f"color set to {color}")
    

    def drawPixel(self, x:int, y:int):
        data = { "x": str(x), "y": str(y) }
        req = requests.post(url=f"{self.url}/drawPixel", data=data)
        if self.debug and req.status_code == 200:
            print(f"drawed pixel at {x},{y}")


    def drawLine(self, x0:int, y0:int, x1:int, y1:int):
        data = { "x0": str(x0), "y0": str(y0), "x1": str(x1), "y1": str(y1) }
        req = requests.post(url=f"{self.url}/drawLine", data=data)
        if self.debug and req.status_code == 200:
            print(f"drawed line from {x0, y0} to {x1, y1}")


    def drawRect(self, x:int, y:int, width:int, height:int):
        data = { "x": str(x), "y": str(y), "width": str(width), "height": str(height) }
        req = requests.post(url=f"{self.url}/drawRect", data=data)
        if self.debug and req.status_code == 200:
            print(f"drawed rect from {x, y}, width: {width}, height: {height}")


    def drawFilledRect(self, x:int, y:int, width:int, height:int):
        data = { "x": str(x), "y": str(y), "width": str(width), "height": str(height) }
        req = requests.post(url=f"{self.url}/drawFilledRect", data=data)
        if self.debug and req.status_code == 200:
            print(f"drawed filled rect from {x, y}, width: {width}, height: {height}")


    def drawRoundRect(self, x:int, y:int, width:int, height:int, radius:int):
        data = { "x": str(x), "y": str(y), "width": str(width), "height": str(height), "radius": str(radius) }
        req = requests.post(url=f"{self.url}/drawRoundRect", data=data)
        if self.debug and req.status_code == 200:
            print(f"drawed filled rect from {x, y}, width: {width}, height: {height}")


    def drawFilledRoundRect(self, x:int, y:int, width:int, height:int, radius:int):
        data = { "x": str(x), "y": str(y), "width": str(width), "height": str(height), "radius": str(radius) }
        req = requests.post(url=f"{self.url}/drawFilledRoundRect", data=data)
        if self.debug and req.status_code == 200:
            print(f"drawed filled round rect from {x, y}, width: {width}, height: {height}")


    def drawCircle(self, x:int, y:int, radius:int):
        data = { "x": str(x), "y": str(y), "radius": str(radius) }
        req = requests.post(url=f"{self.url}/drawCircle", data=data)
        if self.debug and req.status_code == 200:
            print(f"drawed circle in {x, y}, with radius {radius}")


    def drawCircle(self, x:int, y:int, radius:int):
        data = { "x": str(x), "y": str(y), "radius": str(radius) }
        req = requests.post(url=f"{self.url}/drawFilledCircle", data=data)
        if self.debug and req.status_code == 200:
            print(f"drawed filled circle in {x, y}, with radius {radius}")


    def drawTriangle(self, x0:int, y0:int, x1:int, y1:int, x2:int, y2:int):
        data = { "x0": str(x0), "y0": str(y0), "x1": str(x1), "y1": str(y1), "x2": str(x2), "y2": str(y2) }
        req = requests.post(url=f"{self.url}/drawTriangle", data=data)
        if self.debug and req.status_code == 200:
            print(f"drawed triangle with vertexes {x0, y0}, {x1, y1}, {x2, y2}")


    def update(self):
        req = requests.post(url=f"{self.url}/update")
        if self.debug and req.status_code == 200:
            print("updated")