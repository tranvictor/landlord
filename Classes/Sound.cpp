//
//  Sound.cpp
//  landlord
//
//  Created by HaLink on 2/24/14.
//
//

#include "Sound.h"
#include "SimpleAudioEngine.h"

bool sound::music = true;
bool sound::soundFx = true;

void sound::playBackgroundMusic(const char* pFileName)
{
  if(music && !CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
  {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pFileName, true);
  }
}

void sound::playSoundFx(const char* pFileName)
{
  if(soundFx)
  {
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(pFileName);
  }
}

void sound::toggleMusic()
{
  music = !music;
  if(!music)
  {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
  }
}

void sound::toggleSoundFx()
{
  soundFx = !soundFx;
}

bool sound::getMusicState()
{
  return music;
}

bool sound::getSoundFxState()
{
  return soundFx;
}
