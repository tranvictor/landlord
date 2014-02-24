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
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.wav", true);
  }
}

void sound::playSoundFx()
{
  if(soundFx)
  {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("button-6.wav");
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