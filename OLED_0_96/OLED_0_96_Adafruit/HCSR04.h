#pragma once
#define TRIG 15
#define ECHO 14

class HCSR04
{
  public:
    HCSR04() {
      pinMode(TRIG, OUTPUT);   // chân trig sẽ phát tín hiệu
      pinMode(ECHO, INPUT);    // chân echo sẽ nhận tín hiệu
    }
    long getDistance() {
      long duration;
      long distance;
      digitalWrite(TRIG, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG, LOW);
      duration = pulseIn(ECHO, HIGH);
      distance = duration * 0.0343 / 2;
      return distance;
    }
};
