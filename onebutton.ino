int pushButton = 2;

int prevMode = -1;

void setup (){
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
}

void loop(){
  
  int buttonState = digitalRead(pushButton);
  if(prevMode != buttonState) {
    if(buttonState > 0) Serial.write("a");
  }
  prevMode = buttonState;
  delay(1);
  
}
