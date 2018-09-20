#pragma once

#include "model.h"
#include <vector>


class TerrainCreator{
public:
  TerrainCreator();
  TerrainCreator(int _i);
  void switchTerrain(int _i);
  std::vector<Model> getObjects();
private:
  void setTerrainObjects();
  int terrainSetup;
  std::vector<Model> terrainObjects;
};
