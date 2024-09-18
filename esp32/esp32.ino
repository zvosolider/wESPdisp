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

WebServer server(80);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void index();
void clear();
void println();
void print();
void setCursor();
void setSize();
void update();

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