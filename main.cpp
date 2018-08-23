#include <Arduino.h>
#include <Adeept_PWMPCA9685.h>

#define trigger 3
#define echo 2

Adeept_PWMPCA9685 pwm0 = Adeept_PWMPCA9685(0x40);
Adeept_PWMPCA9685 pwm1 = Adeept_PWMPCA9685(0x41);

int angle(int angle){//Angle conversion
  if(angle>=180){angle=180;}
  if(angle<=0){angle=0;}
  return map(angle,0,180,130,600);//130-600
}
    //###############################################################################################//
   //                                   left leg                                                    //
  //                                                                                               //
 //                                                                                               //
//###############################################################################################//
class leftleg
{
  private:
    int _servo1;
    int _servo2;
    int _servo3;
    int _lr;

  public:
    leftleg(byte,byte,byte);
    void stretch();
    void idle();
    void stand();
};

leftleg::leftleg(byte servo1,byte servo2,byte servo3)
{
  _servo1 = servo1;
  _servo2 = servo2;
  _servo3 = servo3;
}
void leftleg::stretch()
{
  pwm0.setPWM(_servo1, 0, angle(90));
  pwm0.setPWM(_servo2, 0, angle(90));
  pwm0.setPWM(_servo3, 0, angle(90));
}

void leftleg::idle()
{
  pwm0.setPWM(_servo1, 0, angle(90));
  pwm0.setPWM(_servo2, 0, angle(130));
  pwm0.setPWM(_servo3, 0, angle(180));
}

void leftleg::stand()
{
  pwm0.setPWM(_servo1, 0, angle(90));
  pwm0.setPWM(_servo2, 0, angle(70));
  pwm0.setPWM(_servo3, 0, angle(145));
}
    //###############################################################################################//
   //                                  right leg                                                    //
  //                                                                                               //
 //                                                                                               //
//###############################################################################################//
class rightleg
{
  private:
    int _servo1;
    int _servo2;
    int _servo3;
    int _lr;

  public:
    rightleg(byte,byte,byte);
    void stretch();
    void idle();
    void stand();
};

rightleg::rightleg(byte servo1,byte servo2,byte servo3)
{
  _servo1 = servo1;
  _servo2 = servo2;
  _servo3 = servo3;
}

void rightleg::stretch()
{
  pwm1.setPWM(_servo1, 0, angle(90));
  pwm1.setPWM(_servo2, 0, angle(90));
  pwm1.setPWM(_servo3, 0, angle(90));
}

void rightleg::idle()
{
  pwm1.setPWM(_servo1, 0, angle(90));
  pwm1.setPWM(_servo2, 0, angle(40));
  pwm1.setPWM(_servo3, 0, angle(0));
}

void rightleg::stand()
{
  pwm1.setPWM(_servo1, 0, angle(90));
  pwm1.setPWM(_servo2, 0, angle(110));
  pwm1.setPWM(_servo3, 0, angle(35));
}
    //###############################################################################################//
   //                                   Head                                                        //
  //                                                                                               //
 //                                                                                               //
//###############################################################################################//
class head
{
  private:
    byte _pwm;
    byte _angle;
  public:
    head(byte);
    void dir(byte);
    int distance();

};

head::head(byte pin)
{
  _pwm = pin;
}

void head::dir(byte dir)
{
  _angle = dir;
  pwm1.setPWM(_pwm,0,angle(_angle));
}

int head::distance()
{
  digitalWrite(trigger,HIGH);
  delayMicroseconds(2);
  digitalWrite(trigger,LOW);
  double t = pulseIn(echo,HIGH,50000);
  t *= 0.034/2;
  return t;
}


    //###############################################################################################//
   //                                   Instances                                                   //
  //                                                                                               //
 //                                                                                               //
//###############################################################################################//
leftleg left1 (0,1,2);
leftleg left2 (3,4,5);
leftleg left3 (6,7,8);
rightleg right1 (0,1,2);
rightleg right2 (3,4,5);
rightleg right3 (6,7,8);
head head (15);


    //###############################################################################################//
   //                                   Setup                                                       //
  //                                                                                               //
 //                                                                                               //
//###############################################################################################//
void setup()
{
  pwm0.begin();
  pwm0.setPWMFreq(60);
  pwm1.begin();
  pwm1.setPWMFreq(60);
}
    //###############################################################################################//
   //                                   Loop                                                        //
  //                                                                                               //
 //                                                                                               //
//###############################################################################################//
void loop()
{
  //idle
  right1.idle();
  right2.idle();
  right3.idle();
  left1.idle();
  left2.idle();
  left3.idle();
  delay(5000);
  // stand
  right1.stand();
  right2.stand();
  right3.stand();
  left1.stand();
  left2.stand();
  left3.stand();
  head.dir(90);
  delay(5000);
}
