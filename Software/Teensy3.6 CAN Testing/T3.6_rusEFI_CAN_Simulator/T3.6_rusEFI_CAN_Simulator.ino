// -------------------------------------------------------------

//

#include <FlexCAN.h>
#define ledPin 13
int ledState = 0;
int var = 13 * 1000 ;
int canID = 512;
int delayTime = 50; 
int canID0 = canID;
int canID1 = canID + 1;
int canID2 = canID + 2;
int canID3 = canID + 3;
int canID4 = canID + 4;
int canID5 = canID + 5;
int canID6 = canID + 6;

float afr = 12.34;
int rpm = 0;
float ignTiming =  0;
float injDuty = 0;
int vss = 0;
int accel = 0;
int tps1 = 0;
int tps2 = 0;
int map1 = 123;
float clt = 56.78;
float iat = 45.67;
int auxT1 =0;
int auxT2 =0;
int mcuT = 0;
int oilPress = 0;
int vvt = 0;
float vbat = 0;
int airMass = 0;
int estAir = 0;
int injPW =0;
int fuel = 0;

int tempOffset = 40;

int warningCount = 0;
int lastError = 0;
int revLimit = 0;
int mainRelay = 0;
int fuelPump = 0;
int cel = 0;
int ego = 0;

//#ifndef __MK66FX1M0__
//  #error "Teensy 3.6 with dual CAN bus is required to run this example"
//#endif

static CAN_message_t msg;
static CAN_message_t msg0;
static CAN_message_t msg1;
static CAN_message_t msg2;
static CAN_message_t msg3;
static CAN_message_t msg4;
static CAN_message_t msg5;

// -------------------------------------------------------------

void messageSetup(){

    msg.ext = 0;
  msg.id = canID - 1;
  msg.len = 8;
  msg.buf[0] = 0;
  msg.buf[1] = 0;
  msg.buf[2] = 0;
  msg.buf[3] = 0;
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  msg0.ext = 0;
  msg0.id = canID0;
  msg0.len = 8;
  msg0.buf[0] = 0;
  msg0.buf[1] = 1;
  msg0.buf[2] = 2;
  msg0.buf[3] = 3;
  msg0.buf[4] = 4;
  msg0.buf[5] = 5;
  msg0.buf[6] = 6;
  msg0.buf[7] = 7;

  msg1.ext = 0;
  msg1.id = canID1;
  msg1.len = 8;
  // RPM
  msg1.buf[0] = (byte) (rpm & 0xFF);
  msg1.buf[1] = (byte) ((rpm >> 8) & 0xFF);
  
  // Ign Timing
 int ignTimingInt = (ignTiming * (1/0.2));
  msg1.buf[2] = (byte) (ignTimingInt & 0xFF);
  msg1.buf[3] = (byte) ((ignTimingInt >> 8) & 0xFF);
 
  // Injector Duty
  int injDutyInt = injDuty * (1/0.5);
  msg1.buf[4] = (byte) (injDutyInt & 0xFF);
  msg1.buf[5] = (byte) ((injDutyInt >> 8) & 0xFF);
  
  // Speed
  msg1.buf[6] = vss;
  // reserved
  msg1.buf[7] = 0;

  msg2.ext = 0;
  msg2.id = canID2;
  msg2.len = 8;
  
  // Pedal Position
  accel = accel * (1/0.01);
  msg2.buf[0] = (byte) (accel & 0xFF);
  msg2.buf[1] = (byte) ((accel >> 8) & 0xFF);
  
  // Tps 1
  tps1 = tps1 * (1/0.01);
  msg2.buf[2] = (byte) (tps1 & 0xFF);
  msg2.buf[3] = (byte) ((tps1 >> 8) & 0xFF);
  
  // Tps 2
  tps2 = tps2 * (1/0.01);
  msg2.buf[4] = (byte) (tps2 & 0xFF);
  msg2.buf[5] = (byte) ((tps2 >> 8) & 0xFF);
  // reserved
  
  msg2.buf[6] = 0;
  msg2.buf[7] = 0;

  msg3.ext = 0;
  msg3.id = canID3;
  msg3.len = 8;

  int map1Int = map1 * (1/0.03);
  msg3.buf[0] = (byte) (map1Int & 0xFF);
  msg3.buf[1] = (byte) ((map1Int >> 8) & 0xFF);
  
  msg3.buf[2] = clt + tempOffset;
  msg3.buf[3] = iat + tempOffset;
  msg3.buf[4] = auxT1;
  msg3.buf[5] = auxT2;
  msg3.buf[6] = mcuT;
  msg3.buf[7] = fuel;
  

  msg4.ext = 0;
  msg4.id = canID4;
  msg4.len = 8;
  // AFR
  
  int afrInt = afr * 1000;
  msg4.buf[0] = (byte) (afrInt & 0xFF);
  msg4.buf[1] = (byte) ((afrInt >> 8) & 0xFF);
  
  // Oil Pressure
  oilPress = oilPress * (1/0.03);
  msg4.buf[2] = (byte) (oilPress & 0xFF);
  msg4.buf[3] = (byte) ((oilPress >> 8) & 0xFF);
  
  // VVT position
  vvt = vvt * (1/0.02);
  msg4.buf[4] = (byte) (vvt & 0xFF);
  msg4.buf[5] = (byte) ((vvt >> 8) & 0xFF);
  
  // Battery milivolts
  int vbatInt = vbat * (1/.001);
  msg4.buf[6] = (byte) (vbatInt & 0xFF);
  msg4.buf[7] = (byte) ((vbatInt >> 8) & 0xFF);

  msg5.ext = 0;
  msg5.id = canID5;
  msg5.len = 8;
  // Air mass, cylinder
  msg5.buf[0] = (byte) (airMass & 0xFF);
  msg5.buf[1] = (byte) ((airMass >> 8) & 0xFF);
  // Est air flow
  estAir = estAir * (1/0.1);
  msg5.buf[2] = (byte) (estAir & 0xFF);
  msg5.buf[3] = (byte) ((estAir >> 8) & 0xFF);
  // Injector pulse width
  injPW = injPW * (1/.003);
  msg5.buf[4] = (byte) (injPW & 0xFF);
  msg5.buf[5] = (byte) ((injPW >> 8) & 0xFF);
  // reserved
  msg5.buf[6] = 0;
  msg5.buf[7] = 0;

}

