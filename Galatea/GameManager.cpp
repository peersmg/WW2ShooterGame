#include "GameManager.h"

#include "gamecode.h"
#include "Building.h"
#include "BulletEnemy.h"
#include "MissileEnemy.h"
#include "MissileLauncher.h"
#include "Missile.h"
#include "myinputs.h"
#include "SoundFX.h"

#include <fstream>
#include <string>
#include <iostream>

GameManager::GameManager() : GameObject(MANAGER)
{
  m_pShip = nullptr;
  m_pBuildingCollection = nullptr;
  m_pEnemyCollection = nullptr;

  m_drawDepth = -10000;
  LoadImage(L"images/background.png");
  LoadImage(L"images/menu/oldPaperGameOver.png");

  LoadImage(L"images/explosion/explosion00.png");
  LoadImage(L"images/explosion/explosion01.png");
  LoadImage(L"images/explosion/explosion02.png");
  LoadImage(L"images/explosion/explosion03.png");
  LoadImage(L"images/explosion/explosion04.png");
  LoadImage(L"images/explosion/explosion05.png");
  LoadImage(L"images/explosion/explosion06.png");
  LoadImage(L"images/explosion/explosion07.png");
  LoadImage(L"images/explosion/explosion08.png");

} // GameManager end

void GameManager::Initialise()
{
  m_gameRunning = true;
  m_handleEvents = true;
  m_playerAmmo = 0;
  m_playerFuel = 0;
  m_playerHealth = 0;
  m_playerLevel = 1;
  m_playerExperience = 0;
  m_experienceNeeded = 70;
  m_flickerCountdown = 0.5f;
  m_upgradeAvailable = false;
  m_newHighScore = -1;

  m_pShip = new Ship;
  m_pShip->Initialise(Vector2D(0, 200));
  Game::instance.m_objects.AddItem(m_pShip, true);
  Game::instance.SetPlayer(m_pShip);

  m_pBuildingCollection = new BuildingCollection;
  m_pBuildingCollection->Initialise(m_pShip);
  Game::instance.m_objects.AddItem(m_pBuildingCollection, false);

  m_pEnemyCollection = new EnemyCollection;
  m_pEnemyCollection->Initialise(m_pBuildingCollection);
  Game::instance.m_objects.AddItem(m_pEnemyCollection, false);

  // Highscore Stuff

  for (int i = 0; i < 5; i++)
  {
    m_highScores[i] = 0;
  }

  std::ifstream myfile("SaveGame.dat");
  std::string line;

  if (myfile.is_open())
  {
    for (int i = 0; i < 5; i++)
    {
      getline(myfile, line);
      m_highScores[i] = atoi(line.c_str());
    }

    myfile.close();
  }

} // Initialise end

void GameManager::Update(float deltaTime)
{

  MyInputs* pInputs = MyInputs::GetInstance();

  pInputs->SampleKeyboard();

  m_flickerCountdown -= deltaTime;

  // Only increase score when enemy killed (or powerup collected?)
  if (m_gameRunning && m_pShip != nullptr)
  {
    m_playerAmmo = (float)m_pShip->GetAmmo();
    m_playerFuel = (float)m_pShip->GetFuel();
    m_playerHealth = (float)m_pShip->GetHealth();

    m_score += 2 * deltaTime;
  }
  else if (pInputs->KeyPressed(DIK_SPACE))
  {
    Game::instance.m_objects.DeactivateAll();
    Game::instance.ChangeState(MENU);
  }

  if (pInputs->KeyPressed(DIK_U) && m_playerExperience >= m_experienceNeeded && m_playerHealth > 0)
  {
    m_playerExperience = 0;
    m_experienceNeeded *= 1.5;
    m_playerLevel++;
    m_upgradeAvailable = false;
    Game::instance.ChangeState(LEVELUP);
  }

  if (m_playerExperience >= m_experienceNeeded && m_playerHealth > 0)
  {
    m_upgradeAvailable = true;
    m_playerExperience = m_experienceNeeded;
  }

} // Update end

