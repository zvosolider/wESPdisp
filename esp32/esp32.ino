#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <WiFi.h>
#include <WebServer.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1

const char* ssid = ""; // !!! SET UP THIS BEFORE COMPILING !!!
const char* pass = "";

String ip = "";
uint16_t curColor = SSD1306_WHITE;
bool inverted = false;
WebServer server(80);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void index();
void clear();
void println();
void print();
void setCursor();
void setSize();
void update();
void setColor();
void drawPixel();
void drawLine();
void drawRect();
void drawFilledRect();
void drawRoundRect();
void drawFilledRoundRect();
void drawCircle();
void drawFilledCircle();
void drawTriangle();
void drawFilledTriangle();
void invert();

void setup()
{
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  if (pass == "") {
    WiFi.begin(ssid);
  } else {
    WiFi.begin(ssid, pass);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.println("pliz weit ima cannecting");
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  ip = WiFi.localIP().toString();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(WiFi.localIP());
  display.setCursor(0, 16);
  display.println("waiting for new request...");
  display.display();

  server.on("/println", println);
  server.on("/print", print);
  server.on("/clear", clear);
  server.on("/setCursor", setCursor);
  server.on("/setSize", setSize);
  server.on("/update", update);
  server.on("/setColor", setColor);
  server.on("/drawPixel", drawPixel);
  server.on("/drawLine", drawLine);
  server.on("/drawRect", drawRect);
  server.on("/drawFilledRect", drawFilledRect);
  server.on("/drawRoundRect", drawRoundRect);
  server.on("/drawFilledRoundRect", drawFilledRoundRect);
  server.on("/drawCircle", drawCircle);
  server.on("/drawFilledCircle", drawFilledCircle);
  server.on("/invert", invert);
  server.on("/drawTriangle", drawTriangle);
  server.on("/", ind);
  server.begin();
}

void loop() {
  server.handleClient();
}

void ind() {
  server.send(200, "text/plain", "display " + ip + " is ready");
}

void clear() {
  if (server.method() == HTTP_POST) {
    display.clearDisplay();
    server.send(200, "text/plain", "OK");
  } else {
    server.send(404, "text/plain", "404");
  }
}

void println() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("text")) {
      String text = server.arg("text");

      display.println(text);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void print() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("text")) {
      String text = server.arg("text");

      display.print(text);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void setCursor() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x") && server.hasArg("y")) {
      int x, y;
      x = server.arg("x").toInt();
      y = server.arg("y").toInt();

      display.setCursor(x, y);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void setSize() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("size")) {
      int size = server.arg("size").toInt();

      display.setTextSize(size);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void update() {
  if (server.method() == HTTP_POST) {
    display.display();
    server.send(200, "text/plain", "OK");
  } else {
    server.send(404, "text/plain", "404");
  }
}

void invert() {
  if (server.method() == HTTP_POST) {
    inverted = !inverted;
    display.invertDisplay(inverted);
    server.send(200, "text/plain", "OK");
  } else {
    server.send(404, "text/plain", "404");
  }
}

void setColor() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("color")) {
      String color = server.arg("color");
      color.toLowerCase();
      if (color == "white") {
        display.setTextColor(SSD1306_WHITE);
        curColor = SSD1306_WHITE;
        server.send(200, "text/plain", "OK");
      } else if (color == "black") {
        display.setTextColor(SSD1306_BLACK);
        curColor = SSD1306_BLACK;
        server.send(200, "text/plain", "OK");
      }
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void drawPixel() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x") && server.hasArg("y")) {
      int x, y;
      x = server.arg("x").toInt();
      y = server.arg("y").toInt();
      
      display.drawPixel(x, y, SSD1306_WHITE);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void drawLine() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x0") && server.hasArg("y0") && server.hasArg("x1") && server.hasArg("y1")) {
      int x0, y0, x1, y1;
      x0 = server.arg("x0").toInt();
      y0 = server.arg("y0").toInt();
      x1 = server.arg("x1").toInt();
      y1 = server.arg("y1").toInt();
      
      display.drawLine(x0, y0, x1, y1, curColor);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void drawRect() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x") && server.hasArg("y") && server.hasArg("width") && server.hasArg("height")) {
      int x, y, width, height;
      x = server.arg("x").toInt();
      y = server.arg("y").toInt();
      width = server.arg("width").toInt();
      height = server.arg("height").toInt();
      
      display.drawRect(x, y, width, height, curColor);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void drawFilledRect() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x") && server.hasArg("y") && server.hasArg("width") && server.hasArg("height")) {
      int x, y, width, height;
      x = server.arg("x").toInt();
      y = server.arg("y").toInt();
      width = server.arg("width").toInt();
      height = server.arg("height").toInt();
      
      display.fillRect(x, y, width, height, curColor);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void drawRoundRect() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x") && server.hasArg("y") && server.hasArg("width") && server.hasArg("height") && server.hasArg("radius")) {
      int x, y, width, height, radius;
      x = server.arg("x").toInt();
      y = server.arg("y").toInt();
      width = server.arg("width").toInt();
      height = server.arg("height").toInt();
      radius = server.arg("radius").toInt();
      
      display.drawRoundRect(x, y, width, height, radius, curColor);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void drawFilledRoundRect() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x") && server.hasArg("y") && server.hasArg("width") && server.hasArg("height") && server.hasArg("radius")) {
      int x, y, width, height, radius;
      x = server.arg("x").toInt();
      y = server.arg("y").toInt();
      width = server.arg("width").toInt();
      height = server.arg("height").toInt();
      radius = server.arg("radius").toInt();
      
      display.fillRoundRect(x, y, width, height, radius, curColor);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void drawCircle() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x") && server.hasArg("y") && server.hasArg("radius")) {
      int x, y, radius;
      x = server.arg("x").toInt();
      y = server.arg("y").toInt();
      radius = server.arg("radius").toInt();
      
      display.drawCircle(x, y, radius, curColor);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void drawFilledCircle() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x") && server.hasArg("y") && server.hasArg("radius")) {
      int x, y, radius;
      x = server.arg("x").toInt();
      y = server.arg("y").toInt();
      radius = server.arg("radius").toInt();
      
      display.fillCircle(x, y, radius, curColor);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void drawTriangle() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x0") && server.hasArg("y0") && server.hasArg("x1") && server.hasArg("y1") && server.hasArg("x2") && server.hasArg("y2")) {
      int x0, y0, x1, y1, x2, y2;
      x0 = server.arg("x0").toInt();
      y0 = server.arg("y0").toInt();
      x1 = server.arg("x1").toInt();
      y1 = server.arg("y1").toInt();
      x2 = server.arg("x2").toInt();
      y2 = server.arg("y2").toInt();
      
      display.drawTriangle(x0, y0, x1, y1, x2, y2, curColor);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}

void drawFilledTriangle() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("x0") && server.hasArg("y0") && server.hasArg("x1") && server.hasArg("y1") && server.hasArg("x2") && server.hasArg("y2")) {
      int x0, y0, x1, y1, x2, y2;
      x0 = server.arg("x0").toInt();
      y0 = server.arg("y0").toInt();
      x1 = server.arg("x1").toInt();
      y1 = server.arg("y1").toInt();
      x2 = server.arg("x2").toInt();
      y2 = server.arg("y2").toInt();
      
      display.fillTriangle(x0, y0, x1, y1, x2, y2, curColor);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(404, "text/plain", "404");
    }
  } else {
    server.send(404, "text/plain", "404");
  }
}