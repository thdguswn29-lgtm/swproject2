#include <Servo.h>

#define _DUTY_MIN 1000
#define _DUTY_MAX 2000
#define TRIG 12
#define ECHO 13
#define LED 9
#define SERVO_PIN 10
#define _DIST_MIN 18
#define _DIST_MAX 36

float alpha = 0.2;

Servo myservo;
float dist_raw = 0;
float dist_ema = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  myservo.attach(SERVO_PIN);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  if (duration == 0) return;

  dist_raw = duration * 0.034 / 2;

  if (dist_raw < _DIST_MIN || dist_raw > _DIST_MAX) {
    digitalWrite(LED, HIGH);
    return;
  } else {
    digitalWrite(LED, LOW);
  }

  dist_ema = alpha * dist_raw + (1 - alpha) * dist_ema;

  float angle;
  if (dist_ema <= _DIST_MIN) angle = 0;
  else if (dist_ema >= _DIST_MAX) angle = 180;
  else angle = map(dist_ema, _DIST_MIN, _DIST_MAX, 0, 180);

  int pulse = map(angle, 0, 180, _DUTY_MIN, _DUTY_MAX);
  myservo.writeMicroseconds(pulse);

  Serial.print("Raw:");
  Serial.print(dist_raw, 1);
  Serial.print(", EMA:");
  Serial.print(dist_ema, 1);
  Serial.print(", Servo:");
  Serial.println((int)angle);

  delay(50);
}