void GameManager::Draw()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Vector2D camPos = pTheDrawEngine->theCamera.ReverseTransform(Vector2D(0, 0));
  float backgroundScale = 2.5;
  static bool showingUpgradeText = false;

  // If the game is running
  if (m_gameRunning)
  {
    // Draw the background
    MyDrawEngine::GetInstance()->DrawAt(Vector2D(-1024 * backgroundScale, 500), MyDrawEngine::GetInstance()->FindPicture(L"images/background.png"), backgroundScale);

    for (int i = 0; i < 100; i++)
    {
      MyDrawEngine::GetInstance()->DrawAt(Vector2D(i * 1024 * backgroundScale, 500), MyDrawEngine::GetInstance()->FindPicture(L"images/background.png"), backgroundScale);
    }

    // Draw UI
    pTheDrawEngine->WriteText(camPos, "Health: " + std::to_string((int)m_playerHealth), pTheDrawEngine->DARKRED, 1);
    pTheDrawEngine->WriteText(camPos + Vector2D(0, -50), "Ammo: " + std::to_string((int)m_playerAmmo), pTheDrawEngine->YELLOW, 1);
    pTheDrawEngine->WriteText(camPos + Vector2D(0, -100), "Fuel: " + std::to_string((int)m_playerFuel), pTheDrawEngine->DARKGREEN, 1);
    pTheDrawEngine->WriteText(camPos + Vector2D(0, -150), "Score: " + std::to_string((int)m_score), pTheDrawEngine->DARKGREEN, 1);

    //pTheDrawEngine->WriteText(camPos + Vector2D(2800, 0), "Score: " + std::to_string((int)m_score), pTheDrawEngine->PURPLE, 1);
    pTheDrawEngine->WriteText(Vector2D(pTheDrawEngine->GetViewport().GetTopRight().XValue - 300, pTheDrawEngine->GetViewport().GetTopRight().YValue), "XP: " + std::to_string((int)((m_playerExperience / m_experienceNeeded) * 100)) + "%", pTheDrawEngine->DARKBLUE, 1);
    pTheDrawEngine->WriteText(Vector2D(pTheDrawEngine->GetViewport().GetTopRight().XValue - 300, pTheDrawEngine->GetViewport().GetTopRight().YValue - 50), "Level: " + std::to_string(m_playerLevel), pTheDrawEngine->DARKGREEN, 1);

    if (m_flickerCountdown <= 0)
    {
      showingUpgradeText = !showingUpgradeText;
      m_flickerCountdown = 0.5f;
    }

    if (m_upgradeAvailable && showingUpgradeText)
    {
      pTheDrawEngine->WriteText(Vector2D(pTheDrawEngine->GetViewport().GetTopRight().XValue - 600, pTheDrawEngine->GetViewport().GetTopRight().YValue - 100), "Upgrade Available!", pTheDrawEngine->DARKGREEN, 1);
    }
  }
  // If the game is over
  else if (!m_gameRunning)
  {

    MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(0, 0));
    MyDrawEngine::GetInstance()->DrawAt(Vector2D(0, -100), MyDrawEngine::GetInstance()->FindPicture(L"images/menu/oldPaperGameOver.png"), 0.9f);

    // Highscore Stuff

    for (int i = 0; i < 5; i++)
    {
      if (i == m_newHighScore)
      {
        // Your score
        pTheDrawEngine->WriteText(camPos + Vector2D(1500, -550 + (i * -90)), std::to_string(i + 1) + ". " + std::to_string(m_highScores[i]), pTheDrawEngine->DARKGREEN, 5);
      }
      else
      {
        pTheDrawEngine->WriteText(camPos + Vector2D(1500, -550 + (i * -90)), std::to_string(i + 1) + ". " + std::to_string(m_highScores[i]), pTheDrawEngine->DARKGREEN, 4);
      }
    }

    if (m_newHighScore == -1)
    {
      pTheDrawEngine->WriteText(camPos + Vector2D(1500, -550 + (5 * -100)), "Your Score: " + std::to_string((int)m_score), pTheDrawEngine->DARKGREEN, 1);
    }
    else
    {
      pTheDrawEngine->WriteText(camPos + Vector2D(1500, -550 + (5 * -100)), "New Highscore!", pTheDrawEngine->DARKGREEN, 1);
    }

    pTheDrawEngine->WriteText(camPos + Vector2D(1200, -1700), "Press space to return to the menu...", pTheDrawEngine->DARKGREEN, 1);
  }

} // Draw end

void GameManager::GameOver()
{
  // Highscore Stuff
  SoundFX::instance.StopThrust();
  SoundFX::instance.StopSuperThrust();

  std::ofstream saveFile;
  saveFile.open("SaveGame.dat");

  // Sort array with score inserted and save it to file

  int position;

  for (position = 0; position < 5; position++)
  {
    if (m_highScores[position] < (int)m_score)
    {
      m_newHighScore = position;
      break;
    }
  }

  if (position < 5)
  {
    for (int i = 3; i >= position; i--)
    {
      m_highScores[i + 1] = m_highScores[i];
    }

    m_highScores[position] = (int)m_score;
  }
  else
  {
    m_newHighScore = -1;
  }

  
  for (int i = 0; i < 5; i++)
  {
    saveFile << m_highScores[i] << "\n";
  }

  saveFile.close();

  m_gameRunning = false;

} // GameOver end

void GameManager::HandleEvent(Event evt)
{
  if (evt.type == EVENT_PLAYERDESTROYED)
  {
    m_pBuildingCollection = nullptr;
    GameOver();
  }
  else if (evt.type == EVENT_PLAYERGONE)
  {
    m_pShip = nullptr;
  }
  else if (evt.type = EVENT_ENEMYDESTROYED)
  {
    m_score += 200;
    if (m_playerExperience < m_experienceNeeded)
    {
      m_playerExperience += 22;
    }
    
  }

} // HandleEvent end



void GameManager::ProcessCollision(GameObject &other)
{}

IShape2D& GameManager::GetCollisionShape()
{ return collisionShape; }