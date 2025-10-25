#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2      
#define DHTTYPE DHT22 

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

int ledY = 3; // LED para temperatura alta
int ledO = 4; // LED para umidade baixa

void setup() {
  Serial.begin(9600);  
  Wire.begin();  
  dht.begin();

  lcd.init();       
  lcd.backlight();  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");

  pinMode(ledY, OUTPUT);
  pinMode(ledO, OUTPUT);
}

void loop() {
  delay(2000); 

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Falha ao ler o sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro no Sensor");
    return;
  }

  // Exibe valores
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);  
  lcd.write(0xDF);  
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Umidade: ");
  lcd.print(humidity, 1);  
  lcd.print("%");

  // LED controle
  if (temperature > 28) {
    digitalWrite(ledY, HIGH);
  } else {
    digitalWrite(ledY, LOW);
  }

  if (humidity < 40) {
    digitalWrite(ledO, HIGH);
  } else {
    digitalWrite(ledO, LOW);
  }

  
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print(" *C  ");
  Serial.print("Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");
}
