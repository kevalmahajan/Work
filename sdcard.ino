
#include <SPI.h>
#include <SD.h>
#include "Sodaq_DS3231.h"
File myFile;
DateTime now;
int wcount=0;
int rcount=0;
int newmin = 0;
int oldmin = 0;


void setup() {  

  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  if (!SD.begin(53)) {
  Serial.println("initialization failed!");
  while (1);
  }
  Serial.println("initialization done.");

  now = rtc.now();
  oldmin = now.minute();
 

}


void pushtosd(String db,int wcount)
{
  File myFile;
  myFile = SD.open(String(wcount)+".txt", FILE_WRITE);
  if (myFile) {
  myFile.print(db);
  Serial.print("File Written");
  }
  else{
    Serial.print("not printed");
  }
  myFile.close();
  Serial.println("Done");
   
}

String popofsd(int rcount)
{
  while (myFile.available()) { 
  String db=myFile.readString();
  return db;
  }
}

void loop() {
  
Serial.println("start");
now = rtc.now();
newmin = now.minute();

if (oldmin != newmin) {
pushtosd(String(newmin),wcount);
wcount++;
Serial.println(wcount);
oldmin = newmin;
}



//now = rtc.now();
//myFile.print(now.minute());
//pushtosd(String(now.minute()),wcount);
//wcount++;
//Serial.println(wcount);

}
