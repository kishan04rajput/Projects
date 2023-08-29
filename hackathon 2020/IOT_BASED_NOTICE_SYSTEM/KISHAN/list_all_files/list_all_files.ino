#include "FS.h"
 
void setup() {
 
  Serial.begin(115200);
 
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
 
  File file = SPIFFS.open("/test.txt", "w");
 
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }
 
  if (file.print("some content")) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
 
  file.close();
 
  Serial.println("\n\n---BEFORE REMOVING---");
  listAllFiles();
 
  SPIFFS.remove("/test.txt");
 
  Serial.println("\n\n---AFTER REMOVING---");
  listAllFiles();
 
}
 
void loop() {}

void listAllFiles(){
 
  File root = SPIFFS.open("/", "w");
 
  File file = root.openNextFile();
 
  while(file){
 
      Serial.print("FILE: ");
      Serial.println(file.name());
 
      file = root.openNextFile();
  }
 
}
