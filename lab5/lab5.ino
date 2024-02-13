const int trigPin = 11;
const int echoPin = 12;
long duration;
int distanceCm, distanceInch;
int threshold = 5; // in cm

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(2,OUTPUT) //red (on when distance > threshold)
  pinMode(4,OUTPUT) //green (on when distance < or = threshold)

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


