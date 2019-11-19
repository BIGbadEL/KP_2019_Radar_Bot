// Define Trig and Echo pin:
#include <Stepper.h>
  

#define trigPin 2
#define echoPin 3
// Define variables:
long duration;
int distance;

const int stepsPerRevolution = 64;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int t = 0.0;
double alfa = 0.0;

void setup() {
  // Define inputs and outputs:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  
  //Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
  t = millis();
}
void loop() {
  // Clear the trigPin by setting it LOW:
  int dt = millis() - t;
  t = millis();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance= duration*0.034/2;
  
  myStepper.step(stepsPerRevolution);
  double dalfa = 2.0 * PI / (60.0 * 1000.0) * dt;
  alfa += dalfa;
  
  Serial.println(distance);
  Serial.println(360.0 * alfa / PI);
 }
