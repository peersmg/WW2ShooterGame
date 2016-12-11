#pragma once

#include "objecttypes.h"
#include "vector2D.h"
#include "Shapes.h"
#include "mydrawengine.h"
#include "event.h"

// Predeclaration of IObjectRenderer
class IObjectRenderer;

// Base class for all game objects
class GameObject
{

	friend class ObjectManager;

private:

protected:
	int m_drawDepth;			// default is 0. Objects with lower numbers will be drawn before objects with higher numbers. (And will therefore be
								// "backgroud". There is no effect
								// if this is altered after adding the object to the object manager.
	bool m_active;				// Indicates if the object is still in use. If set to false, the object will be deleted by the objectManager.
	std::vector<PictureIndex> m_images;		// Indices of the pictures loaded using LoadPicture. If a picture is not loaded, this will be 0
	Vector2D m_position;		// Position of the object
  Vector2D m_objectSize;
	float m_imageScale;			// Scale of the loaded image. If the scale is <1, the obect will be drawn smaller than the image
	float m_angle;				// Angle of rotation of the image. 0 is upright. Angle in radians clockwise
	int m_imageNumber;			// Index of the current image in m_images;
	bool m_handleEvents;		// Whether or not to process events.
  int m_sceneNumber;      // The number of the scene that this GameObject belongs to

public:
	const ObjectType TYPE;		// The type of the object. Must be set to one of the values in objecttypes.h

	// Constructor. All subclasses must set a type using Subclass::Subclass(): GameObject(TYPE)
	explicit GameObject(ObjectType type);

	// Destructor
	virtual ~GameObject();

	// Returns the type of the object
	ObjectType GetType() const;		

	// Sets m_active to false. The object will be deleted by the engine
	void Deactivate();

	// Returns whether the object is active or not
	inline bool IsActive() const
	{
		return m_active;
	}

	// Draws the object using the MyDrawEngine. The position is used for the centre of the object.
	// The position and scale will be transformed by the draw engine's camera
	virtual void Draw();

	// Load an image and stores the index in m_image. 
	// If the filename is invalid, m_image will be set to 0
	void LoadImage(wchar_t* filename);

	// Returns true if the object has collided with the other object
	bool HasCollided( GameObject & other) ;

	// Returns the depth of drawing. Lower numbers are drawn first.
	int GetDrawDepth() const;

  // Returns objects position
  Vector2D GetPosition() const;

  //Returns Object dimensions
  Vector2D GetSize() const;

	// Used to handle the result of any collision
	virtual void ProcessCollision(GameObject& other)=0;

	// Used to process each frame
	virtual void Update(float frametime)=0;

	// Returns the collision shape (Rectangle2D, Circle2D, Segment2D or Point2D)
	// The shape that it returns must be a member variable, not a local variable
	virtual IShape2D& GetCollisionShape()=0;

	virtual void HandleEvent(Event evt);

  // Returns the number of the scene that this GameObject belongs to
  int GetSceneNumber() const;

  // Sets the scene number of the object. Only objects in the current scene will be drawn or updated.
  void SetSceneNumber(int sceneNumber);
};


