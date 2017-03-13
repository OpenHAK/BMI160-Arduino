#include <BMI160Gen.h>

const int bmi160_select_pin = 10;
const int bmi160_interrupt_pin = 20;
#include <Wire.h>
#define SCL_PIN 13
#define SDA_PIN 10

//int 1 = 20
//int 2 = 24

void bmi160_intr(void)
{
  byte int_status = BMI160.getIntStatus0();
  Serial.print("Steps ");
  Serial.print(BMI160.getStepCount());
  Serial.print(" Single ");
  Serial.print(bitRead(int_status,5));
  Serial.print(" Double ");
  Serial.print(bitRead(int_status,4));  
  Serial.print(" REG ");
  Serial.print(int_status,BIN);
  Serial.println(" BMI160 interrupt: TAP! ");
}

void setup() {
  Wire.beginOnPins(SCL_PIN,SDA_PIN);
  NRF_TWI1->FREQUENCY = TWI_FREQUENCY_FREQUENCY_K400 << TWI_FREQUENCY_FREQUENCY_Pos; 
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
  Serial.println("Initializing IMU device...");
  BMI160.begin(bmi160_select_pin, bmi160_interrupt_pin);
  BMI160.attachInterrupt(bmi160_intr);
  BMI160.setIntTapEnabled(true);
  BMI160.setIntDoubleTapEnabled(true);
  BMI160.setStepDetectionMode(BMI160_STEP_MODE_NORMAL);
  //Serial.print("Tap Thresh");
  //BMI160.setTapDetectionThreshold();
  //uint8_t test = BMI160.getTapDetectionThreshold();
  //Serial.println(test);
}

void loop() {
}
