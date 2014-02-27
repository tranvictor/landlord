//
//  GameManager.cpp
//  landlord
//
//  Created by HaLink on 2/24/14.
//
//

#include "GameManager.h"

bool GameManager::musicState = true;
bool GameManager::soundState = true;
bool GameManager::treeModeState = true;

bool GameManager::getMusicState()
{
  return musicState;
}

void GameManager::setMusicState()
{
  musicState = !musicState;
}

bool GameManager::getSoundState()
{
  return soundState;
}

void GameManager::setSoundState()
{
  soundState = !soundState;
}

bool GameManager::getTreeModeState()
{
  return treeModeState;
}

void GameManager::setTreeModeState()
{
  treeModeState = !treeModeState;
}