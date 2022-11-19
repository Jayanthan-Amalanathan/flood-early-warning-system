
volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
void flow () // Interrupt function
{
flow_frequency++;
}
void setup()
{
pinMode(flowsensor, INPUT);
digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
Serial.begin(9600);
attachInterrupt(0, flow, RISING); // Setup Interrupt
 sei(); // Enable interrupts
currentTime = millis();
cloopTime = currentTime;
}
void loop ()
{
currentTime = millis();

if(currentTime >= (cloopTime + 1000))
{
 cloopTime = currentTime; // Updates cloopTime

 l_hour = (flow_frequency * 60 / 7.5);

 flow_frequency = 0; // Reset Counter
 Serial.print(l_hour, DEC); // Print litres/hour
 Serial.println(" L/hour");
}
}
