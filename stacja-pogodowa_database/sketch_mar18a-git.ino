#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"
#define DHTTYPE DHT22

#define termometr_zew 2
#define DHTPIN 3 //termomentr wew

long int haslo=########;
float temp_zewn, temp_wew, wilg, cisnienie;

//Ustawienia dns i połączenia z serwerem
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,176);
IPAddress myDns(8, 8, 8, 8);
char server[] = "########";
EthernetClient client;

//termomentra zew.
OneWire  ds(termometr_zew);
//termometr wew
DHT dht(DHTPIN, DHTTYPE);
//barometr
Adafruit_BMP085 bmp;

void dhcp_setup(){
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

float temp_zew(){
    //termometr zew
  byte i;
    byte present = 0;
    byte type_s;
    byte data[12];
    byte addr[8];
    float celsius;
  
    
  
   if ( !ds.search(addr)) {
      //Serial.println("No more addresses.");
      //Serial.println();
      ds.reset_search();
      delay(250);
      return;
    }
  
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1); 
  
  delay(1000);
  
  present = ds.reset();
    ds.select(addr);    
    ds.write(0xBE);
  
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
      data[i] = ds.read();
  }
  
  int16_t raw = (data[1] << 8) | data[0];
    if (type_s) {
      raw = raw << 3; // 9 bit resolution default
      if (data[7] == 0x10) {
        // "count remain" gives full 12 bit resolution
        raw = (raw & 0xFFF0) + 12 - data[6];
      }
    } else {
      byte cfg = (data[4] & 0x60);
      // at lower res, the low bits are undefined, so let's zero them
      if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
      else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
      else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
      //// default is 12 bit resolution, 750 ms conversion time
    }
    return (float)raw / 16.0;
}


void setup() {
  Serial.begin(9600);
  
  //inicjalizacja ethernet
  dhcp_setup();
  //inicjalizacja termometru wew
  dht.begin();
  //inicjalizacja barometru
  bmp.begin();
}

void loop() {
//Wykonanie odczytów
  temp_zewn=temp_zew();
  temp_wew=dht.readTemperature();
  wilg=dht.readHumidity();
  cisnienie=bmp.readPressure()/100; //w hPa
//Przesłanie odczytów na serial monitor
  Serial.println("Odczyty: ");
  Serial.print("temperatura zew: ");
  Serial.println(temp_zewn);
  Serial.print("Temperatura wew: ");
  Serial.println(temp_wew);
  Serial.print("Wilgotnosc: ");
  Serial.println(wilg);
  Serial.print("Cisnienie = ");
    Serial.print(cisnienie);
    Serial.println(" hPa");
  Serial.println("--------------------------------");
//---------------


 if (client.connect(server, 80)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.print("GET /push.php?temp_zew=");
    client.print(temp_zewn);
    client.print("&temp_wew=");
    client.print(temp_wew);
    client.print("&wilg=");
    client.print(wilg);
    client.print("&cis=");
    client.print(cisnienie);
    client.print("&secret=");
    client.print(haslo);
    client.println(" HTTP/1.1");
    client.println("Host: #########");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
   delay(45000);
}


  
