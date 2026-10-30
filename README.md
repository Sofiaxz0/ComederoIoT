Comedero IoT: 
Es un sistema IoT que detecta, con un sensor infrarrojo, si hay un objeto (comida) frente al sensor y envía el dato por MQTT a Node-RED, se guarda en la base de datos y lo muestra en un dashboard.

Hardware:
ESP32 (DevKit V1)
Sensor infrarrojo de presencia (tipo FC-51)
-> Alimentación: 3V3
Servomotor GG90
-> Alimentación 5v

Software:
Arduino IDE
EMQX (en Docker)
Node-RED (en Docker) - Flujo y Dashboard
PostgreSQL <- pgAdmin

Flujo actual en Node-RED
<img width="825" height="200" alt="image" src="https://github.com/user-attachments/assets/13862143-5b96-462b-bd58-9682298b73be" />

