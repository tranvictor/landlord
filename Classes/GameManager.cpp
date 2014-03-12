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
int  GameManager::playerOneID = 1;
int  GameManager::playerTwoID = 1;
int  GameManager::mapIDTouched = 1;

int  GameManager::player1Score;
int  GameManager::player2Score;
bool GameManager::currentPlayer;

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

void GameManager::setPlayerOneID(int ID)
{
  playerOneID = ID;
}

int GameManager::getPlayerOneID()
{
  return playerOneID;
}

void GameManager::setPlayerTwoID(int ID)
{
  playerTwoID = ID;
}

int GameManager::getPlayerTwoID()
{
  return playerTwoID;
}


void GameManager::setMapIDTouched(int ID)
{
  mapIDTouched = ID;
}

int GameManager::getMapIDTouched()
{
  return mapIDTouched;
}

//  Players infor
void GameManager::initPlayersInfor()
{
  player1Score = 0;
  player2Score = 0;
  currentPlayer = true;
}

void GameManager::increaseScore(bool currentPlayer)
{
  if (currentPlayer == true)
  {
    player1Score++;
  }
  else
  {
    player2Score++;
  }
}

bool GameManager::getCurrentPlayer()
{
  return currentPlayer;
}

int GameManager::getPlayerScore(bool currentPlayer)
{
  if (currentPlayer == true)
  {
    return player1Score;
  }
  else
  {
    return player2Score;
  }
}
