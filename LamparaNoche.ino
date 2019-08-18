/*
LamparaNoche.ino
 
 This sketch use the OneButtonLibrary to detect diferent events on a button.
 
 OneButtonLibrary Copyright (c) by Matthias Hertel, http://www.mathertel.de
 
 **/
#include "OneButton.h"

//ACCIONES
const byte CORTO = 0;
const byte LARGO = 1;
const byte DOBLE = 2;
const byte NINGUNA = 3;

//ESTADAOS
const byte APAGADO = 0;
const byte PRENDIDO = 1;
const byte DORMIR = 2;
const byte C_ROJO = 3;
const byte C_VERDE = 4;
const byte C_AZUL = 5;

const byte ROJO = 5;
const byte VERDE = 3;
const byte AZUL = 6;

const byte BOTON = A1;
const byte NIVEL[5]={
  0,20,80,150,255};

const byte TRANSICION_ESTADO[6][3]={
  {
    PRENDIDO,DORMIR,APAGADO          }
  ,
  {
    APAGADO,DORMIR,C_ROJO          }
  ,
  {
    APAGADO,PRENDIDO,C_ROJO          }
  ,
  {
    C_ROJO,PRENDIDO,C_VERDE          }
  ,
  {
    C_VERDE,PRENDIDO,C_AZUL          }
  ,
  {
    C_AZUL,PRENDIDO,PRENDIDO          }
};
const long TIEMPO_DORMIR=2000000;
const long TIEMPO_CONFIG=4000;
const int PERIODO = 9000;
const int DESPLAZAMIENTO1 = 3000;
const int DESPLAZAMIENTO2 = 6000;
const byte B_DORMIR=10;

// light connected to digital pin 11
long timeEstado=0;

// Setup a new OneButton on pin 5.
OneButton button(A1, true);

byte estado = APAGADO; // no action when starting
byte accion=NINGUNA;
byte nivelRojo=2;
byte nivelVerde=2;
byte nivelAzul=2;

// setup code here, to run once.
void setup() {
 //  Serial.begin(9600);

  // enable the standard led on pin 13.
  pinMode(ROJO, OUTPUT); // rojo
  pinMode(VERDE, OUTPUT); // verde 
  pinMode(AZUL, OUTPUT); // azul
  button.attachClick(myClickFunction);
  button.attachDoubleClick(myDoubleClickFunction);
  button.attachPress(myLongClickFunction);
  // set 80 msec. debouncing time. Default is 50 msec.
  button.setDebounceTicks(80);
} 


// main code here, to run repeatedly:
void loop() {

  button.tick();

  long time = millis();
  if (estado == APAGADO) {
    digitalWrite(ROJO, LOW);
    digitalWrite(VERDE, LOW);
    digitalWrite(AZUL, LOW);

  } 
  else if (estado == PRENDIDO) {
    analogWrite(ROJO, NIVEL[nivelRojo]);
    analogWrite(VERDE, NIVEL[nivelVerde]);
    analogWrite(AZUL, NIVEL[nivelAzul]);

  } 
  else if (estado == DORMIR) {
    if (time-timeEstado>TIEMPO_DORMIR)
      estado=APAGADO;

    byte valueR = B_DORMIR+B_DORMIR*cos(2*PI/PERIODO*time);
    byte valueG = B_DORMIR+B_DORMIR*cos(2*PI/PERIODO*(DESPLAZAMIENTO1-time));
    byte valueB = B_DORMIR+B_DORMIR*cos(2*PI/PERIODO*(DESPLAZAMIENTO2-time));
    analogWrite(ROJO, valueR);           
    analogWrite(VERDE, valueG);           
    analogWrite(AZUL, valueB);           
      // Serial.print(valueR);
     //  Serial.print(" ");
      // Serial.print(valueG);
     //  Serial.print(" ");
     //  Serial.println(valueB);

  } 
  else if (estado == C_ROJO) {
    if (time-timeEstado>TIEMPO_CONFIG)
      estado=PRENDIDO;

    digitalWrite(VERDE, LOW);
    digitalWrite(AZUL, LOW);
    analogWrite(ROJO, NIVEL[nivelRojo]);

    if (accion==CORTO){
      nivelRojo++;
      nivelRojo%=5;
    }

  } 
  else if (estado == C_VERDE) {
    if (time-timeEstado>TIEMPO_CONFIG)
      estado=PRENDIDO;

    digitalWrite(ROJO, LOW);
    digitalWrite(AZUL, LOW);
    analogWrite(VERDE, NIVEL[nivelVerde]);
    if (accion==CORTO){
      nivelVerde++;
      nivelVerde%=5;
    }

  } 
  else if (estado == C_AZUL) {
    if (time-timeEstado>TIEMPO_CONFIG)
      estado=PRENDIDO;

    digitalWrite(ROJO, LOW);
    digitalWrite(VERDE, LOW);
    analogWrite(AZUL, NIVEL[nivelAzul]); 
    if (accion==CORTO){
      nivelAzul++;
      nivelAzul%=5;

    }

  }

  if (accion!=NINGUNA){
    estado=TRANSICION_ESTADO[estado][accion];
    timeEstado= millis();
  }
  // Serial.print(nivelRojo);
  // Serial.print(" ");
  //  Serial.print(nivelVerde);
  // Serial.print(" ");
  // Serial.println(nivelAzul);

  accion=NINGUNA;
  delay(10);
}


void indicarConfiguracion(byte color,byte brillo){
  digitalWrite(ROJO, LOW);
  digitalWrite(VERDE, LOW);
  digitalWrite(AZUL, LOW);
  analogWrite(color, brillo);
  delay(20);
}

void myClickFunction() {
  //  Serial.println("corto");
  accion=CORTO;
}

void myDoubleClickFunction() {
  //  Serial.println("doble");
  accion=DOBLE;
}

void myLongClickFunction() {
  // Serial.println("largo");
  accion=LARGO;
}




