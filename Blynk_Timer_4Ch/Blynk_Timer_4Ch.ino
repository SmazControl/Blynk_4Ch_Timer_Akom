/* 4Ch Blynk Timer 
 * esp8266 D1,D2,D5,D6
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
 *  D1 Relay IN1
 *  D2 Relay IN2
 *  D3 RX --- TX
 *  D4 TX --- RX
 *  D5 Relay IN3
 *  D6 Relay IN4
 *  D7 Relay Pump
 *  10 DHT11      (SD3)
 *  
 */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
SoftwareSerial swSer(D3, D4);  // RX,TX
#include <EEPROM.h>
#include <Adafruit_Sensor.h> // Library Adafruit Unified Sensor
#include <DHT.h> // Library Adafruit DHT
#include <TimeLib.h> // https://github.com/PaulStoffregen/Time
#include <WidgetRTC.h>
BlynkTimer timer;
WidgetRTC rtc;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = ".......Your.Blynk.Token.........";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourWiFiSSID";
char pass[] = "YourPassword";

int count = 0;
bool Connected2Blynk = false;
WidgetLED led99(V99);

#define DHTPIN 10     // Digital pin connected to the DHT sensor
// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

String D1_Start1,D1_Stop1,D1_Day1,D2_Start1,D2_Stop1,D2_Day1;
String D5_Start1,D5_Stop1,D5_Day1,D6_Start1,D6_Stop1,D6_Day1;
String D1_Start2,D1_Stop2,D1_Day2,D2_Start2,D2_Stop2,D2_Day2;
String D5_Start2,D5_Stop2,D5_Day2,D6_Start2,D6_Stop2,D6_Day2;
int ledState = LOW;


