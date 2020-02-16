
//Keep the pin 7,2,4 floating ALWAYS 
//ALWAYS 
//ALWAYS


#include <Wire.h>
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>

ros::NodeHandle  nh;


//Ultrasonic Sesnor Right
sensor_msgs::Range range_msg;
ros::Publisher pub_range( "ultrasound_range/right", &range_msg);
char frameid[] = "ultrasound_right";

//Ultrasonic Sensor Left 
sensor_msgs::Range range_msg2;
ros::Publisher pub_range2( "ultrasound_range/left", &range_msg2);
char frameid2[] = "ultrasound_left";

//Ultrasonic Sensor Front 
sensor_msgs::Range range_msg3;
ros::Publisher pub_range3( "ultrasound_range/front", &range_msg3);
char frameid3[] = "ultrasound_front";

const int pingPin1 = 7;
const int trigPin1 = 11;           //connects to the trigger pin on the distance sensor       
const int echoPin1 = 12; 

const int pingPin2 = 2;
const int trigPin2 = 9;           //connects to the trigger pin on the distance sensor       
const int echoPin2 = 8; 

const int pingPin3 = 4;
const int trigPin3 = 10;           //connects to the trigger pin on the distance sensor       
const int echoPin3 = 13; 


const boolean CENTIMETERS = true;
const boolean INCHES = false;
float distance1 = 0;
float distance2 = 0;
float distance3 = 0;


    

    void setup()
    {
      Wire.begin();                // join i2c bus (address optional for master)
//      Serial.begin(9600);          // start serial communication at 9600bps
    
  nh.initNode(); //Node Handler


  //Ultrasonic Right
  nh.advertise(pub_range);

  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;  //Based on data of Sparkfun HC-SR04 Ultrasonic sensor 
  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.002;  // 2 cm
  range_msg.max_range = 0.150;  // 150 cm
  
  pinMode(trigPin1, OUTPUT);   //the trigger pin will output pulses of electricity 
  pinMode(echoPin1, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

  
  //Ultrasonic Left
  nh.advertise(pub_range2);

  range_msg2.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg2.header.frame_id =  frameid2;

  // Based on data of Sparkfun HC-SR04 Ultrasonic sensor 
  range_msg2.field_of_view = 0.1;  // fake
  range_msg2.min_range = 0.002;  // 2 cm
  range_msg2.max_range = 0.150;  // 150 cm
  
  pinMode(trigPin2, OUTPUT);   //the trigger pin will output pulses of electricity 
  pinMode(echoPin2, INPUT);

  

  //Ultrasonic Right
  nh.advertise(pub_range3);

  range_msg3.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg3.header.frame_id =  frameid3;

  // Based on data of Sparkfun HC-SR04 Ultrasonic sensor 
  range_msg3.field_of_view = 0.1;  // fake
  range_msg3.min_range = 0.002;  // 2 cm
  range_msg3.max_range = 0.150;  // 150 cm
  
  pinMode(trigPin3, OUTPUT);   //the trigger pin will output pulses of electricity 
  pinMode(echoPin3, INPUT);
    
 }







//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance() {
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin1, LOW);

  echoTime = pulseIn(echoPin1, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}

float gd1() {
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin2, LOW);

  echoTime = pulseIn(echoPin2, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}

float gd2() {
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin3, LOW);

  echoTime = pulseIn(echoPin3, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}




    void loop() {

  //Ultrasonic Right
      range_msg.range=getDistance();
  range_msg.header.stamp = nh.now();
  pub_range.publish(&range_msg);
  nh.spinOnce();
  delay(500);
 
  //Ultrasonic Left
     range_msg2.range=gd1();
  range_msg2.header.stamp = nh.now();
  pub_range2.publish(&range_msg2);
  nh.spinOnce();
  delay(500);

  //Ultrasonic Front 
  range_msg3.range=gd2();
  range_msg3.header.stamp = nh.now();
  pub_range3.publish(&range_msg3);
  nh.spinOnce();
  delay(500);    
    }
