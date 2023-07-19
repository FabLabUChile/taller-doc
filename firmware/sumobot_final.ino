
// Este codigo es utilzado para programar el comportamiento de un SumoBot. Al detectar a un oponente a una distancia determinada. En caso contrario, gira hasta encontrarlo.
// A su vez, si el sumobot detecta el limite de la pista, retrocede y gira.

// Pin Motores
int horarioA = 3; // Sentido horario del motor izquerdo
int horarioB = 6; // Sentido horario del motor derecho
int antihorarioA = 5; // Sentido antihorario del motor izquerdo
int antihorarioB = 9; // Sentido antihorario del motor derecho


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
pinMode(antihorarioA, OUTPUT);
pinMode(antihorarioB, OUTPUT);
pinMode(horarioA, OUTPUT);
pinMode(horarioB, OUTPUT);
// Sensor de linea
pinMode(linA, INPUT);
pinMode(linB, INPUT);
}

void loop() {

// Verificar si se ha presionado el botón y esperar 5 segundos
delay(5000);

//++++++++++++++++++++++++++++++++++++++//
// Calculo de distancia del objetivo
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
    
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
    
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(10);          //Hacemos una pausa de 100ms

  //++++++++++++++++++++++++++++++++++++++//
  // Si detecta oponente cercano avanza en linea recta
if (d <= 25) {
  analogWrite(horarioA, potmax);
  analogWrite(horarioB, potmax);
  analogWrite(antihorarioA, 0);
  analogWrite(antihorarioB, 0);
  delay(50);
  }

  // Si no detecta oponente cercano gira.
if (d >= 26) {
  analogWrite(horarioA, 0);
  analogWrite(horarioB, potmax);
  analogWrite(antihorarioA, potmax);
  analogWrite(antihorarioB, 0);
  delay(50);
}
  //++++++++++++++++++++++++++++++++++++++//
  // Lectura Sensores de linea
  int lineaA = digitalRead(linA);
  int lineaB = digitalRead(linB);

  // Si detecta los limites de la pista, retrocede.
if (lineaA == HIGH && lineaB == HIGH){
  analogWrite(horarioA, potmax);
  analogWrite(horarioB, potmax);
  }

  // Si detecta el sensor izquierdo entonces retrocede y gira a la derecha.
if (lineaA == HIGH && lineaB == LOW){
  analogWrite(horarioA, potmax);
  analogWrite(horarioB, potmax);
  delay(100);
  analogWrite(antihorarioA, potmax);
  analogWrite(horarioB, potmax);
  delay(500); // Tiempo de espera hasta encontrar al oponente
  }

  // Si detecta el sensor derecho entonces retrocede y gira a la izquierda.
if (lineaA == LOW && lineaB == HIGH){
  analogWrite(horarioA, potmax);
  analogWrite(horarioB, potmax);
  delay(100);
  analogWrite(antihorarioB, potmax);
  analogWrite(horarioA, potmax);
  delay(500); // Tiempo de espera hasta encontrar al oponente
  }
  
  }
