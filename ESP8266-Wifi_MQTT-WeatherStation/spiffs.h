#include "FS.h"

const char* ssid;
const char* password;

//--------------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------------
bool loadConfig() {
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  DynamicJsonBuffer configBuffer;
  JsonObject& jsonConfig = configBuffer.parseObject(buf.get());

  if (!jsonConfig.success()) {
    Serial.println("Failed to parse config file");
    return false;
  }

  ssid     = jsonConfig["SSID"];
  password = jsonConfig["PASSWORD"];

  return true;
}
