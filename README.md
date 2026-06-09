# 🌱 Sistema de Riego Inteligente con IA Adaptativa

Sistema de riego automático desarrollado sobre **ESP32 + FreeRTOS**, capaz de monitorizar múltiples zonas de cultivo, analizar condiciones ambientales y optimizar los tiempos de riego mediante un sistema de aprendizaje adaptativo.

---

## 📋 Descripción

Este proyecto implementa un sistema de riego inteligente dividido en cuatro zonas independientes. Utiliza sensores de humedad del suelo, temperatura ambiente, detección de lluvia y predicción meteorológica para tomar decisiones automáticas sobre cuándo y cuánto regar.

Además, incorpora una interfaz web en tiempo real y mecanismos avanzados de FreeRTOS como:

- Event Groups
- Software Timers
- Task Notifications
- Watchdog de aplicación
- Persistencia de datos mediante NVS
- Aprendizaje adaptativo basado en eficiencia de riego

---

# 🚀 Características principales

## 🌡️ Monitorización ambiental

- Sensor DHT22 para temperatura y humedad ambiente.
- 4 sensores capacitivos de humedad del suelo.
- Sensor digital de lluvia.
- Consulta de previsión meteorológica mediante OpenWeatherMap.

## 💧 Gestión inteligente del riego

- Control independiente de 4 electroválvulas.
- Algoritmo de decisión basado en lógica difusa.
- Adaptación automática según:
  - Tipo de planta.
  - Estación del año.
  - Hora del día.
  - Temperatura.
  - Probabilidad de lluvia.
  - Historial de eficiencia.

## 🤖 IA Adaptativa

El sistema aprende automáticamente del resultado de cada riego:

- Registra humedad inicial y final.
- Calcula eficiencia (% de humedad ganada por minuto).
- Ajusta factores de riego dinámicamente.
- Guarda el aprendizaje en memoria NVS para conservarlo tras reinicios.

## 🌐 Interfaz Web

Servidor web embebido en el ESP32 con:

- Visualización en tiempo real.
- Estado de sensores y zonas.
- Estadísticas de aprendizaje IA.
- Control manual de riego.
- Actualización automática mediante WebSockets.
- Diseño responsive para móvil, tablet y PC.

## ⚙️ Funcionalidades FreeRTOS

### Event Groups
Sincronización de finalización de riego entre las cuatro zonas.

### Software Timers
Apagado automático de válvulas sin bloquear tareas.

### Task Notifications
Comunicación eficiente entre tareas.

### Watchdog de Aplicación
Detección y recuperación automática ante bloqueos de tareas.

---

# 🏗️ Arquitectura del Proyecto

```text
Proyecto/
│
├── src/
│   └── main.cpp
│
├── include/
│   └── webpagina.h
│
├── platformio.ini
│
└── data/
```

## main.cpp

Contiene:

- Configuración del hardware.
- Definición de estructuras de datos.
- Gestión de sensores.
- Lógica de planificación del riego.
- Control de válvulas.
- Sistema de IA adaptativa.
- Servidor web.
- Gestión de tareas FreeRTOS.

## webpagina.h

Contiene:

- HTML completo.
- CSS responsive.
- JavaScript.
- Cliente WebSocket.
- Dashboard de monitorización.
- Control manual de riego.

## platformio.ini

Configuración de PlatformIO y dependencias del proyecto.

---

# 📌 Hardware Utilizado

## Microcontrolador

- ESP32 DevKit

## Sensores

- DHT22
- 4 × Sensores capacitivos de humedad del suelo
- Sensor digital de lluvia

## Actuadores

- 4 × Relés
- 4 × Electroválvulas

---

# 🔌 Asignación de Pines

| Elemento | GPIO |
|-----------|--------|
| DHT22 | GPIO 4 |
| Sensor de lluvia | GPIO 5 |
| Válvula Zona 1 | GPIO 13 |
| Válvula Zona 2 | GPIO 12 |
| Válvula Zona 3 | GPIO 14 |
| Válvula Zona 4 | GPIO 27 |
| Humedad Zona 1 | GPIO 34 |
| Humedad Zona 2 | GPIO 35 |
| Humedad Zona 3 | GPIO 32 |
| Humedad Zona 4 | GPIO 33 |

---

# 🧵 Tareas FreeRTOS

| Tarea | Función |
|---------|----------|
| Task_Sensores | Lectura periódica de sensores |
| Task_Meteo_API | Consulta meteorológica |
| Task_Planificador | Cálculo del riego óptimo |
| Task_Valvulas | Gestión de electroválvulas |
| Task_Monitor | Servidor web y monitorización |
| Task_CicloRiego | Sincronización de ciclos |
| Task_Watchdog | Supervisión del sistema |
| Task_IA_Aprendizaje | Aprendizaje adaptativo |

---

# 📶 Configuración WiFi

El ESP32 crea un punto de acceso propio:

```cpp
SSID: RiegoInteligente
Password: riego1234
```

Una vez conectado a la red:

```text
http://192.168.4.1
```

---

# 📦 Dependencias

Configuradas en `platformio.ini`:

```ini
[env:esp32dev]
platform = espressif32@6.5.0
board = esp32dev
framework = arduino

lib_deps =
    adafruit/DHT sensor library
    adafruit/Adafruit Unified Sensor
    bblanchon/ArduinoJson
    AsyncTCP
    ESPAsyncWebServer
    WebSockets
```

---

# 🛠️ Instalación

## 1. Clonar el repositorio

```bash
git clone https://github.com/usuario/riego-inteligente.git
```

## 2. Abrir en PlatformIO

Abrir el proyecto desde Visual Studio Code con la extensión PlatformIO.

## 3. Compilar

```bash
pio run
```

## 4. Cargar al ESP32

```bash
pio run --target upload
```

## 5. Abrir monitor serie

```bash
pio device monitor
```

---

# 📊 Funcionamiento

1. Se leen los sensores cada 30 segundos.
2. Se consulta la previsión meteorológica periódicamente.
3. El planificador analiza las condiciones ambientales.
4. Se calcula el tiempo óptimo de riego.
5. Se activan las válvulas mediante Software Timers.
6. Se registran los resultados del riego.
7. La IA ajusta automáticamente los parámetros para futuros ciclos.

---

# 🔒 Seguridad

- Límites mínimos y máximos de riego.
- Watchdog para recuperación automática.
- Protección mediante Mutex para recursos compartidos.
- Persistencia segura mediante NVS.
- Apagado automático de válvulas mediante temporizadores.

---

# 📈 Futuras Mejoras

- Integración MQTT.
- Dashboard en la nube.
- Aplicación móvil.
- Integración con Home Assistant.
- Notificaciones push.
- Predicción meteorológica avanzada.

---

# 👨‍💻 Autor

Proyecto académico desarrollado para la práctica de sistemas embebidos y FreeRTOS sobre ESP32.

Temas aplicados:

- FreeRTOS
- IoT
- Sistemas en Tiempo Real
- Servidores Web Embebidos
- Inteligencia Adaptativa
- Comunicación WiFi
- Automatización de Riego

---
