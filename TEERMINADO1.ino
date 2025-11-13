#include <SoftwareSerial.h>

#include <ThreeWire.h>

#include <RtcDS1302.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <DHT.h>

#include <SD.h>

// ---------- LCD ----------

LiquidCrystal_I2C lcd(0x27, 16, 2); // Cambia 0x27 si tu módulo usa otra dirección

// ---------- DS1302 ----------

const int IO   = 4;  // DAT

const int SCLK = 3;  // CLK

const int CE   = 5;  // RST

ThreeWire myWire(IO, SCLK, CE);

RtcDS1302<ThreeWire> Rtc(myWire);

// ---------- DHT11 ----------

#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ---------- LDR ----------

#define LDR_PIN A1

// ---------- MicroSD ----------

#define SD_CS 9

// estado SD y reintentos ---

bool sd_ok = false;

unsigned long lastSdRetry = 0;

const unsigned long sdRetryEvery = 2000; // reintento cada 2 s

// ---------- Variables ----------

int luzPct = 0;

int fireDigital = 0;

unsigned long previousMillis = 0;

const unsigned long interval = 1000; // 1 segundo

void setup() {

  Serial.begin(9600);     // Monitor serie (USB)

  lcd.begin();

  lcd.backlight();

  dht.begin();

  // ---- RTC ----

  Rtc.Begin();

  Rtc.SetIsWriteProtected(false);  // por si estaba protegido

  RtcDateTime nowRTC = Rtc.GetDateTime();

  if (nowRTC.Year() < 2024 || nowRTC.Year() > 2099) {

    Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));  // fuerza año correcto una vez

  }

  if (Rtc.GetIsWriteProtected()) {

    Rtc.SetIsWriteProtected(false);

  }

  if (!Rtc.IsDateTimeValid()) {

    Serial.println(F("RTC sin hora válida, seteando compilación"));

    RtcDateTime compiled(__DATE__, __TIME__);

    Rtc.SetDateTime(compiled);

  }

  // ---- Sensor fuego ----

  pinMode(FIRE_DO, INPUT);

  // ---- SD ----

  pinMode(10, OUTPUT); // UNO como SPI master (esencial)

  sd_ok = SD.begin(SD_CS);

  if (!sd_ok) {

   Serial.println("Error al inicializar la tarjeta SD");

  } else {

    Serial.println("SD inicializada correctamente");

  }

}  // <- cierre de setup (ESENCIAL)

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis < interval) return;

  previousMillis = currentMillis;

  // ---------- RTC ----------

  RtcDateTime now = Rtc.GetDateTime();

  if (!now.IsValid()) {

    Serial.println(F("RTC perdió la confianza en la hora!"));

  }

  // ---------- DHT ----------

  float temp = dht.readTemperature();

  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {

    temp = 0; hum = 0;           // valores de seguridad

    Serial.println(F("Error DHT11"));

  }

  // ---------- LDR ----------

  int luzRaw = analogRead(LDR_PIN);

  luzPct = map(luzRaw, 0, 1023, 0, 100);

  // ---------- Fuego ----------

  fireDigital = digitalRead(FIRE_DO);                    // (ESENCIAL para el bloque SD)

  String fuego = (digitalRead(FIRE_DO) == LOW) ? "ON" : "OFF";

  // ---------- Fecha/Hora en char[] para SD (ESENCIAL) ----------

  char datestring[30];

  snprintf_P(datestring, sizeof(datestring), PSTR("%02u/%02u/%04u %02u:%02u:%02u"),

             now.Day(), now.Month(), now.Year(),

             now.Hour(), now.Minute(), now.Second());

  // ---------- Fecha/Hora en un solo String ----------

  String fechaHora = String(now.Day()) + "/" +

                     String(now.Month()) + "/" +

                     String(now.Year()) + " " +

                     String(now.Hour()) + ":" +

                     String(now.Minute()) + ":" +

                     String(now.Second());

  // ---------- Construir toda la línea ----------

  String datos =  String(temp, 1) + "C | " +  

                  String(hum, 0) + "% | " +

                  String(luzPct) + "% | " +

                  fuego + " | " +

                  fechaHora + " | ";

  // ---------- Depuración por USB ----------

  Serial.println(datos);

// ---------- Guardar en SD ----------

if (sd_ok) {

  File dataFile = SD.open("datalog.csv", FILE_WRITE);  // crea/abre en modo append

  if (dataFile) {

    // Si el archivo recién se crea, escribimos encabezado

    if (dataFile.size() == 0) {

      dataFile.println("FechaHora,Temperatura,Humedad,Luz,Fuego");

    }

    // Escribimos los datos separados por comas

    dataFile.print(datestring); dataFile.print(",");

    dataFile.print(temp, 1);    dataFile.print(",");

    dataFile.print(hum, 0);     dataFile.print(",");

    dataFile.print(luzPct);     dataFile.print(",");

    if (fireDigital == LOW) dataFile.println("ON");

    else dataFile.println("OFF");

    dataFile.close();

  } else {

    Serial.println("Error al abrir datalog.csv");

    sd_ok = false;

    lastSdRetry = millis();

  }

} else {

  // Reintento no bloqueante cada 2 s si la SD no está

  if (millis() - lastSdRetry >= sdRetryEvery) {

    Serial.println("Reintentando SD.begin()...");

    sd_ok = SD.begin(SD_CS);

    lastSdRetry = millis();

    if (sd_ok) Serial.println("SD detectada nuevamente");

  }

}


  // ---------- LCD ----------

  lcd.clear();

  lcd.setCursor(0, 0);

  if (now.Hour() < 10) lcd.print('0');

  lcd.print(now.Hour()); lcd.print(':');

  if (now.Minute() < 10) lcd.print('0');

  lcd.print(now.Minute());

  lcd.print(" T:");

  lcd.print(temp, 1); lcd.print("C");

  lcd.setCursor(0, 1);

  lcd.print("H:"); lcd.print(hum, 0); lcd.print("% ");

  lcd.print("L:"); lcd.print(luzPct); lcd.print("% ");

  lcd.print("F:"); lcd.print(fuego);

}
 
