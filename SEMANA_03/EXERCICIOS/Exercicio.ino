#define LED1 9
#define LED2 3
#define LED3 17
#define LED4 7
#define BUZZER 11
#define BOTAO1 5
#define BOTAO2 6
#define LDR 18

int salvos[15] = {};
int contador = 0;

int converter() {
  int LDR_valor = analogRead(LDR);
  int valor = map(LDR_valor, 32, 4095, 0, 15);

  return valor;
}

void tocar(int iluminacao) {
  switch (iluminacao) {
    case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 1:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      break;
    case 2:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break;
    case 3:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      break;
    case 4:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 5:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      break;
    case 6:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break;
    case 7:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      break;
    case 8:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 9:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      break;
    case 10:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break;
    case 11:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      break;
    case 12:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 13:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      break;
    case 14:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break;
    case 15:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      break;
  }
  tone(BUZZER, iluminacao * 50, 20);
  delay(1000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  noTone(BUZZER);
}

void salvar(int iluminacao) {
  if (contador < 15) {
    salvos[contador] = iluminacao;
    contador++;
    tocar(iluminacao);
  }
}

void executar() {
  for (int i = 0; i < contador; i++) {
    int iluminacao = salvos[i];
    tocar(iluminacao);
  }
  salvos[15] = {};
  contador = 0;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BOTAO1, INPUT_PULLUP);
  pinMode(BOTAO2, INPUT_PULLUP);
  pinMode(LDR, OUTPUT);
}


void loop() {
  if (digitalRead(BOTAO1) == LOW) {
    int iluminacao = converter();
    salvar(iluminacao);
  }
  if (digitalRead(BOTAO2) == LOW) {
    executar();
  }
}
