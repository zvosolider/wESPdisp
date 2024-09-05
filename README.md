# 🖥 wESPdisplay
> **name of the library stands for "WiFi ESP display"**

the following folders are located in this repository:
- 📁 **esp32** with .ino file *(you need to set WiFi name and password in it)*
- 📁 **wespdisplay** with python library

📄 there is also a file **example.py** where is the example of using the library

## 📩  downloading
1. install **Adafruit GFX** and **Adafruit SSD1306** libraries
2. compile and upload **esp32.ino** file to your board
3. from **wespdisp** folder run
```sh
pip install .
```
and now you can use your display!

## ✨ future
most likely, I will transfer the text scrolling functions and try to add the ability to send.bmp files, or other images