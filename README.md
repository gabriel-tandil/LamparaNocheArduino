# LamparaNocheArduino
Lampara de Noche RGB con Arduino con un solo botón.

Usa la biblioteca OneButtonLibrary de Matthias Hertel http://www.mathertel.de

## Nota
Los ledes se deben conectar a pines PWM del arduino.

## Matriz de transicion de Estados

|Estado / Evento         |Pulsación corta     |Pulsación doble     |Pulsación larga|Reloj :alarm_clock:|
|         :---:          |--------------------|--------------------|---------------|-------------------|
|**Apagado**             |Prendido            |Apagado             |Dormir         |                   |
|**Prendido**            |Apagado             |Conf. Rojo          |Dormir         |                   |
|**Conf. Rojo**          |Conf. Rojo          |Conf. Verde         |Prendido       |Prendido (4 seg.)  |
|**Conf. Verde**         |Conf. Verde         |Conf. Azul          |Prendido       |Prendido (4 seg.)  |
|**Conf. Azul**          |Conf. Azul          |Conf. Brillo        |Prendido       |Prendido (4 seg.)  |
|**Conf. Brillo**        |Conf. Brillo        |Prendido            |Prendido       |Prendido (4 seg.)  |
|**Dormir**              |Apagado             |Conf. Brillo Dormir |Prendido       |Apagado  (20 min.) |
|**Conf. Brillo Dormir** |Conf. Brillo Dormir |Conf. Periodo Dormir|Dormir         |Dormir   (4 seg.)  |
|**Conf. Periodo Dormir**|Conf. Periodo Dormir|Dormir              |Dormir         |Dormir   (4 seg.)  |

## Constantes
Todos los valores son parametrizables mediante constantes

```c
const byte ROJO = 5;  // Pata led rojo
const byte VERDE = 3; // Pata led verde
const byte AZUL = 6;  // Pata led azul

const byte BOTON = A1;// Pata boton pulsador

const long TIEMPO_DORMIR=2000000;
const long TIEMPO_CONFIG=4000;
```
