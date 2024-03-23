#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Your Wi-Fi credentials
char ssid[] = ""; //name of the wifi or network goes here
char pass[] = ""; // password goes here

// Your Blynk authentication token
char auth[] = ""; //copy paste the auth token from above

// Pin connected to the LED
#define LED_PIN 4

int led = 4;
int ds = 21;
int val1;
int IN1 = 26;
int IN2 = 27;
int relay1=18;
BlynkTimer timer;


void myTimerEvent() {            
  Blynk.virtualWrite(V1, val1); 
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(led, OUTPUT);
  pinMode(ds, INPUT);
  timer.setInterval(10, myTimerEvent);  // Call myTimerEvent every 0.01 seconds
  pinMode(IN1, OUTPUT);//curtain
  pinMode(IN2, OUTPUT);//curtain
  pinMode(relay1, OUTPUT);
}

void loop() {
  val1 = digitalRead(ds);
  if (val1 == HIGH) {
    Blynk.logEvent("dooropened");
    Serial.println("The Door is Open");


    
  } 
  Blynk.run();
  timer.run();  // Run the timer
}

// Blynk virtual pin handler for LED control


BLYNK_WRITE(V0) {
  int ledState = param.asInt();  // Get value from Blynk app (1 for ON, 0 for OFF)

  // Update the physical LED
  digitalWrite(led, ledState);
}

// Blynk virtual pin handler for fan controlled by relay
BLYNK_WRITE(V2) {
  int motorState = param.asInt();  // Get value from Blynk app (1 for ON, 0 for OFF)

  // Update the physical LED
  digitalWrite(relay1, motorState);
}

// Blynk virtual pin handler for curtain open
BLYNK_WRITE(V3) {  // Use V3 for motor control forward
   digitalWrite(IN2, param.asInt());
}

// Blynk virtual pin handler for curtain close
BLYNK_WRITE(V4) {  // Use V3 for motor control backward
   digitalWrite(IN1, param.asInt());
}