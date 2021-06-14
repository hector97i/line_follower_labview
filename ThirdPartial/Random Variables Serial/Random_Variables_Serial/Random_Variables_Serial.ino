//arduino mega, uart 1
char letter;
long temperature, distance, voltage;

void setup() 
{
  Serial1.begin(9600);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() 
{
  //random measurements
  temperature = random(20, 40);
  distance = random(15, 50); //cm
  voltage = random(0, 5);
  
  if(Serial1.available())
  {
    letter = Serial1.read();
    //Serial.print(letter);
    switch(letter)
    {
      case 'a': Serial1.print(temperature);
                break;
      case 'b': Serial1.print(distance);
                break;
      case 'c': Serial1.print(voltage);
                break;
      default:  Serial1.print(letter);
    }
  }
}
