#include <ArduinoBLE.h>

const int trigPin = 8;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;
int threshold = 5; // in cm

BLEService newService("180A"); // creating the service
BLEByteCharacteristic readChar("2A57", BLERead);
BLEByteCharacteristic writeChar("2A58", BLEWrite);

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(2,OUTPUT) //red (on when distance > threshold)
  pinMode(4,OUTPUT) //green (on when distance < or = threshold)
  
  // while(!Serial);
  if (!BLE.begin()){
    Serial.println("Waiting for ArduinoBLE");
    while(1);
  }

  BLE.setDeviceName("Paula,Sathvik");
  //BLE.setAdvertisedServiceUuid("paulasathvik1234")
  BLE.setAdvertisedService(newService);
  newService.addCharacteristic(readChar);
  newService.addCharacteristic(writeChar);
  BLE.addService(newService);

  readChar.writeValue(0);
  writeChar.writeValue(0);

  BLE.advertise();
  Serial.println("Bluetooth device active");  

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distanceCm = duration/58;
  distanceInch = duration/148;
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.print(" cm/");
  Serial.print(distanceInch);
  Serial.println(" in");
  readChar.writeValue(distanceCm);
  if (distanceCm>threshold) {
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
  }
  else {
    digitalWrite(4,HIGH);
    digitalWrite(2,LOW); 
  }
  delay(1000);
}


