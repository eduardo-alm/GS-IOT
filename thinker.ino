#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Sensores
const int sensorTemp    = A0;
const int sensorLuz     = A1;
const int botaoVibracao = 13;

// LEDs
const int ledVerde    = 8;
const int ledVermelho = 7;

void setup() {
  lcd.begin(16, 2);
  pinMode(ledVerde,       OUTPUT);
  pinMode(ledVermelho,    OUTPUT);
  pinMode(botaoVibracao,  INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Leitura da temperatura
  int   leituraTemp  = analogRead(sensorTemp);
  float tensao       = leituraTemp * (5.0 / 1023.0);
  float temperatura  = (tensao - 0.5) * 100.0;

  // Leitura da luminosidade
  int luminosidade = analogRead(sensorLuz);

  // Leitura da vibração
  bool vibracaoDetectada = digitalRead(botaoVibracao) == LOW;

  // Alertas
  bool   alerta   = false;
  String mensagem = "NORMAL";

  if (temperatura > 35 && luminosidade < 400 && vibracaoDetectada) {
    alerta  = true;
    mensagem = "TEMP+LUZ+VIB";
  }
  else if (temperatura > 35 && luminosidade < 400) {
    alerta  = true;
    mensagem = "TEMP+LUZ";
  }
  else if (temperatura > 35 && vibracaoDetectada) {
    alerta  = true;
    mensagem = "TEMP+VIB";
  }
  else if (luminosidade < 400 && vibracaoDetectada) {
    alerta  = true;
    mensagem = "LUZ+VIB";
  }
  else if (temperatura > 35) {
    alerta  = true;
    mensagem = "TEMP ALTA";
  }
  else if (luminosidade < 400) {
    alerta  = true;
    mensagem = "LUZ BAIXA";
  }
  else if (vibracaoDetectada) {
    alerta  = true;
    mensagem = "VIBRACAO";
  }

  // Acionamento dos LEDs
  if (alerta) {
    digitalWrite(ledVerde,    LOW);
    digitalWrite(ledVermelho, HIGH);
  } else {
    digitalWrite(ledVerde,    HIGH);
    digitalWrite(ledVermelho, LOW);
  }

  // LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperatura, 1);
  lcd.print("C ");
  lcd.print("L:");
  lcd.print(luminosidade);
  lcd.setCursor(0, 1);
  lcd.print(mensagem);

  delay(500);
}