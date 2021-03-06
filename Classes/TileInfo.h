//
//  TileInfo.h
//  landlord
//
//  Created by Giap Nguyen on 3/10/14.
//
//

#ifndef __TILEINFO_H__
#define __TILEINFO_H__

#include "Constant.h"
#include "cocos2d.h"

class TileInfo
{
private:
  
public:
  CC_SYNTHESIZE(eEdgeStatus, mEdgeTopStatus, EdgeTopStatus);
  CC_SYNTHESIZE(eEdgeStatus, mEdgeBottomStatus, EdgeBottomStatus);
  CC_SYNTHESIZE(eEdgeStatus, mEdgeLeftStatus, EdgeLeftStatus);
  CC_SYNTHESIZE(eEdgeStatus, mEdgeRightStatus, EdgeRightStatus);
  
  CC_SYNTHESIZE(bool, mHasTopPop, HasTopPop);
  CC_SYNTHESIZE(bool, mHasBottomPop, HasBottomPop);
  CC_SYNTHESIZE(bool, mHasLeftPop, HasLeftPop);
  CC_SYNTHESIZE(bool, mHasRightPop, HasRightPop);
  
  CC_SYNTHESIZE(int, mNumberEdgeAvailale, NumberEdgeAvailale);
  CC_SYNTHESIZE(cocos2d::CCSprite*, mTile, Tile);
  CC_SYNTHESIZE(bool, mHasEdgeTouched, HasEdgeTouched);
  
  CC_SYNTHESIZE(int, mGIDTileUp, GIDTileUp);
  CC_SYNTHESIZE(int, mGIDTileDown, GIDTileDown);
  CC_SYNTHESIZE(int, mGIDTileLeft, GIDTileLeft);
  CC_SYNTHESIZE(int, mGIDTileRight, GIDTileRight);
  CC_SYNTHESIZE(int, mGID, GID);
  
  CC_SYNTHESIZE(int, mBelongToPlayer, BelongToPlayer);
  CC_SYNTHESIZE(bool, mHasItem, HasItem);
  CC_SYNTHESIZE(bool, mHasTree, HasTree);
  CC_SYNTHESIZE(bool, mHasAxe, HasAxe);
  CC_SYNTHESIZE(bool, mHasStone, HasStone);
  
  TileInfo();
  
};

#endif /* defined(__landlord__TileInfo__) */
