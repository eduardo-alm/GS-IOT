#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Sensores
const int pinoTemperatura = A0;
const int pinoLuminosidade = A1;
const int pinoImpacto = 13;

// LEDs de status
const int ledNormal = 8;
const int ledAlerta = 7;

float obterTemperatura() {
  int leitura = analogRead(pinoTemperatura);
  float tensao = leitura * (5.0 / 1023.0);
  return (tensao - 0.5) * 100.0;
}

int obterLuminosidade() {
  return analogRead(pinoLuminosidade);
}

bool detectarImpacto() {
  return digitalRead(pinoImpacto) == LOW;
}

void setup() {
  lcd.begin(16, 2);

  pinMode(ledNormal, OUTPUT);
  pinMode(ledAlerta, OUTPUT);
  pinMode(pinoImpacto, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {

  float temperatura = obterTemperatura();
  int luminosidade = obterLuminosidade();
  bool impactoDetectado = detectarImpacto();

  bool situacaoCritica = false;
  String mensagemLCD = "OPERACAO OK";