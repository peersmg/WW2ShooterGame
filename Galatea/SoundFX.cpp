#include "SoundFX.h"

SoundFX::SoundFX()
{
  m_nextExplosion = 0;

} // SoundFX end

SoundFX::~SoundFX()
{
}

void SoundFX::LoadSounds()
{
  m_pSoundEngine = MySoundEngine::GetInstance();

  for (int i = 0; i < NUMEXPLOSIONS; i++)
  {
    m_explosions[i] = m_pSoundEngine->LoadWav(L"sound/explosion.wav");
  }

  for (int i = 0; i < NUMSHOTS; i++)
  {
    m_shots[i] = m_pSoundEngine->LoadWav(L"sound/shoot.wav");
  }

  m_thrustVolume = -5000;

  m_thrust = m_pSoundEngine->LoadWav(L"sound/thrust_loop.wav");
  m_pSoundEngine->SetVolume(m_thrust, m_thrustVolume);

  m_superThrust = m_pSoundEngine->LoadWav(L"sound/thrust_loop.wav");
  m_pSoundEngine->SetVolume(m_superThrust, -500);

  m_powerup = m_pSoundEngine->LoadWav(L"sound/powerup.wav");

} // LoadSounds

void SoundFX::PlayExplosion()
{
  m_pSoundEngine->Play(m_explosions[m_nextExplosion], false);

  m_nextExplosion++;

  if (m_nextExplosion >= NUMEXPLOSIONS)
  {
    m_nextExplosion = 0;
  }
  
} // PlayExplosion end

void SoundFX::PlayShot()
{
  m_pSoundEngine->Play(m_shots[m_nextShot], false);

  m_nextShot++;

  if (m_nextShot >= NUMSHOTS)
  {
    m_nextShot = 0;
  }

} // PlayShot end

void SoundFX::PlayPowerup()
{
  m_pSoundEngine->Play(m_powerup);

} // PlayPowerup end

void SoundFX::PlayThrust()
{
  if (m_thrustVolume < -1000)
  {
    m_thrustVolume += 400;
  }
  
  m_pSoundEngine->SetVolume(m_thrust, m_thrustVolume);
  m_pSoundEngine->Play(m_thrust, true);

} // PlayThrust end

void SoundFX::StopThrust()
{
  m_pSoundEngine->Stop(m_thrust);
  m_thrustVolume = -10000;

} // StopThrust end

void SoundFX::PlaySuperThrust()
{
  m_pSoundEngine->Play(m_superThrust, true);

} // PlaySuperThrust end

void SoundFX::StopSuperThrust()
{
  m_pSoundEngine->Stop(m_superThrust);

} // StopSuperThrust end


SoundFX SoundFX::instance;