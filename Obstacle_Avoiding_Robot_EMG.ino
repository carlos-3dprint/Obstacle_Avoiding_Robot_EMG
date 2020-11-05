/* A program to control 2 DC Motors with an ultrasonic sensor HC-SR04, a L9110S H-bridge motor driver and an Arduino Nano.
    Original Program Creator: SmartTronics
    Link: https://create.arduino.cc/projecthub/SmartTronics/obstacle-avoiding-robot-using-arduino-and-ultrasonic-sensor-c179bb

    Remix by: Electromechanical Guy
    Say Thanks with a coffee :)
    https://www.buymeacoffee.com/emguy
*/

/*******IMPORTANT******
   Please test the program before installing the wheels
   some times you will need to inverse the motor pins
*/

// Pins of the HC-SR-04 Sensor
int trigPin = 7;      // trig pin of HC-SR04
int echoPin = 8;     // Echo pin of HC-SR04

//Variables for the HC-SR-04 Sensor
long duration, distance;

//Pins for the 2 LEDs
int led_1 = 11; // GO LED (green for example)
int led_2 = 12; // STOP LED (Red for example)

/*Declaring the pins for the L9110S H-bridge motor driver
 * Using PWM pins to modulate the Speed 
 */
int revLeft = 5;       //Reverse motion of Left motor
int fwdLeft = 6;       //Forward motion of Left motor
int revRight = 9;      //Reverse motion of Right motor
int fwdRight = 10;      //Forward motion of Right motor

//Analog Values for Speed (Min 125 - Max 255)
const int maxSpeed = 125;
const int zeroSpeed = 0;

void setup() {

  // set Motor pins as output
  pinMode(revLeft, OUTPUT);
  pinMode(fwdLeft, OUTPUT);
  pinMode(revRight, OUTPUT);
  pinMode(fwdRight, OUTPUT);

  pinMode(trigPin, OUTPUT); // set trig pin as output
  pinMode(echoPin, INPUT); //set echo pin as input to capture reflected waves

  //set LED pins as Output
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
}

void loop() {

  //Sequence to measure the distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration / 58.2;   // convert to distance
  delay(10);

  /* Sequences for movements
      After readings of distance we will decide to move on a certain direction
  */

  if (distance > 19)//feel free to change this value to adapt the obstacle distance
  {
    digitalWrite(led_1, HIGH);// Turn ON GO LED
    digitalWrite(led_2, LOW);// Turn OFF STOP LED

    analogWrite(fwdLeft, maxSpeed); //Write maxSpeed value on the FWD Left Motor
    analogWrite(revLeft, zeroSpeed); //Write zeroSpeed value on the REV Left Motor
    analogWrite(fwdRight, maxSpeed); //Write maxSpeed value on the FWD Right Motor
    analogWrite(revRight, zeroSpeed);//Write zeroSpeed value on the REV Right Motor

  }//Close 1st IF

  if (distance < 19)//feel free to change this value to adapt the obstacle distance
  {
    digitalWrite(led_1, LOW);// Turn OFF GO LED
    digitalWrite(led_2, HIGH); // Turn ON STOP LED
    
    //STOP all motors
    analogWrite(fwdRight, zeroSpeed);  
    analogWrite(revRight, zeroSpeed);
    analogWrite(fwdLeft, zeroSpeed);
    analogWrite(revLeft, zeroSpeed);
    delay(500);

    //Move backwards
    analogWrite(fwdLeft, zeroSpeed);
    analogWrite(revLeft, maxSpeed);
    delay(10);
    analogWrite(fwdRight, zeroSpeed);      
    analogWrite(revRight, maxSpeed);
    delay(500);

    //STOP all motors
    analogWrite(fwdRight, zeroSpeed);  
    analogWrite(revRight, zeroSpeed);
    analogWrite(fwdLeft, zeroSpeed);
    analogWrite(revLeft, zeroSpeed);
    delay(100);

    //Turn Right
    analogWrite(revLeft, zeroSpeed);
    analogWrite(fwdLeft, zeroSpeed);
    delay(10);
    analogWrite(fwdRight, maxSpeed);
    analogWrite(revRight, zeroSpeed);
    delay(500);
    
  }//Close 2nd IF

}//Close loop
