import processing.serial.*;
import processing.opengl.*;
import toxi.geom.*;
import toxi.processing.*;


ToxiclibsSupport gfx;

Serial port;                         
char[] teapotPacket = new char[14];  
int serialCount = 0;                 
int aligned = 0;
int interval = 0;
String read;
int index1=0;
int dato1=0;
float[] axis = new float[4];

float[] q = new float[4];
Quaternion quat = new Quaternion(1, 0, 0, 0);

float[] gravity = new float[3];
float[] euler = new float[3];
float[] ypr = new float[3];
float yawOffset = 0.0f;


void setup() {
   
    //size(400, 400, OPENGL);
    size (1280, 768, P3D);
    gfx = new ToxiclibsSupport(this);


    lights();
    smooth();
   

    println(Serial.list());

    String portName = "/dev/ttyUSB0";
    
 
    port = new Serial(this, portName, 9600);
     port.bufferUntil('$');
    

}

void draw() {
    

    background(0);
    //translate(width/2, height/2, 0);
    //background(#374046);
    //fill(200, 200, 200); 
    textSize(32);
    text("Roll: " + axis[1]+ "     Pitch: " + axis[0] + "     Yaw: " + axis[2]+ "     dist: " + axis[3] , (width/2)-200, (width/2)-100);
    
    translate((width/2)+axis[3]*10, (height/2));
    print("axis:");
    print(axis[0]);
     print(":");
    print(axis[1]);
     print(":");
    println(axis[2]);
      print(":");
    println(axis[3]);
    rotateX(-radians(axis[1]));
    rotateY(-radians(axis[0])-yawOffset);
    rotateZ(radians(axis[2]));
    
    drawCube();
}

void drawCube() {
  //strokeWeight(1);
  //stroke(255, 255, 255);
  fill(#607D8B); 
  box (30, 10, 50);
  
  //strokeWeight(4);
  stroke(#E81E63);
  line(0, 0, 0, 20, 0, 0);
  stroke(#2196F2);
  line(0, 0, 0, 0, -35, 0);
  stroke(#8BC24A);
  line(0, 0, 0, 0, 0, 50);
}

void serialEvent(Serial port)
{
   
  
    read = port.readStringUntil('$');
     read = read.substring(0,read.length()-1);   
   float[] nums = float(split(read, ','));
   println(read);
   axis[0]= nums[1];
   axis[1]= nums[2];
   axis[2]= nums[3];
   axis[3]= nums[4];

}
void keyPressed() {
  switch (key) {
  
    case 'a': 
      yawOffset = axis[0];
  }
}
