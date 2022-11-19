//Rain Sensor
const int capteur_D = 1;
const int capteur_A = A0;
int val_analogique;

//Water Flow
volatile int flow_frequency; 
unsigned int l_hour; 
unsigned char flowsensor = 2; 
unsigned long currentTime;
unsigned long cloopTime;
void flow () 
{
flow_frequency++;
}

//Ultra Sonic
#define echoPin 10 
#define trigPin 9 
long duration; 
int distance; 

//16x2 LCD Display
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//GSM Module
#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8 ); //Rx 7 & Tx 8

//Buzzer and LED
const int buzzer = 13; 

void setup()
{ Serial.begin(9600);

  //Rain Sensor
  pinMode(capteur_D, INPUT);
  pinMode(capteur_A, INPUT);

  //Flow Sensor
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
  attachInterrupt(0, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
  currentTime = millis();
  cloopTime = currentTime;

  //UltraSonic Sensor
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  //GSM Module
  mySerial.begin(9600);

  lcd.begin(16, 2);
  
  pinMode(buzzer, OUTPUT); 
}

void loop()

{
  rainwater();
  waterlevel();
  waterflow ();
  delay(5000);
  if (val_analogique > 500 && l_hour < 15 && distance > 20) 
    {
    tone(buzzer, 1000);
    Serial.print ("Flood Alert");
    Serial.println("");
    SendMessage();
    lcd.setCursor(0, 3); 
    lcd.print("Flood Alert");
    delay(5000);

    }
    else 
    {
    noTone(buzzer);     
    Serial.println ("No Flood Alert");
    Serial.println("");
    lcd.setCursor(0, 2);
    lcd.print("No Flood Alert");
    delay(5000);
     }
}


void SendMessage()
{
  mySerial.println("AT+CMGF=1");    
  delay(1000);  
  mySerial.println("AT+CMGS=\"+94766646404\"\r"); 
  delay(1000);
  mySerial.println("Flood Aleart");
  delay(100);
   mySerial.println((char)26);// 
  delay(1000);
}



void waterflow ()
{
currentTime = millis();

if(currentTime >= (cloopTime + 1000))
{
 cloopTime = currentTime; // Updates cloopTime

 l_hour = (flow_frequency * 60 / 7.5);

 flow_frequency = 0; // Reset Counter
 Serial.print(l_hour, DEC); // Print litres/hour
 Serial.println(" L/hour");
 Serial.println("");
}
}



void rainwater()
{
if(digitalRead(capteur_D) == LOW) 
  {
    Serial.println("Digital value : Raining"); 
    delay(10); 
  }
else
  {
    Serial.println("Digital value : Not Raining");
    delay(10); 
  }
val_analogique=analogRead(capteur_A); 
 Serial.print("Analog value : ");
 Serial.println(val_analogique);  
}



void waterlevel() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
