#define TRIG 15
#define ECHO 14
void getDistance() {
  long duration;
  int distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.0343 / 2;
  Serial.println("distance: " + String(distance));
}
void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(ECHO, INPUT);    // chân echo sẽ nhận tín hiệu
}

void loop() {
  getDistance();
  delay(1000);
}
