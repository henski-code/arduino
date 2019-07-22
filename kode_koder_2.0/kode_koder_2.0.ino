#include <SPI.h>
#include <SD.h>

#define red 3
#define green 5
#define blue 6


void odczyt();
void zapis();
void kodowanie();
void dekodowanie();
bool inicjalizacja();
void swiec(char kolor);

char tekst[510];
int x=0;

void setup() {


  Serial.begin(9600);
  pinMode(8,INPUT_PULLUP); //przycisk kodowania
  pinMode(9,INPUT_PULLUP);  //przycisk dekodowania

  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  swiec('b');
  


  while(true)
  {
    if(digitalRead(8)==LOW)
    {
     if(inicjalizacja()==true)
     {
      odczyt();
      kodowanie();
      zapis();
      break;
     }
     else
     {
      while(true) swiec('r');

      
     }
    }
    if(digitalRead(9)==LOW)
    {
      if(inicjalizacja()==true)
      {
      odczyt();
      dekodowanie();
      zapis();
      break;
      }
      else while(true)swiec('r');
    }

    
  }

 

  


  



}

void loop() {
 
}

bool inicjalizacja()
{
  Serial.print("Initializing SD card...");
 if (!SD.begin(A0)) {
    Serial.println("initialization failed!");
    return false;
  }
  Serial.println("initialization done.");
  return true;
  
}
void odczyt()
{
  swiec('y');
  File plik;
  plik=SD.open("kod.txt",FILE_READ);
  while (plik.available()) 
   {
      tekst[x]=plik.read();
     x++;
    }
  plik.close();
  
    Serial.println("Pobrano dane");
    Serial.println(tekst);
}

void zapis()
{
  
  File plik;
  plik=SD.open("kod.txt",FILE_WRITE);
  plik.seek(0);
  plik.print(tekst);
  plik.close();
  swiec('g');
  Serial.println();
  Serial.println("Zapisano");
  Serial.print("Oto zapisany tekst: ");
  Serial.print(tekst); 
 
}


void kodowanie()
{
  for(int i=0; i<x ;i++)
    {
       tekst[i]=(int)tekst[i]+5;
    }


      Serial.println("Zakodowano");
      Serial.println("Zakodowane dane: ");
      Serial.print(tekst);
  
}

void dekodowanie()
{
  for(int i=0; i<x ;i++)
    {
       tekst[i]=(int)tekst[i]-5;
    }


      Serial.println("Odkodowano");
      Serial.println("Odkodowane dane: ");
      Serial.print(tekst);
  
}
void swiec(char kolor)
{
  switch(kolor)
  {
    case 'r':
      digitalWrite(red,LOW);
      digitalWrite(green,HIGH);
      digitalWrite(blue,HIGH);
      break;
    case 'g':
     digitalWrite(red,HIGH);
      digitalWrite(green,LOW);
      digitalWrite(blue,HIGH);
     
     break;
    case 'b':
      digitalWrite(red,HIGH);
      digitalWrite(green,HIGH);
      digitalWrite(blue,LOW);
     break;
     case 'y':
     digitalWrite(red, 0);
     digitalWrite(green, 0);
     digitalWrite(blue, 200);
     break;
    
  }

}




