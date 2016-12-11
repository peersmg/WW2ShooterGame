#include "Ship.h"
#include "myinputs.h"
#include "Bullet.h"
#include "gamecode.h"
#include "string"
#include "Building.h"
#include "Explosion.h"
#include "SoundFX.h"
#include "ParticleEmitter.h"

Ship::Ship() : GameObject(SHIP)
{
  LoadImage(L"images/plane.png");

} // Ship end

void Ship::Initialise(Vector2D startPos)
{
  m_position = startPos;
  m_gravity = Vector2D(0, -320);
  m_friction = 0.0008f;
  m_thrust = 0.0f;
  m_thrustSuper = 2000.0f;
  m_velocityLimit = 320;
  m_superThrust = false;
  m_handleEvents = true;

  m_imageScale = 2;
  m_objectSize = Vector2D(100, 100)*m_imageScale;

  m_maxHealth = 200;
  m_maxAmmo = 50;
  m_maxBulletCooldown = 0.2f;
  m_maxFuel = 50;
  m_trailSize = 0.02f;

  m_collisionDamage = 5.0f;
  m_health = m_maxHealth;
  m_fuel = m_maxFuel;
  m_ammo = m_maxAmmo;
  m_bulletCooldown = m_maxBulletCooldown;

  m_drawDepth = -1;

} // Initialise end

void Ship::Update(float deltaTime)
{
  MyInputs* pInputs = MyInputs::GetInstance();

  pInputs->SampleKeyboard();

  // Reduce the cooldown by deltaTime
  m_bulletCooldown -= deltaTime;

  // If the health hits 0 explode
  if (m_health <= 0)
  {
    Explode();
  }

  // Basic ship rotation
  if (pInputs->KeyPressed(DIK_LEFT))
  {
    m_angle -= 1.4f * deltaTime;

    if (m_angle < -3.14)
    {
      m_angle += 6.28;
    }
  }
  if (pInputs->KeyPressed(DIK_RIGHT))
  {
    m_angle += 1.4f * deltaTime;

	if (m_angle > 3.14)
    {
      m_angle -= 6.28;
    }
  }

  // Upwards thrust
  if (pInputs->KeyPressed(DIK_UP) && m_position.YValue < 800 && m_fuel > 0)
  {

    // Limit the thrust to 1620
    if (m_thrust < 1620.0f)
    {
      m_thrust += 20;
    }

    m_acceleration.setBearing(m_angle, m_thrust);

    SoundFX::instance.PlayThrust();
    
    if (m_landed)
    {
      m_landed = false;
    }

    // If the ship is not thrusting forwards
    if (!m_superThrust)
    {
      if ((m_velocity.XValue < m_velocityLimit || m_acceleration.XValue < 0) && (m_velocity.XValue > -m_velocityLimit || m_acceleration.XValue > 0))
      {
        m_velocity += m_acceleration*deltaTime;

        m_fuel -= 5 * deltaTime;

        if (m_fuel < 0)
        {
          m_fuel = 0;
        }

      }

      // Create engine trail
      if (rand() % 100 < 90 && m_fuel > 0)
      {
        Vector2D downVel;

        if (m_trailSize < 0.06)
        {
          m_trailSize += 0.05*deltaTime;
        }

        downVel.setBearing(m_angle + 3.14, 800);

        Explosion *pExplosion = new Explosion;
        pExplosion->Initialise(m_position, downVel, m_trailSize);
        Game::instance.m_objects.AddItem(pExplosion, false);
      }
    }

    // Apply acceleration
    m_velocity.YValue += m_acceleration.YValue*deltaTime;
  }
  else
  {
    m_trailSize = 0.02f;
    m_thrust = 0;
    SoundFX::instance.StopThrust();
  }

  // Forwards thrust
  if (pInputs->KeyPressed(DIK_X) && !m_landed  && m_position.YValue < 800 && m_fuel > 0)
  {
    m_acceleration.setBearing(m_angle + 1.57, (m_thrustSuper));

    SoundFX::instance.PlaySuperThrust();

    if (m_fuel < 0)
    {
      m_fuel = 0;
    }

    // Limit x velocity
    if (m_velocity.XValue > (m_velocityLimit*4))
    {
      m_velocity.XValue = m_velocityLimit*4;
    }
    else if (m_velocity.XValue < (-m_velocityLimit)*4)
    {
      m_velocity.XValue = -m_velocityLimit;
    }
    else
    {
      m_velocity += m_acceleration*deltaTime;

      m_fuel -= 5 * deltaTime;

      m_superThrust = true;
    }

    // Trail
    if (rand() % 100 < 90 && m_fuel > 0)
    {
      Vector2D downVel;

      downVel.setBearing(m_angle + 3.14f, 800);

      Explosion *pExplosion = new Explosion;
      pExplosion->Initialise(m_position, downVel, 0.08f);
      Game::instance.m_objects.AddItem(pExplosion, false);
    }

  }
  else
  {
    m_superThrust = false;
    SoundFX::instance.StopSuperThrust();
  }

  // Limit Y velocity
  if (m_velocity.YValue > m_velocityLimit)
  {
    m_velocity.YValue = m_velocityLimit;
  }
  else if (m_velocity.YValue < -m_velocityLimit)
  {
    m_velocity.YValue = -m_velocityLimit;
  }

  // Move the camera
  if (m_position.YValue < 300)
  {
    MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(m_position.XValue, 0));
  }
  else
  {
    MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(m_position.XValue, (-m_position.YValue)+300));
  }

  // Shoot
  if (pInputs->KeyPressed(DIK_Z) && m_bulletCooldown <= 0 && m_ammo > 0)
  {
    Bullet *pBullet = new Bullet;
    pBullet->Initialise(m_angle, m_position, m_gravity);
    Game::instance.m_objects.AddItem(pBullet, true);

    SoundFX::instance.PlayShot();

    m_ammo--;
    m_bulletCooldown = m_maxBulletCooldown;
  }

  // Apply Friction
  m_velocity -= m_velocity * m_friction; 

  // Apply Gravity
  if (!m_landed)
  {
    m_velocity += m_gravity*deltaTime;
  }
  
  // Apply Velocity
  m_position += m_velocity*deltaTime;

} // Update end

