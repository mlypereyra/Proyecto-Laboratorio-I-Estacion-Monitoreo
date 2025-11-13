# Estación de Monitoreo Ambiental Autónoma - Laboratorio I

[cite_start]Proyecto final para la materia **Laboratorio I** (2025) en la Universidad Blas Pascal[cite: 5].

**Integrantes:**
* Ignacio Truffa
* Joaquina Pacheco
* Mateo Donda
* Milagros Pereyra

---

## 1. Descripción del Proyecto

[cite_start]El objetivo fue diseñar y construir un prototipo funcional capaz de medir, registrar y visualizar variables ambientales (temperatura, humedad, luminosidad y gases) de manera continua y autónoma[cite: 15]. [cite_start]El sistema integra un sensor MQ-2 como elemento diferenciador [cite: 20][cite_start], almacena datos en una tarjeta SD [cite: 19] [cite_start]y muestra valores en una pantalla LCD[cite: 19].

## 2. Componentes Principales

* [cite_start]**MCU:** Arduino Uno [cite: 67]
* **Sensores:**
    * [cite_start]Sensor DHT22 (Temperatura y Humedad) [cite: 67]
    * [cite_start]Sensor LDR (Luz ambiental) [cite: 67]
    * [cite_start]Sensor MQ-2 (Gases/Humo) [cite: 67]
* **Módulos:**
    * [cite_start]Módulo RTC DS3231 (Fecha/Hora) [cite: 67]
    * [cite_start]Módulo microSD (Registro de datos) [cite: 67]
    * [cite_start]Pantalla LCD I2C 16x2 [cite: 67]
    * [cite_start]Buzzer pasivo (Alerta sonora) [cite: 67]

## 3. Contenido del Repositorio

[cite_start]Este repositorio contiene todos los entregables solicitados por la cátedra:

* [cite_start]`/firmware/`: Contiene el código fuente (`.ino`) final para Arduino IDE.
* [cite_start]`/stl/`: Contiene los archivos `.stl` del diseño 3D de la carcasa realizada en Tinkercad[cite: 112, 393].
* [cite_start]`/datasheets/`: Contiene las hojas de datos (PDF) de los componentes electrónicos clave.

## 4. Estado Final del Proyecto

* [cite_start]**Núcleo del Sistema:** 100% funcional (Lectura de sensores, registro en microSD [cite: 103] [cite_start]y alertas sonoras [cite: 102]).
* [cite_start]**Carcasa:** Diseñada[cite: 112]. [cite_start](Nota: Para la defensa se utilizó una carcasa prestada por motivos externos [cite: 118, 119]).
* **App Móvil (Bluetooth):** En desarrollo. [cite_start]Se logró conexión [cite: 109] [cite_start]pero no la visualización de datos en MIT App Inventor[cite: 110, 125].
