#include <Keypad.h>
#include <Servo.h>

// Configuração do teclado 4x4
const byte ROWS = 4; // Número de linhas
const byte COLS = 4; // Número de colunas
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Pinos conectados às linhas do teclado
byte colPins[COLS] = {5, 4, 3, 2}; // Pinos conectados às colunas do teclado

// Inicializa o teclado
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Definindo o pino do servo
const int servoPin = 10; 
Servo myServo;

// Código correto
const char correctCode[] = "1234";
char inputCode[4];
int codeIndex = 0;

void setup() {
  Serial.begin(9600); // Inicializa o Monitor Serial
  Serial.println("Digite o código de 4 digitos...");
  
  // Conecta o servo ao pino 10
  myServo.attach(servoPin); 
}

void loop() {
  // Lê a tecla pressionada
  char key = keypad.getKey();

  // Se uma tecla for pressionada
  if (key) {
    Serial.print("Tecla pressionada: ");
    Serial.println(key);
    
    // Adiciona o dígito ao código de entrada
    if (codeIndex < 4) {
      inputCode[codeIndex] = key;
      codeIndex++;
    }

    // Se o código de 4 dígitos for inserido
    if (codeIndex == 4) {
      // Verifica se o código está correto
      inputCode[codeIndex] = '\0';  // Finaliza a string
      if (strcmp(inputCode, correctCode) == 0) {
        Serial.println("Código correto!");
        Serial.println("Servo girando...");
        
        // Move o servo de forma suave
        for (int pos = 0; pos <= 90; pos++) { // Move de 0 a 90 graus
          myServo.write(pos);
          delay(20);  // Espera para mover lentamente
        }
        
        delay(2000);  // Aguarda 2 segundos
        
        // Move o servo de volta para 0 graus
        for (int pos = 90; pos >= 0; pos--) { // Move de 90 a 0 graus
          myServo.write(pos);
          delay(20);  // Espera para mover lentamente
        }
        
        delay(2000);  // Aguarda 2 segundos
      } else {
        Serial.println("Código incorreto!");
      }

      // Reseta para o próximo código
      codeIndex = 0;
      memset(inputCode, 0, sizeof(inputCode));  // Limpa o código de entrada
      Serial.println("Tente novamente...");
    }
  }
}