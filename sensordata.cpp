#include "sensordata.h"

SensorData::SensorData(int & sector, int & iron, int & silicon) : sector{sector}, iron{iron}, silicon{silicon} {
}

const int & SensorData::getSector() {return sector;}
const int & SensorData::getIron() {return iron;}
const int & SensorData::getSilicon() {return silicon;}
