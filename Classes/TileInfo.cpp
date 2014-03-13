//
//  TileInfo.cpp
//  landlord
//
//  Created by Giap Nguyen on 3/10/14.
//
//

#include "TileInfo.h"

//TileInfo* TileInfo::create(const char* pFileName)
//{
//  TileInfo *tile = new TileInfo();
//  if (tile && tile->init(pFileName))
//  {
//    tile->autorelease();
//    return tile;
//  }
//  else
//  {
//    CC_SAFE_DELETE(tile);
//    return NULL;
//  }
//}
//
//bool TileInfo::init(const char *pFileName)
//{
//  if (!CCSprite::initWithFile(pFileName))
//  {
//    return false;
//  }
//  mEdgeTopSts = mEdgeBottomSts = mEdgeLeftSts = mEdgeRightSts = STS_NOT_APPEAR;
//  return true;
//}
//
//bool TileInfo::init()
//{
//  if (!CCSprite::init())
//  {
//    return false;
//  }
//  mEdgeTopSts = mEdgeBottomSts = mEdgeLeftSts = mEdgeRightSts = STS_NOT_AVAILABLE;
//  return true;
//}

TileInfo::TileInfo()
{
  mEdgeTopSts = mEdgeBottomSts = mEdgeLeftSts = mEdgeRightSts = STS_AVAILABLE;
  mNumberEdgeAvailale = NUMBER_EDGE_AVAILABLE;
  mHasBottomPop = mHasLeftPop = mHasRightPop = mHasTopPop = false;
  mHasEdgeTouched = false;
  mGIDTileDown = mGIDTileLeft = mGIDTileRight = mGIDTileUp = -1;
  mGID = 0;
}

