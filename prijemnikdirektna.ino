const int LDR = A0;
int input_val = 0;
int tresh=1000;
volatile float vreme=0;
float pocetak=0;
float trajanjeSignala=0;
bool sija=false;
int brojac=128;
int ascii=0;
char ch;
const float t=250; 
int inicijalna_sekv=2;

void setup()
{
  Serial.begin(9600);
  TCCR1A = 0b00000000;
  TCCR1B = 0b00001011;
  OCR1A = 100;
  TCNT1=0;
  TIMSK1=0B00000010;
}
ISR(TIMER1_COMPA_vect)
{
  vreme++;
} 
void pametan_delay(float v)
{
  float pocetak = vreme;
  while(vreme-pocetak<=v){
  }
}
void loop()
{
  input_val = analogRead(LDR);
  //primanje inicijalne sekvence
  if(inicijalna_sekv>0)
  {
    if(input_val>tresh && !sija)
    {
      //pocetak=vreme;
      inicijalna_sekv--;
      sija=true;
      Serial.println("sijaa");
    }
     else if(input_val<=tresh && sija)
    {
      //t=vreme-pocetak;
      sija=false;
      inicijalna_sekv--;
      pametan_delay(t/2);
      pocetak=vreme;
      Serial.println("gasi");
      //Serial.println("trajanje inic: ");
      //Serial.println(t);
    } 
   }
   else if(vreme - pocetak>=t)
   {
     pocetak=vreme;
     if(input_val>=tresh)
     {
       Serial.print("1");
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
     else
     {
       Serial.print("0");
        if(brojac==1)
       {
         ch = char(ascii);
         if(ascii==10)
         {
           inicijalna_sekv=2;
           Serial.println("kraj poruke");
           pametan_delay(t/2);
         }
         else
           Serial.print(ch);
         ascii=0;
         brojac=128;
       }
       else brojac/=2; 
     }
  }
}
