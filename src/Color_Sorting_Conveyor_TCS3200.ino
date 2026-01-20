#include <Servo.h>

// ---------- TCS3200 Color Sensor Pins ----------
#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define sensorOut 7

// ---------- L298N Motor Driver Pins ----------
#define ENA 8   // PWM
#define IN1 11
#define IN2 12

// ---------- IR Sensor ----------
#define IRSENSOR 2  // NOTE: here LOW = object detected (change if your sensor is opposite)

// ---------- Servos ----------
#define SERVO_RED_PIN   9
#define SERVO_BLUE_PIN 10

Servo servoRed;
Servo servoBlue;

unsigned long R_val, G_val, B_val;

void setup() {
  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IRSENSOR, INPUT);

  // TCS3200 frequency scaling = 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  servoRed.attach(SERVO_RED_PIN);
  servoBlue.attach(SERVO_BLUE_PIN);

  servoRed.write(0);
  servoBlue.write(0);

  // Stop motor at start
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  Serial.println("System Ready...");
  Serial.println("R\tG\tB\tDetectedColor");
}

static void runConveyor(uint8_t speedPWM, unsigned long ms) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedPWM);
  delay(ms);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

static void readRGB() {
  // Red
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  R_val = pulseIn(sensorOut, LOW);

  // Green
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  G_val = pulseIn(sensorOut, LOW);

  // Blue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  B_val = pulseIn(sensorOut, LOW);
}

static String classifyColor() {
  // Basic logic: smaller pulse width => stronger color
  bool isRed = (R_val < (G_val - 20) && R_val < (B_val - 20));
  bool isBlue = (B_val < (R_val - 20) && B_val < (G_val - 20));
  bool isWhite =
    (abs((long)R_val - (long)G_val) < 25) &&
    (abs((long)G_val - (long)B_val) < 25) &&
    (abs((long)R_val - (long)B_val) < 25);

  if (isRed) return "RED";
  if (isBlue) return "BLUE";
  if (isWhite) return "WHITE";
  return "UNKNOWN";
}

void loop() {
  bool objectHere = (digitalRead(IRSENSOR) == LOW);
  if (!objectHere) {
    delay(100);
    return;
  }

  readRGB();
  String detectedColor = classifyColor();

  if (detectedColor == "RED") {
    servoRed.write(90);
    runConveyor(200, 1000);
    servoRed.write(0);
  }
  else if (detectedColor == "BLUE") {
    servoBlue.write(90);
    runConveyor(200, 1000);
    servoBlue.write(0);
  }
  else if (detectedColor == "WHITE") {
    runConveyor(200, 1000);
  }
  // UNKNOWN: do nothing (or you can still run conveyor)

  Serial.print(R_val); Serial.print("\t");
  Serial.print(G_val); Serial.print("\t");
  Serial.print(B_val); Serial.print("\t");
  Serial.println(detectedColor);

  delay(200);
}