void Ship::IncreseMaxHealth()
{
  m_maxHealth *= 1.2;
  m_health = m_maxHealth;

  SoundFX::instance.PlayPowerup();

} // IncreseMaxHealth end

void Ship::IncreaseMaxAmmo()
{
  m_maxAmmo *= 1.2;
  m_ammo = (int)m_maxAmmo;

  SoundFX::instance.PlayPowerup();

} // IncreaseMaxAmmo end

void Ship::IncreaseMaxFuel()
{
  m_maxFuel *= 1.2;
  m_fuel = m_maxFuel;

  SoundFX::instance.PlayPowerup();

} // IncreaseMaxFuel end

void Ship::ReduceBulletCooldown()
{
  m_maxBulletCooldown *= 0.5;

  SoundFX::instance.PlayPowerup();

} // ReduceBulletCooldown end

void Ship::ReduceCollisionDamage()
{
  m_collisionDamage *= 0.85;

  SoundFX::instance.PlayPowerup();

} // ReduceCollisionDamage end

void Ship::ProcessCollision(GameObject &other)
{
  // If the ship collides with the building
  if (other.GetType() == BUILDING)
  {
    // Deal with the collision
    HitBuilding(other);

    // Cast the gameobject to a Building
    Building *pOtherBuilding = dynamic_cast<Building*> (&other);
    
    // Check if the building is a refuel building
    if (pOtherBuilding->IsRefuel())
    {
      // Increase fuel and ammo
      if (m_ammo < m_maxAmmo)
      {
        m_ammo+= 0.1;
      }
      if (m_fuel < m_maxFuel)
      {
        m_fuel+= 0.1;
      }
    }
  }

  // If the ship collides with an enemy bullet
  else if (other.GetType() == ENEMYBULLET)
  {
    m_health--;
  }

  // If the ship collides with an enemy
  else if (other.GetType() == ENEMY)
  {
    m_velocity = -m_velocity;

    m_health -= m_collisionDamage;
  }

  // If the ship collides with a missile
  else if (other.GetType() == MISSILE)
  {
    m_health -= 5;
  }

  // If the ship collides with a bomb
  else if (other.GetType() == BOMB)
  {
    m_health -= 7;
  }

} // ProcessCollision end

