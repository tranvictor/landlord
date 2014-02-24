//
//  Sound.cpp
//  landlord
//
//  Created by HaLink on 2/24/14.
//
//

#include "Sound.h"
#include "SimpleAudioEngine.h"


void sound::playBackgroundMusic()
{
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.wav", true);
}