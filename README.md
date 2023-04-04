# ESP32-DHT-Sensor-OLED
A Simple display of temperature and humidity using a DHT22 Sensor and an Esp32 Dev Module.

Made using the Arduino IDE and C++, the project monitors the current temperature and Humidity of the room/ambient, it has an OLED display installed for easy to see information.
The Updated version has a Async Web Server that is easy to customize and setup, only requiring a network to connect to.
Next iterations will have a self hosting network for those who dont want to use it in conjunction with their main network.

Attention! The default IP for acess can change based on your network!

# ESP32 Pin Out and DHT22 Setup for Reference
For this project i am using Pin #4 (D4/GPIO4) for the DHT Sensor and Pin #5(D5/GPIO5) for the Relay Module.
<br>
<p>
<img alt= "ESP32-PinOut" src = "https://www.mischianti.org/wp-content/uploads/2020/11/ESP32-DOIT-DEV-KIT-v1-pinout-mischianti.png" /> 
</p>
<br>
<p>
<img alt= "DHT22-PinOut" src = "https://esp32io.com/images/tutorial/esp32-dht22-temperature-humudity-module-wiring-diagram.jpg" /> 
</p>
<br>
<p>
<img alt= "Application" src = "img/Application.jpg" /> 
</p>
<br>
<p>
<img alt= "WebServer Implementation" src = "img/WebServerExample.jfif" /> 
</p>
For the next part, you will need a Relay Module, the manufacturer does not matter as long as it has 3 pin outputs.
I found a simple pinout for reference, so feel free to follow the print bellow.
NOTE: Its not recommended but you should be able to use the "VIN" Pin in the Esp32 board to get 5V power out of it.
<p>
<br>
<img alt = "SingleRelayPinOut" src = img/SingleRelayPinOut.png />

# Known Issues  
  
The DHT Sensor can fail reading higher temperatures (Over 50 degrees Celcius).
<br>
The Relay Button does not appear on the webpage as shown above.
<br>
<img alt = "NoButtonInScreen" src = img/NoButtonInScreen.png />

