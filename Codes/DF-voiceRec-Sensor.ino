//=======================================================================================================//
// Projet Tutorial       - Getting started with DFRobot Voice Recognition Sensor 
// Author                - https://www.hackster.io/maheshyadav216
// Hardware              - SKU_SEN0539-EN_Gravity_Voice_Recognition_Module, Arduino Uno, 5v Relay Board 
// Softare               - Arduino IDE 1
// GitHub Repo of Projet - https://github.com/maheshyadav216/DFRobot-Offline-Voice-Recognition-Sensor
// Code last Modified on - 19/09/2023
//=======================================================================================================//
#include "DFRobot_DF2301Q.h"    // DFRobot Voice Recognition sensor library

// Connected appliances Pin definitions
#define Light 8
#define fan 9
#define ac 10
#define buzzer 11

//I2C communication
DFRobot_DF2301Q_I2C asr;

void setup() {
  Serial.begin(115200);

// Please note that my Relay module follows Active Low logic
  pinMode(Led, OUTPUT);    //Init LIGHT pin to output mode
  digitalWrite(Led, HIGH);  //Set LIGHT pin to low initially

  pinMode(fan, OUTPUT);    //Init Fan pin to output mode
  digitalWrite(fan, HIGH);  //Set Fan pin to low 

  pinMode(ac, OUTPUT);    //Init AC pin to output mode
  digitalWrite(ac, HIGH);  //Set AC pin to low 

  pinMode(buzzer, OUTPUT);    //Init Buzzer pin to output mode
  digitalWrite(buzzer, HIGH);  //Set Buzzer pin to low 

  // Init the sensor
  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * @brief Set voice volume
   * @param voc - Volume value(1~7)
   */
  asr.setVolume(7);

  /**
     @brief Set mute mode
     @param mode - Mute mode; set value 1: mute, 0: unmute
  */
  asr.setMuteMode(0);

  /**
     @brief Set wake-up duration
     @param wakeTime - Wake-up duration (0-255)
  */
  asr.setWakeTime(20);

  /**
     @brief Get wake-up duration
     @return The currently-set wake-up period
  */
  uint8_t wakeTime = 0;
  wakeTime = asr.getWakeTime();
  Serial.print("wakeTime = ");
  Serial.println(wakeTime);

  // asr.playByCMDID(1);   // Wake-up command

  /**
     @brief Play the corresponding reply audio according to the ID
     @param CMDID - command word ID
  */
  //asr.playByCMDID(23);  // Command word ID
}

void loop() {
  /**
     @brief Get the ID corresponding to the command word 
     @return Return the obtained command word ID, returning 0 means no valid ID is obtained
  */
  uint8_t CMDID = asr.getCMDID();
  switch (CMDID) {
    case 103:                                                  //If the command is “Turn on the light”
      digitalWrite(Led, LOW);                                 //Turn on the LED (Active low Logic)
      Serial.println("received'Turn on the light',command flag'103'");  //Serial transmits "received"Turn on the light",command flag"103"
      break;

    case 104:                                                  //If the command is “Turn off the light”
      digitalWrite(Led, HIGH);                                  //Turn off the LED
      Serial.println("received'Turn off the light',command flag'104'");  //The serial transmits "received"Turn off the light",command flag"104"
      break;

    case 75:                                                  //If the command is “Turn on the fan”
      digitalWrite(fan, LOW);                                 //Turn on the fan (Active low Logic)
      Serial.println("received'Turn on the fan',command flag'75'");  //Serial transmits "received"Turn on the fan",command flag"75"
      break;

    case 76:                                                  //If the command is “Turn off the fan”
      digitalWrite(fan, HIGH);                                  //Turn off the fan 
      Serial.println("received'Turn off the fan',command flag'76'");  //The serial transmits "received"Turn off the fan",command flag"76"
      break;
      
    case 124:                                                  //If the command is “Turn on the ac”
      digitalWrite(ac, LOW);                                 //Turn on the ac (Active low Logic)
      Serial.println("received'Turn on the ac',command flag'124'");  //Serial transmits "received"Turn on the ac",command flag"124"
      break;

    case 125:                                                  //If the command is “Turn off the ac”
      digitalWrite(ac, HIGH);                                  //Turn off the ac
      Serial.println("received'Turn off the ac',command flag'125'");  //The serial transmits "received"Turn off the ac",command flag"125"
      break;

    case 88:                                                  //If the command is “Turn on the buzzer”
      digitalWrite(buzzer, LOW);                                 //Turn on the buzzer
      Serial.println("received'Turn on the buzzer',command flag'88'");  //Serial transmits "received"Turn on the buzzer",command flag"88"
      break;

    case 89:                                                  //If the command is “Turn off the buzzer”
      digitalWrite(buzzer, HIGH);                                  //Turn off the buzzer
      Serial.println("received'Turn off the buzzer',command flag'89'");  //The serial transmits "received"Turn off the buzzer",command flag"89"
      break;
      
    default:
      if (CMDID != 0) {
        Serial.print("CMDID = ");  //Printing command ID
        Serial.println(CMDID);
      }
  }
  delay(300);
}

//================================================================================================================================================//