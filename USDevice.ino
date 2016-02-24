class UltrasonicSensor
{
  static constexpr double V_SOUND = 340.29 * 100.0 / 1000000.0;
  int pin;

public:
  UltrasonicSensor(int pin = 7) :
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

UltrasonicSensor us;

void setup() {}

void loop()
{
  //
}
