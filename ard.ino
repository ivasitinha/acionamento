#include <Servo.h>

Servo servo1;
Servo servo2;

const int LED1_PIN = 2;
const int LED2_PIN = 3;
const int SERVO1_PIN = 9;
const int SERVO2_PIN = 10;

void setup() {
  Serial.begin(9600);

  // Conecta os servos aos pinos
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);

  // Configura os pinos dos LEDs
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  // Posição inicial (90 graus) e LEDs desligados
  servo1.write(90);
  servo2.write(90);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    // Interpreta comandos no formato "SERVO:ANGULO" (ex: "1:180" ou "2:45")
    int colonIndex = input.indexOf(':');
    if (colonIndex != -1) {
      int servoNum = input.substring(0, colonIndex).toInt();
      int angle = input.substring(colonIndex + 1).toInt();

      if (servoNum == 1) {
        digitalWrite(LED1_PIN, HIGH);
        servo1.write(angle);
        delay(100);
        digitalWrite(LED1_PIN, LOW);
      }
      else if (servoNum == 2) {
        digitalWrite(LED2_PIN, HIGH);
        servo2.write(angle);
        delay(100);
        digitalWrite(LED2_PIN, LOW);
      }
    }
  }
}
