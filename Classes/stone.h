//
//  Stone.h
//  landlord
//
//  Created by Tuan TQ on 3/29/14.
//
//

#ifndef __landlord__Stone__
#define __landlord__Stone__

#include <iostream>

class Stone
{
private:
  static int nStones;
  
public:
  static void setNumOfStones(int pNumOfStones);
  static int  getNumOfStones();
};

#endif /* defined(__landlord__Stone__) */
