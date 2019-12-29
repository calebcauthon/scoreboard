class ButtonState {
  public:
    int threshold = 500;
    int buttonPin;
    bool wasButtonPressed = false;
    void (*onPressHandler)(void);

    bool getState() {
      pinMode(buttonPin, INPUT);
      return digitalRead(buttonPin);
    }

    void onPress(void (*f)()) {
      onPressHandler = f;
    }

    int timeOfLastChange = 0;
    int timeSinceLastChange() {
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
