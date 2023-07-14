#pragma once
#include "linkedlist.h"

class DataLogger {
public:

  DataLogger();
  void addData(int & sector, int & iron, int & silicon);
  bool containsSector(const int & sector);
  void removeSector(int & sector);
  void printReport();
  void printSectorList();
  void printLine();


private:
  LinkedList list;
};
