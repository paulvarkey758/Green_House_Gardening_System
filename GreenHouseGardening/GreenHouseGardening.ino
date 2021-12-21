 
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLnZfLUn07"
#define BLYNK_DEVICE_NAME "DHT"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG


#include "DHTStable.h"
DHTStable DHT;
#define DHT11_PIN 14
#include "BlynkEdgent.h"

int temp;
int hum;
int pinvalue;
float moist;
int mod;
int motor;
int pumb;
int a;
int b;
BLYNK_WRITE(V0){
  pinvalue=param.asInt();
  digitalWrite(13,pinvalue);
  Blynk.virtualWrite(V4,pinvalue);
}

BLYNK_WRITE(V5){
  mod=param.asInt();
}
BLYNK_WRITE(V6){
  motor=param.asInt();
  Serial.println(motor);
  if(motor==1){
    digitalWrite(5,1);
    digitalWrite(16,0);
    Serial.println("ggod job");
   
  }
  if(motor==0){
    digitalWrite(5,0);
    digitalWrite(16,0);
    Serial.println("stop");
  }
}
BLYNK_WRITE(V7){
  pumb=param.asInt();
  Serial.println(pumb);
  if(pumb==1){
    digitalWrite(3,1);
    digitalWrite(1,0);
    Serial.println("super job");
   
  }
  if(pumb==0){
    digitalWrite(3,0);
    digitalWrite(1,0);
    Serial.println("fine");
  }
}
void setup()
{  
  Serial.begin(115200);
  delay(100);
  BlynkEdgent.begin();
  pinMode(13,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(12,INPUT);
  //pinMode(0,INPUT);
  
  
}

void loop() {
  BlynkEdgent.run();
  int chk = DHT.read11(DHT11_PIN);
  hum=DHT.getHumidity();
  Serial.print(hum);
  Serial.print(",\t");
  temp = DHT.getTemperature();
  Serial.println(temp);
  Blynk.virtualWrite(V1,temp);
  Blynk.virtualWrite(V2,hum);
  int moist=analogRead(0);
  moist = moist/10;
  Serial.println("Moist Value");
  Serial.println(moist);
  int ldrin=digitalRead(12);
  Blynk.virtualWrite(V3,moist);
  if (mod==0){
    if(temp>=34){
      b=1;
    }
    if(b==1){
      digitalWrite(5,1);
      digitalWrite(16,0);
      Blynk.virtualWrite(V1,temp);
        }
    if(temp<=28 && temp>=22){
      b=0;
    }
    if(b==0){
      digitalWrite(5,0);
      digitalWrite(16,0);
      Blynk.virtualWrite(V1,temp);
        }
    
    if(moist >=98){
      a=1;
    }
    if (a==1){
       
        digitalWrite(3,1);
        digitalWrite(1,0);
        Blynk.virtualWrite(V3,moist);
      }
    if(moist<=70){
      a=0;
    }
    if(a==0){
      digitalWrite(3,0);
      digitalWrite(1,0);
      Blynk.virtualWrite(V3,moist);
    }
    if(ldrin == 1){
      digitalWrite(13,1);
      Blynk.virtualWrite(V4,1);
      }
    else{
      digitalWrite(13,0);
      Blynk.virtualWrite(V4,0);
      }
    }
  }
