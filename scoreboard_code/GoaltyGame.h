class GoaltyGame {
public:
  int leftScore = 0;
  int rightScore = 0;

  void increaseLeft() {
    leftScore++;
  }

  void increaseRight() {
    rightScore++;
  }

  void decreaseLeft() {
    leftScore--;
  }

  void decreaseRight() {
    rightScore--;
  }
};
