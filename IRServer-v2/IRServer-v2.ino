/*
 * IR-THROPOD, an IR blaster created in 2024 with the help of the following tutorials:
 * https://techposts.org/make-diy-ir-blaster-esp8266-nodemcu/
 * https://randomnerdtutorials.com/esp32-esp8266-web-server-outputs-momentary-switch/
 * https://techtutorialsx.com/2016/10/15/esp8266-http-server-serving-html-javascript-and-css/#google_vignette
 */
#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#endif  // ESP8266
#if defined(ESP32)
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#endif  // ESP32
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>

const char* kSsid = "*****";
const char* kPassword = "*****";
MDNSResponder mdns;

#if defined(ESP8266)
ESP8266WebServer server(80);
#undef HOSTNAME
#define HOSTNAME "esp8266"
#endif  // ESP8266
#if defined(ESP32)
WebServer server(80);
#undef HOSTNAME
#define HOSTNAME "esp32"
#endif  // ESP32

const uint16_t kIrLed = 4;  // ESP GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

void handleRoot() {
  server.send(200, "text/html",
              "<html>" \
                "<head><title> IR-thropod </title>" \
                "<script src=\"https://kit.fontawesome.com/913023e2fb.js\" crossorigin=\"anonymous\"></script>" \
                "<meta http-equiv=\"Content-Type\"" \
                    "content=\"text/html;charset=utf-8\">" \
                "<meta name=\"viewport\" content=\"width=device-width," \
                    "initial-scale=1.0,minimum-scale=1.0," \
                    "maximum-scale=5.0\">" \
                "</head>" \
                  "<style>" \
                    ".button {" \
                      "background-color: #ffffff;" \
                      "border: 2px solid rgba(27, 31, 35, 0.15);" \
                      "border-radius: 4px;" \
                      "box-shadow: 3px 3px 10px #c91c1c;" \
                      "box-sizing: border-box;" \
                      "color: #a1a1a1;" \
                      "display: inline-block;" \
                      "vertical-align: bottom;" \
                      "text-align: center;" \
                      "width: 50px;" \
                      "height: 50px;" \
                      "font-size: 30px;" \
                      "padding: 8px 1px;" \
                      "margin: 1px 1px 1px 1px;" \
                      "transition: background-color 0.2s cubic-bezier(0.3, 0, 0.5, 1);" \
                      "touch-action: manipulation;" \
                      "touch-action: manipulation;" \
                      "outline: 0;" \
                    "}" \
                    ".button:hover {" \
                      "background-color: #d2d6dd;" \
                      "text-decoration: none;" \
                      "transition-duration: 0.1s;" \
                    "}" \
                    ".button2 {" \
                      "background-color: #f52222;" \
                      "border: 2px solid rgba(27, 31, 35, 0.15);" \
                      "border-radius: 4px;" \
                      "box-shadow: 3px 3px 10px #c91c1c;" \
                      "box-sizing: border-box;" \
                      "color: #a1a1a1;" \
                      "display: inline-block;" \
                      "vertical-align: bottom;" \
                      "text-align: center;" \
                      "padding-top: 4px;" \
                      "width: 50px;" \
                      "height: 50px;" \
                      "font-size: 30px;" \
                      "padding: 8px 1px;" \
                      "margin: 1px 1px 1px 1px;" \
                      "transition: background-color 0.2s cubic-bezier(0.3, 0, 0.5, 1);" \
                      "touch-action: manipulation;" \
                      "touch-action: manipulation;" \
                      "outline: 0;" \
                    "}" \
                    ".button2:hover {" \
                      "background-color: #b04848;" \
                      "text-decoration: none;" \
                      "transition-duration: 0.1s;" \
                    "}" \
                    ".spaceh {" \
                      "background-color: #1acd4100;" \
                      "color: #a1a1a100;" \
                      "display: inline-block;" \
                      "text-align: center;" \
                      "width: 53px;" \
                      "height: 50px;" \
                      "font-size: 34px;" \
                      "padding: 2px 2px;" \
                      "margin: 1px px 1px 1px;" \
                      "transition: background-color 0.2s cubic-bezier(0.3, 0, 0.5, 1);" \
                      "touch-action: manipulation;" \
                    "}" \
                    ".spacev {" \
                      "width: 20px;" \
                      "height: 10px;" \
                      "margin: 1px;" \
                      "display: inline-block;" \
                      "font-size: 1px;" \
                    "}" \
                    "a {" \
                      "text-decoration: none;" \
                    "}" \
                    "#back {" \
                      "background: -webkit-gradient(linear, left, right, from(#000000), to(#505050));" \
                      "background: -webkit-linear-gradient(left, #000000, #505050);" \
                      "background: -moz-linear-gradient(left, #000000, #505050);" \
                      "background: -ms-linear-gradient(left, #000000, #505050);" \
                      "background: -o-linear-gradient(left, #000000, #505050);" \
                      "position: absolute;" \
                      "padding-right: 20px;" \
                      "padding-top: 5px;" \
                      "border-radius: 10px;" \
                    "}" \

                  "</style>" \
                "<body>" \
                  "<h1>Welcome to IR-thropod!</h1>" \
                  "<p>This is our self-hosted remote control</p>" \
                  "<section id=\"back\">" \

                  "<div class=\"spacev\">1</div>" \
                  "<a href=\"ir?code=551489775\" class=\"button2\"><i class=\"fa-solid fa-power-off\"></i></a>" \
                  "<div class=\"spaceh\">1</div><div class=\"spaceh\">1</div>" \
                  "<a href=\"ir?code=551490795\" class=\"button\"><i class=\"fa-solid fa-arrow-rotate-left\"></i></a>" \
                  "<a href=\"ir?code=551538735\" class=\"button\"><i class=\"fa-solid fa-tv\"></i></a>" \

                  "<p><div class=\"spacev\">1</div>" \
                  "<div class=\"spaceh\">1</div><div class=\"spaceh\">1</div><div class=\"spaceh\">1</div>" \
                  "<a href=\"ir?code=551501505\" class=\"button\"><i class=\"fa-solid fa-house\"></i></a>" \
                  "<a href=\"ir?code=551535165\" class=\"button\"><i class=\"fa-solid fa-gear\"></i></a></p>" \

                  "<p><div class=\"spacev\">1</div></p>" \
                  
                  "<p><div class=\"spacev\">1</div>" \
                  "<a href=\"ir?code=149372099\" class=\"button\"><i class=\"fa-solid fa-volume-high\"></i></a>" \
                  "<div class=\"spaceh\">1</div><div class=\"spaceh\">1</div>" \
                  "<a href=\"ir?code=551486205\" class=\"button\"><i class=\"fa-solid fa-circle-up\"></i></a></p>" \

                  "<p><div class=\"spacev\">1</div>" \
                  "<a href=\"ir?code=149402189\" class=\"button\"><i class=\"fa-solid fa-volume-low\"></i></a>" \
                  "<div class=\"spaceh\">1</div> " \
                  "<a href=\"ir?code=551542815\" class=\"button\"><i class=\"fa-solid fa-circle-left\"></i></a>" \
                  "<a href=\"ir?code=551494365\" class=\"button\"><i class=\"fa-solid fa-circle\"></i></a>" \
                  "<a href=\"ir?code=551510175\" class=\"button\"><i class=\"fa-solid fa-circle-right\"></i></a></p>" \

                  "<p><div class=\"spacev\">1</div>" \
                  "<a href=\"ir?code=149410859\" class=\"button\"><i class=\"fa-solid fa-volume-xmark\"></i></a>" \
                  "<div class=\"spaceh\">1</div><div class=\"spaceh\">1</div>" \
                  "<a href=\"ir?code=551518845\" class=\"button\"><i class=\"fa-solid fa-circle-down\"></i></a></p>" \

                  "<p><div class=\"spacev\">1</div></p>" \

                  "<p><div class=\"spacev\">1</div>" \
                  "<a href=\"ir?code=551547150\" class=\"button2\"><i class=\"fa-solid fa-backward\"></i></a>" \
                  "<a href=\"ir?code=551489010\" class=\"button2\"><i class=\"fa-solid fa-play\"></i></a>" \
                  "<a href=\"ir?code=551509410\" class=\"button2\"><i class=\"fa-solid fa-pause\"></i></a>" \
                  "<a href=\"ir?code=551514510\" class=\"button2\"><i class=\"fa-solid fa-forward\"></i></a>" \
                  "<a href=\"ir?code=551521650\" class=\"button2\"><i class=\"fa-solid fa-stop\"></i></a></p> " \

                  "</section>" \
                "</body>" \
              "</html>");
}

void handleIr() {
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "code") {
      uint32_t code = strtoul(server.arg(i).c_str(), NULL, 10);
#if SEND_NEC
      irsend.sendNEC(code, 32);
#endif  // SEND_NEC
    }
  }
  handleRoot();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  irsend.begin();

  Serial.begin(115200);
  WiFi.begin(kSsid, kPassword);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(kSsid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP().toString());

#if defined(ESP8266)
  if (mdns.begin(HOSTNAME, WiFi.localIP())) {
#else  // ESP8266
  if (mdns.begin(HOSTNAME)) {
#endif  // ESP8266
    Serial.println("MDNS responder started");
    // Announce http tcp service on port 80
    mdns.addService("http", "tcp", 80);
  }

  server.on("/", handleRoot);
  server.on("/ir", handleIr);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
#if defined(ESP8266)
  mdns.update();
#endif
  server.handleClient();
}
