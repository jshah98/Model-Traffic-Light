/*
Sophia Weng, Jinansh Shah & Lior Levy
 Mr. Wong
 May-June 2015
 This program controls 11 LED lights on a stoplight and pedestrian crossing sign of a T-intersection, a light that goes off when it gets dark enough and a button that will speed up the intersection's lights for one round.
 */
#include <Servo.h> 

boolean m=false;

Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 

unsigned long forMotor; // stores the time at which motor was opened
unsigned long forTraffic; // stores the times at which the traffic lights change

boolean lior = false;  // stores whether the button has been pressed 
int thing = 1; // variable used to alter the timings of the traffic lights
int but = 3; // stores the state of the button (pressed or not).

int lrR= 13; // stores the pin number of the left/right red light
int lrG = 11; // stores the pin number of the left/right green light
int lrY = 12; // stores the pin number of the left/ right yellow light

int midR = 10; // stores the pin number of the mid red light
int midY = 9; // stores the pin number of the mid yellow light
int midG = 8; // stores the pin number of the mid gren light

int irSensorPin = 5; // stores the pin numnber of the ir sensor pin
int irLED = 2  ; //stores the pin number of the ir light

int PCS = 6; // stores the pin number of the photocell sensor
int photocellReading;     // stores the analog reading from the sensor divider
int lamp = 7;          // stores the pin number of an LED connected to the photocell sensor

int buttonReading; // stores the button reading

int pedG = A2; // stores the pin of the pedestrian walk light
int pedR = A1; // stores the pin of the pedestrian stop light 

// variables check if corresponding traffic code has run before running next code (needed to check that it has been run or not when the traffic light system speeds up)
boolean traffica;
boolean trafficb;
boolean trafficc;
boolean trafficd;
boolean traffice;
boolean trafficf;
boolean trafficg;
boolean traffich;
boolean traffici;
boolean trafficj;
boolean traffick;

// setup - sets up necessary parts, runs once
void setup() {                
  // initialize the digital pin as an output.
  pinMode(lrR, OUTPUT);     
  pinMode(lrY, OUTPUT);     
  pinMode(lrG, OUTPUT);     
  pinMode(midR, OUTPUT);     
  pinMode(midY, OUTPUT);     
  pinMode(midG, OUTPUT);     
  pinMode(PCS, OUTPUT);
  pinMode (pedG, OUTPUT);
  pinMode (pedR, OUTPUT);
  digitalWrite (PCS, HIGH);
  pinMode(lamp, OUTPUT);  // have an LED for output 
/////////////////  pinMode (irLED, HIGH);
  Serial.begin(9600);   
  pinMode (but, INPUT_PULLUP);
  myservo.attach(4);  
  forMotor = millis();
  forTraffic = millis();
  pinMode(irSensorPin, INPUT);
  pinMode(irLED, OUTPUT);
}

// ir - returns the status of the IR (whether something has been detected)
boolean ir ()
{
  digitalWrite (irLED, HIGH);
  int temp= analogRead (A5);
  Serial.println (temp);
  return (temp >10);
}

// light - turns on light if photocell reading is low (it is dark)
void light ()
{
  // read the resistor 
  photocellReading = analogRead (A3);
  if (photocellReading > 80)
    digitalWrite(lamp, LOW);
  else
    digitalWrite(lamp, HIGH);  
}


// button - checks if the button has been pressed
void button ()
{                                                 
  buttonReading = digitalRead(but);
  if (buttonReading == LOW) {
    thing = 2;
    lior = true;
  }
  else
    thing = 1; 
}


// traffic1 - turns on th left/ right red light and mid green light
void traffic1()
{
  digitalWrite(lrR, HIGH);   //top is red
  digitalWrite (midG,HIGH); // mid is green

}


// traffic2 - turns off mid green light and turns on mid yellow light
void traffic2()
{
  digitalWrite (midG,LOW); // mid is now yellow
  digitalWrite(midY, HIGH); 
}


// traffic3 - turns off mid yellow right and turns on mid red light, turns off left/right red light and turns on left/right gren light
void traffic3()
{
  digitalWrite(lrR, LOW);    // top is now green
  digitalWrite (lrG, HIGH); 
  digitalWrite(midY, LOW);  // mid is now red
  digitalWrite(midR, HIGH); 
}


// traffic4 - turns off left/right green light and turns on left/right yellow light
void traffic4()
{
  digitalWrite (lrG, LOW);   // top is yellow
  digitalWrite (lrY, HIGH);
}


// traffic5 - turns off left/right yellow light and mid red light
void traffic5()
{
  digitalWrite (lrY, LOW); // turns off top yellow
  digitalWrite (midR, LOW); //turns off mid red   
}


// ped1 - turns off walk light and turns on stop light
void ped1()
{
  digitalWrite (pedG, LOW);
  digitalWrite (pedR, HIGH); 
}


// ped2 - turns off stop light
void ped2()
{
  digitalWrite (pedR, LOW);
}

// ped3 - turns on walk light 
void ped3()
{
  ped2();
  digitalWrite (pedG, HIGH);
}


// loop - runs forever
// if statements - check ifit is the right time to change traffic lights or close gates, if it is dark the photocell light turns on, and if the ir detects something motor () is called.
void loop() 
{
 
 light();
  if (lior==false)
    button();

  if (millis()-forTraffic >= 1/thing && traffica==false)
  {
    traffic1();
    ped1();
    traffica=true;
  }
  if (millis()-forTraffic >= 4000/thing && trafficb==false)
  {
    traffic2();
    trafficb=true;
  }
  if (millis()-forTraffic >= 6000/thing && trafficc==false)
  {
    traffic3();
    ped3();
    trafficc=true;
  }

  if (millis()-forTraffic >= 9000/thing && trafficd==false)
  {
    ped1();
    trafficd=true;
  }
  if (millis()-forTraffic >= 9500/thing && traffice==false)
  {
    ped2();
    traffice=true;
  }
  if (millis()-forTraffic >= 10000/thing && trafficf==false)
  {
    ped1();
    trafficf=true;
  }
  if (millis()-forTraffic >= 10500/thing && trafficg==false)
  {
    ped2();
    trafficg=true;
  }
  if (millis()-forTraffic >= 11000/thing && traffich==false)
  {
    ped1();
    traffich=true;
  }
  if (millis()-forTraffic >= 11500/thing && traffici==false)
  {
    ped2();
    traffici=true;
  }
  if (millis()-forTraffic >= 12000/thing && trafficj==false)
  {
    ped1();myservo.write(0);              // tell servo to go to position in variable 'pos'                      // waits 15ms for the servo to reach the position 
    trafficj=true;
  }
    
  if (millis()-forTraffic >= 10000/thing && traffick==false)
  {
    traffic4();
    traffick=true;
  }

  if (millis()-forTraffic >= 12000/thing)
  {
    traffic5();
    lior=false;
    forTraffic = millis();
    traffica=false;
    trafficb=false;
    trafficc=false;
    trafficd=false;
    traffice=false;
    trafficf=false;
    trafficg=false;
    traffich=false;
    traffici=false;
    trafficj=false;
    traffick=false;
  } 
  
 if (ir ())
 {
    myservo.write(0);     
    forMotor = millis ();
    Serial.println ("op");
 }
 if (millis ()-forMotor > 1000)
    myservo.write(120);     
}













