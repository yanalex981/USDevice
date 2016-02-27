class UltrasonicSensor
{
  static constexpr unsigned int DELAY = 70;
  unsigned int pin;

  unsigned long nextPing;
  unsigned long prevRead;

  inline unsigned long ping()
  {
    pinMode(pin, OUTPUT);

    digitalWrite(pin, LOW);
    delayMicroseconds(2);

    digitalWrite(pin, HIGH);
    delayMicroseconds(12);

    digitalWrite(pin, LOW);

    pinMode(pin, INPUT);
    //long duration = pulseIn(pin, HIGH, 11764);
    unsigned long duration = pulseIn(pin, HIGH);

    return duration;
  }

public:
  UltrasonicSensor(unsigned int pin = 7) :
    pin{pin},
    nextPing{0},
    prevRead{0}
  {
    distance();
  }

  inline unsigned long distance()
  {
    unsigned long t = millis();
    
    if (t < nextPing)
      return prevRead;

    nextPing = t + DELAY;
    unsigned long duration = ping();
    unsigned long distance = duration / 58;
    prevRead = distance;
    
    return distance;
  }
};

static constexpr int SPEAKER_PIN = 6;
static UltrasonicSensor us = 7;

static constexpr unsigned long MIN_D = 10;
static constexpr unsigned long MAX_D = 400;

static constexpr unsigned long MIN_FREQ = 500;
static constexpr unsigned long MAX_FREQ = 6000;

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
  unsigned long distance = us.distance();
  
  if (distance < 0.1)
    distance = 400;
  //double frequency = map(distance, MIN_D, MAX_D, MIN_FREQ, MAX_FREQ);
  unsigned long pause = map(distance, MIN_D, MAX_D, MIN_PAUSE, MAX_PAUSE);
  unsigned long t = millis();

  next = last + pause;

  if (t >= next)
  {
    last = t;

    tone(SPEAKER_PIN, 1024, BEEP_TIME);
  }

#ifdef DEBUGGING
  //Serial.print("L: ");
  //Serial.println(last);
  //Serial.print("D:");
  Serial.println(distance);
#endif
}
