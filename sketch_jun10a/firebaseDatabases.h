#include <Firebase_ESP_Client.h>
// Provide the token generation process info.
#include <addons/TokenHelper.h>
// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 2. Define the API Key */
#define API_KEY "AIzaSyAf-29WTZO3Ng0XCvL-Y00HcO5QD9KWGpQ"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://smartswitch-f9381-default-rtdb.asia-southeast1.firebasedatabase.app/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;


void initFirebase() {
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = "smartswitch@gmail.com";
  auth.user.password = "123456";

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);

  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  config.timeout.serverResponse = 10 * 1000;
}

void initFirstVirtualState() {
  if (Firebase.ready()) {
    if (Firebase.RTDB.getBool(&fbdo, "Switch")) {
      virtSaklar = fbdo.to<bool>();
    }
  }
}

void setSaklarState() {
  if (Firebase.ready()) {
    Firebase.RTDB.setBool(&fbdo, F("Lamp"), saklarState);
  }
}

void getVirtualSwitchState() {
  if (Firebase.ready()) {
    if (Firebase.RTDB.getBool(&fbdo, "Switch")) {
      if (fbdo.to<bool>() != virtSaklar) {
        virtSaklar = !virtSaklar;
        saklarState = !saklarState;
        digitalWrite(lampu, saklarState);
        setSaklarState();
        Serial.println("Saklar Virtual Changes");
      }
    } else {
      Serial.println("Error Get Data");
    }
  } else {
    Serial.println("Error Ready");
  }
}

void getAlarmTime() {
  if (Firebase.ready()) {
    if (Firebase.RTDB.getInt(&fbdo, F("Type"))) {
      alarmType = fbdo.to<int>();
      if (alarmType == 0) {
        timeSetAlarm = "";
      } else {
        if (Firebase.RTDB.getString(&fbdo, F("TimeSet"))) {
          timeSetAlarm = fbdo.to<const char *>();
          Serial.println("Alarm " + String(alarmType) + " Set at " + timeSetAlarm);
        }
      }
    }
  }
}

void setAlarmTimeOff(){
  if (Firebase.ready()) {
    Firebase.RTDB.setString(&fbdo, F("TimeSet"), " ");
    Firebase.RTDB.setInt(&fbdo, F("type"), 0);
  }
}
