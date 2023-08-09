#include  <EEPROM.h>
void setup() {
  // put your setup code here, to run once:

}

void loop() {
EEPROM.write(0, 10);

EEPROM.write(1, 20);
EEPROM.write(2, 30);
EEPROM.write(3, 40);
EEPROM.write(4, 50);

}
