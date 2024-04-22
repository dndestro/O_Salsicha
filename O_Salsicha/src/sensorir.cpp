#include "sensorir.h"

SensorIR::SensorIR(){

}

uint8_t SensorIR::iniciaSensorIR(){
    if(!cLox.begin()){
        return 0;
    }
    else{
        return 1;
    }
}

float SensorIR::getDistance(){
    VL53L0X_RangingMeasurementData_t medida;
    cLox.rangingTest (&medida, false);
      if (medida.RangeStatus != ERROLEITURA)
      {
        return medida.RangeMilliMeter;
      }
      else{
        return (-1);
      }
}