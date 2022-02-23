#define in1  13
#define in2  12
#define PWM  9

int start;
int checker;

#define button1  3
#define button2  4
#define button3  5
#define button4  6
#define Led 7

boolean Unlocked = false;
const unsigned long longPressThreshold = 2000;//all variables
const unsigned long debounceThreshold = 50;
const unsigned long changeCodeLimit = 10000;
const unsigned long passwordButton = 5000;
unsigned long buttonLimit = 0;
unsigned long twoThreeTimer = millis();
unsigned long Limit = 0;
unsigned long LimitTimer = 0;
unsigned long buttonTimer = 0;
unsigned long buttonPressDuration = 0;
boolean buttonActive = false;
boolean longPressActive = false;
boolean lock = true;
boolean change = false;
String password = "123";
String input = "" ;
String passChange = "";
boolean inputer = false;

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
}

void loop() {
  //look for correct password and stop loop when we get it
  Serial.println("Top of loop");
  while (inputer == false) {
    Serial.println(input);
    if (digitalRead(button1) == LOW) { //Check for button 1 press

      input = input + "1";
      Serial.println(input);
      while (digitalRead(button1) == LOW) {}
      delay(10);
    }

    if (digitalRead(button2) == LOW) { // Check for button 2 press
      input = input + "2";
      Serial.println(input);
      while (digitalRead(button2) == LOW) {}
      delay(10);
    }

    if (digitalRead(button3) == LOW) { // Check for button 3 press
      input = input + "3";
      Serial.println(input);
      while (digitalRead(button3) == LOW) {}
      delay(10);
    }

    if (input.indexOf(password) >= 0) {
      inputer = true;
    }
  }

  //wait for the enter button before doing anything
  while (digitalRead(button4) == HIGH) {
    buttonPressDuration = 0;
  }


  if (digitalRead(button4) == LOW) {

    // mark the button as active, and start the timer
    if (buttonActive == false)
    {
      buttonActive = true;
      buttonTimer = millis();
    }

    buttonPressDuration = millis() - buttonTimer;
    Serial.println(buttonPressDuration);

    if ((buttonPressDuration > longPressThreshold) && (longPressActive == false))
    {
      longPressActive = true;
      Serial.print("Long press detected: Moving to unlock");
      Serial.println(buttonPressDuration);

      Serial.println("UNLOCKED");
      Unlocked = true;
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(7, HIGH);
      analogWrite(9, 50);
      delay(200);
      analogWrite(9, 0);
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(7, LOW);
      Password();
    }
  }

  // button either hasn't been pressed, or has been released
  else
  {
    // if the button was marked as active, it was recently pressed

    if (buttonActive == true)
    {
      buttonActive = false;
      // reset the long press active state
      if (longPressActive == true)
      {
        buttonPressDuration = 0;
        longPressActive = false;
        buttonActive = false;
      }
    }
  }
}


void Password(void) {
  buttonPressDuration = 0;
  longPressActive = false;
  buttonActive = false;
  inputer = false;
  Limit = millis();
  while (Unlocked == true && change == false) {
    buttonPressDuration = millis();
    while (digitalRead(button1) == LOW) {

      if (digitalRead(button1) == LOW && buttonTimer < 2000); {
        buttonTimer = millis() - buttonPressDuration;
        Serial.println(buttonTimer);
      }
      if (buttonTimer >= 2000) {
        Unlocked = false;
        lock = true;
        Serial.println("LOCKING");
        Serial.println("Locked");
        digitalWrite(13, LOW);
        digitalWrite(12, HIGH);
        digitalWrite(7, HIGH);
        analogWrite(9, 50);
        delay(200);
        analogWrite(9, 0);
        digitalWrite(7, LOW);
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        lock = true;
        buttonTimer = 0;
        buttonPressDuration = 0;
        LimitTimer = 0;
        twoThreeTimer = 0;
        buttonLimit = 0;
        input = "";
        while (digitalRead(button1) == LOW) {}
        delay(10);
        return;
      }
    }
    LimitTimer = millis() - Limit;
    Serial.println(LimitTimer);
    buttonPressDuration = millis();
    while (digitalRead(button2) == LOW && digitalRead(button3) == LOW && LimitTimer < 10000) {
      if (digitalRead(button2) == LOW && digitalRead(button3) == LOW && twoThreeTimer < 5000) {
        twoThreeTimer = millis() - buttonPressDuration;
        Serial.println(twoThreeTimer);
      }
      if (twoThreeTimer >= 5000) {
        while (digitalRead(button2) == LOW || digitalRead(button3) == LOW) {}
        change = true;
        delay(10);
        Serial.println("IM STILL NOT IN");

      }
      input = "";
      Serial.println("IM REAAAAAAALLLLY LOST");
    }

  }


  Serial.println("IM NOT INT");
  while (change == true) {
    Serial.println("IM INN FINNALLY I KNOW MY SPELLING IS CRAP");
    if (twoThreeTimer >= 5000) {
      Serial.println("Were in");
      boolean check = false;
      //start reading the new password
      while (digitalRead(button4) == HIGH ) {
        Serial.println(input);
        if (digitalRead(button1) == LOW) { //Check for button 1 press
          input = input + "1";
          Serial.println(input);
          while (digitalRead(button1) == LOW) {}
          delay(10);
        }

        if (digitalRead(button2) == LOW) { // Check for button 2 press
          input = input + "2";
          Serial.println(input);
          while (digitalRead(button2) == LOW) {}
          delay(10);
        }

        if (digitalRead(button3) == LOW) { // Check for button 3 press
          input = input + "3";
          Serial.println(input);
          while (digitalRead(button3) == LOW) {}
          delay(10);
        }
        passChange = input;

      }

      while (digitalRead(button4) == LOW) {}
      input = "";
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(7, HIGH);
      analogWrite(9, 50);
      delay(200);
      analogWrite(9, 0);
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(7, LOW);
      while (digitalRead(button4) == HIGH) {
        Serial.println(input);
        if (digitalRead(button1) == LOW) { //Check for button 1 press
          input = input + "1";
          Serial.println(input);
          while (digitalRead(button1) == LOW) {}
          delay(10);
        }
        if (digitalRead(button2) == LOW) { // Check for button 2 press
          input = input + "2";
          Serial.println(input);
          while (digitalRead(button2) == LOW) {}
          delay(10);
        }

        if (digitalRead(button3) == LOW) { // Check for button 3 press
          input = input + "3";
          Serial.println(input);
          while (digitalRead(button3) == LOW) {}
          delay(10);
        }
      }

      while (digitalRead(button4) == LOW) {}
      delay(10);
      if (input.length() < 3 || input.length() > 10 || input.indexOf(passChange) < 0) {
        Serial.print("Incorrect, Resseting to defualt password.");
        input = "";

      }
      else if (input.indexOf(passChange) >= 0 && input.length() >= 3 && input.length() <= 10 && input.indexOf("") >= 0) {
        Serial.println("Password changed");
        password = passChange;
        input = "";
        int flash = 0;

        while (flash < 3) {
          digitalWrite(7, HIGH);
          delay(200);
          digitalWrite(7, LOW);
          delay(200);
          flash++;
        }
        change = false;
      }
    }
  }
}
