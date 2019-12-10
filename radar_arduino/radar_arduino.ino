// Define Trig and Echo pin:
#include <Stepper.h>
#include <SPI.h>
#include <math.h>

#define trigPin 2
#define echoPin 3
// Define variables:
int duration;
int distance;

const int RPM = 30;
const int stepsPerRevolution = 64;  // change this to fit the number of steps per revolution for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

double t = 0.0;
double dt = 0.0;
double alfa = 0.0;

void setup() {
  // Define inputs and outputs:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // set the speed at 60 rpm:
  myStepper.setSpeed(RPM);
  
  //Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
  t = millis();
}

void loop() {
  // Clear the trigPin by setting it LOW:
  dt = millis() - t;
  t = millis();
   Serial.println();
   Serial.println(dt);
   Serial.println(t);
Serial.println();

  int distances[3] = {0};
  for(int i = 0; i < 3; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    // Trigger the sensor by setting the trigPin high for 10 microseconds:
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
    duration = pulseIn(echoPin, HIGH);
    // Calculate the distance:
    distance = duration * 0.034 / 2.0;
    distances[i] = distance;
  }

  double dalfa = 2.0*(1.0/dt);
  alfa += dalfa;
  if(alfa >= 2.0 * PI){
    alfa -= 2.0 * PI;
  }
//  for(int i = 0; i < 3; i++) {
//    Serial.println(distances[i]);
//  }
//  Serial.println(180.0 * alfa / PI);
  
  myStepper.step(-stepsPerRevolution);
}
