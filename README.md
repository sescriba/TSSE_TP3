# CESE Testing de Software en Sistemas Embebidos

## Driver para módulo IMU MPU9250


### Introducción
El proyecto contenido en este repositorio formula un Driver genérico para un IMU (Unidad de Medición Inercial, por sus siglas en inglés) MPU9250 que, mediante comunicación I2C, permite obtener los valores del Giroscopio, aceleración y temperatura medidos por el dispositivo. Dada su portabilidad, es posible cambiar de sensor inercial simplemente modificando las direcciones de los registros intervinientes. También es posible alternar el protocolo de comunicación sin necesidad de modificar el alto nivel del software.

### Implementación
El driver es del tipo no bloqueante mediante el uso de interrupciones. A su vez se encuentra modularizado en capas según el diagrama a continuación.

    dev
    ├── inc 
    │   ├── mpu9250.h 
    │   └── port.h 
    └── src 
        ├── mpu9250.c 
        └── port.c 

### Testing
Para el test del driver se implementan pruebas unitarias a traves del uso de la libreria Unity y se corren mediante la herramienta Ceedling
