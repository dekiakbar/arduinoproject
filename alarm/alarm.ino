#include <Sim800l.h> 
#include <SoftwareSerial.h>
Sim800l Sim800l; 
char* text;
char* number;
String command; 
String potong;
String Lang;
String Long;
String jadi;
String gabung; 
String wasiat;

const int sapi = 5;
const int sasap = 3;
const int pb = 4;

int konsapi;
int konsasap;
int konpb;

void setup(){
  pinMode(sapi, INPUT);
  pinMode(sasap, INPUT);
  pinMode(pb, INPUT);
  Serial.begin(9600);
  Sim800l.begin();
  Sim800l.activateBearerProfile();
  
  
}
void loop(){
  konsapi = digitalRead(sapi);
  konsasap = digitalRead(sasap);
  konpb = digitalRead(pb);
  command = Sim800l.dateNet();
  command = Sim800l.dateNet();
  potong = command.substring(2,22);
  Lang = potong.substring(0,9);
  Long = potong.substring(11,22);
  jadi = Long+','+Lang;
  gabung = "https://www.google.com/maps/place/"+jadi;
  if (konsapi == LOW){
    wasiat = " Terdeteksi ada Api "+gabung;
    Sim800l.sendSms("+6285759858485",string2char(wasiat));
    Serial.println("Ancaman : Api");
    delay(500);
  } 
  if (konsasap == LOW ){
    wasiat = " Terdeteksi ada Gas/Asap "+gabung;
    Sim800l.sendSms("+6285759858485",string2char(wasiat));
    Sim800l.sendSms("+6281585463652",string2char(wasiat));
    Serial.println("Ancaman : Asap");
    delay(12000);
  }
  if (konpb == LOW ){
    wasiat = " Terdeteksi Adanya kecelakaan "+gabung;
    Sim800l.sendSms("+6285759858485",string2char(wasiat));
    Serial.println("Tombol emergency ditekan");
    delay(500);
  }
}

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}
