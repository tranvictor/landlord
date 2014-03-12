//
//  SimpleAI.cpp
//  landlord
//
//  Created by HaLink on 3/12/14.
//
//

#include "SimpleAI.h"
#include "PlayScene.h"

int SimpleAI::qfirst = 0;
int SimpleAI::qlast = 0;
std::vector<int> SimpleAI::queue;
std::vector<int> SimpleAI::tileAccepted;
std::vector<TileInfo*> SimpleAI::tileArr;

void SimpleAI::initQueue()
{
  qfirst = 0;
  qlast = -1;
}

bool SimpleAI::qEmpty()
{
  return qfirst > qlast;
}

void SimpleAI::push(int pSender)
{
  qlast++;
  if(qlast >= queue.size())
  {
    queue.push_back(pSender);
  }
  else
    queue.at(qlast) = pSender;
}

int SimpleAI::pop()
{
  int returnValue = queue[qfirst];
  qfirst++;
  return returnValue;
}


void update(int pSender)
{
  int vt = pSender;
  SimpleAI::tileArr.at(vt)->setNumberEdgeAvailale(0);
  
  //BOTTOM
  if(!SimpleAI::tileArr.at(vt)->getHasBottomPop())
  {
    SimpleAI::tileArr.at(vt)->setHasBottomPop(true);
    SimpleAI::tileArr.at(vt)->setEdgeBottomSts(STS_NOT_AVAILABLE);
    for (int i = 0; i < SimpleAI::tileArr.size(); ++i)
    {
      if (SimpleAI::tileArr.at(i)->getGID() == SimpleAI::tileArr.at(vt)->getGIDTileDown())
      {
        SimpleAI::tileArr.at(i)->setHasTopPop(true);
        SimpleAI::tileArr.at(i)->setEdgeTopSts(STS_NOT_AVAILABLE);
        SimpleAI::tileArr.at(i)->setNumberEdgeAvailale(SimpleAI::tileArr.at(i)->getNumberEdgeAvailale()-1);
        break;
      }
    }
  } else
  
  //TOP
  if(!SimpleAI::tileArr.at(vt)->getHasTopPop())
  {
    SimpleAI::tileArr.at(vt)->setHasTopPop(true);
    SimpleAI::tileArr.at(vt)->setEdgeTopSts(STS_NOT_AVAILABLE);
    for (int i = 0; i < SimpleAI::tileArr.size(); ++i)
    {
      if (SimpleAI::tileArr.at(i)->getGID() == SimpleAI::tileArr.at(vt)->getGIDTileUp())
      {
        SimpleAI::tileArr.at(i)->setHasBottomPop(true);
        SimpleAI::tileArr.at(i)->setEdgeBottomSts(STS_NOT_AVAILABLE);
        SimpleAI::tileArr.at(i)->setNumberEdgeAvailale(SimpleAI::tileArr.at(i)->getNumberEdgeAvailale()-1);
        break;
      }
    }
  } else
  
  //LEFT
  if(!SimpleAI::tileArr.at(vt)->getHasLeftPop())
  {
    SimpleAI::tileArr.at(vt)->setHasLeftPop(true);
    SimpleAI::tileArr.at(vt)->setEdgeLeftSts(STS_NOT_AVAILABLE);
    for (int i = 0; i < SimpleAI::tileArr.size(); ++i)
    {
      if (SimpleAI::tileArr.at(i)->getGID() == SimpleAI::tileArr.at(vt)->getGIDTileLeft())
      {
        SimpleAI::tileArr.at(i)->setHasRightPop(true);
        SimpleAI::tileArr.at(i)->setEdgeRightSts(STS_NOT_AVAILABLE);
        SimpleAI::tileArr.at(i)->setNumberEdgeAvailale(SimpleAI::tileArr.at(i)->getNumberEdgeAvailale()-1);
        break;
      }
    }
  } else
  
  //RIGHT
  if(!SimpleAI::tileArr.at(vt)->getHasRightPop())
  {
    SimpleAI::tileArr.at(vt)->setHasRightPop(true);
    SimpleAI::tileArr.at(vt)->setEdgeRightSts(STS_NOT_AVAILABLE);
    for (int i = 0; i < SimpleAI::tileArr.size(); ++i)
    {
      if (SimpleAI::tileArr.at(i)->getGID() == SimpleAI::tileArr.at(vt)->getGIDTileRight())
      {
        SimpleAI::tileArr.at(i)->setHasLeftPop(true);
        SimpleAI::tileArr.at(i)->setEdgeLeftSts(STS_NOT_AVAILABLE);
        SimpleAI::tileArr.at(i)->setNumberEdgeAvailale(SimpleAI::tileArr.at(i)->getNumberEdgeAvailale()-1);
        break;
      }
    }
  }
}

void SimpleAI::Breath_First_Search(int ptileIndex_i, int ptileIndex_j)
{
  tileArr = PlayScene::getTileInfoVector();
  tileAccepted.clear();
  CCLog("Number of tile arr is %lu", tileArr.size());
  
  initQueue();
  
  int k = PAIR_FUNC(ptileIndex_i, ptileIndex_j);
  push(k);
  CCLog("i= %i, j= %i", ptileIndex_i, ptileIndex_j);
  CCLog("k= %i", k);
  int direct_i[4] = {-1, 0, 1, 0};
  int direct_j[4] = {0, 1, 0, -1};
  
  while (!qEmpty())
  {
    int u = pop();
    CCLog("u= %i", u);
    int i, j;
    for(int t=0; t<tileArr.size(); t++)
    {
      if (tileArr.at(t)->getGID() == u)
        {
          i = tileArr.at(t)->getGridX();
          j = tileArr.at(t)->getGridY();
          CCLog("i= %i, j= %i", i, j);
          break;
        }
    }
  
    int x, y;
    for(int k = 0; k<4; k++)
    {
      x = i + direct_i[k];
      y = j + direct_j[k];
      for(int r = 0; r<tileArr.size(); r++)
      {
        if(tileArr.at(r)->getGridX()== x && tileArr.at(r)->getGridY()==y)
        {
          if (tileArr.at(r)->getNumberEdgeAvailale() == 1)
          {
            update(r);
            tileArr.at(r)->getTile()->setColor(ccGRAY);
            tileArr.at(r)->setNumberEdgeAvailale(0);
            push(tileArr.at(r)->getGID());
            tileAccepted.push_back(tileArr.at(r)->getGID());
          }
        }
      }
    }
    CCLog("%lu", tileAccepted.size());
  }
}