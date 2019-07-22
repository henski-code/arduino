#define d1 2
#define d2 3
#define d3 4
#define d4 5

#define p1 8
#define p2 9
#define p3 12
#define p4 13

int glosnik= 11;

#include "pitches.h"


int tablica[100];
int ile=1;

void zaswiec(int dioda,int glosnik,int czas)
{
 digitalWrite(dioda,HIGH);
  tone(glosnik, NOTE_C4, 10);
  delay(czas);
 
  digitalWrite(dioda,LOW);
  delay(czas);
  noTone(glosnik);
 // Serial.println(dioda);


}

void setup() {

Serial.begin(9600);
  
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
//------------------------------------
  pinMode(p1, INPUT_PULLUP);
  pinMode(p2, INPUT_PULLUP);
  pinMode(p3, INPUT_PULLUP);
  pinMode(p4, INPUT_PULLUP);

   randomSeed(analogRead(A5)); //Ziarno dla generatora liczb losowych
   
   

   for(int i=0;i<100;i++)
   {
    tablica[i]=random(4);
    //Serial.println(tablica[i]);
   }
   
   }



void loop()
{
  if(digitalRead(p1)==LOW)
  {
 for(int i=0;i<ile;i++)
 {
  switch(tablica[i])
  {
  case 0: 
  zaswiec(d1,glosnik,150);
  Serial.println("d1");
  break; 
  
  case 1: 
  zaswiec(d2,glosnik,150);
  Serial.println("d2");
  break;
  
  case 2: 
  zaswiec(d3,glosnik,150);
  Serial.println("d3");
  break;
  
  case 3: 
 zaswiec(d4,glosnik,150);
  Serial.println("d4");
  break;   
  }
    
 }
     ile=ile+1;
     Serial.println("zwiekszam ile");
     //Serial.println(ile);
  }
delay(20);
}
