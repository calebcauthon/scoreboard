class ButtonState {
  public:
    int threshold = 500;
    int buttonPin;
    bool wasButtonPressed = false;
    void (*onPressHandler)(void);

    void setPin(int pin) {
      buttonPin = pin;
      pinMode(buttonPin, INPUT);
    }

    bool getState() {
      return digitalRead(buttonPin);
    }

    void onPress(void (*f)()) {
      onPressHandler = f;
    }

    void reset() {
      wasButtonPressed = false;
    }

    unsigned long timeOfLastChange = 0;
    unsigned long timeSinceLastChange() {
      return millis() - timeOfLastChange;
    }

    bool tick() {
      bool isButtonPressed = getState() == HIGH ? true : false;

      if (!wasButtonPressed && isButtonPressed && timeSinceLastChange() > threshold) {
        onPressHandler();
        timeOfLastChange = millis();
      } else if (wasButtonPressed && !isButtonPressed && timeSinceLastChange() > threshold) {
        onPressHandler();
        timeOfLastChange = millis();
      }

      wasButtonPressed = isButtonPressed;
    }
};
