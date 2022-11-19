const int capteur_D = 6;
const int capteur_A = A0;

int val_analogique;

void setup()
{
  pinMode(capteur_D, INPUT);
  pinMode(capteur_A, INPUT);
  Serial.begin(9600);
}

void loop()
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
 Serial.println("");
  delay(1000);
}
