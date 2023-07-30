#include "datalogger.h"
#include <iostream>

DataLogger::DataLogger() {}

void DataLogger::addData(int & sector, int & iron, int & silicon) {
  SensorData newData{sector, iron, silicon};
  list.addSensorData(newData); 
}

bool DataLogger::containsSector(const int & sector) {
  return list.containsSector(sector);
}

void DataLogger::removeSector(int & sector) {
  list.removeSector(sector);
}

void DataLogger::printLine() {
  for (int i{70}; i > 0; --i) {
    std::cout << "-";
  }
  std::cout << "\n";
}

void DataLogger::printReport() {
  printLine();
  std::cout << "Data values\n";
  printLine();

  list.printListBySector();
  list.printListByIron();
  list.printListBySilicon();

  printLine();
  std::cout << "Averages per sector\n";
  printLine();

  list.printSectorAverages();
}

void DataLogger::printSectorList() {
  list.printSectors();
}
