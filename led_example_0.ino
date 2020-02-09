/* Pins constants */ 
int INCREASE_BUTTON_PIN = 2;
int FLASHER_BUTTON_PIN  = 4;

int H_LED_PIN    = 3;
int O_LED_PIN    = 5;
int M_LED_PIN    = 6;
int E_LED_PIN    = 9;
int R_LED_PIN    = 10;
int LOVE_LED_PIN = 11;

/* States */
boolean INCREASE_BUTTON_WAS_UP         = true;  
boolean IS_FLASHER_BUTTON_ENABLED      = true;
boolean IS_INTERVAL_PASSED             = false;
boolean IS_DECREASE_BRIGHTNESS_ENABLED = false;

/* Components variable values */
int MAX_BRIGHTNESS = 250;

int DEFAULT_BRIGHTNESS = 0;
int CURRENT_BRIGHTNESS = DEFAULT_BRIGHTNESS;

unsigned long PREVIOUS_MILLIS = 0;

void setup() {
  pinMode(INCREASE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(FLASHER_BUTTON_PIN,  INPUT_PULLUP);
  
  pinMode(H_LED_PIN,    OUTPUT);
  pinMode(O_LED_PIN,    OUTPUT);
  pinMode(M_LED_PIN,    OUTPUT);
  pinMode(E_LED_PIN,    OUTPUT);
  pinMode(R_LED_PIN,    OUTPUT);
  pinMode(LOVE_LED_PIN, OUTPUT);

  analogWrite(3,  0);
  analogWrite(5,  CURRENT_BRIGHTNESS);
  analogWrite(6,  CURRENT_BRIGHTNESS);
  analogWrite(9,  CURRENT_BRIGHTNESS);
  analogWrite(10, CURRENT_BRIGHTNESS);
  analogWrite(11, CURRENT_BRIGHTNESS);
}


void loop() {
  unsigned long currentMillis = millis();

  if (IS_FLASHER_BUTTON_ENABLED) {
    if (currentMillis - PREVIOUS_MILLIS >= 15 && !IS_INTERVAL_PASSED) {
      if (CURRENT_BRIGHTNESS >= MAX_BRIGHTNESS) {
        IS_DECREASE_BRIGHTNESS_ENABLED = true; 
      }

      if (CURRENT_BRIGHTNESS <= 3) {
        IS_DECREASE_BRIGHTNESS_ENABLED = false; 
      }

      CURRENT_BRIGHTNESS = IS_DECREASE_BRIGHTNESS_ENABLED ? CURRENT_BRIGHTNESS - 3 : CURRENT_BRIGHTNESS + 2;

      analogWrite(H_LED_PIN,    CURRENT_BRIGHTNESS);
      analogWrite(O_LED_PIN,    CURRENT_BRIGHTNESS);
      analogWrite(M_LED_PIN,    CURRENT_BRIGHTNESS);
      analogWrite(E_LED_PIN,    CURRENT_BRIGHTNESS);
      analogWrite(R_LED_PIN,    CURRENT_BRIGHTNESS);
      analogWrite(LOVE_LED_PIN, CURRENT_BRIGHTNESS);

      IS_INTERVAL_PASSED = true;
      PREVIOUS_MILLIS = currentMillis;

    } else {
      IS_INTERVAL_PASSED = currentMillis - PREVIOUS_MILLIS == 0;  
    }

  }
  //handleFlasherButton();
  handleIncreaseButton();
}

void handleFlasherButton() {
  boolean flasherButtonUp = digitalRead(FLASHER_BUTTON_PIN);

  if (IS_FLASHER_BUTTON_ENABLED && !flasherButtonUp) {
    delay(10);

    flasherButtonUp = digitalRead(FLASHER_BUTTON_PIN);
    if (!flasherButtonUp) { 
      IS_FLASHER_BUTTON_ENABLED = !IS_FLASHER_BUTTON_ENABLED;
    }
    analogWrite(H_LED_PIN, CURRENT_BRIGHTNESS);
  }

  IS_FLASHER_BUTTON_ENABLED = flasherButtonUp;
}

void handleIncreaseButton() {
  boolean increaseButtonUp = digitalRead(INCREASE_BUTTON_PIN);

  if (INCREASE_BUTTON_WAS_UP && !increaseButtonUp) {
    delay(10);

    increaseButtonUp = digitalRead(INCREASE_BUTTON_PIN);
    if (!increaseButtonUp) { 
      CURRENT_BRIGHTNESS = CURRENT_BRIGHTNESS >= MAX_BRIGHTNESS ? DEFAULT_BRIGHTNESS : CURRENT_BRIGHTNESS + 20;
    }
    analogWrite(H_LED_PIN, CURRENT_BRIGHTNESS);
  }

  INCREASE_BUTTON_WAS_UP = increaseButtonUp;
}