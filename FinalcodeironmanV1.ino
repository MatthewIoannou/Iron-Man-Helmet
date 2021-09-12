#include <Servo.h>
#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(2,3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

Servo myservo;
Servo myservo2;
int pos = 0; 
int postwo = 0;
bool isopen = false;
int fingerprintID = 0;
bool previousstate = 0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  finger.begin(57600);
   
  myservo.attach(10);
  myservo2.attach(8);
  myservo.write(-130);
  myservo2.write(310); 
  
  pinMode(7, INPUT);

  //lED flicker
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13,HIGH);
  delay(50);
  digitalWrite(13,LOW);
  delay(30);
  digitalWrite(13,HIGH);
  delay(20);
  digitalWrite(13,LOW);
  delay(15);
  digitalWrite(13,HIGH);

}

void loop() {
  fingerprintID = 0;
  fingerprintID = getFingerprintIDez(); //reading fingerprint
   
   if(isopen == false && fingerprintID != -1) //opening loop
  {
    myservo.attach(10);
    myservo2.attach(8);
  
    for (pos = -130, postwo = 310; pos <= 190, postwo>=-10; pos += 5, postwo-=5)
    { 
     myservo.write(pos);
     myservo2.write(postwo);
    
     delay(17);     
    }
    delay(500);
    for (pos = 190, postwo = -10; pos <= 160, postwo>=20; pos += 5, postwo-=5)
    { 
     myservo.write(pos);
     myservo2.write(postwo);
    
     delay(17);     
    }
    isopen = true;
    myservo.detach();
    myservo2.detach();
  }
  
  fingerprintID = 0;
  
  if(previousstate != digitalRead(7) && isopen == true) //closing loop
  { 
    myservo.attach(10);
    myservo2.attach(8);
    
    for (pos = 160, postwo = 20; pos >=-130, postwo<=310; pos -= 10, postwo +=10)
    { 
       myservo.write(pos);  
       myservo2.write(postwo); 
       delay(15);                       
    }
    delay(200);

    isopen = false;
    myservo.detach();
    myservo2.detach();
    previousstate = digitalRead(7);
  }
}



int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  return finger.fingerID;
}
