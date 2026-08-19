#include <Servo.h>

// Definição dos pinos
#define SERVO1_PIN 3
#define SERVO2_PIN 5

// Objetos Servo
Servo servo1;
Servo servo2;

// Variáveis para armazenar os ângulos atuais
int currentAngle1 = 0;
int currentAngle2 = 0;

// Buffer para receber comandos
String inputString = "";
boolean stringComplete = false;

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);
  
  // Aguarda a serial estabilizar
  delay(100);
  
  // Anexa os servos aos pinos
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  
  // Posiciona os servos no ângulo inicial (0°)
  servo1.write(0);
  servo2.write(0);
  
  // Reserva 100ms para os servos se moverem
  delay(100);
  
  // Mensagem de inicialização
  Serial.println("Sistema de Servos iniciado");
  Serial.println("Aguardando comandos...");
  Serial.println("Formato: S1:<angulo> ou S2:<angulo>");
}

void loop() {
  // Verifica se há dados disponíveis na serial
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    
    // Verifica se é o caractere de final de linha
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      // Adiciona o caractere ao buffer (ignora \r)
      if (inChar != '\r') {
        inputString += inChar;
      }
    }
  }
  
  // Processa o comando quando recebido completamente
  if (stringComplete) {
    processCommand(inputString);
    
    // Limpa o buffer para o próximo comando
    inputString = "";
    stringComplete = false;
  }
}

void processCommand(String command) {
  // Remove espaços extras
  command.trim();
  
  // Verifica se o comando está vazio
  if (command.length() == 0) {
    return;
  }
  
  // Encontra a posição do separador ':'
  int separatorIndex = command.indexOf(':');
  
  // Verifica se o separador existe
  if (separatorIndex == -1) {
    Serial.println("ERRO: Comando inválido (formato esperado: S1:90)");
    return;
  }
  
  // Extrai o ID do servo e o ângulo
  String servoID = command.substring(0, separatorIndex);
  String angleStr = command.substring(separatorIndex + 1);
  
  // Converte o ângulo para inteiro
  int angle = angleStr.toInt();
  
  // Valida o ângulo (0-180)
  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;
  
  // Processa o comando baseado no ID do servo
  if (servoID == "S1") {
    servo1.write(angle);
    currentAngle1 = angle;
    
    // Confirmação para o PC
    Serial.print("OK S1:");
    Serial.println(angle);
    
  } else if (servoID == "S2") {
    servo2.write(angle);
    currentAngle2 = angle;
    
    // Confirmação para o PC
    Serial.print("OK S2:");
    Serial.println(angle);
    
  } else {
    // Comando desconhecido
    Serial.print("ERRO: ID desconhecido - ");
    Serial.println(servoID);
  }
}

// Função para debug - pode ser chamada para testar comandos manualmente
void testServo(int servoNumber, int angle) {
  if (servoNumber == 1) {
    servo1.write(angle);
    currentAngle1 = angle;
    Serial.print("Teste S1:");
    Serial.println(angle);
  } else if (servoNumber == 2) {
    servo2.write(angle);
    currentAngle2 = angle;
    Serial.print("Teste S2:");
    Serial.println(angle);
  }
}