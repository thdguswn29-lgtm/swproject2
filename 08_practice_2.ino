#define PIN_LED  9
#define PIN_TRIG 12
#define PIN_ECHO 13

#define SND_VEL 346.0
#define INTERVAL 25
#define PULSE_DURATION 10
#define _DIST_MIN 100.0
#define _DIST_MAX 300.0

#define TIMEOUT ((INTERVAL / 2) * 1000.0)
#define SCALE (0.001 * 0.5 * SND_VEL)

unsigned long last_sampling_time;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  
  pinMode(PIN_ECHO, INPUT);   
  digitalWrite(PIN_TRIG, LOW);  
  Serial.begin(57600);
}

void loop() { 
  float distance;

  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO);

  if ((distance == 0.0) || (distance > _DIST_MAX)) {
      distance = _DIST_MAX + 10.0;    
      analogWrite(PIN_LED, 255);
  } else if (distance < _DIST_MIN) {
      distance = _DIST_MIN - 10.0;    
      analogWrite(PIN_LED, 255);
  } else {    
      int duty = calcLEDBrightness(distance);
      analogWrite(PIN_LED, duty);
  }

  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(", distance:"); Serial.print(distance);
  Serial.print(", Max:");      Serial.print(_DIST_MAX);
  Serial.print(", duty:");     Serial.print(calcLEDBrightness(distance));
  Serial.println("");

  last_sampling_time += INTERVAL;
}

float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE;
}

int calcLEDBrightness(float dist) {
  if (dist < _DIST_MIN || dist > _DIST_MAX) return 255;
  float duty = 255.0 * (abs(dist - 200.0) / 100.0);
  int result = constrain((int)duty, 0, 255);
  return result;
}
