//
//  Tree.h
//  landlord
//
//  Created by Tuan TQ on 3/27/14.
//
//

#ifndef __landlord__Tree__
#define __landlord__Tree__

#include <iostream>
#include "TileInfo.h"

class Tree
{
private:
  static int  nTrees;

public:
  static void setNumOfTrees(int pNumOfTrees);
  static int  getNumOfTrees();
  
};

#endif /* defined(__landlord__Tree__) */
