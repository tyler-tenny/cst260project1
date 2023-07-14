#include "linkedlist.h"
#include <iostream>

LinkedList::LinkedList() {}

LinkedList::LinkedList(const LinkedList & other) {}

LinkedList & LinkedList::operator=(const LinkedList & other) {return *this;}

LinkedList::~LinkedList() {
  //start at head
  Node * cur{head_by_sector};
  //traverse by sector, pointing temp to cur, setting cur to next, and then deleting temp, until !cur
  while (cur) {
    Node * temp = cur;
    cur = temp->next_by_sector;
    delete temp;
  }

  //explicitly make sure heads are null
  head_by_sector = nullptr;
  head_by_iron = nullptr;
  head_by_silicon = nullptr;
  count = 0;
}

void LinkedList::addSensorData(SensorData & newData) {
  //create a node and pointer for the new data
  Node * newNode = new Node{newData};
  bool insertedSector{false};
  bool insertedIron{false};
  bool insertedSilicon{false};

  //if there is no head, new node becomes the head
  if (head_by_sector == nullptr) {
    head_by_sector = newNode;
    head_by_iron = newNode;
    head_by_silicon = newNode;
    newNode->next_by_sector = nullptr;
    newNode->next_by_iron = nullptr;
    newNode->next_by_silicon = nullptr;
    ++count;
    insertedSector = true;
    insertedIron = true;
    insertedSilicon = true;
  }
  //if we haven't already inserted, check if the new node data is smaller than or equal to head. if so, nn becomes head by data.
  if (!insertedSector && (newNode->data.getSector() <= head_by_sector->data.getSector())) {
    newNode->next_by_sector = head_by_sector;
    head_by_sector = newNode;
    insertedSector = true;
  }
  if (!insertedIron && (newNode->data.getIron() <= head_by_iron->data.getIron())) {
    newNode->next_by_iron = head_by_iron;
    head_by_iron = newNode;
    insertedIron = true;
  }
  if (!insertedSilicon && (newNode->data.getSilicon() <= head_by_silicon->data.getSilicon())) {
    newNode->next_by_silicon = head_by_silicon;
    head_by_silicon = newNode;
    insertedSilicon = true;
  }
  //go through the list until there is a node equal to or bigger than nn. then insert before it
  Node * next = head_by_sector->next_by_sector;
  Node * prev = head_by_sector;
  //traverse while next is valid and we haven't marked it as inserted yet
  while (!insertedSector && next) {
    //if nn sector is smaller than or equal to the next one, insert before it and mark as inserted
    if (newNode->data.getSector() <= next->data.getSector()) {
      prev->next_by_sector = newNode;
      newNode->next_by_sector = next;
      insertedSector = true;
    }
    //if nn sector is bigger than the next one get ready to check the next one
    else if (next) {
      prev = next;
      next = next->next_by_sector;
    }
  }
  //if we traversed and never inserted, add at end
  if (!insertedSector) {
    prev->next_by_sector = newNode;
    insertedSector = true;
  }
  //start over for iron
  next = head_by_iron->next_by_iron;
  prev = head_by_iron;
  //traverse while next is valid and we haven't marked it as inserted yet
  while (!insertedIron && next) {
    //if nn iron is smaller than or equal to the next one, insert before it and mark as inserted
    if (newNode->data.getIron() <= next->data.getIron()) {
      prev->next_by_iron = newNode;
      newNode->next_by_iron = next;
      insertedIron = true;
    }
    //if nn iron is bigger than the next one, get ready to check the next one
    else if (next) {
      prev = next;
      next = next->next_by_iron;
    }
  }
  //if we traversed and never inserted, add at end
  if (!insertedIron) {
    prev->next_by_iron = newNode;
    insertedIron = true;
  }
  //start over for silicon
  next = head_by_silicon->next_by_silicon;
  prev = head_by_silicon;
  //traverse while next is valid and we haven't marked it as inserted yet
  while (!insertedSilicon && next) {
    //if nn silicon is smaller than or equals the next one, insert before it and mark as inserted
    if (newNode->data.getSilicon() <= next->data.getSilicon()) {
      prev->next_by_silicon = newNode;
      newNode->next_by_silicon = next;
      insertedSilicon = true;
    }
    //if nn silicon is bigger than the next one or equal, get ready to check the next one
    else if (next) {
      prev = next;
      next = next->next_by_silicon;
    }
  }
  //if we traversed and never inserted, add at end
  if (!insertedSilicon) {
    prev->next_by_silicon = newNode;
    insertedSilicon = true;
  }
  ++count;
}

void LinkedList::printListBySector() {
  Node * cur = head_by_sector;
  std::cout << "Data by Sector \n";
  while (cur) {
    std::cout << "Sector: #" << cur->data.getSector() << " " << cur->data.getIron() << " grams iron, " << cur->data.getSilicon() << " milligrams silicon";
    std::cout << "\n";
    cur = cur->next_by_sector;
  }
}

