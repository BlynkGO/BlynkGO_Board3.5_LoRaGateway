#include "BlynkGO_DuinoLoRa.h"

#define LORA_FREQUENCY  433E6 //     //433E6 - Asia, 866E6 - Europe, 915E6 - North America

GTimerDuino lora_timer;
uint32_t counter;

void setup(){
  Serial.begin(115200); Serial.println();
  Serial.println("[LoRaNow] Simple Node");

  LoRaNow.setFrequency(LORA_FREQUENCY);
  if (!LoRaNow.begin()) {
    Serial.println("[LoRaNow] init failed. Check your connections.");
    while (true);
  }

  // เมื่อมีการส่ง Message เข้ามา
  LoRaNow.onMessage([](uint8_t *data, size_t len){
    char buf[len+1];
    memcpy(buf, data, len); buf[len]= 0;
    
    Serial.print("[LoRaNow] Receive Message: ");
    Serial.println(buf);
    Serial.println();
  });
  
  LoRaNow.onSleep([](){
    Serial.println("[LoRaNow] Sleep");
  });

  LoRaNow.showStatus(Serial);
  
  // ตั้งเวลาทุกๆ 5000ms ทำการส่งข้อมูลออกไป
  lora_timer.setInterval(5000,[](){
    // จัดข้อมูลที่จะส่ง
    String data = String("Hello ") + String(counter++);

    // ส่งข้อมูลไปทาง LoRa
    LoRaNow.print(data);
    LoRaNow.send();
    Serial.println( String("[Sender] ") + data);
  });

}

void loop(){
  LoRaNow.loop();
  lora_timer.run();
}
