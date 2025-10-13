#include <Servo.h>

#define _DUTY_MIN 1000
#define _DUTY_MAX 2000
#define TRIG 12
#define ECHO 13
#define LED 9
#define SERVO_PIN 10
#define _DIST_MIN 18
#define _DIST_MAX 36

Servo myservo;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  myservo.attach(SERVO_PIN);
}

void loop() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(10);
  digitalWrite(TRIG, HIGH);

  long duration = pulseIn(ECHO, HIGH);
  if (duration == 0) return;

  float distance = duration * 0.034 / 2;
  Serial.println(distance);

  if (distance >= _DIST_MIN && distance <= _DIST_MAX) {
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }

  float angle;
  if (distance <= _DIST_MIN) angle = 0;
  else if (distance >= _DIST_MAX) angle = 180;
  else angle = map(distance, _DIST_MIN, _DIST_MAX, 0, 180);

  int pulse = map(angle, 0, 180, _DUTY_MIN, _DUTY_MAX);
  myservo.writeMicroseconds(pulse);

  delay(50);
}


