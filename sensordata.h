#pragma once

class SensorData {
public:
  SensorData(int & sector, int & iron, int & silicon);
  const int & getSector();
  const int & getIron();
  const int & getSilicon();
private:
  int sector;
  int iron;
  int silicon;
};
