#include <NewPing.h>

#define TRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

class MOTORS
{
  private:
    const int Lpin1 = 11;
    const int Lpin2 = 10;
    const int Rpin1 = 9;
    const int Rpin2 = 6;
    
  public:
    void setLeft(int speed)
    {
      this->setMotor(this->Lpin1, this->Lpin2, speed);
    };

    void setRight(int speed)
    {
      this->setMotor(this->Rpin1, this->Rpin2, speed);
    }

    void setMotor(int pin1, int pin2, int speed)
    {
      if(speed > 0)
      {
        pinMode(pin1, OUTPUT);
        pinMode(pin2, INPUT);
        analogWrite(pin1, speed);
      }
      else if(speed < 0)
      {
        pinMode(pin1, INPUT);
        pinMode(pin2, OUTPUT);
        analogWrite(pin2, abs(speed));
      }
    };
} Motors;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int distance = sonar.ping_cm();
  if(distance > 20 || distance == 0)
  {
    Motors.setLeft(255);
    Motors.setRight(255);
  }
  else
  {
    Motors.setLeft(150);
    Motors.setRight(-150);
  }
}

