const int buzzer = 13; 

void setup(){
  pinMode(buzzer, OUTPUT); 
  pinMode(led, OUTPUT); 
  }

void loop(){
  tone(buzzer, 1000); 
  delay(1000);       
  noTone(buzzer);     
  delay(1000);        
}