void incrementData(){
  warningCount++;
  lastError++;

  if (cel==1){
    revLimit = 0;
    mainRelay = 0;
    cel = 0;
    ego = 0;
    fuelPump = 0;
  }
  else {
    revLimit = 1;
    mainRelay = 1;
    cel = 1;
    ego = 1;
    fuelPump = 1;
  }

   
  afr = afr + 0.2;
  if (afr > 22){
    afr = 0;
  }
  
  rpm = rpm + 10;
  if (rpm>8000){
    rpm=0;
  }

  ignTiming = ignTiming + 1;
  if (ignTiming > 50){
    ignTiming = -50;
  }

  injDuty = (injDuty + 1);
  if (injDuty > (100)){
  injDuty = 0;
  }

  vss++;
  if (vss > 300){
    vss =0;
  }

  accel++;
  if (accel > 100){
    accel = 0;
  }

  tps1++;
  if (tps1 > 100){
    tps1 = 0;
  }

  tps2++;
  if (tps2 > 100){
    tps2 = 0;
  }

  map1=map1 + 1;
    if (map1 > (250)){
    map1 = 0;
  }
  
  clt=clt+1; 
  if (clt > 280){
    clt = -50;
  }

  iat=iat+1;
  if (iat > 120){
    iat = -50;
  }

  auxT1=auxT1+2;
  if (auxT1 > 200){
    auxT1 = 0;
  }

   auxT2=auxT2+2;
  if (auxT2 > 200){
    auxT2 = 0;
  }

  mcuT=mcuT+2;
  if (mcuT > 200){
    mcuT = 0;
  }

  fuel++;
  if (fuel > 100){
    fuel = 0;
  }

  oilPress++;
    if (oilPress > 100){
    oilPress = 0;
  }

  vvt++;
    if (vvt > 100){
    vvt = 0;
  }

    vbat = vbat + 0.5;
    if (vbat > 20){
    vbat = 0;
  }


    airMass++;
    if (airMass > 100){
    airMass = 0;
  }

    estAir++;
    if (estAir > 100){
    estAir = 0;
  }

     injPW++;
    if (injPW > 100){
    injPW = 0;
  }
}

// -------------------------------------------------------------
void setup(void)
{
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,ledState);
  ledState = !ledState;
    
  delay(1000);
  Serial.println(F("Hello Teensy CAN Test Transmitter."));

  Can1.begin(500000);  
//  Can1.begin();

  //if using enable pins on a transceiver they need to be set on
  pinMode(2, OUTPUT);
  pinMode(35, OUTPUT);

  digitalWrite(2, HIGH);
  digitalWrite(35, HIGH);

 
  messageSetup();

  digitalWrite(ledPin,ledState);
  ledState = !ledState;
}


// -------------------------------------------------------------


// -------------------------------------------------------------
void loop(void)
{

  

  
  //incrementData();
  messageSetup();
  
  msg.buf[0]++;
  msg.buf[1]++;
  msg.buf[2]++;
  msg.buf[3]++;
  msg.buf[4]++;
  msg.buf[5]++;
  msg.buf[6]++;
  msg.buf[7]++;
  
  Can1.write(msg);
  Can1.write(msg0);
  Can1.write(msg1);
  Can1.write(msg2);
  Can1.write(msg3);
  Can1.write(msg4);
  Can1.write(msg5);
  delay(delayTime);

  digitalWrite(ledPin,ledState);
  ledState = !ledState;
}
