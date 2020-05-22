#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int butState = 0;
const int buzzPin = 8;

/// Whistle Decleration ///
double commandWhistles[10] = 0;
const int lowWhistle = 0;   //Placeholder
const int medWhistle = 1;
const int highWhistle = 2;
/// END Whistle Decleration ///

int chooseCommand(const double& inputWhistles[10]) //INVALID Command = -1
{
  //IDEA 1: ALOT of nested switch statements....
  //IDEA 2: Lol idk
  switch(inputWhistles[0])
  {
    case 0:
      switch(inputWhistles[1]{
        //valid cases
        case 0:
        break;
        default: return -1;
        }
    break;
    case 1:
    break;
    case 2:
    break;
  }
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Booting...");
  delay(3000);
  lcd.clear();
  Serial.begin(9600);
}

int doThisCommand;

void loop() {
  //if no one is whistling (no input being processed) probably intensity of input check
    lcd.print("Waiting for command");
     
  //else if Arduino is hearing a whistle 
  //{
    //while (stop whistle has not been said)
      //write "Listening..."
    
  //Call function to send to Python for processing here
  /*
   * 
   * delay(3000); //Allow ample time for Python to do its magic
   * Continuous Python Witchcraft here
   * 
   * 
   */
  //Call function to recieve processed whistles here commandWhistles = something something

  //Maybe map whistles to a string of 0,1,2

  //Parse through the entire commandwhistle array
    //for(int i = 0; i < 10; i++)
      //if (commandWhistles[i] != lowWhistle || commandWhistles[i] != midWhistle || commandWhistles[i] != highWhistle)
        //print "I'm sorry. I can't understand what you're whistling."

  doThisCommand = chooseCommand(commandWhistles); //Call function to determine command
  if(doThisCommand == -1)
  {
    lcd.print("I'm sorry. I don't understand your language Dumbass");
    //Probably need to scroll this
    delay(3000); //Stop everything, let this message sink in  
  }
  else //do the listed command below
  {
    switch(doThisCommand):
    case 0: //play Happy Birthday   break;
    case 1: //do a Rave light party break;
    case 2: //break your ears       break; 
    case 3: //spin a motor          break;
    case 4: //Turn on the fan       break;
    case 5: //Turn off the fan      break;
    case 6: //Say hello             break;
    case 7: break;
    case 8: break;
  }


  // }

  
  //butState = digitalRead(butPin);
  int val = analogRead(A0);

  delay(10);
  tone(buzzPin,val);
  
  lcd.clear(); //Clear the LCD screen for the next thing to be displayed
  delay(100);

}
