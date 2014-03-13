//
//  GameManager.cpp
//  landlord
//
//  Created by HaLink on 2/24/14.
//
//

#include "cocos2d.h"
#include "GameManager.h"
#include "Constant.h"

USING_NS_CC;

bool GameManager::musicState = true;
bool GameManager::soundState = true;
bool GameManager::treeModeState = true;
int  GameManager::playerOneID = 1;
int  GameManager::playerTwoID = 1;
int  GameManager::mapIDTouched = 1;

int  GameManager::player1Score;
int  GameManager::player2Score;
bool GameManager::currentPlayer;
bool GameManager::winPlayer;
int  GameManager::numberOfTilesChose;

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
void GameManager::initPlayersInfo()
{
  player1Score = 0;
  player2Score = 0;
  currentPlayer = true;
  numberOfTilesChose = 0;
}

void GameManager::increaseScore(bool currentPlayer)
{
  if (currentPlayer)
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
  if (currentPlayer)
  {
    return player1Score;
  }
  else
  {
    return player2Score;
  }
}

bool GameManager::getWinPlayer()
{
  return winPlayer;
}

void GameManager::changeCurrentPlayer()
{
  if (currentPlayer)
  {
    currentPlayer = false;
  }
  else
  {
    currentPlayer = true;
  }
}

void GameManager::setWinPlayer(bool _currentPlayer)
{
  winPlayer = _currentPlayer;
}