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
    delayMicroseconds(12);

    digitalWrite(pin, LOW);

    pinMode(pin, INPUT);
    //long duration = pulseIn(pin, HIGH, 11764);
    long duration = pulseIn(pin, HIGH);
    //double distance = V_SOUND * duration;
    double distance = duration / 29.0 / 2.0;
    //Serial.println(duration);
    return distance;
  }
};

static constexpr int SPEAKER_PIN = 6;
static constexpr UltrasonicSensor us = 7;

static constexpr double MIN_D = 35.0;
static constexpr double MAX_D = 400.0;

static constexpr double MIN_FREQ = 500.0;
static constexpr double MAX_FREQ = 6000.0;

static constexpr int MIN_PAUSE = 100;
static constexpr int MAX_PAUSE = 2000;

static constexpr unsigned long BEEP_TIME = 50;

static unsigned long last = 0;
static unsigned long next = 0;
#define DEBUGGING
void setup()
{
#ifdef DEBUGGING
  Serial.begin(9600);
#endif
}

void loop()
{
  //tone(SPEAKER_PIN, 1024, BEEP_TIME);
  double distance = us.distance();
  if (distance < 0.1)
    distance = 400;
  double frequency = map(distance, MIN_D, MAX_D, MIN_FREQ, MAX_FREQ);
  unsigned long pause = max(map(distance, MIN_D, MAX_D, MIN_PAUSE, MAX_PAUSE), MIN_PAUSE);
  unsigned long t = millis();

  next = last + pause;

  if (t >= next)
  {
    last = t;

    //tone(SPEAKER_PIN, 1024, BEEP_TIME);
  }

#ifdef DEBUGGING
  //Serial.print("L: ");
  //Serial.println(last);
  //Serial.print("D:");
  Serial.println(distance);
#endif
}
