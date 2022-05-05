byte * reverseBitOrder(byte img[]){ //reverses bit order for each byte of img
    for(int i = 0; i < 8; i++){
        img[i] = (img[i] & 0xF0) >> 4 | (img[i] & 0x0F) << 4;
        img[i] = (img[i] & 0xCC) >> 2 | (img[i] & 0x33) << 2;
        img[i] = (img[i] & 0xAA) >> 1 | (img[i] & 0x55) << 1;
    }
    return img;
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



class ledMatrix{
    public:
        int dataPin;        //Pin 14 On the Shift Register
        int clockPin;       //Pin 11 On the Shift Register
        int latchPin;       //Pin 12 On the Shift Register
        unsigned int prevMillis;    //Defining variable to be used for timing
        unsigned int currMillis;

        ledMatrix(int x, int y, int z){
            dataPin = x;            //Assigning the pin variables to their repsective pins
            clockPin = y;
            latchPin = z;
            pinMode(dataPin, OUTPUT);   //Setting the pins to outputs
            pinMode(clockPin, OUTPUT);
            pinMode(latchPin, OUTPUT);
        }
      
        void clearDisplay(){            //Setting all outputs of the shift registers to LOW
            digitalWrite(latchPin, LOW);
            shiftOut(dataPin, clockPin, LSBFIRST, 0);
            shiftOut(dataPin, clockPin, LSBFIRST, 0);
            digitalWrite(latchPin, HIGH);
        }

        void toDisplay(byte img[]){     //Displaying image bases on 8 Byte array sent to function
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

        void timedDisplay(byte img[], unsigned int interval){   //Displaying image for a timed duration
            prevMillis = millis();
            currMillis = millis();
            while(currMillis - prevMillis <= interval){
                currMillis = millis();
                toDisplay(img);
            };
        }
        void fromSide(byte img[], bool dir){ //Pans image from left or right off screen
            for(int i = 8; i >= 0; i--){
                timedDisplay(frameShift(img, !dir, 0, i), 300);
            }
        }

        
        void panDisplay(byte img[], bool dir){  //Pans the image left or right until off screen starting from the center
            for(int i = 0; i <= 8; i++){        //For loop to determine how far it is moved each frame
                timedDisplay(frameShift(img, dir, 0, i), 300);
            }   
        }
        void ventDisplay(byte img[],bool dir){  //Pans image up or down until off screen starting from center
                for(int i = 0; i <= 8; i++){  
                    timedDisplay(frameShift(img, dir, 1, i), 300);
                }
        }

        void fromVertical(byte img[], bool dir){          
            for(int i = 8; i >= 0; i--){  
                timedDisplay(frameShift(img, !dir, 1,  i), 300);
            }
        }

};



// Maps of letters and images
// byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
// byte BOX[] = {B11111111,B11111111,B11000011,B11000011,B11000011,B11000011,B11111111,B11111111};
// byte CREEPER[] = {B11111111, B10011001, B10011001, B11100111, B11000011, B11000011, B11011011, B11111111};
// byte AMOGUS[] = {B01111100,B11111110,B00011111,B00011111,B11111111,B11111110,B11101110,B11101110};
// byte EX[] = {B00000000,B00010000,B00010000,B00010000,B00010000,B00000000,B00010000,B00000000};
//byte A[] = {B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110};
//byte B[] = {B01111000,B01001000,B01001000,B01110000,B01001000,B01000100,B01000100,B01111100};
//byte C[] = {B00000000,B00011110,B00100000,B01000000,B01000000,B01000000,B00100000,B00011110};
//byte D[] = {B00000000,B00111000,B00100100,B00100010,B00100010,B00100100,B00111000,B00000000};
//byte E[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
//byte F[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00100000,B00000000};
//byte G[] = {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
//byte H[] = {B00000000,B00100100,B00100100,B00111100,B00100100,B00100100,B00100100,B00000000};
//byte I[] = {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
//byte J[] = {B00000000,B00011100,B00001000,B00001000,B00001000,B00101000,B00111000,B00000000};
//byte K[] = {B00000000,B00100100,B00101000,B00110000,B00101000,B00100100,B00100100,B00000000};
//byte L[] = {B00000000,B00100000,B00100000,B00100000,B00100000,B00100000,B00111100,B00000000};
//byte M[] = {B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000};
//byte N[] = {B00000000,B00100010,B00110010,B00101010,B00100110,B00100010,B00000000,B00000000};
//byte O[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
//byte P[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100000,B00100000,B00000000};
//byte Q[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000110,B00111110,B00000001};
//byte R[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
//byte S[] = {B00000000,B00111100,B00100000,B00111100,B00000100,B00000100,B00111100,B00000000};
//byte T[] = {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
//byte U[] = {B00000000,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000,B00000000};
//byte V[] = {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
//byte W[] = {B00000000,B10000010,B10010010,B01010100,B01010100,B00101000,B00000000,B00000000};
//byte X[] = {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};
//byte Y[] = {B00000000,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00000000};
//byte Z[] = {B00000000,B00111100,B00000100,B00001000,B00010000,B00100000,B00111100,B00000000};


void setup() {
    // put your setup code here, to run once:
      
}


void loop() {
    // put your main code here, to run repeatedly:


}
