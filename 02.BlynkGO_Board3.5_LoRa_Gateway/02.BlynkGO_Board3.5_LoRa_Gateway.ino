#include <BlynkGOv2.h>
#include "src/LoRaNow.h"

#define LORA_SCK        18 
#define LORA_MISO       19
#define LORA_MOSI       23
#define LORA_SS         5
#define LORA_RST        21
#define LORA_DIO0       22
#define LORA_FREQUENCY  433E6 //     //433E6 - Asia, 866E6 - Europe, 915E6 - North America

GLabel label;

void setup(){
  Serial.begin(115200); Serial.println();
  BlynkGO.begin();

  label.font(prasanmit_40);
    
  LoRaNow.setPinsSPI(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS, LORA_DIO0); 
  LoRaNow.setFrequency(LORA_FREQUENCY);
  if (!LoRaNow.begin()) {
    Serial.println("[LoRaNow] init failed. Check your connections.");
  }
  LoRaNow.onMessage([](uint8_t* data, size_t len){
    uint32_t id     = LoRaNow.id();
    byte     count  = LoRaNow.count();
    char buf[len+1];
    memcpy(buf, data, len); buf[len]= 0;
    
    Serial.print("Node Id: ");
    Serial.println(id, HEX);
    Serial.print("Count: ");
    Serial.println(count);
    Serial.print("Message: ");
    Serial.print(buf);
    Serial.println();
    Serial.println();

    label = buf;
  });
  
  LoRaNow.gateway();
  
}

void loop(){
  BlynkGO.update();
  LoRaNow.loop();
}
