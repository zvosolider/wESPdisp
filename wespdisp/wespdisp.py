import requests

class CustomError(Exception):
    def __init__(self, message):
        self.message = message

    def __str__(self):
        return f"{self.message}"

class wDisplay:
    def __init__(self, ip:str, port:int=80, debug:bool=False):
        self.url = f"http://{ip}:{port}"
        self.debug = debug
        self.port = port
        self.ip = ip

    def setup(self, x:int=0, y:int=0, size:int=1):
        if self.debug: print(f"connecting to {self.ip}")
        req = requests.get(url=f"{self.url}")
        if req.text == f"display {self.ip} is ready" and self.debug:
            print(f"display {self.ip} is ready")
        self.clear()
        self.setCursor(x, y)
        self.setSize(size)

    def println(self, text:str, size:int=-1):
        if size > -1:
            self.setSize(size)
        data = { "text": text }
        req = requests.post(url=f"{self.url}/println", data=data)
        if self.debug and req.status_code == 200: print(f"printed {text}")

    def print(self, text:str, size:int=-1):
        if size > -1:
            self.setSize(size)
        data = { "text": text }
        req = requests.post(url=f"{self.url}/print", data=data)
        if self.debug and req.status_code == 200: print(f"printed {text}")

    def clear(self):
        req = requests.post(url=f"{self.url}/clear")
        if self.debug and req.status_code == 200: print("cleared")

    def setCursor(self, x:int=0, y:int=0):
        data = { "x": str(x), "y": str(y) }
        req = requests.post(url=f"{self.url}/setCursor", data=data)
        if self.debug and req.status_code == 200: print(f"cursor set to {x},{y}")
    
    def setSize(self, size:int):
        data = { "size": str(size) }
        req = requests.post(url=f"{self.url}/setSize", data=data)
        if self.debug and req.status_code == 200: print(f"font size set to {size}")