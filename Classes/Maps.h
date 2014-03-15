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

class Maps : public cocos2d::CCSprite
{
private:
  
public:
  CC_SYNTHESIZE(int, mMapID, MapID);
  
  static Maps* create(const char * pFileName);
  virtual bool init(const char * pFileName);
};

#endif /* defined(__landlord__Maps__) */
