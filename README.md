# Estación de Monitoreo Ambiental Autónoma - Laboratorio I

Proyecto final para la materia **Laboratorio I** (2025) en la Universidad Blas Pascal.

**Integrantes:**
* Ignacio Truffa
* Joaquina Pacheco
* Mateo Donda
* Milagros Pereyra

---

## 1. Descripción del Proyecto

El objetivo fue diseñar y construir un prototipo funcional capaz de medir, registrar y visualizar variables ambientales (temperatura, humedad, luminosidad y gases) de manera continua y autónoma. El sistema integra un sensor MQ-2 como elemento diferenciador, almacena datos en una tarjeta SD y muestra valores en una pantalla LCD.

## 2. Componentes Principales

* **MCU:** Arduino Uno
* **Sensores:**
    * Sensor DHT22 (Temperatura y Humedad)
    * Sensor LDR (Luz ambiental)
    * Sensor MQ-2 (Gases/Humo)
* **Módulos:**
    * Módulo RTC DS3231 (Fecha/Hora)
    * Módulo microSD (Registro de datos)
    * Pantalla LCD I2C 16x2
    * Buzzer pasivo (Alerta sonora)

## 3. Contenido del Repositorio

Este repositorio contiene todos los entregables solicitados por la cátedra:

* **firmware/**: Contiene el código fuente (`.ino`) final para Arduino IDE.
* **stl/**: Contiene los archivos `.stl` del diseño 3D de la carcasa realizada en Tinkercad.
* **datasheets/**: Contiene las hojas de datos (PDF) de los componentes electrónicos clave.

## 4. Estado Final del Proyecto

* **Núcleo del Sistema:** 100% funcional (Lectura de sensores, registro en microSD y alertas sonoras).
* **Carcasa:** Diseñada. (Nota: Para la defensa se utilizó una carcasa prestada por motivos externos).
* **App Móvil (Bluetooth):** En desarrollo. Se logró conexión pero no la visualización de datos en MIT App Inventor.
