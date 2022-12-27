# ESP32-DHT-Sensor-OLED
A Simple display of temperature and humidity using a DHT22 Sensor and a Esp32 Dev Module.

Made using the Arduino IDE in C, the project gets the current temperature and Humidity of the room/ambience it is installed and displays it on a OLED Display.
In future iterations i'll try implementing a webserver to show the information on an HTTPS page and integrate MQTT to send the information daily to a computer/server for analysis and control over temperature under isolated enviroments.

# ESP32 Pin Out and DHT22 Setup for Reference
For this project i am using Pin #4 (D4/GPIO4)
<p>
<img alt= "ESP32-PinOut" src = "https://www.mischianti.org/wp-content/uploads/2020/11/ESP32-DOIT-DEV-KIT-v1-pinout-mischianti.png" /> 
</p>
<p>
<img alt= "DHT22-PinOut" src = "https://esp32io.com/images/tutorial/esp32-dht22-temperature-humudity-module-wiring-diagram.jpg" /> 
</p>
