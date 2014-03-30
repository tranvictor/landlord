//
//  Axe.h
//  landlord
//
//  Created by Tuan TQ on 3/27/14.
//
//

#ifndef __landlord__Axe__
#define __landlord__Axe__

#include <iostream>

class Axe
{
private:
  static int  nAxes;
  static int  nAxesOfPlayerOne;
  static int  nAxesOfPlayerTwo;
  
public:
  static void setNumOfAxes(int pNumOfAxes);
  static int getNumOfAxes(int pCurrentPlayer);
  static void increaseNumOfAxes(int pCurrentPlayer);
  static void decreaseNumOfAxes(int pCurrentPlayer);
};

#endif /* defined(__landlord__Axe__) */
