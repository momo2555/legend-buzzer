#include <Arduino.h>
#include <legendMaster.h>

std::unique_ptr<LegendMaster> legendMaster {}; 

void setup() {
  // put your setup code here, to run once:
  legendMaster = std::make_unique<LegendMaster>(LegendMaster());
  legendMaster->run();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  legendMaster->setup();
  delay(20);
}

