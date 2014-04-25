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

void sound::playBackgroundMusic()
{
  if(music && !CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
  {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/Music/background.wav", true);
  }
}

void sound::playSoundFx()
{
  if(soundFx)
  {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/SFX/tick.wav");
  }
}

void sound::toggleMusic()
{
  music = !music;
  if(!music)
  {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
  } else{
    sound::playBackgroundMusic();
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
