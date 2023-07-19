#define laser 2

volatile float vreme=0;
const double t0 =5;
const double t1 = 10;
const double tp = 5;
const double tdir =1000;
bool inic = 0;
//izmeniti kasnije!!

void milipauza(double v){
  double pocetak = vreme;
  while(vreme-pocetak<=v){  
  }
}

//! izmenjeno
void charToSignal(char c)
{
  if(c==10){
    inic=0;  
  }
  int n=c;
  Serial.print("konverzija: ");
  Serial.println(n);
  for (int i = 7; i >= 0; i--) {
  int k = n >> i;
  if (k & 1)
    sendSignalDir('1');
  else
    sendSignalDir('0');
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

void sendSignal(char incomingByte){
  if(incomingByte=='1'){
      digitalWrite(laser, HIGH);
      milipauza(t1);
      Serial.print(incomingByte);
    }else if(incomingByte=='0'){
      digitalWrite(laser,HIGH);
      milipauza(t0);
      Serial.print(incomingByte);
    }
    digitalWrite(laser,LOW);
    milipauza(tp);
}

void sendSignalDir(char incomingByte){
  if(incomingByte=='1'){
      digitalWrite(laser, HIGH);
      Serial.println("1");
      milipauza(tdir);
      digitalWrite(laser, LOW);
      //Serial.println(incomingByte);
    }else if(incomingByte=='0'){
      digitalWrite(laser,LOW);
      Serial.println("0");
      milipauza(tdir);
      //Serial.println(incomingByte);
    }
}

void initSeq(){
    Serial.println("Inicijalna sekvenca");
    digitalWrite(laser, LOW);
    Serial.println("0");
    milipauza(tdir);
    digitalWrite(laser, HIGH);
    Serial.println("1");
    milipauza(tdir);
    digitalWrite(laser, LOW);
    Serial.println("0");
    milipauza(tdir);
    Serial.println("Pocetak signala");
}

void loop() {
  if (Serial.available() > 0) {
    if (!inic){
      initSeq();
      inic = 1;  
    }
    char incomingByte = Serial.read();
    ///Serial.println("tekst: ");
    Serial.println(incomingByte);
    //signal(incomingByte);
    charToSignal(incomingByte);
  }
}
