#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>

#define LED 12

LiquidCrystal_I2C lcd(0x3F,16,2);

int czas=100;

String tekst;
int dlugosc=0;

void na_lcd(char x)
{
  lcd.print(x);
}

void kropka()
{
  
  digitalWrite(LED, HIGH);   
  delay(czas);                       
  digitalWrite(LED, LOW);
  delay(czas*2);
  
  
}
void dlugi()
{
  
  digitalWrite(LED, HIGH);   
  delay(czas*6);                      
  digitalWrite(LED, LOW);
  delay(czas*2);
  
  
}
void litera(String x, int dlugosc)
{
  Serial.println("Jestem funkcja litera!");
  for(int i=0;i<dlugosc;i++)
  {
   na_lcd(x[i]);
  switch(x[i])
  {
   case 'a':kropka();dlugi();Serial.print("a");break;
   case 'b':dlugi();kropka();kropka();kropka();Serial.print("b");break;
   case 'c':dlugi();kropka();dlugi();kropka();Serial.print("c");break;
   case 'd':dlugi();kropka();kropka();Serial.print("d");break;
   case 'e':kropka();Serial.print("e");break;
   case 'f':kropka();kropka();dlugi();kropka();Serial.print("f");break;
   case 'g':dlugi();dlugi();kropka();Serial.print("g");break;
   case 'h':kropka();kropka();kropka();kropka();Serial.print("h");break;
   case 'i':kropka();kropka();Serial.print("i");break;
   case 'j':kropka();dlugi();dlugi();dlugi();Serial.print("j");break;
   case 'k':dlugi();kropka();dlugi();Serial.print("k");break;
   case 'l':kropka();dlugi();kropka();kropka();Serial.print("l");break;
   case 'm':dlugi();dlugi();Serial.print("m");break;
   case 'n':dlugi();kropka();Serial.print("m");break;
   case 'o':dlugi();dlugi();dlugi();Serial.print("o");break;
   case 'p':kropka();dlugi();dlugi();kropka();Serial.print("p");break;
   case 'q':dlugi();dlugi();kropka();dlugi();Serial.print("q");break;
   case 'r':kropka();dlugi();kropka();Serial.print("r");break;
   case 's':kropka();kropka();kropka();Serial.print("s");break;
   case 't':dlugi();Serial.print("t");break;
   case 'u':kropka();kropka();dlugi();Serial.print("u");break;
   case 'v':kropka();kropka();kropka();dlugi();Serial.print("v");break;
   case 'w':kropka();dlugi();dlugi();Serial.print("w");break;
   case 'x':dlugi();kropka();kropka();dlugi();Serial.print("x");break;
   case 'y':dlugi();kropka();dlugi();dlugi();Serial.print("y");break;
   case 'z':dlugi();dlugi();kropka();kropka();Serial.print("z");break;
  
  }
}
Serial.println();
Serial.println("Nadawanie zakonczone !");
lcd.clear();

lcd.setCursor(0,0);
lcd.print("Nadawanie");
lcd.setCursor(0,1);
lcd.print("zakonczono !");

//lcd.scrollDisplayRight("Nadawanie zakonczono pomyslnie !");
}

// the setup function runs once when you press reset or power the board
void setup() {
 
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.print("Wprowadz wyraz");
  lcd.setCursor(0,1);
  lcd.print("na Serial moni.");
}

// the loop function runs over and over again forever
void loop() {


Serial.flush();
dlugosc=Serial.available();

if(dlugosc>0)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nadano:");
  lcd.setCursor(0,1);
  Serial.println("Jestem if!");
 // Serial.println("Wartosc dlugosc: "+dlugosc);
    tekst=Serial.readStringUntil("/n");
    tekst.toLowerCase();
    litera(tekst,dlugosc);
}
tekst="";

delay(50);
 
  
  
}