// Digital clock display of the time
void clockDisplay()
{
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details
  char hh[4],mm[4],ss[4],mm_minus[4];
  sprintf(hh, "%02d", hour());
  sprintf(mm, "%02d", minute());
  sprintf(mm_minus, "%02d", int(minute())-1);
  sprintf(ss, "%02d", second());   
  char dd[4],mo[4],yy[8];
  sprintf(dd, "%02d", day());
  sprintf(mo, "%02d", month());
  sprintf(yy, "%04d", year());   

  String currentTime = String(hh) + ":" + String(mm) + ":" + String(ss);
  String currentTime_minus = String(hh) + ":" + String(mm_minus) + ":" + String(ss);
  String currentDate = String(dd) + "-" + String(mo) + "-" + String(yy);
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();
  Serial.print("Current time minus: ");
  Serial.println(currentTime_minus);
  if(D1_Day1.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D1_Start1 && currentTime_minus<D1_Start1 && currentTime<D1_Stop1) {
      Blynk.virtualWrite(V81, 1);
      Serial.println("Run D1");
      digitalWrite(D1,LOW);
      digitalWrite(D7,LOW); 
      led99.on();    
    } else {
      if(currentTime>D1_Stop1 && currentTime_minus<D1_Stop1) {
        Blynk.virtualWrite(V81, 0);      
        digitalWrite(D1,HIGH);
        digitalWrite(D7,HIGH);      
        led99.off();    
      }
    }
  }
  if(D2_Day1.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D1_Start1 && currentTime_minus<D2_Start1 && currentTime<D2_Stop1) {
      Blynk.virtualWrite(V82, 1);
      Serial.println("Run D2");
      digitalWrite(D2,LOW);
      digitalWrite(D7,LOW);
      led99.on();          
    } else {
      if(currentTime>D2_Stop1 && currentTime_minus<D2_Stop1) {
        Blynk.virtualWrite(V82, 0);      
        digitalWrite(D2,HIGH);
        digitalWrite(D7,HIGH);
        led99.off();    
      }
    }
  }
  if(D5_Day1.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D5_Start1 && currentTime_minus<D5_Start1 && currentTime<D5_Stop1) {
      Blynk.virtualWrite(V85, 1);
      Serial.println("Run D5");
      digitalWrite(D5,LOW);
      digitalWrite(D7,LOW);
      led99.on();    
    } else {
      if(currentTime>D5_Stop1 && currentTime_minus<D5_Stop1) {
        Blynk.virtualWrite(V85, 0);      
        digitalWrite(D5,HIGH);
        digitalWrite(D7,HIGH);
        led99.off();    
      }
    }
  }
  if(D6_Day1.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D6_Start1 && currentTime_minus<D6_Start1 && currentTime<D6_Stop1) {
      Blynk.virtualWrite(V86, 1);
      Serial.println("Run D6");
      digitalWrite(D6,LOW);
      digitalWrite(D7,LOW);
      led99.on();    
    } else {
      if(currentTime>D6_Stop1 && currentTime_minus<D6_Stop1) {
        Blynk.virtualWrite(V86, 0);      
        digitalWrite(D6,HIGH);
        digitalWrite(D7,HIGH);
        led99.off();    
      }
    }
  }
  if(D1_Day2.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D1_Start2 && currentTime_minus<D1_Start2 && currentTime<D1_Stop2) {
      Blynk.virtualWrite(V81, 1);
      Serial.println("Run D1");
      digitalWrite(D1,LOW);
      digitalWrite(D7,LOW);
      led99.on();    
    } else {
      if(currentTime>D1_Stop2 && currentTime_minus<D1_Stop2) {
        Blynk.virtualWrite(V81, 0);      
        digitalWrite(D1,HIGH);
        digitalWrite(D7,HIGH);
        led99.off();    
      }
    }
  }
  if(D2_Day2.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D2_Start2 && currentTime_minus<D2_Start2 && currentTime<D2_Stop2) {
      Blynk.virtualWrite(V82, 1);
      Serial.println("Run D2");
      digitalWrite(D2,LOW);
      digitalWrite(D7,LOW);
      led99.on();    
    } else {
      if(currentTime>D2_Stop2 && currentTime_minus<D2_Stop2) {
        Blynk.virtualWrite(V82, 0);      
        digitalWrite(D2,HIGH);
        digitalWrite(D7,HIGH);
        led99.off();    
      }
    }
  }
  if(D5_Day2.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D5_Start2 && currentTime_minus<D5_Start2 && currentTime<D5_Stop2) {
      Blynk.virtualWrite(V85, 1);
      Serial.println("Run D5");
      digitalWrite(D5,LOW);
      digitalWrite(D7,LOW);
      led99.on();    
    } else {
      if(currentTime>D5_Stop2 && currentTime_minus<D5_Stop2) {
        Blynk.virtualWrite(V85, 0);      
        digitalWrite(D5,HIGH);
        digitalWrite(D7,HIGH);
        led99.off();    
      }
    }
  }
  if(D6_Day2.substring(weekday()-1,weekday())=="1") {
    if(currentTime>D6_Start2 && currentTime_minus<D6_Start2 && currentTime<D6_Stop2) {
      Blynk.virtualWrite(V86, 1);
      Serial.println("Run D6");
      digitalWrite(D6,LOW);
      digitalWrite(D7,LOW);
      led99.on();    
    } else {
      if(currentTime>D6_Stop2 && currentTime_minus<D6_Stop2) {
        Blynk.virtualWrite(V86, 0);      
        digitalWrite(D6,HIGH);
        digitalWrite(D7,HIGH);
        led99.off();    
      }
    }
  }  
  // Send time to the App
  Blynk.virtualWrite(V97, currentTime);
  // Send date to the App
  Blynk.virtualWrite(V98, currentDate);
}
// This function sends Arduino's up time every second to Virtual Pin (0).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
float LastT = 0;
float LastH = 0;

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
    if(LastT==0) {
      LastT = newT;
    } else {
      if(LastT>newT*1.2 || LastT<newT*0.8) {
        newT = LastT;
      } else {
        LastT = newT;
      }
    }
    // You can send any value at any time.
    // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V90, newT);
    Serial.println(newT);
  }  

  // Read Humidity
  float newH = dht.readHumidity();
  // if humidity read failed, don't change h value 
  if (isnan(newH)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else {
    if(LastH==0) {
      LastH = newH;
    } else {
      if(LastH>newH*1.2 || LastH<newH*0.8) {
        newH = LastH;
      } else {
        LastH = newH;
      }
    }
    // You can send any value at any time.
    // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V91, newH);
    Serial.println(newH);
  }
}

