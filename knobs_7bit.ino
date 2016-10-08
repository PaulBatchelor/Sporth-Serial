#define USE_PUSHBUTTON

#ifdef USE_PUSHBUTTON
int pval[3];
unsigned char msg[3];
int pushButton = 2;
#else 
unsigned char msg[2];
int pval[2];
#endif



void setup (){
    pval[0] = -1;     
    pval[1] = -1;  

#ifdef USE_PUSHBUTTON
    pval[2] = -1;
    pinMode(pushButton, INPUT);
#endif


#ifdef USE_PUSHBUTTON
    Serial.begin(115200);
#else
    Serial.begin(9600);
#endif

}



static void writeVals()
{
    msg[0] = 255;
    msg[1] = analogRead(0) >> 3;
    msg[2] = analogRead(1) >> 3;

#ifdef USE_PUSHBUTTON
    msg[3] = (digitalRead(pushButton) > 0) ? 127 : 0;
#endif

    if(msg[1] != pval[0] || 
       msg[2] != pval[1] 
#ifdef USE_PUSHBUTTON 
       || msg[3] != pval[2] 
#endif
      ) {
        Serial.write(msg[0]);
        Serial.write(msg[1]);
        Serial.write(msg[2]);
#ifdef USE_PUSHBUTTON
        Serial.write(msg[3]);
#endif
        pval[0] = msg[1];
        pval[1] = msg[2];
#ifdef USE_PUSHBUTTON
        pval[2] = msg[3];
#endif
    }

}

void loop() {
    writeVals();
}
