#include <NTPClient.h>
#include <WiFiUdp.h>

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void initTime(){
  timeClient.begin();
  timeClient.setTimeOffset(28800); //3600 each GMT +1
  timeClient.update();
}

void getTimeNTP(){
  timeClient.update();
  currentHour = timeClient.getHours();
  currentMinute = timeClient.getMinutes();
  HourMunite = String(currentHour) + ":" + String(currentMinute);
  Serial.println(HourMunite);
}
