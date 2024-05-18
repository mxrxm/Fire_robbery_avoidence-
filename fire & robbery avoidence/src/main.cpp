#include <LiquidCrystal.h>
#include <Arduino.h>

#define FLAME_SENSOR A4
#define BUZZER A3
#define MOTOR_1 A1
#define MOTOR_2 A0
#define MOTOR_SPEED A2

const int TRIG_PIN = 8;
const int ECHO_PIN = 7;
const int RS = 12, E = 11, D4 = 5, D5 = 4, D6 = 6, D7 = 2;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

bool detectFlame = false;
bool detectObject = false;

void setup()
{
  //defining each in as input or output
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(FLAME_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_SPEED, OUTPUT);
//lcd configurations
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
}

void checkFlame()
{
  detectFlame = digitalRead(FLAME_SENSOR) == HIGH;

  if (detectFlame)
  {
    // Flame detected
    lcd.setCursor(0, 1);
    lcd.print("Fire Detected  ");
    digitalWrite(MOTOR_1, HIGH);
    digitalWrite(MOTOR_2, LOW);
    analogWrite(MOTOR_SPEED, 180);
  }
  else
  {
    // No flame detected
    lcd.setCursor(0, 1);
    lcd.print("No Fire       ");
    digitalWrite(MOTOR_1, LOW);
    digitalWrite(MOTOR_2, LOW);
    analogWrite(MOTOR_SPEED, 0);
  }
}

void checkDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long pulseDuration = pulseIn(ECHO_PIN, HIGH);
  float distance = pulseDuration * 0.034 / 2;

  if (distance <= 20)
  {
    // Object too close
    detectObject = true;
    lcd.setCursor(0, 0);
    lcd.print("Object too close");
    digitalWrite(BUZZER, HIGH);
  }
  else
  {
    // Safe distance
    detectObject = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Safe distance  ");
    digitalWrite(BUZZER, LOW);
  }
}

void loop()
{
  checkFlame();
  checkDistance();
}