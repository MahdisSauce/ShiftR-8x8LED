#ifndef SHIFTLIB_H
#define SHIFTLIB_H
#include <Arduino.h>

byte * reverseBitOrder(byte img[]); //reverses bit order for each byte of img

byte * frameShift(byte img[], bool dir, bool axis, int offset); //returns img with proper offset

class ledMatrix{
    private:
        short dataPin;        //Pin 14 On the Shift Register
        short clockPin;       //Pin 11 On the Shift Register
        short latchPin;       //Pin 12 On the Shift Register
    
    public:
        unsigned int prevMillis;    //Defining variable to be used for timing
        unsigned int currMillis;
        
        ledMatrix(short x, short y, short z); //Initializes the shift register pins
        
        void clearDisplay();    // Clears the display

        void toDisplay(byte img[]); //Displays the image

        void timedDisplay(byte img[], unsigned int interval);   //Displays the image for set amount of time
        
        void fromSide(byte img[], bool dir);    //Pans image from left or right off screen

        void panDisplay(byte img[], bool dir);//Pans the image left or right until off screen starting from the center
        
        void ventDisplay(byte img[],bool dir);//Pans image up or down until off screen starting from center

        void fromVertical(byte img[], bool dir);

};

#endif