void LinkedList::printListByIron() {
  Node * cur = head_by_iron;
  std::cout << "Data by Iron Level\n";
  while (cur) {
    std::cout << "Sector: #" << cur->data.getSector() << " " << cur->data.getIron() << " grams iron, " << cur->data.getSilicon() << " milligrams silicon";
    std::cout << "\n";
    cur = cur->next_by_iron;
  }
}

void LinkedList::printListBySilicon() {
  Node * cur = head_by_silicon;
  std::cout << "Data by Silicon Level\n";
  while (cur) {
    std::cout <<"Sector: #" << cur->data.getSector() << " " << cur->data.getIron() << " grams iron, " << cur->data.getSilicon() << " milligrams silicon";
    std::cout << "\n";
    cur = cur->next_by_silicon;
  }
}

void LinkedList::printSectorAverages() {
  Node * cur{head_by_sector};
  int curSector{1};
  int count{};
  int sumIron{};
  int sumSilicon{};
  //while we are in the list...
  while (cur) {
    //if our cur pointer is a higher number sector than we're looking at and we have no current sectors counted, print no data
    if (cur->data.getSector() > curSector && count == 0) {
      std::cout << "Sector: #" << curSector << "  -- no data -- \n";
      ++curSector;
    }
    //if our cur pointer is a higher number sector than we're looking at and we have previous counts at current value, calc the avg and print it  
    else if (cur->data.getSector() > curSector && count > 0) {
      int averageIron = sumIron / count;
      int averageSilicon = sumSilicon / count;
      std::cout << "Sector: #" << curSector << " " << averageIron << " grams iron, " << averageSilicon << " milligrams silicon";
      std::cout << "\n";
      count = 0;
      sumIron = 0;
      sumSilicon = 0;
      ++curSector;
    }
    //if our cur pointer is equal to our sector number, add to sums and keep looking at this number and move cur
    else if (cur->data.getSector() == curSector) {
      sumIron += cur->data.getIron();
      sumSilicon += cur->data.getSilicon();
      ++count;
      cur = cur->next_by_sector;
    }
  }
  //print last sector
  int averageIron = sumIron / count;
  int averageSilicon = sumSilicon / count;
  std::cout << "Sector: #" << curSector << " " << averageIron << " grams iron, " << averageSilicon << " milligrams silicon";
  std::cout << "\n";
}

void LinkedList::printSectors() {
  Node * cur{head_by_sector};
  int curSector{};
  int prevSector{};
  while (cur) {
    //set the int to the pointer number
    curSector = cur->data.getSector();
    //if the int is different, print it. then move on
    if (curSector != prevSector) {
      std::cout << curSector;
    }
    if (cur->next_by_sector && curSector != prevSector) {
      std::cout << ", ";
      prevSector = curSector;
    }
    cur = cur->next_by_sector;
  }
  std::cout << "\n";
}

bool LinkedList::containsSector(const int & sector) {
  Node * cur{head_by_sector};
  while (cur) {
    if (sector == cur->data.getSector()) {
      return true;
    }
    cur = cur->next_by_sector;
  }
  return false;
}

void LinkedList::removeSector(int & sector) {
  //by sector first
  Node * cur{head_by_sector};
  Node * prev{};
  
  while (cur) {
    if (cur->data.getSector() == sector) {
      if(!prev) {
        head_by_sector = cur->next_by_sector;
      }
      else {
        prev->next_by_sector = cur->next_by_sector;
      }
      cur = (!prev) ? head_by_sector : prev->next_by_sector;
    }
    else {
      prev = cur;
      cur = cur->next_by_sector;
    }
  }
  //by iron now
  cur = head_by_iron;
  prev = nullptr;

  while (cur) {
    if (cur->data.getSector() == sector) {
      if(!prev) {
        head_by_iron = cur->next_by_iron;
      }
      else {
        prev->next_by_iron = cur->next_by_iron;
      }
      cur = (!prev) ? head_by_iron : prev->next_by_iron;
    }
    else {
      prev = cur;
      cur = cur->next_by_iron;
    }
  }
  //by silicon finally with delete
  cur = head_by_silicon;
  prev = nullptr;

  while (cur) {
    if (cur->data.getSector() == sector) {
      if(!prev) {
        head_by_silicon = cur->next_by_silicon;
      }
      else {
        prev->next_by_silicon = cur->next_by_silicon;
      }
      delete cur;
      cur = (!prev) ? head_by_silicon : prev->next_by_silicon;
    }
    else {
      prev = cur;
      cur = cur->next_by_silicon;
    }
  }
}
     
