// Define Trig and Echo pin:
#include <Stepper.h>
#include <SPI.h>
#include <WiFi.h>
#include <math.h>

char ssid[] = "op6";     // the name of your network
char pass[] = "blinku1234"; // network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

#define trigPin 2
#define echoPin 3
// Define variables:
int duration;
int distance;

const int RPM = 60;
const int stepsPerRevolution = 64;  // change this to fit the number of steps per revolution for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 11, 12);

int t = 0.0;
double alfa = 0.0;

const uint16_t port = 8090;
const char * host = "192.168.43.84";

static WiFiClient client;

void setup() {
  // Define inputs and outputs:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // set the speed at 60 rpm:
  myStepper.setSpeed(RPM);
  
  //Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
  t = millis();

  Serial.println("Attempting to connect t o WPA network...");
  status = WiFi.begin(ssid, pass);

  if ( status != WL_CONNECTED) { 
   Serial.println("Couldn't get a wifi connection");
   while(true);
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  if (!client.connect(host, port)) {

      Serial.println("Connection to host failed");

      delay(1000);
      return;
  }
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
  distance = duration * 0.034 / 2.0;
  
  myStepper.step(stepsPerRevolution);
  
  double dalfa = 2.0 * PI / (RPM * 1000.0) * dt;
  alfa += dalfa;
  if(alfa >= 2.0 * PI){
    alfa -= 2.0 * PI;
  }

  Serial.println(distance);
  Serial.println(180.0 * alfa / PI);
  
  client.print(distance);
  client.print(";");
  client.print(double(180.0 * alfa / PI));
}
