#include "ShiftLib.h"

void setup(){

    
}

ledMatrix mat1(3, 4, 2);
byte AMOGUS[] = {
    B01111100,
    B11111110,
    B00011111,
    B00011111,
    B11111111,
    B11111110,
    B11101110,
    B11101110};

void loop(){
mat1.timedDisplay(reverseBitOrder(AMOGUS), 500);
    
}
