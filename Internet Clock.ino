#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "LedControl.h"

const char *ssid     = "RUDRAKSHA";
const char *password = "9043309074";

const long utcOffsetInSeconds = 3600;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// 7 Segment 
LedControl lc= LedControl(D7,D4,D5,1);

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();


//7 Segment Code

  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  
}

void updateClock(){
  
  
}
void loop() {
  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours()+ 4);
  Serial.print(":");
  Serial.print(timeClient.getMinutes() + 30);
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());

//  Write Hours to 7-Segment
  if((timeClient.getHours() + 4) <= 24){
      lc.setDigit(0,6,(timeClient.getHours() + 4)%10,false);
      lc.setDigit(0,7,((timeClient.getHours() + 4)/10)%10,false);
  }

  else{
    lc.setDigit(0,6,(29 - timeClient.getHours())%10,false);
     lc.setDigit(0,7,((29 - timeClient.getHours())/10)%10,false);
  }


//  Write Minutes to 7-Segment

  if((timeClient.getMinutes()+ 30) <= 60){
      lc.setDigit(0,4,(timeClient.getMinutes()+ 30)%10,false);
      lc.setDigit(0,5,((timeClient.getMinutes() + 30)/10)%10,false);
  }

  else{
    lc.setDigit(0,4,(90 - timeClient.getMinutes())%10,false);
    lc.setDigit(0,5,((90 - timeClient.getMinutes())/10)%10,false);
  }


//  Write Minutes to 7-Segment
  lc.setDigit(0,2,(timeClient.getSeconds())%10,false);
  lc.setDigit(0,3,(timeClient.getSeconds()/10)%10,false);

  delay(1000);

}
