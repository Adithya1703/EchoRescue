#define button 14 

void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT);
}

void loop() {
  int buttonState = digitalRead(button);
  if(buttonState == HIGH){
    Serial.println("manual trigger pressed");
    delay(1000); // debounce delay
  }
}
