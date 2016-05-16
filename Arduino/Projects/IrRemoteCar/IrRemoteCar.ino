#include <DualDriver.h>
#include <IrRobotKeyMap.h>
#include <IRremote.h>

DualDriver Motor;

#define RECV_PIN (4)
IRrecv irrecv(RECV_PIN);

void setup()
{
  irrecv.enableIRIn(); // Start the receiver

  Serial.begin(9600);
  while(!Serial);
}

void loop(){
  long key = GetIrKey();

  switch(key)
  {
    case IR_KEY_UP:
      Motor.SetSpeedA(255);
      Motor.SetSpeedB(255);
      break;

    case IR_KEY_DOWN:
      Motor.SetSpeedA(-255);
      Motor.SetSpeedB(-255);
      break;

    case IR_KEY_LEFT:
      Motor.SetSpeedA(255);
      Motor.SetSpeedB(0);
      break;

    case IR_KEY_RIGHT:
      Motor.SetSpeedA(0);
      Motor.SetSpeedB(255);
      break;

    default:
      Motor.SetSpeedA(0);
      Motor.SetSpeedB(0);
      break;
  }
  delay(100);
}

long lastKeyPressed;
decode_results results;
#define REPEAT_KEY (0xFFFFFFFF)

long GetIrKey()
{
  if (irrecv.decode(&results)) {
    if(results.value != REPEAT_KEY)
    {
      lastKeyPressed = results.value;
    }
    irrecv.resume(); // Receive the next value
    return lastKeyPressed;    
  }
  return 0;
}

