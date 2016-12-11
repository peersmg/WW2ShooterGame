#pragma once
#include "mysoundengine.h"

class SoundFX
{
private:
  static const int NUMEXPLOSIONS = 10;
  static const int NUMSHOTS = 5;

  SoundIndex m_explosions[NUMEXPLOSIONS];
  SoundIndex m_shots[NUMSHOTS];
  SoundIndex m_thrust;
  SoundIndex m_superThrust;
  SoundIndex m_powerup;
  MySoundEngine *m_pSoundEngine;

  int m_thrustVolume;

  int m_nextExplosion;
  int m_nextShot;
  SoundFX();

public:
  static SoundFX instance;
  void LoadSounds();
  void PlayExplosion();
  void PlayShot();
  void PlayPowerup();
  void PlayThrust();
  void StopThrust();

  void PlaySuperThrust();
  void StopSuperThrust();

  ~SoundFX();
};

