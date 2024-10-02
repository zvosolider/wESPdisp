# 🖥 wESPdisplay
> **Name of the library stands for "WiFi ESP display"**

The following folders are located in this repository:
- 📁 **esp32** with .ino file *(you need to set WiFi name and password in it)*
- 📁 **wespdisplay** with python library

📄 There is also a file **example.py** where is the example of using the library

## 📩 Downloading
1. Install **Adafruit GFX** and **Adafruit SSD1306** libraries
2. Compile and upload **esp32.ino** file to your board
3. From **wespdisp** folder run
```sh
pip install .
```
And now you can use your display!

## ✨ Future
Most likely, I will transfer the text scrolling functions and try to add the ability to send.bmp files, or other images
