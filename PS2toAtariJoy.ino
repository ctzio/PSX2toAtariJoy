#include <PS2X_lib.h>  //for v1.6

#define up 7
#define down 6
#define left 5
#define right 4
#define fire 2

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){
 Serial.begin(57600);

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(10,12,11,8, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }


  //Setup Atari Joystick Pins

  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);

  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  

  
}

void loop(){

   
   
 if(error == 1) //skip loop if no controller found
  return; 
  
 
 //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    

         
     if(ps2x.Button(PSB_PAD_UP) || ps2x.Button(PSB_RED)) {         //will be TRUE as long as button is pressed
       digitalWrite(up, LOW);
       }
      else {
        digitalWrite(up, HIGH);
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
        digitalWrite(right, LOW);
      }
        else {
        digitalWrite(right, HIGH);
      }
      
      if(ps2x.Button(PSB_PAD_LEFT)){
        digitalWrite(left, LOW);
      }
      else {
        digitalWrite(left, HIGH);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
     digitalWrite(down, LOW);
      }  
      else {
        digitalWrite(down, HIGH);
      }
       
      if(ps2x.Button(PSB_BLUE)){
       digitalWrite(fire, LOW);
      }   
      else {
        digitalWrite(fire, HIGH);
      }

}
     
 

     