void Ship::HitBuilding(GameObject &other)
{

  MyInputs* pInputs = MyInputs::GetInstance();

  // Cast the gameobject to a building
  Building *pOtherBuilding = dynamic_cast<Building*> (&other);

  // Get the collision normal
  Vector2D normal = collisionShape.CollisionNormal(pOtherBuilding->GetShape());
  normal = normal.unitVector();

  float otherYPosition = other.GetPosition().YValue;
  
  // Check if the ship has collided with the top of the building
  if (m_position.YValue - (m_objectSize.YValue / 2) < otherYPosition + (other.GetSize().YValue / 2) - 60 && normal == Vector2D(0, 1))
  {
    // If the ship is at a reasonable angle
    if (m_angle < 1 && m_angle > -1)
    {
      // Slow the ship down as it skids off the building
      m_velocity -= m_velocity*(m_friction * 60);

      RotateTo(0);

      // Move the ship to the top of the building
      m_position.YValue = otherYPosition + (other.GetSize().YValue / 2) + (m_objectSize.YValue / 2) - 60;

      // Snow!
      if (!m_landed && !pInputs->KeyPressed(DIK_UP))
      {
        Game::instance.m_objects.AddItem(new ParticleEmitter(m_position - Vector2D(-20, 40), 150, (rand() % 6) + 2, 0.4f, MyDrawEngine::WHITE), false);
        Game::instance.m_objects.AddItem(new ParticleEmitter(m_position - Vector2D(20, 40), 150, (rand() % 6) + 2, 0.4f, MyDrawEngine::WHITE), false);
      }

      m_landed = true;
    }
    else
    {
      // Damage the ship if it collides with the building too quickly
      if (m_velocity.magnitude() > 800)
      {
        m_health -= m_collisionDamage * 5;
      }
      else if (m_velocity.magnitude() > 1200)
      {
        m_health = 0;
      }
      else
      {
        m_health -= m_collisionDamage;
      }

      if (m_angle > 0)
      {
        RotateTo(m_angle + 2);
      }
      else
      {
        RotateTo(m_angle - 2);
      }

      // Collision effect
      Game::instance.m_objects.AddItem(new ParticleEmitter(m_position, 1000, (rand() % 10) + 8, 0.5f, MyDrawEngine::GREY), false);

      // Bounce the ship off the building
      m_velocity = m_velocity - (2 * normal*m_velocity)*normal;
    }
    
  }

  // Check if the ship has collided with one side of the building
  if (m_position.XValue < other.GetPosition().XValue && m_position.YValue - (m_objectSize.YValue / 2) < otherYPosition + (other.GetSize().YValue / 2) - 75)
  {
    // Damage the ship if it collides with the building too quickly
    if (m_velocity.magnitude() > 800)
    {
      m_health -= m_collisionDamage * 5;
    }
    else if (m_velocity.magnitude() > 1200)
    {
      m_health = 0;
    }
    else
    {
      m_health -= m_collisionDamage;
    }

    if (m_angle > 0)
    {
      RotateTo(m_angle+2);
    }
    else
    {
      RotateTo(m_angle - 2);
    }

    // Collision effect
    Game::instance.m_objects.AddItem(new ParticleEmitter(m_position, 1000, (rand() % 10) + 8, 0.5f, MyDrawEngine::GREY), false);

    // Bounce the ship off the building
    m_velocity = m_velocity - (2*normal*m_velocity)*normal;
  }

  // Check if the ship has collided with one side of the building
  else if (m_position.XValue > other.GetPosition().XValue && m_position.YValue - (m_objectSize.YValue / 2) < other.GetPosition().YValue + (other.GetSize().YValue / 2) - 75)
  {
    // Damage the ship if it collides with the building too quickly
    if (m_velocity.magnitude() > 800)
    {
      m_health -= m_collisionDamage * 5;
    }
    else if (m_velocity.magnitude() > 1200)
    {
      m_health = 0;
    }
    else
    {
      m_health -= m_collisionDamage;
    }

    if (m_angle > 0)
    {
      RotateTo(m_angle + 2);
    }
    else
    {
      RotateTo(m_angle - 2);
    }

    // Collision effect
    Game::instance.m_objects.AddItem(new ParticleEmitter(m_position, 1000, (rand() % 10) + 8, 0.5f, MyDrawEngine::GREY), false);

    // Bounce the ship off the building
    m_velocity = m_velocity - (2 * normal*m_velocity)*normal;
  }
} // HitBuilding end

void Ship::RotateTo(float angle)
{
  // Rotate to the given angle
  if (abs(m_angle) - abs(angle) < 0.05 && abs(m_angle) - abs(angle) > -0.05)
  {
    m_angle = angle;
  }
  else
  {
    if (m_angle > angle)
    {
      m_angle -= 0.1f;
    }
    else if (m_angle < angle)
    {
      m_angle += 0.1f;
    }
  }

} // RotateTo end

void Ship::Explode()
{
  Explosion *pExplosion = new Explosion;
  pExplosion->Initialise(m_position, Vector2D(0, 0), 0.3f, 20, true);
  Game::instance.m_objects.AddItem(pExplosion, false);

  SoundFX::instance.PlayExplosion();

  Game::instance.m_objects.AddItem(new ParticleEmitter(m_position, 1000, (rand() % 10) + 8, 0.5f, MyDrawEngine::DARKRED), false);

  Event evt;
  evt.type = EVENT_PLAYERGONE;
  Game::instance.NotifyEvent(evt);

  m_active = false;

} // Explode end

int Ship::GetHealth()
{
  return (int)m_health;

} // GetHealth end

int Ship::GetFuel()
{
  return (int)m_fuel;

} // GetFuel end

int Ship::GetAmmo()
{
  return (int)m_ammo;

} // GetAmmo end

IShape2D& Ship::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position.YValue + (m_objectSize.YValue / 2), m_position.XValue - (m_objectSize.XValue / 2), 
                         m_position.YValue - (m_objectSize.YValue / 2), m_position.XValue + (m_objectSize.XValue / 2));
  return collisionShape;

} // GetCollisionShape end

void Ship::HandleEvent(Event evt)
{

}