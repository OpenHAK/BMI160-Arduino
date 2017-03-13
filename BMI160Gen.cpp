#include "BMI160Gen.h"
#include "internal/ss_spi.h"

#if defined(ARDUINO_ARC32_TOOLS)
#define digitalPinToInterrupt(a) (a)
#endif

bool BMI160GenClass::begin(const int spi_cs_pin, const int intr_pin1, const int intr_pin2)
{
    ss_spi_cs = spi_cs_pin;
    if (0 <= intr_pin1) {
        //interrupt_pin = digitalPinToInterrupt(intr_pin);
        interrupt_pin1 = intr_pin1;
        Serial.println("setting int pin in begin");
    }
    if (0 <= intr_pin2) {
        interrupt_pin2 = intr_pin2;
        Serial.println("setting int pin2 in begin");
    }
    return CurieIMUClass::begin();
}

void BMI160GenClass::attachInterrupt(void (*callback)(void))
{
    Serial.println("calling attachInterrupt");
    CurieIMUClass::attachInterrupt(NULL);
    Serial.println(0 <= interrupt_pin1);
    if (0 <= interrupt_pin1) {
        ::attachInterrupt(interrupt_pin1, callback, LOW);
        Serial.println("BMI160GenClass::attachInterrupt1.");
    } else {
        Serial.println("BMI160GenClass::attachInterrupt: No interruption pin specified.");
    }
}

BMI160GenClass BMI160;
