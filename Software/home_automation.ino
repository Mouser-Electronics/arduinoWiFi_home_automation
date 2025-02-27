#include "arduino_secrets.h"
/* 
  Sketch generated by the Arduino IoT Cloud Thing "home_automation"
  https://create.arduino.cc/cloud/things/b7ecec84-a1ec-49ba-982e-25ac5b78b50d 

  Arduino IoT Cloud Properties description

  The following variables are automatically generated and updated when changes are made to the Thing properties

  CloudColoredLight coloredLight;
  CloudMotionSensor motionSensor;
  CloudTelevision bedroomTv;
  CloudTemperature roomTemperature;

  Properties which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"

/* RGB LED */
#define PIN_Red 4
#define PIN_Blue 2
#define PIN_Green 3
/***********/

/* Temperature sensor */
#include <OneWire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
/***********************/

/* TV remote controller */
#include <IRremote.h>
IRsend irsend;
bool first;

int prevChannel;
int prevVolume;
bool prevSwitch;
bool prevMute;

#define RAW_DATA_LEN 67
unsigned int onoff[RAW_DATA_LEN]={4600,4600, 600,1700, 550,1700, 600,1700, 600,550, 650,500, 550,550, 600,600, 650,450, 600,1700, 600,1700, 550,1700, 600,550, 600,550, 600,550, 600,550, 600,550, 550,600, 550,1700, 600,550, 600,550, 600,550, 600,550, 550,600, 550,550, 600,1700, 600,550, 600,1700, 550,1700, 600,1700, 600,1700, 600,1650, 600,1700, 600};

unsigned int volUp[RAW_DATA_LEN] = {4600,4600, 550,1700, 600,1700, 600,1700, 550,600, 550,550, 600,550, 600,600, 550,600, 550,1700, 550,1750, 550,1700, 600,550, 600,550, 600,550, 550,600, 550,550, 600,1700, 600,1700, 550,1700, 600,600, 550,600, 550,550, 600,550, 600,550, 550,600, 550,550, 600,600, 550,1700, 600,1700, 550,1700, 600,1700, 600,1700, 600};  
unsigned int volDown[RAW_DATA_LEN] = {4600,4600, 550,1700, 600,1700, 600,1700, 550,600, 550,600, 550,600, 550,550, 600,550, 600,1700, 550,1700, 600,1750, 550,550, 600,550, 550,600, 550,550, 600,550, 600,1700, 600,1700, 550,600, 550,1700, 600,550, 600,550, 600,550, 600,550, 650,500, 550,550, 600,1700, 600,550, 600,1700, 550,1700, 600,1700, 600,1700, 550};

unsigned int chanUp[RAW_DATA_LEN] = {4650,4550, 600,1700, 600,1700, 550,1700, 600,550, 600,550, 600,550, 600,550, 600,550, 550,1700, 600,1700, 600,1700, 550,550, 600,550, 600,550, 600,550, 600,550, 600,550, 600,1650, 600,550, 600,550, 600,1700, 600,550, 600,550, 550,550, 600,1700, 600,550, 600,1700, 550,1700, 600,550, 600,1700, 600,1700, 550,1700, 600}; 
unsigned int chanDown[RAW_DATA_LEN] = {4600,4600, 650,1650, 550,1700, 600,1750, 550,550, 600,550, 600,550, 550,550, 700,500, 550,1700, 600,1700, 650,1600, 600,550, 600,550, 600,550, 600,550, 600,550, 550,550, 600,550, 700,450, 700,450, 650,1650, 550,600, 550,600, 550,550, 600,1700, 650,1650, 550,1700, 700,1600, 650,500, 600,1700, 550,1700, 600,1700, 650};

unsigned int mute[RAW_DATA_LEN] = {4650,4600, 550,1700, 600,1700, 600,1700, 550,550, 600,550, 600,550, 600,550, 600,550, 600,1700, 550,1700, 600,1700, 600,550, 600,550, 600,550, 550,550, 600,550, 600,1700, 600,1700, 550,1700, 600,1700, 600,550, 600,550, 600,550, 550,550, 600,550, 600,550, 600,550, 600,550, 600,1700, 550,1700, 600,1700, 600,1700, 550};


