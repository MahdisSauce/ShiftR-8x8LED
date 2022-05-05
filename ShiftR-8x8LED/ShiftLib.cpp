#include "ShiftLib.h"

byte * flipX(byte img[]){ //reverses bit order for each byte of img
    for(int i = 0; i < 8; i++){
        img[i] = (img[i] & 0xF0) >> 4 | (img[i] & 0x0F) << 4;
        img[i] = (img[i] & 0xCC) >> 2 | (img[i] & 0x33) << 2;
        img[i] = (img[i] & 0xAA) >> 1 | (img[i] & 0x55) << 1;
    }
    return img;
}

byte * flipY(byte img[]){   //flips the order of the bytes
    byte* holder = new byte[8];
    for(int i = 0; i < 8; i++)
        holder[i] = img[8 - i];
    
    return holder;
}

byte * frameShift(byte img[], bool dir, bool axis, int offset){ //returns img with proper offset
    byte* holder = new byte[8];
    for(int x = 0; x < 8; x++){
        if(dir == 0){
            if(axis == 0)
                holder[x] = img[x] >> offset;
            else    
                if(x + offset >= 8)
                    holder[x] = 0;
                else
                    holder[x] = img[x + offset];
        }
        else
            if(axis == 0)
                holder[x] = img[x] << offset;
            else
                if(x-offset < 0)
                    holder[x] = 0;
                else
                    holder[x] = img[x-offset];  
    }
    return holder;
}



ledMatrix::ledMatrix(byte x, byte y, byte z){
    dataPin = x;            //Assigning the pin variables to their repsective pins
    clockPin = y;
    latchPin = z;
    pinMode(dataPin, OUTPUT);   //Setting the pins to outputs
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
}

void ledMatrix::clearDisplay(){            //Setting all outputs of the shift registers to LOW
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0);
    shiftOut(dataPin, clockPin, LSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
}

void ledMatrix::toDisplay(byte img[]){     //Displaying image bases on 8 Byte array sent to function
    for(int i = 0; i < 8; i++){
        digitalWrite(latchPin, LOW);                    //Prepares pin for rising edge
        shiftOut(dataPin, clockPin, LSBFIRST, ~img[i]); //Displays the current byte
        shiftOut(dataPin, clockPin, MSBFIRST, (1 << i));//Turns on pin for current byte
        digitalWrite(latchPin, HIGH);                   //Shifts data from shift register to output register
        delay(1);
        }
    clearDisplay();
    delay(5);
}   

void ledMatrix::timedDisplay(byte img[], unsigned int interval){   //Displaying image for a timed duration
    prevMillis = millis();
    currMillis = millis();
    while(currMillis - prevMillis <= interval){
        currMillis = millis();
        toDisplay(img);
    };
}
void ledMatrix::fromSide(byte img[], bool dir){ //Pans image from left or right off screen
    for(int i = 8; i >= 0; i--){
        timedDisplay(frameShift(img, !dir, 0, i), 300);
    }
}


void ledMatrix::panDisplay(byte img[], bool dir){  //Pans the image left or right until off screen starting from the center
    for(int i = 0; i <= 8; i++){        //For loop to determine how far it is moved each frame
        timedDisplay(frameShift(img, dir, 0, i), 300);
    }   
}
void ledMatrix::ventDisplay(byte img[],bool dir){  //Pans image up or down until off screen starting from center
        for(int i = 0; i <= 8; i++){  
            timedDisplay(frameShift(img, dir, 1, i), 300);
        }
}

void ledMatrix::fromVertical(byte img[], bool dir){          
    for(int i = 8; i >= 0; i--){  
        timedDisplay(frameShift(img, !dir, 1,  i), 300);
    }
}
