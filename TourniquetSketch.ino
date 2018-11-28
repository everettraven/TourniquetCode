/*
 * This is the arduino sketch that runs the tourniquet circuit.
 * Created By : Bryce Palmer
 * 10/31/2018
 */
 

//Gets the built-in LED on the arduino
const int LedPin = LED_BUILTIN;

//int value of the LOW state for an output
int LedState = LOW;

//setting up an unsigned long to take the value of the millis() function later
unsigned long PreviousMillis = 0;

//setting a value for an interval
long TournStartInterval = 5000;

//char value used to get the on/off/change values command from the serial monitor
String Response = "";

char ResponseChar[256];

//char array to change the values of the resting PWM value and the start to resting interval
char ValueChanger[256];

char * key;


int TournPin = 3;

int TourniquetOn = 0;

//PWM Lower power number
int LowPower = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(LedPin, OUTPUT);

  pinMode(TournPin, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:


  while(Serial.available() > 0)
  {
    //Get the character inputted through the serial monitor
    Response = Serial.readString();

    Response.toCharArray(ResponseChar, 256);

    key = strstr(ResponseChar, ":");

    //Reprint the character for validation
    Serial.print(Response);

    if(Response.compareTo("O") == 0)
    {
      //Check to see if the tourniquet is already on
      if(TourniquetOn == 1)
      {
        
      }
      else
      {
        //Run the function to turn on the tourniquet
        PowerOnTourniquet();
      }
      
    }
    else if(Response.compareTo("I") == 0)
    {
      //Check to see if the tourniquet is on
      if(TourniquetOn == 1)
      {
        //Run the function to turn off the tourniquet
        PowerOffTourniquet();        
      }
      else
      {
        
      }

    }
    else if(strcmp(key, ":") != NULL)
    {
      Response.toCharArray(ValueChanger, 256);
      ChangeValues();
    }


  }
  

}


//Function to turn on the tourniquet
void PowerOnTourniquet()
{
  Serial.print("Tourniquet On");
  
  digitalWrite(LedPin, HIGH);

  //Set the tourniquet value to "ON"
  TourniquetOn = 1;
  
  //send the required PWM signal to run the circuit
  analogWrite(TournPin, 255);

  //Set the value of current millis
  unsigned long CurrentMillis = 0;
  
  //delay through millis()
  //set previous to current millis
  PreviousMillis = millis();
  
  do
  {
    //Set current millis and constantly update it
     CurrentMillis = millis();

    //Check to see if the current - the previous is greater or equal to the interval
     if(CurrentMillis - PreviousMillis >= TournStartInterval)
     {
        break;
     }
     //check to see if the command has told the tourniquet to be off
     else if(Serial.read() == 'I')
     {
        //Run the function to turn off the tourniquet
        PowerOffTourniquet();
        return 0;
     }
     
  }while(CurrentMillis - PreviousMillis < TournStartInterval);

  //Set the PWM to a lower pulse value to draw less power but keep the tourniquet on
  analogWrite(TournPin, LowPower);

  
}

void PowerOffTourniquet()
{
  Serial.print("Tourniquet Off");
  
  digitalWrite(LedPin, LOW);

  //Set tourniquet 
  TourniquetOn = 0;

  //Set the PWM pulse value to nothing so the toruniquet turns off
  analogWrite(TournPin, 0);

  
}


void ChangeValues()
{
  char *token;

  token = strtok(ValueChanger, ":");

  LowPower = atoi(token);

  token = strtok(NULL, ":");

  TournStartInterval = atoi(token);

  Serial.print("Data Recieved");

  
}
