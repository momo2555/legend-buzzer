#include <Arduino.h>
#include <WiFi.h>
#include <request.h>
#include <memory>
#include <legend.h>

std::unique_ptr<Legend> legend {};


#ifdef TEST
void setup() {

  legend = std::make_unique<Legend>(Legend());
  legend->run();

}

void loop() {
  if (legend->isReady()) {
    delay(5000);
    // create a new request
    Logger::log("FRAME 1 ---");
    Request request {};
    request.asData();
    request.setData<int>("test", 45);
    request.setData<float>("test2", 45.5);
    request.setData<bool>("test3", false);
    request.setReceiver(Entity::MONITOR, {});
    request.setSender(Entity::DEVICE, MacAddress("AD:AD:AD:AD:AD:AD"));
    Logger::log(request.toString());

    /*Logger::log("FRAME 2 ---");
    Request request2 {std::string("{\"header\":{\"type\":\"confirm_identity\",\"from\":\"master\",\"to\":\"device\",\"from_addr\":\"AB:AB:AB:AB:AB:AB\",\"to_addr\":\"FF:FF:FF:FF:FF:FF\"},\"data\":[{\"res\":1, \"type\":\"int\"}]}")};
    if (request2.getIdentifactionResult() == IdentificationResult::ACCEPTED) {
      Logger::log("Identification accepted ! ");
    } else if (request2.getIdentifactionResult() == IdentificationResult::REFUSED) {
      Logger::log("Identification refused ! ");
    }
    Logger::log(request2.getSenderAddress().toString());*/


    legend->sendRequest(request, Entity::MONITOR);
    Logger::log("I'm ready - send event");
    
  }
  
}
#endif

#ifdef LIDL_BUZZER

#define K1_BLUE 36
#define K2_RED 39
#define K3_YELLOW 34
#define K4_GREEN 35

#define L1_BLUE 21
#define L2_RED 19
#define L3_YELLOW 5
#define L4_GREEN 17

bool ledState[4] {false, false, false, false};
bool buttonPressed[4] {false, false, false, false};
uint8_t pressCounter[4] {0, 0, 0, 0};
int buttonPin[4] {K1_BLUE, K2_RED, K3_YELLOW, K4_GREEN};
std::string colorNames[4] {"blue", "red", "yellow", "green"};

void setup() {
  // INIT legend 
  legend = std::make_unique<Legend>(Legend());
  legend->run();
  //INIT pins
  pinMode(K1_BLUE, INPUT_PULLDOWN);
  pinMode(K2_RED, INPUT_PULLDOWN);
  pinMode(K3_YELLOW, INPUT_PULLDOWN);
  pinMode(K4_GREEN, INPUT_PULLDOWN);

  pinMode(L1_BLUE, OUTPUT);
  pinMode(L2_RED, OUTPUT);
  pinMode(L3_YELLOW, OUTPUT);
  pinMode(L4_GREEN, OUTPUT);

}

void loop() {
 if (legend->isReady()) {
   /* if (i1) {
      digitalWrite(L1_BLUE, HIGH);
      digitalWrite(L2_RED, HIGH);
      digitalWrite(L3_YELLOW, HIGH);
      digitalWrite(L4_GREEN, HIGH);
    }else {
      digitalWrite(L1_BLUE, LOW);
      digitalWrite(L2_RED, LOW);
      digitalWrite(L3_YELLOW, LOW);
      digitalWrite(L4_GREEN, LOW);
    }
    i1 = !i1;
    delay(1000);*/
    for(uint8_t i = 0;i<4;i++) {
      if (digitalRead(buttonPin[i])==HIGH) {
        pressCounter[i]++;
      }else {
        pressCounter[i]=0;
        buttonPressed[i]=false;
      }
      if(pressCounter[i]>3) {
        
        if(!buttonPressed[i]) {
          Serial.print("Button ");
          Serial.print(colorNames[i].c_str());
          Serial.println(" pressed");
          //send the request button pressed
          Request request {};
          request.asEvent(colorNames[i].c_str());
          legend->sendRequest(request, Entity::CONTROLLER);
        }
        buttonPressed[i] = true;
      }
    }
    /*if(==HIGH) {
      Serial.println("bouton bleu appuyé");
    }else   {
      Serial.println("bouton bleu non appuyé");
    }*/
    delay(30);
  }
  
}
#endif

