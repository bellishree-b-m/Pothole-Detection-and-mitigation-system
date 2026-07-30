#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

#include <Wire.h>
#include <SparkFun_ADXL345.h>
ADXL345 accelerometer;

#include <SoftwareSerial.h>
SoftwareSerial gps(8,9); // RX, TX

int led = 13;
int relay = 12;
int ir = 14;
const int trigPin1 = 10;  
const int echoPin1 = 11;

float dd, flat, flng;
String slat, slng;
float targetDistance1 = 0;
String lat = "12.9716";
String lng = "77.5946";

void read_gps_data();
float conv_coords(float val);
void get_dist1();
void send_data(const char* message);
void send_sms();


void setup() 
{
  lcd.begin(16,2);
  Serial.begin(9600);

  gps.begin(9600);
 
  pinMode(led,OUTPUT);
  pinMode(relay,OUTPUT);
  pinMode(ir,INPUT);
  
  pinMode(trigPin1, OUTPUT);    //SR04 trig
  pinMode(echoPin1, INPUT);     //SR04 echo

  lcd.print(" WELCOME To");
  lcd.setCursor(0,1);
  lcd.print(" The Project ");
  delay(2000);
  
  gps.print("AT+CMGF=1\r\n");
  delay(700);
  gps.print("AT+CSMP=17,167,0,0\r\n"); //AT+CSMP=17,167,0,0
  delay(700);
    
  delay(700);  
    
  digitalWrite(relay,1);
  

}

  int x,y,z;  
  int tap = 0;
  int button = 0;

  
void loop()
{                                                                               
  read_gps_data();
  
  dd = atof(lat.c_str());  
  flat =  conv_coords(dd);      
  delay(10);
  
  dd = atof(lng.c_str());
  flng =  conv_coords(dd);     
  delay(10); 
  
  get_dist1();  

  slat = String(flat,6);
  slng = String(flng,6);

    if(accelerometer.isDoubleTap)
    {
      tap = 1;
    }
       
    if(tap == 1)
    {  
       {   
          Serial.println("Un-Even-Road");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Un-Even Road "); //Print blanks to clear the row
          lcd.setCursor(0, 1);
          lcd.print("*** Alert ***"); //Print blanks to clear the row
          
          digitalWrite(relay,0);
          tracking(); 
          digitalWrite(relay,1);
          delay(1000);
          tap =0;
       }     
    
    }
    
    if(!digitalRead(ir))
    {  
       {   
          Serial.println("HUMP");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("***Alert***"); //Print blanks to clear the row
          lcd.setCursor(0, 1);
          lcd.print("    HUMP"); //Print blanks to clear the row
          
          digitalWrite(relay,0);
          tracking1(); 
          digitalWrite(relay,1);
          delay(1000);
       }     
    
    }
  

  get_dist1();  
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(slat); //Print blanks to clear the row
  lcd.print(" "); //Print blanks to clear the row
  lcd.print(targetDistance1); //Print blanks to clear the row
  lcd.setCursor(0, 1);
  lcd.print(slng); //Print blanks to clear the row       
  //delay(1000);
  if (targetDistance1 > 10)
  {  
            
          Serial.println("PATH-HOLE");
          
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("***ALERT***"); //Print blanks to clear the row
          lcd.setCursor(0, 1);
          lcd.print("PATH HOLE"); //Print blanks to clear the row
  
          digitalWrite(relay,0);
          digitalWrite(led,1);
          tracking2(); 
          digitalWrite(relay,1);
          digitalWrite(led,0);
          delay(1000);
  }
  
  
}


void init_sms()
{
  gps.println("AT+CMGF=1");
  delay(400);
  gps.println("AT+CMGS=\"+919496523018\"");   // use your 10 digit cell no. here //8712704247
  delay(400);
}


void tracking()
{
 
    init_sms();
    send_data("*** ALERT *** Un-Even Road At:");  
    delay(500);  
    gps.print("http://maps.google.com/?q=");   
    gps.print(slat);
    gps.print(",");
    gps.println(slng);
    send_sms();
    delay(2500);
        
}

void tracking1()
{
    init_sms();
    send_data("***ALERT*** HUMP hasbeen Detected At:");  
    delay(500);   
    gps.print("http://maps.google.com/?q=");   
    gps.print(slat);
    gps.print(",");
    gps.println(slng);
    send_sms();
    delay(2500);
}

void tracking2()
{
    init_sms();
    send_data("***ALERT***PATH HOLE hasbeen Detected At:");  
    delay(500);   
    gps.print("http://maps.google.com/?q=");   
    gps.print(slat);
    gps.print(",");
    gps.println(slng);
    send_sms();
    delay(2500);
}
