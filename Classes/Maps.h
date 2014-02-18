//
//  Maps.h
//  landlord
//
//  Created by Giap Nguyen on 2/19/14.
//
//

#ifndef __MAPS_H__
#define __MAPS_H__

#include "cocos2d.h"

USING_NS_CC;

class Maps : public CCSprite
{
private:
  CC_SYNTHESIZE(int, mMapID, MapID);
  
public:
  static Maps* create(const char* pFileName);
  virtual bool init(const char* pFileName);
};

#endif /* defined(__landlord__Maps__) */
