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

class TileInfo : public cocos2d::CCSprite
{
private:
  
public:
  CC_SYNTHESIZE(eEdgeStatus, mEdgeTopSts, EdgeTopSts);
  CC_SYNTHESIZE(eEdgeStatus, mEdgeBottomSts, EdgeBottomSts);
  CC_SYNTHESIZE(eEdgeStatus, mEdgeLeftSts, EdgeLeftSts);
  CC_SYNTHESIZE(eEdgeStatus, mEdgeRightSts, EdgeRightSts);
  CC_SYNTHESIZE(int, mBelongToTile, BelongToTile);
  CC_SYNTHESIZE(cocos2d::CCSprite*, mEdgeTop, EdgeTop);
  CC_SYNTHESIZE(cocos2d::CCSprite*, mEdgeBottom, EdgeBottom);
  CC_SYNTHESIZE(cocos2d::CCSprite*, mEdgeLeft, EdgeLeft);
  CC_SYNTHESIZE(cocos2d::CCSprite*, mEdgeRight, EdgeRight);
  
  static TileInfo* create(const char* pFileName);
  virtual bool init(const char* pFileName);
  virtual bool init();
  CREATE_FUNC(TileInfo);
};

#endif /* defined(__landlord__TileInfo__) */
