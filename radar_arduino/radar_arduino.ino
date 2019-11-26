// Define Trig and Echo pin:
#include <Stepper.h>
#include <SPI.h>
#include <WiFi.h>
#include <math.h>

char ssid[] = "op6";     // the name of your network
char pass[] = "blinku1234" // network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

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

  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(ssid, pass);

   if ( status != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    while(true);
  
}

//double calculate_distance_form_points(double points[3]){
//  double d01 = abs(points[0] - points[1]);
//  double d02 = abs(points[0] - points[2]);
//  double d12 = abs(points[1] - points[2]);
//  if(d01 < d02) {
//    if(d01 < d12) {
//      
//    }
//  }
//}

void loop() {
  // Clear the trigPin by setting it LOW:
  int dt = millis() - t;
  t = millis();
//  float distances[3];
//  for(int i = 0; i < 3; i++){
//    
//  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance = duration * 0.034 / 2;
  
  myStepper.step(stepsPerRevolution);
  double dalfa = 2.0 * PI / (60.0 * 1000.0) * dt;
  alfa += dalfa;
  if(alfa >= 360.0){
    alfa -= 360.0;
  }
  Serial.println(distance);
  Serial.println(360.0 * alfa / PI);
 }
