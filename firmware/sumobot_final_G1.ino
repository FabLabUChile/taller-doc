
// Este codigo es utilzado para programar el comportamiento de un SumoBot. Si los sensores de linea no detectan la linea entonces busca al oponente y
// lo ataca. En caso contrario se aleja del borde de la pista

#include<Button.h> // Librería control del Boton de inicio y fin

// Pin Motores 
int adelanteA = 3; // Sentido adelante del motor izquerdo
int adelanteB = 6; // Sentido adelante del motor derecho
int atrasA = 5; // Sentido atras del motor izquerdo
int atrasB = 9; // Sentido atras del motor derecho

// Botón
int botonpin = 13; // Pin del botón
bool boton = false;
Button boton1(botonpin);


// Pin Sensor ultrasonico
const int Trigger = A0;   //Pin digital A0 para el Trigger del sensor
const int Echo = A1;   //Pin digital A1 para el Echo del sensor

// Pin IR de linea
const int linA = 7;   //Pin digital 7 para el sensor de linea bajo el motor A (izquierdo)
const int linB = 8;   //Pin digital 8 para el sensor de linea bajo el motor B (derecho)

//Potencia máxima y minima en ruedas:
int potmax = 255;

void setup() {
Serial.begin(9600);

// Sensor ultrasonico 
pinMode(Trigger, OUTPUT); //pin como salida
pinMode(Echo, INPUT);  //pin como entrada
digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
// Motores
pinMode(atrasA, OUTPUT);
pinMode(atrasB, OUTPUT);
pinMode (adelanteA, OUTPUT);
pinMode (adelanteB, OUTPUT);
// Sensor de linea
pinMode(linA, INPUT);
pinMode(linB, INPUT);

// Botón
boton1.begin();
}

void loop() {

//++++++++++++++++++++++++++++++++++++++//
// Calculo de distancia del objetivo
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
    
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  delay(10);          //Hacemos una pausa de 10ms
  //++++++++++++++++++++++++++++++++++++++//


// Verificar si se ha presionado el botón y esperar 5 segundos
if (boton1.toggled() && boton1.read() == Button::RELEASED && boton == false){

  delay(5000); // Pausa de 5 segundos
  boton = true;
  }

if (boton == true){
 // Lectura Sensores de linea

  int lineaA = digitalRead(linA);
  int lineaB = digitalRead(linB);
  if (lineaA == HIGH && lineaB == HIGH){ // Si no detecta linea blanca en ningun sensor

    // Si detecta oponente cercano avanza en linea recta
    if (d <= 35) {
      analogWrite(adelanteA, potmax); // Avanzar motor A
      analogWrite(adelanteB, potmax); // Avanzar motor B
      analogWrite(atrasA, 0); 
      analogWrite(atrasB, 0);
      delay(50);
      }

    // Si no detecta oponente cercano gira.
    if (d >= 36) {
      analogWrite(adelanteA, 0);
      analogWrite(adelanteB, potmax);
      analogWrite(atrasA, potmax);
      analogWrite(atrasB, 0);
      delay(50);
    }
  }

    //++++++++++++++++++++++++++++++++++++++//


    // Si detecta los limites de la pista, retrocede.
  if (lineaA == LOW && lineaB == LOW){
    analogWrite(adelanteA,0);
    analogWrite(adelanteB,0);
    analogWrite(atrasA, potmax);
    analogWrite(atrasB, potmax);
    delay(1000); // Retrocede durante 1 segundo
    }

  // Si solo una rueda detecta la pista retrocede y gira
  if (lineaA == HIGH && lineaB == LOW){
    analogWrite(adelanteA,0);
    analogWrite(adelanteB,0);
    analogWrite(atrasA, potmax);
    analogWrite(atrasB, potmax);
    delay(400); // Retrocede durante 0,4 segundos y luego gira
    analogWrite(atrasA, potmax);
    analogWrite(adelanteB, potmax);
    delay(400); // Gira por 0,4 segundos
    }

  // Si solo una rueda detecta la pista retrocede y gira
  if (lineaA == LOW && lineaB == HIGH){
    analogWrite(adelanteA,0);
    analogWrite(adelanteB,0);
    analogWrite(atrasA, potmax);
    analogWrite(atrasB, potmax);
    delay(400); // Retrocede durante 0,4 segundos y luego gira
    analogWrite(adelanteA, potmax);
    analogWrite(atrasB, potmax);
    delay(400);  // Gira por 0,4 segundos
    }
}

// Si el boton se presiona nuevamente entonces detiene todas las acciones
if (boton == 1 && boton1.toggled() && boton1.read() == Button::RELEASED){
  boton = false;
  delay(50);
  if (boton == false){
    analogWrite (adelanteA, 0);
    analogWrite(atrasA, 0);
    analogWrite (adelanteB, 0);
    analogWrite(atrasB, 0);
  }
  }
}
