#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL62GJu7xnU"
#define BLYNK_TEMPLATE_NAME "First project"
#define BLYNK_AUTH_TOKEN "DsRPjxC_3A2Qm_fJT-7ZJvJy_xQJyQ6O"
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Azad's house";  
char pass[] = "Napa625682"; 

int Buzzerpin= D0; 
#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;



BLYNK_WRITE (V1){
  int pinValue = param.asInt();
  //map (variable, fromLow, fromHigh, toLow, toHigh)
  int newValue = map(pinValue, 0, 100,0,255);
  analogWrite(Buzzerpin, newValue);

  Serial.print ("V1 value is: ");
  Serial.println (newValue);
}

BLYNK_WRITE (V2){
  int pinValue = param.asInt();
  if(pinValue ==1)
  analogWrite(Buzzerpin, 255);
  else 
  analogWrite(Buzzerpin, 0);
  Serial.print ("V2 value is: ");
  Serial.println (pinValue);
}

void sendDataToBlynk()
{
  float t= dht.readTemperature();
  float h = dht.readHumidity();

if (isnan(h) || isnan(t))
{
  Serial.println("Failed to read from DHT sensor!");
  return;
}
Blynk.virtualWrite(V3, t);
Blynk.virtualWrite(V4, h);
Serial.print("Temperature data: ");
Serial.println(t);

Serial.print("hum data: ");
Serial.println(h);


}

void setup()
{
  pinMode(Buzzerpin, OUTPUT);
  Serial.begin (115200);
  Blynk.begin (auth, ssid, pass, "blynk.cloud", 80 );
  dht.begin();
  timer.setInterval(3000L, sendDataToBlynk);



}

void loop()
{
  Blynk.run();
  timer.run();
}