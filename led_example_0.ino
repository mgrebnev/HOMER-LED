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
boolean IS_FLASHER_BUTTON_ENABLED      = false;
boolean IS_INTERVAL_PASSED             = false;
boolean IS_DECREASE_BRIGHTNESS_ENABLED = false;
boolean IS_FLASHER_ENABLED             = false;

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

  analogWrite(3,  DEFAULT_BRIGHTNESS);
  analogWrite(5,  DEFAULT_BRIGHTNESS);
  analogWrite(6,  DEFAULT_BRIGHTNESS);
  analogWrite(9,  DEFAULT_BRIGHTNESS);
  analogWrite(10, DEFAULT_BRIGHTNESS);
  analogWrite(11, DEFAULT_BRIGHTNESS);
}


void loop() {
  unsigned long currentMillis = millis();

  if (IS_FLASHER_ENABLED) {
    if (currentMillis - PREVIOUS_MILLIS >= 15 && !IS_INTERVAL_PASSED) {
      if (CURRENT_BRIGHTNESS >= MAX_BRIGHTNESS) {
        IS_DECREASE_BRIGHTNESS_ENABLED = true; 
      }

      if (CURRENT_BRIGHTNESS <= 3) {
        IS_DECREASE_BRIGHTNESS_ENABLED = false; 
      }

      CURRENT_BRIGHTNESS = IS_DECREASE_BRIGHTNESS_ENABLED ? CURRENT_BRIGHTNESS - 3 : CURRENT_BRIGHTNESS + 2;

      setBrightness(H_LED_PIN, CURRENT_BRIGHTNESS);

      IS_INTERVAL_PASSED = true;
      PREVIOUS_MILLIS = currentMillis;

    } else {
      IS_INTERVAL_PASSED = currentMillis - PREVIOUS_MILLIS == 0;  
    }
  }

  handleFlasherButton();
  handleIncreaseButton();
}

void handleFlasherButton() {
  boolean flasherButtonUp = digitalRead(FLASHER_BUTTON_PIN);

  if (IS_FLASHER_BUTTON_ENABLED && !flasherButtonUp) {
    delay(10);

    flasherButtonUp = digitalRead(FLASHER_BUTTON_PIN);
    if (!flasherButtonUp) { 
      IS_FLASHER_ENABLED = !IS_FLASHER_ENABLED;
      setGeneralBrightness(DEFAULT_BRIGHTNESS + 20);
    }
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

    setGeneralBrightness(CURRENT_BRIGHTNESS);
  }
  INCREASE_BUTTON_WAS_UP = increaseButtonUp;
}

void setGeneralBrightness(int brightness) {
  setBrightness(H_LED_PIN,    brightness);
  setBrightness(O_LED_PIN,    brightness);
  setBrightness(M_LED_PIN,    brightness);
  setBrightness(E_LED_PIN,    brightness);
  setBrightness(R_LED_PIN,    brightness);
  setBrightness(LOVE_LED_PIN, brightness);

  CURRENT_BRIGHTNESS = brightness;
}

void setBrightness(int pin, int brightness) {
  analogWrite(pin, brightness);
}
