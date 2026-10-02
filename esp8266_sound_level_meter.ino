
const int sesPin = A0;


void setup() {
Serial.begin(115200);

pinMode(sesPin,INPUT);


}



void loop() {

unsigned int maxsignal = 0;
unsigned int minsignal = 1024;

unsigned int startmillis = millis();
unsigned int seslisten = 50;    //50 ms


while(millis() - startmillis < seslisten)
{
    int  sensordegeri = analogRead(sesPin);
 
  if (sensordegeri < 1024)
  {

    if(sensordegeri > maxsignal)
      maxsignal = sensordegeri;
  if(sensordegeri < minsignal)
      minsignal = sensordegeri;

  }
}

int genlik = maxsignal - minsignal;

int ses_seviyesi = map(genlik,0,500,1,100);    
   ses_seviyesi  = constrain(ses_seviyesi,1,100);            //  map() fonksiyonunu kullandım 1 - 100 arasına oranlıyarak.


//Serial.print("HEY NIGGA \n\n");

Serial.print("That's Real DATA:  ");
Serial.print(genlik);
Serial.print("SOUND LEVEL");
Serial.print(ses_seviyesi);


}
