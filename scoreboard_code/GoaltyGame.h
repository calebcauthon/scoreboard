class GoaltyGame {
public:
  int leftScore = 0;
  int rightScore = 0;
  int minimumScore = 0;

  void (*onGameOverHandler)(void);
  void onGameOver(void (*f)()) {
    onGameOverHandler = f;
  }

  void (*onScoreIncreaseHandler)(void);
  void onScoreIncrease(void (*f)()) {
    onScoreIncreaseHandler = f;
  }

  void reset() {
    leftScore = 0;
    rightScore = 0;
  }

  bool isGameOver() {
    int higherScore = leftScore > rightScore ? leftScore : rightScore;
    int lowerScore  = leftScore > rightScore ? rightScore : leftScore;

    if (higherScore >= 5 && lowerScore <= (higherScore - 2)) {
      return true;
    } else if (higherScore == 7) {
      return true;
    } else {
      return false;
    }
  }

  void changeLeft(int amount) {
    if (isGameOver()) {
      return;
    }

    if ((leftScore + amount) < minimumScore) {
      return;
    }

    leftScore += amount;

    if (amount > 0) {
      onScoreIncreaseHandler();
    }

    if (isGameOver()) {
      onGameOverHandler();
    }
  }

  void changeRight(int amount) {
    if (isGameOver()) {
      return;
    }

    if ((rightScore + amount) < minimumScore) {
      return;
    }

    rightScore += amount;

    if (amount > 0) {
      onScoreIncreaseHandler();
    }

    if (isGameOver()) {
      onGameOverHandler();
    }
  }

  void increaseLeft() {
    changeLeft(1);
  }

  void increaseRight() {
    changeRight(1);
  }

  void decreaseLeft() {
    changeLeft(-1);
  }

  void decreaseRight() {
    changeRight(-1);
  }
};
