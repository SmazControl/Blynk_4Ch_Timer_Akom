/* 4Ch Blynk Timer 
 * esp8266 D3,D4,D5,D6
 *  ArKom Blynk 
 *  https://github.com/SmazControl/Blynk_ARKOM_thaibaanSoft
 * Thai Baan Soft
 * (c) 2020
 */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
SoftwareSerial swSer(D5, D6);  // RX,TX
#include <Adafruit_Sensor.h> // Library Adafruit Unified Sensor
#include <DHT.h> // Library Adafruit DHT

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

BlynkTimer timer;
int count = 0;
bool Connected2Blynk = false;

#define DHTPIN D1     // Digital pin connected to the DHT sensor
// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

// This function sends Arduino's up time every second to Virtual Pin (0).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // Read temperature as Celsius (the default)
  float newT = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float newT = dht.readTemperature(true);
  // if temperature read failed, don't change t value
  if (isnan(newT)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else {
    Blynk.virtualWrite(V0, newT);
    Serial.println(newT);
  }  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, newT);
  Serial.println(newT);

  // Read Humidity
  float newH = dht.readHumidity();
  // if humidity read failed, don't change h value 
  if (isnan(newH)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else {
    // You can send any value at any time.
    // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V1, newH);
    Serial.println(newH);
  }
}

BLYNK_WRITE(V3)
{
  // You'll get HIGH/1 at startTime and LOW/0 at stopTime.
  // this method will be triggered every day
  // until you remove widget or stop project or
  // clean stop/start fields of widget
  if(param.asInt()==1) {
    digitalWrite(D3,HIGH);
  } else {
    digitalWrite(D3,LOW);
  }
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
}

BLYNK_WRITE(V4)
{
  if(param.asInt()==1) {
    digitalWrite(D4,HIGH);
  } else {
    digitalWrite(D4,LOW);
  }
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
}

BLYNK_WRITE(V5)
{
  if(param.asInt()==1) {
    digitalWrite(D5,HIGH);
  } else {
    digitalWrite(D5,LOW);
  }
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
}

BLYNK_WRITE(V6)
{
  if(param.asInt()==1) {
    digitalWrite(D6,HIGH);
  } else {
    digitalWrite(D6,LOW);
  }
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
}

void WiFiConnect()
{
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_STA);
  delay(100);
  WiFi.begin(ssid, pass);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());    
}

void CheckConnection(){
  if (WiFi.status() != WL_CONNECTED) {
    WiFiConnect();
  }
  if (count>5) {
    Serial.println("reset");
    swSer.println("reset");
    count = 0;
    delay(5000);    
  } else {
    Connected2Blynk = Blynk.connected();
    if(!Connected2Blynk){
      count++;
      Serial.println("Not connected to Blynk server"); 
      Blynk.connect(3333);  // timeout set to 10 seconds and then continue without Blynk  
    }
    else{
      myTimerEvent();     
    }  
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  WiFiConnect();
  Blynk.config(auth);  // in place of Blynk.begin(auth, ssid, pass);
  Blynk.connect(3333);  // timeout set to 10 seconds and then continue without Blynk
  while (Blynk.connect() == false) {
    // Wait until connected
  }
  Serial.println("Connected to Blynk server");
  timer.setInterval(4000L, CheckConnection); // check if still connected every 11 seconds 
}

void loop()
{
  if(Connected2Blynk){
    Blynk.run();
  }
  timer.run();
}