unsigned int chan[3][RAW_DATA_LEN]={
  {4650,4550, 600,1700, 600,1700, 550,1700, 600,550, 600,550, 600,550, 600,550, 600,550, 550,1700, 600,1700, 600,1700, 550,600, 550,550, 600,550, 600,550, 600,550, 600,550, 600,550, 550,1700, 600,550, 600,550, 600,550, 600,550, 600,550, 550,1700, 600,1700, 600,550, 600,1700, 550,1700, 600,1700, 600,1700, 550,1700, 600},
  {4750,4450, 600,1700, 600,1700, 600,1650, 600,550, 600,550, 600,550, 600,550, 600,550, 550,1700, 600,1700, 600,1700, 600,550, 550,600, 550,550, 600,550, 600,550, 600,1700, 600,550, 550,1700, 600,600, 550,550, 600,550, 600,550, 550,600, 550,550, 600,1700, 600,550, 600,1700, 550,1700, 600,1700, 600,1700, 550,1700, 600},
  {4600,4600, 550,1700, 600,1700, 600,1700, 550,550, 600,550, 600,550, 600,550, 600,550, 600,1700, 550,1700, 600,1700, 600,550, 650,500, 550,600, 550,550, 600,550, 600,550, 600,1700, 600,1650, 600,550, 600,550, 700,450, 600,550, 600,550, 550,1700, 600,550, 600,550, 600,1700, 600,1700, 550,1700, 600,1700, 600,1700, 550}
  
};
/******************************/

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  delay(5000);
  ArduinoCloud.printDebugInfo();
  
  // temperature sensor begin
  sensors.begin();

  first = true;

  pinMode(1, INPUT);

}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  
  sensors.requestTemperatures(); // Send the command to get temperature readings 

  roomTemperature=sensors.getTempCByIndex(0); 
  
  /*motion detection*/
  if(digitalRead(1)== HIGH)  // 
  {
   motionSensor = true; //PIR sensor pin
   Serial.print("motion ");
   Serial.println(motionSensor);
  } 
  else{
    
    motionSensor = false;
  }
}


void sendIR(unsigned int rawData[]) {
  digitalWrite(LED_BUILTIN, HIGH);
  irsend.sendRaw(rawData,RAW_DATA_LEN,38);
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
}


void onBedroomTvChange() {
  Serial.println("==================");
  Serial.println("Switch:"+String(bedroomTv.getSwitch()));
  Serial.println("Volume:"+String(bedroomTv.getVolume()));
  Serial.println("Channel:"+String(bedroomTv.getChannel()));
  Serial.println("Mute:"+String(bedroomTv.getMute()));
  Serial.println("==================");
  
   if (first){
      prevSwitch = bedroomTv.getSwitch();
      prevVolume = bedroomTv.getVolume();
      prevChannel = bedroomTv.getChannel();
      prevMute = bedroomTv.getMute();
      first = false;
      return;
  } 
  
    // On Off changed
  if (bedroomTv.getSwitch() != prevSwitch) {
      prevSwitch = bedroomTv.getSwitch();
      if (bedroomTv.getSwitch()) {
        sendIR(chan[1]);
        Serial.println("chan1");  
      } else {
        sendIR(onoff);
        Serial.println("onoff");
      }
      Serial.println("Switch changed:"+String(bedroomTv.getSwitch()));
    }
    
    // Volume changed
  if (bedroomTv.getVolume() > prevVolume) {
    bedroomTv.setMute(false);
    prevMute = false;
    for (int k = prevVolume + 1 ; k<=bedroomTv.getVolume(); k++) {
      sendIR(volUp);
      Serial.println("Volume requested:"+String(bedroomTv.getVolume())+" Set:"+String(k));  
    }
    prevVolume = bedroomTv.getVolume();
  }
  else if (bedroomTv.getVolume() < prevVolume) {
    bedroomTv.setMute(false);
    prevMute = false;
    for (int k = prevVolume - 1; k>=bedroomTv.getVolume(); k--) {
      sendIR(volDown);
      Serial.println("Volume changed:"+String(bedroomTv.getVolume())+" Set:"+String(k));  
    }
    prevVolume = bedroomTv.getVolume();
  }
  
  // Mute changed
  if (bedroomTv.getMute() != prevMute && bedroomTv.getMute()) {
    prevMute = bedroomTv.getMute();
    sendIR(mute);
    Serial.println("Mute changed:"+String(bedroomTv.getMute()));
  }
  else if (bedroomTv.getMute() != prevMute && !bedroomTv.getMute()) {
    prevMute = bedroomTv.getMute();
    sendIR(mute);
    Serial.println("Mute changed:"+String(bedroomTv.getMute()));
  }
  
  // Channel changed
  if (bedroomTv.getChannel() != prevChannel) {
    int newChannel = bedroomTv.getChannel();
    if (newChannel > 0 && newChannel < 10) {
      sendIR(chan[newChannel-1]);
    } else if (newChannel > 9) {
      if (newChannel > prevChannel) {
        for (int ch = prevChannel; ch < newChannel; ch++) {
          sendIR(chanUp);
          Serial.println("Chan requested:"+String(newChannel)+" Set:"+String(ch));  
        }  
      } else if (newChannel < prevChannel) {
          for (int ch = prevChannel; ch > newChannel; ch--) {
            sendIR(chanDown);
            Serial.println("Chan requested:"+String(newChannel)+" Set:"+String(ch));  
          }
      }
    }
    prevChannel = newChannel;
    Serial.println("Channel changed:"+String(bedroomTv.getChannel()));
  }
  

}




void onColoredLightChange() {
  // Do something
  
  uint8_t r, g, b;
  coloredLight.getValue().getRGB(r, g, b);
    if (coloredLight.getSwitch()) {
     Serial.println("R:"+String(r)+" G:"+String(g)+ " B:"+String(b));
     analogWrite(PIN_Red, 255-r);
     analogWrite(PIN_Blue, 255-b);
     analogWrite(PIN_Green, 255-g);
   }
   else{
      Serial.println("Lamp Off");
      analogWrite(PIN_Red, 255);
      analogWrite(PIN_Blue, 255);
      analogWrite(PIN_Green, 255);
   }
}



