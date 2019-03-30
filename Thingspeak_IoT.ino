#include <DHT.h>  
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>  

#define DHTPIN 4 
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
  
const char* ssid = "duinoelektronik";  //masukan nama WiFi
const char* password = "usbasp88";   //paswwor wifi
WiFiClient client;  
unsigned long myChannelNumber = 744671;  //chanel ID
const char * myWriteAPIKey = "MON36XO3EKRY6BIK";  //Wtite

uint8_t temperature, humidity;  

#define buzzer 12
#define led1 13
#define led2 14
void setup()  
{  
  Serial.begin(115200);  
  dht.begin();
  pinMode (buzzer, OUTPUT);
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);

  delay(10);
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");
   digitalWrite(led1, HIGH);
   delay(500);  
   digitalWrite(led1, LOW);
  }  
  Serial.println("");  
  Serial.println("WiFi connected");
  digitalWrite(led2, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
}  
void loop()   
{  
  static boolean data_state = false;  
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();  
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write to field 1.  
  if( data_state )  
  {  
   ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);  
   data_state = false;  
  }  
  else  
  {  
   ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);  
   data_state = true;  
  }  
  delay(30000); // ThingSpeak will only accept updates every 15 seconds.  
}