BLYNK_WRITE(V11)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D1_Start1 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D1 Start1: ") + D1_Start1);
    write_String(100,D1_Start1);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D1_Stop1 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D1 Stop1 : ") + D1_Stop1);
    write_String(150,D1_Stop1);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D1_Day1="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D1_Day1+="1";
    } else {
      D1_Day1+="0";
    }
  }  
  Serial.println(String("D3 Day1 ") + D1_Day1);
  write_String(200,D1_Day1);
}

BLYNK_WRITE(V12)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D2_Start1 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D2 Start1: ") + D2_Start1);
    write_String(250,D2_Start1);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D2_Stop1 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D2 Stop1 : ") + D2_Stop1);
    write_String(300,D2_Stop1);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D2_Day1="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D2_Day1+="1";
    } else {
      D2_Day1+="0";
    }
  }  
  Serial.println(String("D2 Day1 ") + D2_Day1);
  write_String(350,D2_Day1);
}

BLYNK_WRITE(V15)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D5_Start1 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D5 Start1: ") + D5_Start1);
    write_String(400,D5_Start1);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D5_Stop1 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D5 Stop1 : ") + D5_Stop1);
    write_String(450,D5_Stop1);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D5_Day1="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D5_Day1+="1";
    } else {
      D5_Day1+="0";
    }
  }  
  Serial.println(String("D5 Day1 ") + D5_Day1);
  write_String(500,D5_Day1);
}

BLYNK_WRITE(V16)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D6_Start1 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D6 Start1: ") + D6_Start1);
    write_String(550,D6_Start1);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D6_Stop1 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D6 Stop1 : ") + D6_Stop1);
    write_String(600,D6_Stop1);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D6_Day1="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D6_Day1+="1";
    } else {
      D6_Day1+="0";
    }
  }  
  Serial.println(String("D6 Day1 ") + D6_Day1);
  write_String(650,D6_Day1);
}

BLYNK_WRITE(V21)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D1_Start2 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D1 Start2: ") + D1_Start2);
    write_String(700,D1_Start2);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D1_Stop2 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D1 Stop2 : ") + D1_Stop2);
    write_String(750,D1_Stop2);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D1_Day2="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D1_Day2+="1";
    } else {
      D1_Day2+="0";
    }
  }  
  Serial.println(String("D3 Day2 ") + D1_Day2);
  write_String(800,D1_Day2);
}

BLYNK_WRITE(V22)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D2_Start2 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D2 Start2: ") + D2_Start2);
    write_String(850,D2_Start2);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D2_Stop2 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D2 Stop2 : ") + D2_Stop2);
    write_String(900,D2_Stop2);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D2_Day2="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D2_Day2+="1";
    } else {
      D2_Day2+="0";
    }
  }  
  Serial.println(String("D2 Day2 ") + D2_Day2);
  write_String(950,D2_Day2);
}

BLYNK_WRITE(V25)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D5_Start2 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D5 Start2: ") + D5_Start2);
    write_String(1000,D5_Start2);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D5_Stop2 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D5 Stop2 : ") + D5_Stop2);
    write_String(1050,D5_Stop2);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D5_Day2="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D5_Day2+="1";
    } else {
      D5_Day2+="0";
    }
  }  
  Serial.println(String("D5 Day2 ") + D5_Day2);
  write_String(1100,D5_Day2);
}

BLYNK_WRITE(V26)
{
  TimeInputParam t(param);
  // Process start time
  if (t.hasStartTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStartHour());
    sprintf(mm, "%02d", t.getStartMinute());
    sprintf(ss, "%02d", t.getStartSecond());   
    D6_Start2 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("1D6 Start: ") + D6_Start2);
    write_String(1150,D6_Start2);
  }
  if (t.hasStopTime())
  {
    char hh[4],mm[4],ss[4];
    sprintf(hh, "%02d", t.getStopHour());
    sprintf(mm, "%02d", t.getStopMinute());
    sprintf(ss, "%02d", t.getStopSecond());   
    D6_Stop2 = String(hh)+":"+String(mm)+":"+String(ss);
    Serial.println(String("D6 Stop2 : ") + D6_Stop2);
    write_String(1200,D6_Stop2);
  }
  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  D6_Day2="";
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      D6_Day2+="1";
    } else {
      D6_Day2+="0";
    }
  }  
  Serial.println(String("D6 Day2 ") + D6_Day2);
  write_String(1250,D6_Day2);
}


