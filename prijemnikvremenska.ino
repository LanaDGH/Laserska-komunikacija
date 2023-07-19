const int LDR = A0;
int input_val = 0;
int tresh=800;
volatile float vreme=0;
float pocetak=0;
float trajanjeSignala=0;
bool sija=false;
int brojac=128;
int ascii=0;
char ch;
const int offset1=2;
const int t0=5; //odredicemo naknadno
const int t1=10; //isto
const int offset2=3;

void setup()
{
  Serial.begin(9600);
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
void loop()
{
  input_val = analogRead(LDR);
  if(input_val>tresh && !sija)
  {
    sija=true;
    pocetak=vreme;
    //Serial.println("poceo je da sija");
  }
  else if(input_val<=tresh && sija)
  {
    sija=false;
    trajanjeSignala=vreme-pocetak;
    //Serial.println("trajanje: ");
    //Serial.println(trajanjeSignala);
    if(trajanjeSignala>=t0-offset1 && trajanjeSignala<=t0+offset2)
    {
      //Serial.print("0");
       if(brojac==1)
      {
        ch = char(ascii);
        //Serial.println("primljen karakter:");
        //Serial.println(ascii);
        Serial.print(ch);
        ascii=0;
        brojac=128;
      }
      else brojac/=2; 
    }
    else if(trajanjeSignala>=t1-offset1)
    {
      //Serial.print("1");
      ascii+=brojac;
      //erial.println("trenutna vrednost:");
      //Serial.println(ascii);
      if(brojac==1)
      {
        ch = char(ascii);
        //Serial.println("primljen karakter:");
        //Serial.println(ascii);
        Serial.print(ch);
        ascii=0;
        brojac=128;
      }
      else brojac/=2;
    }
    //Serial.println("trajanje signala:");
    //Serial.println(trajanjeSignala);
  }
}
