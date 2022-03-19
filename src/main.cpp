#include <ESP8266WiFi.h>
#include "creds.cpp"
int port = 12511;  
WiFiServer server(port);
const char *ssid = SSID;  
const char *password = PASSWORD;  
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(U8G2_R0,D1, D2, D3, D4,D5);  

char* zuluTime = "zuluTime";
char* localTime = "localTime";
char* localDate = "localDate";

String dataBuffer = "";
void setup(void) {
  zuluTime = "--:-- ";
  localTime = "--:--";
  localDate = "xxxx-xx-xx";
  u8g2.begin();
  u8g2.setFontRefHeightExtendedText();
  u8g2.setFontPosTop();
   Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Connect to wifi
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);
}
void drawTimeDate() 
{
  u8g2.clearBuffer();				
  u8g2.setFont(u8g_font_6x10);
  u8g2.drawStr( 25, 20, "LOCAL");
  u8g2.drawLine( 70, 16, 70, 64);
  u8g2.drawLine( 14, 16, 140, 16);
  u8g2.drawStr( 88, 20, "ZULU");
  u8g2.drawStr(40, 5, localDate);
  u8g2.setFont(u8g2_font_fub11_tr);
  u8g2.drawStr( 20, 30, localTime);
  u8g2.drawStr( 80, 30, zuluTime);
  u8g2.sendBuffer();		
}
void decodeString(String data){
  int starCounter = 0;
  String id = "";
  String valueType = "";
  String value = "";
  for(int i = 0; i < data.length(); i++){
    
    if(data[i]=='*'){
      
      starCounter++;
      
    }else{
      if(starCounter ==0){
       id+=data[i]; 
      }else if(starCounter ==1){
       valueType+=data[i]; 
      }else  if(starCounter ==2){
       value+=data[i]; 
      }
    }
  }

  if(starCounter == 2){
    switch (id.toInt())
    {
    case 0:
       value.toCharArray(zuluTime,value.length()+1);
      break;
    
    case 1:
      value.toCharArray(localTime,value.length()+1);
      break;
      
    case 2:
      value.toCharArray(localDate,value.length()+1);
      break;
    default:
      break;
    }
    drawTimeDate();
  }

}
void loop(void) {
  WiFiClient client = server.available();
  drawTimeDate();
  if (client) {
    if(client.connected())
    {
      Serial.println("Client Connected");
    }
    
    while(client.connected()){      
      while(client.available()>0){

        dataBuffer = client.readStringUntil(';');
        Serial.print(dataBuffer);
        decodeString(dataBuffer);
        client.write("0");
      }
      //Send Data to connected client
      while(Serial.available()>0)
      {
        client.write(Serial.read());
      }

     
    }
    client.stop();
    Serial.println("Client disconnected");    
  }
  
  delay(1000);  
}

