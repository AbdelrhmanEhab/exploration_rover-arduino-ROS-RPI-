#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Empty.h>
#include <ArduinoHardware.h>
#include <string.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <DHT.h>

//left motors direction pins
#define front_left_dir     15
#define mid_left_dir       21
#define back_left_dir      25
//left motor speed pins
#define front_left_PWM     13
#define mid_left_PWM        7
#define back_left_PWM       3


//right motors direction pins
#define front_right_dir     17
#define mid_right_dir       19
#define back_right_dir      23
//right motor speed pins
#define front_right_PWM     11
#define mid_right_PWM       9
#define back_right_PWM      5

// Create a ROS node handle and a publisher for twist messages 
ros::NodeHandle nh;  


//ultrsonic pins
const int trigPin1 = 48;   //trigger pin of ultrasonic 1 
const int echoPin1 = 49;  //echo pin of ultrasonic 1 
const int trigPin2 = 44;  //trigger pin of ultrasonic 2  
const int echoPin2 = 43;  //echo pin of ultrasonic 2  

// Define the DHT pin and type
#define DHTPIN 40     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor for normal 16mhz Arduino


// Create a message object for the motor control topic 
geometry_msgs::Twist twist_msg;   // Motor control message type is Twist 

 //create the massage of the ultrasonic
std_msgs::Float32 ultrasonic1;
std_msgs::Float32 ultrasonic2;

//publish the ultrasonic massage
ros::Publisher pub1("ultrasonic1", &ultrasonic1);  //publish ultrasonic 1 data 
ros::Publisher pub2("ultrasonic2", &ultrasonic2);  //publish ultrasonic 2 data 


//DHT publish
std_msgs::Float32 temperature_msg;  // Create a message object for temperature data 
std_msgs::Float32 hum_msg;

ros::Publisher temp_pub("temperature", &temperature_msg); // Create a publisher object for temperature data
ros::Publisher hum_pub("humidity", &hum_msg); 

 void twistCallback(const geometry_msgs::Twist &twist) { 
    
  geometry_msgs::Vector3 linear = twist.linear;
  float LinerVelocity = float(linear.x);
  //float LinerVelocity = twist.linear.x;
  
  geometry_msgs::Vector3 angular = twist.angular;
  float AngularVelocity = float(angular.z);
  //float AngularVelocity = twist.angular.z;
 
  if (LinerVelocity > 0.1)
  {
    //forward
     digitalWrite(front_left_dir, LOW);
     digitalWrite(mid_left_dir, HIGH);
     digitalWrite(back_left_dir, HIGH);
     digitalWrite(front_right_dir, HIGH);
     digitalWrite(mid_right_dir, LOW);
     digitalWrite(back_right_dir, HIGH);
     analogWrite(front_left_PWM ,100);
     analogWrite(mid_left_PWM ,100);
     analogWrite(back_left_PWM ,100);
  
     analogWrite(front_right_PWM ,100);
     analogWrite(mid_right_PWM ,100);
     analogWrite(back_right_PWM ,100);
  
  }else if (LinerVelocity< -0.1)
  {
    //backward
     digitalWrite(front_left_dir, HIGH);
     digitalWrite(mid_left_dir,  LOW);
     digitalWrite(back_left_dir,  LOW);          
     digitalWrite(front_right_dir,  LOW);
     digitalWrite(mid_right_dir,  HIGH);
     digitalWrite(back_right_dir,  LOW);
     analogWrite(front_left_PWM ,100);
     analogWrite(mid_left_PWM ,100);
     analogWrite(back_left_PWM ,100);
  
     analogWrite(front_right_PWM ,100);
     analogWrite(mid_right_PWM ,100);
     analogWrite(back_right_PWM ,100);
  
           
  }
  else if(AngularVelocity > 0.1) { 
    //left
     digitalWrite(front_left_dir, LOW);
     digitalWrite(mid_left_dir,  LOW);
     digitalWrite(back_left_dir,  LOW);          
     digitalWrite(front_right_dir,  LOW);
     digitalWrite(mid_right_dir,  LOW);
     digitalWrite(back_right_dir,  HIGH);
     analogWrite(front_left_PWM ,120);
     analogWrite(mid_left_PWM ,120);
     analogWrite(back_left_PWM ,120);
  
     analogWrite(front_right_PWM ,70);
     analogWrite(mid_right_PWM ,70);
     analogWrite(back_right_PWM ,70);
     
    } else if (AngularVelocity < -0.1){
      //right
     digitalWrite(front_left_dir, HIGH);
     digitalWrite(mid_left_dir,  HIGH);
     digitalWrite(back_left_dir,  HIGH);          
     digitalWrite(front_right_dir,  HIGH);
     digitalWrite(mid_right_dir,  HIGH);
     digitalWrite(back_right_dir,  LOW);
     analogWrite(front_left_PWM ,120);
     analogWrite(mid_left_PWM ,120);
     analogWrite(back_left_PWM ,120);
  
     analogWrite(front_right_PWM ,70);
     analogWrite(mid_right_PWM ,70);
     analogWrite(back_right_PWM ,70);
   
    }
    else 
    {
      analogWrite(front_left_PWM ,0);
     analogWrite(mid_left_PWM ,0);
     analogWrite(back_left_PWM ,0);
  
     analogWrite(front_right_PWM ,0);
     analogWrite(mid_right_PWM ,0);
     analogWrite(back_right_PWM ,0);
    }
  
  
 }    
        
   
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &twistCallback);  
 

 void setup() {  

     // Initialize motor pins as outputs  
  
  nh.advertise(pub1);   //advertise the topic for publishing data from Ultrasonics 1  
  nh.advertise(pub2);   //advertise the topic for publishing data from Ultrasonics 2
  dht.begin();   // Initialize the DHT sensor
  nh.advertise(temp_pub);   // Advertise the topic containing temperature data 
 
  
  pinMode(trigPin1, OUTPUT);     //set trigger pin as output for Ultrasonics 1  
  pinMode(echoPin1, INPUT);      //set echo pin as input for Ultrasonics 1  

  pinMode(trigPin2, OUTPUT);     //set trigger pin as output for Ultrasonics 2  
  pinMode(echoPin2, INPUT);      //set echo pin as input for Ultrasonics 2  

  pinMode(front_left_dir,OUTPUT);
  pinMode(mid_left_dir,OUTPUT);
  pinMode(back_left_dir,OUTPUT);
  pinMode(front_left_PWM,OUTPUT);
  pinMode(mid_left_PWM,OUTPUT);
  pinMode(back_left_PWM,OUTPUT);
  
  pinMode(front_right_dir,OUTPUT);
  pinMode(mid_right_dir,OUTPUT);
  pinMode(back_right_dir,OUTPUT);
  pinMode(front_right_PWM,OUTPUT);
  pinMode(mid_right_PWM,OUTPUT);
  pinMode(back_right_PWM,OUTPUT);  

  
     // Initialize ROS node handle and subscriber   

     nh.initNode();   
     nh.subscribe(sub); 
     Serial.begin(57600);
 }   

 void loop() {   
     ultrasonic_1(trigPin1,echoPin1);
     ultrasonic_2(trigPin2,echoPin2);
      
     DHT_reader();
     
     nh.spinOnce();   

 }   


 
