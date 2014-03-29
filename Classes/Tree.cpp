//
//  Tree.cpp
//  landlord
//
//  Created by Tuan TQ on 3/27/14.
//
//

#include "Tree.h"

int Tree::nTrees;

void Tree::setNumOfTrees(int pNumOfTrees)
{
  nTrees = pNumOfTrees;
}

int Tree::getNumOfTrees()
{
  return nTrees;
}
