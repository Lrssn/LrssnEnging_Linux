#include "terrainCreator.h"

TerrainCreator::TerrainCreator(){
  this->terrainSetup = 0;
  setTerrainObjects();
}

TerrainCreator::TerrainCreator(int _i){
  this->terrainSetup = _i;
  setTerrainObjects();
}

void TerrainCreator::switchTerrain(int _i){
  this->terrainSetup = _i;
  setTerrainObjects();
}

std::vector<Model> TerrainCreator::getObjects(){
  return this->terrainObjects;
}

void TerrainCreator::setTerrainObjects(){
  if(terrainSetup == 0){//JUST FLOOR
    Model Ground("res/models/mountain/plane.obj");
    terrainObjects.push_back(Ground);
  }else if(terrainSetup == 1){ //TESTSCENE
    Model Ground("res/models/mountain/plane.obj");
    terrainObjects.push_back(Ground);
    Model cube1("res/models/cube/cube.obj", glm::vec3(1.0f, 0.5f, 2.0f));
    terrainObjects.push_back(cube1);
    cube1.setScale(glm::vec3(10.0f, 10.0f, 1.0f));
    cube1.setPosition(glm::vec3(15.0f, 5.0f, 2.0f));
    terrainObjects.push_back(cube1);
  }
}
