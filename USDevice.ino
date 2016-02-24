class UltrasonicSensor
{
  static constexpr double V_SOUND = 340.29 * 100.0 / 1000000.0;
  int pin;

public:
  constexpr UltrasonicSensor(int pin = 7) :
    pin(pin)
  {}

  inline double distance() const
  {
    pinMode(pin, OUTPUT);

    digitalWrite(pin, LOW);
    delayMicroseconds(2);

    digitalWrite(pin, HIGH);
    delayMicroseconds(5);

    digitalWrite(pin, LOW);

    pinMode(pin, INPUT);
    long duration = pulseIn(pin, HIGH);
    float distance = V_SOUND * duration;

    return distance;
  }
};

static constexpr int SPEAKER_PIN = 6;
static constexpr UltrasonicSensor us = 7;

static constexpr double MIN_D = 20.0;
static constexpr double MAX_D = 400.0;

static constexpr double MIN_FREQ = 500.0;
static constexpr double MAX_FREQ = 6000.0;

void setup() {}

void loop()
{
  double distance = us.distance();
  double frequency = map(distance, MIN_D, MAX_D, MIN_FREQ, MAX_FREQ);

  tone(SPEAKER_PIN, frequency);
}
