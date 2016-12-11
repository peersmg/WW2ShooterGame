#pragma once
#include "GameObject.h"
#include "Building.h"
#include "Ship.h"

class BuildingCollection : public GameObject
{
  const static int NUMBER_OF_BUILDINGS = 15;      // Number of buildings to create initially
  const static float BUILDING_START;              // Start position of the building

  Rectangle2D collisionShape;                     // Collision shape
  Building *m_pBuildings[NUMBER_OF_BUILDINGS];    // Array of pointers to buildings
  Ship *m_pShip;                                  // Pointer to the player
  int m_firstBuildingIndex;                       // Index of the first building
  int m_lastBuildingIndex;                        // Index of the last building
  int m_buildingsPassed;                          // Number of buildings the player has passed

public:

  // Constructor
  BuildingCollection();

  // Initialise the gameobject with default values
  void Initialise(Ship *player);

  // Process the collisions of this gameobject
  void ProcessCollision(GameObject &other);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);

  // Finds the index of the last building
  int FindLastBuilding();

  // Find the index of the first building
  int FindFirstBuilding();
   
  // Returns how many buildings have been passed
  int GetBuildingsPassed();

  // Finds a building offscreen
  Building *GetOffscreenBuilding();

  // Returns the collision shape
  IShape2D& GetCollisionShape();

  // Recieves and handles events
  void HandleEvent(Event evt);

  // Update the gameojects graphics
  void Draw();

  // Runs when the player is destroyed
  void GameOver();
};

