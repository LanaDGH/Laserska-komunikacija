#define laser 2


volatile float vreme=0;
const int t0 = 1000;
const int t1 = 2000;
const int tp = 500;
//izmeniti kasnije!!

void milipauza(double v){
  double pocetak = vreme;
  while(vreme-pocetak<=v){  
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
  TCCR1A = 0b00000000;
  TCCR1B = 0b00001011;
  OCR1A = 250;
  TCNT1=0;
  TIMSK1=0B00000010;
}

ISR(TIMER1_COMPA_vect)
{
  vreme++;
}

void sendSignalDir(char incomingByte){
  if(incomingByte=='1'){
      digitalWrite(laser, HIGH);
      Serial.println("HIGH");
      milipauza(tp);
      digitalWrite(laser, LOW);
      Serial.print(incomingByte);
    }else if(incomingByte=='0'){
      digitalWrite(laser,LOW);
      Serial.println("LOW");
      milipauza(tp);
      Serial.print(incomingByte);
    }
}

void sendSignal(char incomingByte){
  if(incomingByte=='1'){
      digitalWrite(laser, HIGH);
      delay(t1);
      Serial.print(incomingByte);
    }else if(incomingByte=='0'){
      digitalWrite(laser,HIGH);
      delay(t0);
      Serial.print(incomingByte);
    }
    digitalWrite(laser,LOW);
    delay(tp);
}

void loop() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    //Serial.println(incomingByte);
    //Serial.print(incomingByte);
    sendSignal(incomingByte);
  }
}
