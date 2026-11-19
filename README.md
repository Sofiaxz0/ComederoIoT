Comedero IoT: 
Es un sistema IoT que detecta, con un sensor infrarrojo, si hay un objeto (comida) frente al sensor y toma la decisión de abrir o no la compuerta para dejar caer la comida. 

Funcionamiento:
El sensor envía el dato booleano por MQTT a Node-RED y allí se guarda en la base de datos, posteriormente este dato se envia por MQTT al broker MQX en donde el servo toma una decisión dependiendo de lo que llegue, si es un 0 (no hay nada frente al sensor) abre la compuerta y de lo contrario no hace nada. Por otra parte en el dashboard del sensor se muestra si se ha detectado o no un objeto, y en el dashboard del servo se muestra la posición del servomotor (0° o 90°)

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
<img width="1193" height="351" alt="Flujo Node-RED" src="https://github.com/user-attachments/assets/a23bc32b-fe57-4c2f-bc19-a041df9710f9" />


