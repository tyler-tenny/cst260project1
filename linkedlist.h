#pragma once

#include "sensordata.h"

class LinkedList {
public:
  LinkedList();

  LinkedList(const LinkedList & other);

  LinkedList & operator=(const LinkedList & other);

  ~LinkedList();

  void addSensorData(SensorData & newData);

  void printListBySector();
  void printListByIron();
  void printListBySilicon();
  void printSectorAverages();
  void printSectors();

  bool containsSector(const int & sector);

  void removeSector(int & sector);

  struct Node {
    SensorData data;
    Node * next_by_sector{};
    Node * next_by_iron{};
    Node * next_by_silicon{};
  };

private:
  Node * head_by_sector{};
  Node * head_by_iron{};
  Node * head_by_silicon{};

  int count{};
};


