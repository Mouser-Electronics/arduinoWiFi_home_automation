#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>


const char THING_ID[] = "b7ecec84-a1ec-49ba-982e-25ac5b78b50d";

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)

void onColoredLightChange();
void onBedroomTvChange();

CloudColoredLight coloredLight;
CloudMotionSensor motionSensor;
CloudTelevision bedroomTv;
CloudTemperature roomTemperature;

void initProperties(){

  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(coloredLight, READWRITE, ON_CHANGE, onColoredLightChange);
  ArduinoCloud.addProperty(motionSensor, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(bedroomTv, READWRITE, ON_CHANGE, onBedroomTvChange);
  ArduinoCloud.addProperty(roomTemperature, READ, ON_CHANGE, NULL, 1.000000);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
