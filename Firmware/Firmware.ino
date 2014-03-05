/*
Copy this into Spark Cloud Build.

turn on led:
curl https://api.spark.io/v1/devices/<spark_token>/ledstate -d access_token=<spark_token> -d "args=high"

turn off led:
curl https://api.spark.io/v1/devices/<spark_token>/ledstate -d access_token=<spark_token> -d "args=low"

return status of led 1 or 0:
curl https://api.spark.io/v1/devices/<spark_token>/ledstate -d access_token=<spark_token> -d "args=status"

*/

// ************************* variables

// set pin for button & led
const int buttonPin = 0;
const int ledPin =  3;

// set button states to start at zero
int buttonState = 0;
int lastButtonState = 0; 
int buttonPushCounter = 0;

int coastCoast(String command);

// ************************* setup 

void setup() {
  // expose a function through Spark Cloud
  // http://docs.spark.io/#/firmware/data-and-control-spark-function
  Spark.function("ledstate", coastCoast);
  // config buttonPin to INPUT
  pinMode(buttonPin, INPUT);
  // config ledPin to OUTPUT
  pinMode(ledPin, OUTPUT);
}

// ************************* loop

// set state of led via button
void loop() {
  
  // read the value of button 
  buttonState = digitalRead(buttonPin);

  // compare buttonState to its previous state
  if (buttonState != lastButtonState) {
    // check if the button is pressed
    // if button is pressed, buttonState is HIGH
    if (buttonState == HIGH) { 
      if (buttonPushCounter == 0) {
        turnOn();
      } else {
        turnOff();
      }
    } 
    // remember last state
    lastButtonState = buttonState;
  }
}


// ************************* spark cloud api function

// set state of led via api call
// set functon for call from Spark Cloud
int coastCoast(String command) {
  // argument for api call "args=high"
  if (command == "high") {
    turnOn();
    return 1;
  } 
  // argument for api call "args=low"
  if (command == "low") {
    turnOff();
    return 0;
  }
  // argument for api call "args=status"
  if (command == "status") {
      return buttonPushCounter;
  }
  // reads current state of led
  // changes to opposite state
  // argument for api call "args=toggle"
  if (command == "toggle") {
    if (buttonPushCounter == 0) {
      turnOn();
      return 1;
    } else {
      turnOff();
      return 0;
    }
  }
}

// ************************* functions

void turnOn() {
  // turn on led
  digitalWrite(3, HIGH);
  // when led is on buttonPushCounter = 1
  buttonPushCounter = 1;
}

void turnOff() {
  // turn off led
  digitalWrite(3, LOW);
  // when led is off buttonPushCounter = 0
  buttonPushCounter = 0;
}
