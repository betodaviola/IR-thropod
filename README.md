# IR-thropod
Phone controled IR-Blaster using an ESP8266. 

This was my first project using Arduino and my first time using HTML/CSS. Some lines of this code are probably useless, but were kept either because I didn't know what I was doing, or because I wanted to leave them in the code for future reference (such as the ones related to the HOSTNAME). 

My next steps on this project will be:
1. Review my code after I learn more about coding for Arduino and HTML (which I currently started studying in a more systematic manner).
2. Adding a receiver, to make it easier to reverse-engineer the IR code from future controlers.
3. Add a Plex button.
4. Make it more aestethically pleasing somehow and solder everything in a way that I can still replace the LED in case it burns.

If you are just copying this code, remember to properly fill out the information regarding your own wifi on lines 22 and 23:
```
const char* kSsid = "*****";
const char* kPassword = "*****";
```


For anyone trying to attempt this, more important than my code are the tutorials I followed to achieve the final results:
- Ravi Singh's [How to make a DIY IR Blaster using ESP8266](https://techposts.org/make-diy-ir-blaster-esp8266-nodemcu/): This is the most important tutorial used on this project. Stil, I was very unhappy with the solution of using http shortcuts to control things.
- [ESP32/ESP8266 Web Server: Control Outputs with Momentary Switch](https://randomnerdtutorials.com/esp32-esp8266-web-server-outputs-momentary-switch/), by Random Nerd Tutorials: this short exercise/tutorial helped me to grasp the proccess of creating a button that could be used in place of the links that are in the screen when you access the webserver in the first tutorial
- techtutorialsx's [ESP8266 HTTP server: Serving HTML, Javascript and CSS](https://techtutorialsx.com/2016/10/15/esp8266-http-server-serving-html-javascript-and-css/#google_vignette): this tutorial helped me understand better what I was doing with the Arduino code, and finally helped me style it the way I wanted

This is how my webserver looked after everything was done:
![Screenshot of my IR-blaster webserver](/images/IR-thropod_server.png)
