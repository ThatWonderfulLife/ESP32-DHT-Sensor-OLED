#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <AsyncTCP.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);

Adafruit_SSD1306 display(-1);

AsyncWebServer server(80);

const char* ssid = "yourSSID";
const char* password = "yourPassword";

String readDHTTemp(){
  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println("Falha no sensor! -> Temperatura");
    return "null";
  }
  else {
    Serial.println(t);
    return String(t);
  }
};

String readDHTHum(){
  float h = dht.readHumidity();

  if (isnan(h)) {
    Serial.println("Falha no sensor! -> Humidade");
    return "null";
  }
  else {
    Serial.println(h);
    return String(h);
  }
};

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>DHT 22 Async Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#b71919;"></i> 
    <span class="dht-labels">Temp:</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color: lightskyblue;"></i> 
    <span class="dht-labels">Humid:</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 2000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 2000 ) ;
</script>
</html>)rawliteral";

String process(const String& var){
  Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemp();
  }
  else if(var == "HUMIDITY"){
    return readDHTHum();
  }
  return String();
}

void displaySetup(){
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.display();

}

void displayLoop(){
  delay(250);
  float readData = dht.computeHeatIndex();
  float hu = dht.readHumidity();
  float temp = dht.readTemperature();

  display.clearDisplay();
  display.setCursor(0,20);

  display.print(F("Humidade: "));
  display.print(hu);
  display.print("\nTemperatura: ");
  display.print(temp);
  display.print("°C ");
  delay(500);
  display.display();
}

void setup(){

  Serial.begin(115200);

  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a rede...");
  displaySetup();
  }

  Serial.println(WiFi.localIP());
   //Rotas
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, process);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemp().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHum().c_str());
  });

 
  server.begin();
}


void loop(){
  displayLoop();
}