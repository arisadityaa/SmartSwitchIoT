#include "variabels.h"
#include "pins.h"
#include "wifiConfig.h"
#include "ntpTimes.h"
#include "firebaseDatabases.h"

void setup() {
  Serial.begin(115200);
  initPin();
  initWifi();
  initTime();
  initFirebase();
  initFirstVirtualState();
}

void loop() {
  if (digitalRead(pSaklar) != tmpSaklar) {
    tmpSaklar = !tmpSaklar;
    saklarState = !saklarState;
    digitalWrite(lampu, saklarState);
    Serial.println("State Lamp Changes");
  }

  if (millis() > saklarMillis + 5000) {
    getVirtualSwitchState();
    saklarMillis = millis();
  }
  if (millis() > timeMillis + 10000) {
    timeMillis = millis();
    getTimeNTP();
  }

  if(millis()> setMillisSaklar + 5000){
    setSaklarState();
    setMillisSaklar = millis();
  }

  if(millis()> setMillisAlarm + 10000){
    getAlarmTime();
    setMillisAlarm = millis();
  }

  if(millis() > getAlarmState + 10000){
    if(alarmType != 0){
      if(HourMunite.equals(timeSetAlarm)){
        saklarState = alarmType == 1 ? false : true;
        digitalWrite(lampu, saklarState);
        timeSetAlarm = "";
        setAlarmTimeOff();
      }
    }
    getAlarmState = millis();
  }
  
}