void ultrasonic_1(int trig, int echo)
{
   long duration, distance;      //variable to store duration and distance value from both the sensors
   digitalWrite(trigPin1, LOW);      //set trigger to low for Ultrasonics 1  
     delayMicroseconds(2);            //delay of 2 microseconds before sending a pulse to trigger Pin of Ultrasonics 1 

     digitalWrite(trigPin1, HIGH);     //send a 10 microsecond pulse to trigger Pin of Ultrasonics 1 
     delayMicroseconds(10);          

     digitalWrite(trigPin1, LOW);      //set trigger to low again for Ultrasonics 1 

     duration = pulseIn(echoPin1, HIGH);//read the echo Pin and store the time taken by the pulse in a variable called duration for Ultrasonics 1 

     distance= (duration/2) / 29.1;    /*calculate the distance by dividing it by 29.1 (speed of sound is 340 m/s and it takes time to travel back and forth so divide it by two). 
                                        To convert cm into meters*/

     ultrasonic1.data = distance;   // Assigns the calculated distance to a message variable    

     pub1.publish(&ultrasonic1);     // Publishes the message variable to topic "distance"    
}
void ultrasonic_2(int trig, int echo)
{
   long duration, distance;      //variable to store duration and distance value from both the sensors
   digitalWrite(trigPin1, LOW);      //set trigger to low for Ultrasonics 1  
     delayMicroseconds(2);            //delay of 2 microseconds before sending a pulse to trigger Pin of Ultrasonics 1 

     digitalWrite(trigPin1, HIGH);     //send a 10 microsecond pulse to trigger Pin of Ultrasonics 1 
     delayMicroseconds(10);          

     digitalWrite(trigPin1, LOW);      //set trigger to low again for Ultrasonics 1 

     duration = pulseIn(echoPin1, HIGH);//read the echo Pin and store the time taken by the pulse in a variable called duration for Ultrasonics 1 

     distance= (duration/2) / 29.1;    /*calculate the distance by dividing it by 29.1 (speed of sound is 340 m/s and it takes time to travel back and forth so divide it by two). 
                                        To convert cm into meters*/

     ultrasonic2.data = distance;   // Assigns the calculated distance to a message variable    

     pub2.publish(&ultrasonic2);     // Publishes the message variable to topic "distance"    
}
void DHT_reader(){
    float t = dht.readTemperature();   // Read temperature as Celsius (the default)
    float h = dht.readHumidity();
    if (isnan(t)) {   // Check if any reads failed and exit early (to try again).

        Serial.println("Failed to read from DHT sensor!");

        return; }

    else {   // Publish the message containing the temperature data on ROS topic if read is successful 

        temperature_msg.data = t;     // Assign the read value to the message object's data field 
        hum_msg.data=h;
        temp_pub.publish(&temperature_msg);     // Publish the message object on ROS topic }     
        hum_pub.publish(&hum_msg);
    //delay(2000); 
        }
  
}
