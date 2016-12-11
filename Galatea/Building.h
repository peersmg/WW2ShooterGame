#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "objecttypes.h"

class Building : public GameObject
{
private:
  Rectangle2D collisionShape;   // Collision shape
  int m_buildingType;           // Type of building
  bool m_refuelBuilding;        // Is the building a refuel building

public:

  // Constructor
  Building();

  // Initialise the gameobject with default values
  void Initialise(int startX, int buildingType);

  // Process the collisions of this gameobject
  void ProcessCollision(GameObject &other);

  // Update the gameobject logic, called every frame
  void Update(float deltaTime);

  // Update the gameojects graphics
  void Draw();

  // Returns true if this is a refule building
  bool IsRefuel();

  // Sets the position of the building
  void SetPostion(float newXPosition);

  // Returns the collision shape
  IShape2D& GetCollisionShape();

  // Returns the collision shape as a rectangle
  Rectangle2D GetShape();

  // Recieves and handles events
  void HandleEvent(Event evt);
};

