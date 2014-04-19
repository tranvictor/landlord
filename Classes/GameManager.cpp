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
int  GameManager::playerOneID = -1;
int  GameManager::playerTwoID = -1;
int  GameManager::mapIDTouched = -1;

int  GameManager::player1Score;
int  GameManager::player2Score;
int  GameManager::currentPlayer;
int  GameManager::winPlayer;

int  GameManager::nTrees;

int  GameManager::nAxes;
int  GameManager::nAxesOfPlayerOne = 0;
int  GameManager::nAxesOfPlayerTwo = 0;

int GameManager::nStones = 0;

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
  currentPlayer = PLAYER_ONE;
  playerOneID = playerTwoID = -1;
}

void GameManager::increaseScore(int currentPlayer)
{
  if (currentPlayer == PLAYER_ONE)
  {
    player1Score++;
  }
  else
  {
    player2Score++;
  }
}

int GameManager::getCurrentPlayer()
{
  return currentPlayer;
}

int GameManager::getPlayerScore(int currentPlayer)
{
  if (currentPlayer == PLAYER_ONE)
  {
    return player1Score;
  }
  else
  {
    return player2Score;
  }
}

int GameManager::getWinPlayer()
{
  return winPlayer;
}

void GameManager::changeCurrentPlayer()
{
  if (currentPlayer == PLAYER_ONE)
  {
    currentPlayer = PLAYER_TWO;
  }
  else
  {
    currentPlayer = PLAYER_ONE;
  }
}

void GameManager::setWinPlayer(int _currentPlayer)
{
  winPlayer = _currentPlayer;
}

void GameManager::setNumOfTrees(int pNumOfTrees)
{
  nTrees = pNumOfTrees;
}

int GameManager::getNumOfTrees()
{
  return nTrees;
}


void GameManager::setNumOfAxes(int pNumOfAxes)
{
  nAxes = pNumOfAxes;
}

int GameManager::getNumOfAxes(int pCurrentPlayer)
{
  if (pCurrentPlayer == PLAYER_ONE)
  {
    return nAxesOfPlayerOne;
  }
  else
  {
    return nAxesOfPlayerTwo;
  }
}

void GameManager::increaseNumOfAxes(int pCurrentPlayer)
{
  if (pCurrentPlayer == PLAYER_ONE)
  {
    nAxesOfPlayerOne++;
  }
  else
  {
    nAxesOfPlayerTwo++;
  }
}

void GameManager::decreaseNumOfAxes(int pCurrentPlayer)
{
  if (pCurrentPlayer == PLAYER_ONE && nAxesOfPlayerOne > 0)
  {
    nAxesOfPlayerOne--;
  }
  else if (nAxesOfPlayerTwo > 0)
  {
    nAxesOfPlayerTwo--;
  }
}

void GameManager::setNumOfStones(int pNumOfStones)
{
  nStones = pNumOfStones;
}

int GameManager::getNumOfStones()
{
  return nStones;
}