// When App button is pushed - switch the state
BLYNK_WRITE(V81) {
  ledState = param.asInt();
  digitalWrite(D1, ledState);
  if(ledState==0) {
    digitalWrite(D7, HIGH);
    led99.off();    
  } else {
    digitalWrite(D7, LOW);
    led99.on();    
  }
  Serial.println("D1 "+String(ledState));
}
BLYNK_WRITE(V82) {
  ledState = param.asInt();
  digitalWrite(D2, ledState);
  if(ledState==0) {
    digitalWrite(D7, HIGH);
    led99.off();    
  } else {
    digitalWrite(D7, LOW);
    led99.on();    
  }
  Serial.println("D2 "+String(ledState));
}
BLYNK_WRITE(V85) {
  ledState = param.asInt();
  digitalWrite(D5, ledState);
  if(ledState==0) {
    digitalWrite(D7, HIGH);
    led99.off();    
  } else {
    digitalWrite(D7, LOW);
    led99.on();    
  }
  Serial.println("D5 "+String(ledState));
}
BLYNK_WRITE(V86) {
  ledState = param.asInt();
  digitalWrite(D6, ledState);
  if(ledState==0) {
    digitalWrite(D7, HIGH);
    led99.off();    
  } else {
    digitalWrite(D7, LOW);
    led99.on();    
  }
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
      count = 0;
      myTimerEvent();     
    }  
  }
}

void write_String(int add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}

String read_String(int add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<100)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  delay(5000);
  EEPROM.begin(4096);
  D1_Start1 = read_String(100);
  Serial.println(D1_Start1);
  D1_Stop1 = read_String(150);
  Serial.println(D1_Stop1);
  D1_Day1 = read_String(200);
  Serial.println(D1_Day1);
  D2_Start1 = read_String(250);
  Serial.println(D2_Start1);
  D2_Stop1 = read_String(300);
  Serial.println(D2_Stop1);
  D2_Day1 = read_String(350);
  Serial.println(D2_Day1);
  D5_Start1 = read_String(400);
  Serial.println(D5_Start1);
  D5_Stop1 = read_String(450);
  Serial.println(D5_Stop1);
  D5_Day1 = read_String(500);
  Serial.println(D5_Day1);
  D6_Start1 = read_String(550);
  Serial.println(D6_Start1);
  D6_Stop1 = read_String(600);
  Serial.println(D6_Stop1);
  D6_Day1 = read_String(650);
  Serial.println(D6_Day1);
  D1_Start2 = read_String(700);
  Serial.println(D1_Start2);
  D1_Stop2 = read_String(750);
  Serial.println(D1_Stop2);
  D1_Day2 = read_String(800);
  Serial.println(D1_Day2);
  D2_Start2 = read_String(850);
  Serial.println(D2_Start2);
  D2_Stop2 = read_String(900);
  Serial.println(D2_Stop2);
  D2_Day2 = read_String(950);
  Serial.println(D2_Day2);
  D5_Start2 = read_String(1000);
  Serial.println(D5_Start2);
  D5_Stop2 = read_String(1050);
  Serial.println(D5_Stop2);
  D5_Day2 = read_String(1100);
  Serial.println(D5_Day2);
  D6_Start2 = read_String(1150);
  Serial.println(D6_Start2);
  D6_Stop2 = read_String(1200);
  Serial.println(D6_Stop2);
  D6_Day2 = read_String(1250);
  Serial.println(D6_Day2);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,HIGH);
  WiFiConnect();
  Blynk.config(auth);  // in place of Blynk.begin(auth, ssid, pass);
  Blynk.connect(3333);  // timeout set to 10 seconds and then continue without Blynk
  while (Blynk.connect() == false) {
    // Wait until connected
  }
  Serial.println("Connected to Blynk server");
  // Begin synchronizing time
  led99.off();    
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
  
