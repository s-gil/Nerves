#include "GY_85.h"
#include <DFRobot_QMC5883.h>
#include <Ultrasonic.h>
#include <Wire.h>

GY_85 GY85;     //create the object
DFRobot_QMC5883 compass;
Ultrasonic ultrasonic(12, 13);

float pitch;
float yaw;
float roll;
float mag_x;
float mag_y;
float azimut;
float cos_roll;
float sin_roll;
float cos_pitch;
float sin_pitch;
float volts;

#define TO_DEG(x) (x * (180/PI))  // *180/pi
//#define sensor A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

 
void setup()
{
    Wire.begin();
    delay(10);
    Serial.begin(9600);
    
    while (!compass.begin())
    {
      Serial.println("Could not find a valid QMC5883 sensor, check wiring!");
      delay(500);
    }
    compass.setRange(QMC5883_RANGE_2GA);
    compass.setMeasurementMode(QMC5883_CONTINOUS); 
    compass.setDataRate(QMC5883_DATARATE_50HZ);
    compass.setSamples(QMC5883_SAMPLES_8);
    
    delay(10);
    GY85.init();
    delay(10);
}


void loop()
{
    int ax = GY85.accelerometer_x( GY85.readFromAccelerometer() );
    int ay = GY85.accelerometer_y( GY85.readFromAccelerometer() );
    int az = GY85.accelerometer_z( GY85.readFromAccelerometer() );

    Vector norm = compass.readNormalize();

    float declinationAngle = (-9 + (2.0 / 60.0)) / (180 / PI); // Formula: (deg + (min / 60.0)) / (180 / PI);
    heading += declinationAngle;
    if (heading < 0){     // Correct for heading < 0deg and heading > 360deg
      heading += 2 * PI;
    }
    if (heading > 2 * PI){
      heading -= 2 * PI;
    }

//    float gx = GY85.gyro_x( GY85.readGyro() );
//    float gy = GY85.gyro_y( GY85.readGyro() );
//    float gz = GY85.gyro_z( GY85.readGyro() );
//    float gt = GY85.temp  ( GY85.readGyro() );

    roll= atan2(-ax,az); //get roll from acel data
    pitch= atan2(ay, sqrt(ax * ax + az * az)); //get pitch from accel data
    float heading = atan2(norm.YAxis, norm.XAxis); //get yaw from magnetometer data
    int distance = ultrasonic.read(); // get distance from ultrasonic sensor data

//    cos_roll = cos(roll);
//    sin_roll = sin(roll);
//    cos_pitch = cos(pitch);
//    sin_pitch = sin(pitch);
//    mag_x = norm.XAxis* cos_pitch + norm.YAxis * sin_roll * sin_pitch + norm.ZAxis * cos_roll * sin_pitch;
//    mag_y =norm.YAxis * cos_roll - norm.ZAxis * sin_roll;
//    yaw = atan2(-mag_y, mag_x);
  
//  volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
//  int distance = 13*pow(volts, -1); // worked out from datasheet graph
      
    Serial.print  ( "," );
    Serial.print  (TO_DEG(heading) );
    Serial.print  ( "," );
    Serial.print  ( (TO_DEG(pitch)));
    Serial.print  ( "," );
    Serial.print  ( (TO_DEG(roll)));
    Serial.print  ( "," );
    Serial.print  (distance );
    Serial.println  ( "$" );
    delay(100);           
}
