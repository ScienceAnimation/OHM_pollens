//Array of pins
int ButtonPins[] = {
  30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47};
//Number of pins
int PinsNo = 18;
//last known switch states [PinsNo]
int ButtonPrev[18] = {
  0};
// array of bits for status
int CellArray[]={
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// Decimal Cell value
int CellValue = 0;

// Array of green leds
int GreenLedPins[] = {
  A0,A2,A4,A6,A8,A10};
// Array of red leds
int RedLedPins[] = {
  A1,A3,A5,A7,A9,A11};
// Number of leds
int LedsNo = 6;

// Serial Debug
int DEBUG = 0; // DEBUG counter; if set to 1, will write values back via serial


void setup()
{
  if (DEBUG) {           // If we want to see the pin values for debugging...
    Serial.begin(9600);
    Serial.println("Buttons Test");
    //Set the Pin Mode
    Serial.println("Setting Pins...");  
  }
  //Start Serial

  for(int Pin = 0; Pin < PinsNo; Pin++)
  {
    pinMode(ButtonPins[Pin], OUTPUT);
    digitalWrite(ButtonPins[Pin], HIGH);
  }

  //Set the Led Mode
  if (DEBUG) {           // If we want to see the pin values for debugging...

    Serial.println("Setting Leds...");
  }
  for(int Pin = 0; Pin < LedsNo; Pin++)
  {
    pinMode(GreenLedPins[Pin], OUTPUT);
    digitalWrite(GreenLedPins[Pin], HIGH); // Note : set LOW to put the led ON
    pinMode(RedLedPins[Pin], OUTPUT);
    digitalWrite(RedLedPins[Pin], HIGH); // Note : set LOW to put the led ON

  }
  if (DEBUG) {           // If we want to see the pin values for debugging...

    Serial.println("Ready!");
  }
} 

void loop()
{
  //Loop through the switches
  for(int Pin = 0; Pin < PinsNo; Pin++)
  {
    digitalWrite(ButtonPins[Pin], LOW);

    //Check if each switch is pressed
    if(digitalRead(ButtonPins[Pin]) == LOW)
    {
      //Check to see if the state has chnged since last time
      if(ButtonPrev[Pin] == 0)
      {
        //Do action here, switch is on
        if (DEBUG) {           // If we want to see the pin values for debugging...

          Serial.print(ButtonPins[Pin]);
          Serial.print(", ");
          Serial.print(ButtonPins[Pin]);
          Serial.println(" ON");
        }
        CellArray[Pin] = 0;
        //Update last known state of this switch
        ButtonPrev[Pin] = 1;
        digitalWrite(GreenLedPins[(Pin/3)], HIGH); // Note : set LOW to put the led ON
        digitalWrite(RedLedPins[(Pin/3)], HIGH); // Note : set LOW to put the led ON


      }
    } 
    else {
      //Check to see if the state has chnged since last time
      if(ButtonPrev[Pin] == 1)
      {
        //Do action here, switch is off
        if (DEBUG) {           // If we want to see the pin values for debugging...

          Serial.print(ButtonPins[Pin]);
          Serial.print(", ");
          Serial.print(ButtonPins[Pin]);
          Serial.println(" OFF");
        }
        CellArray[Pin] = 1;
        //Update last known state of this switch
        ButtonPrev[Pin] = 0;
        digitalWrite(GreenLedPins[(Pin/3)], HIGH); // Note : set LOW to put the led ON
        digitalWrite(RedLedPins[(Pin/3)], LOW); // Note : set LOW to put the led ON


      }
    }
    digitalWrite(ButtonPins[Pin], HIGH);
  }
  // Check for values
  for (int i = 0; i < 6; i++)
  {
    CellValue = CellArray[(3*i)]+(CellArray[((3*i)+1)])*2+(CellArray[((3*i)+2)])*4;
    if(CellValue == i+1)
    {
      if (DEBUG) {           // If we want to see the pin values for debugging...

        Serial.print("piece :");
        Serial.print(i+1);
        Serial.println(" OK");
      }
      digitalWrite(GreenLedPins[i], LOW); // Note : set LOW to put the led ON
      digitalWrite(RedLedPins[i], HIGH); // Note : set LOW to put the led ON


    }
    if (DEBUG) {           // If we want to see the pin values for debugging...

      Serial.print("Case : ");
      Serial.print(i+1);
      Serial.print(" Valeur :");
      Serial.println(CellValue);
    }


  }

}


