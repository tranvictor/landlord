//
//  Axe.cpp
//  landlord
//
//  Created by Tuan TQ on 3/27/14.
//
//

#include "Axe.h"
#include "Constant.h"

int  Axe::nAxes;
int  Axe::nAxesOfPlayerOne = 0;
int  Axe::nAxesOfPlayerTwo = 0;

void Axe::setNumOfAxes(int pNumOfAxes)
{
  nAxes = pNumOfAxes;
}

int Axe::getNumOfAxes(int pCurrentPlayer)
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

void Axe::increaseNumOfAxes(int pCurrentPlayer)
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

void Axe::decreaseNumOfAxes(int pCurrentPlayer)
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