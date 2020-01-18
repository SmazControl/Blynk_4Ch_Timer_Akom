/* 4Ch Blynk Timer 
 * esp8266 D3,D4,D5,D6
 *  ArKom Blynk 
 *  https://github.com/SmazControl/Blynk_ARKOM_thaibaanSoft
 * Thai Baan Soft
 * (c) 2020
 * 
 *  Please Beware
 *  =============
 *  D3 will small spark but not effect to Trick relay
 *  D4 will Spark when Upload code
 *  then unplug Vcc form your relay board until upload 
 * 
 *  D1 RX --- TX
 *  D2 TX --- RX
 *  D3 Relay IN1
 *  D4 Relay IN2
 *  D5 Relay IN3
 *  D6 Relay IN4
 *  D7 DHT11
 *  
 */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
SoftwareSerial swSer(D1, D2);  // RX,TX
#include <Adafruit_Sensor.h> // Library Adafruit Unified Sensor
#include <DHT.h> // Library Adafruit DHT
#include <TimeLib.h> // https://github.com/PaulStoffregen/Time
#include <WidgetRTC.h>
BlynkTimer timer;
WidgetRTC rtc;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f2b32463578a4a95811cda91c6487038";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "phloenlom_2.4GHz";
char pass[] = "248248248";

int count = 0;
bool Connected2Blynk = false;

#define DHTPIN D7     // Digital pin connected to the DHT sensor
// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

String D3_Start,D3_Stop,D3_Day,D4_Start,D4_Stop,D4_Day;
String D5_Start,D5_Stop,D5_Day,D6_Start,D6_Stop,D6_Day;
int ledState = LOW;


// Digital clock display of the time
void clockDisplay()
{
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details
  char hh[4],mm[4],ss[4],mm_plus[4];
  sprintf(hh, "%02d", hour());
  sprintf(mm, "%02d", minute());
  sprintf(mm_plus, "%02d", int(minute())-1);
  sprintf(ss, "%02d", second());   
  char dd[4],mo[4],yy[8];
  sprintf(dd, "%02d", day());
  sprintf(mo, "%02d", month());
  sprintf(yy, "%04d", year());   

  String currentTime = String(hh) + ":" + String(mm) + ":" + String(ss);
  String currentTime_plus = String(hh) + ":" + String(mm_plus) + ":" + String(ss);
  String currentDate = String(dd) + "-" + String(mo) + "-" + String(yy);
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();
  Serial.print("Current time plus: ");
  Serial.println(currentTime_plus);
  if(D3_Day.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D3_Start && currentTime<D3_Stop) {
      Blynk.virtualWrite(V13, 1);
      Serial.println("Run D3");
    } else {
      if(currentTime>D3_Start && currentTime_plus<D3_Stop) {
        Blynk.virtualWrite(V13, 0);      
      }
      pinMode(D3,LOW);
    }
  } else {
    pinMode(D3,LOW);
  }
  if(D4_Day.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D4_Start && currentTime<D4_Stop) {
      Blynk.virtualWrite(V14, 1);
      Serial.println("Run D4");
    } else {
      if(currentTime>D4_Start && currentTime_plus<D4_Stop) {
        Blynk.virtualWrite(V14, 0);      
      }
      pinMode(D4,LOW);
    }
  } else {
    pinMode(D4,LOW);
  }
  if(D5_Day.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D5_Start && currentTime<D5_Stop) {
      Blynk.virtualWrite(V15, 1);
      Serial.println("Run D5");
    } else {
      if(currentTime>D5_Start && currentTime_plus<D5_Stop) {
        Blynk.virtualWrite(V15, 0);      
      }
      pinMode(D5,LOW);
    }
  } else {
    pinMode(D5,LOW);
  }
  if(D6_Day.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D6_Start && currentTime<D6_Stop) {
      Blynk.virtualWrite(V16, 1);
      Serial.println("Run D6");
    } else {
      if(currentTime>D6_Start && currentTime_plus<D6_Stop) {
        Blynk.virtualWrite(V16, 0);      
      }
      pinMode(D6,LOW);
    }
  } else {
    pinMode(D6,LOW);
  }
  // Send time to the App
  Blynk.virtualWrite(V1, currentTime);
  // Send date to the App
  Blynk.virtualWrite(V2, currentDate);
}
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
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D3_Start = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D3 Start: ") + D3_Start);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D3_Stop = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D3 Stop : ") + D3_Stop);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D3_Day="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D3_Day+="1";
    } else {
      D3_Day+="0";
    }
  }  
  Serial.println(String("D3 Day ") + D3_Day);
}

BLYNK_WRITE(V4)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D4_Start = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D4 Start: ") + D4_Start);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D4_Stop = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D4 Stop : ") + D4_Stop);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D4_Day="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D4_Day+="1";
    } else {
      D4_Day+="0";
    }
  }  
  Serial.println(String("D4 Day ") + D4_Day);
}

BLYNK_WRITE(V5)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D5_Start = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D5 Start: ") + D5_Start);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D5_Stop = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D5 Stop : ") + D5_Stop);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D5_Day="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D5_Day+="1";
    } else {
      D5_Day+="0";
    }
  }  
  Serial.println(String("D5 Day ") + D5_Day);
}

BLYNK_WRITE(V6)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D6_Start = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D6 Start: ") + D6_Start);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D6_Stop = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D6 Stop : ") + D6_Stop);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D6_Day="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D6_Day+="1";
    } else {
      D6_Day+="0";
    }
  }  
  Serial.println(String("D6 Day ") + D6_Day);
}

// When App button is pushed - switch the state
BLYNK_WRITE(V13) {
  ledState = param.asInt();
  digitalWrite(D3, ledState);
  Serial.println("D3 "+String(ledState));
}
BLYNK_WRITE(V14) {
  ledState = param.asInt();
  digitalWrite(D4, ledState);
  Serial.println("D4 "+String(ledState));
}
BLYNK_WRITE(V15) {
  ledState = param.asInt();
  digitalWrite(D5, ledState);
  Serial.println("D5 "+String(ledState));
}
BLYNK_WRITE(V16) {
  ledState = param.asInt();
  digitalWrite(D6, ledState);
  Serial.println("D6 "+String(ledState));
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
  // Begin synchronizing time
  rtc.begin();
  // Display digital clock every 10 seconds
  timer.setInterval(10000L, clockDisplay);  
  timer.setInterval(4000L, CheckConnection); // check if still connected every 11 seconds 
}

void loop()
{
  if(Connected2Blynk){
    Blynk.run();
  }
  timer.run();
}
  
