//
//  BounceButton.h
//  landlord
//
//  Created by Hoang Ha on 4/25/14.
//
//

#ifndef __BOUNCE_BUTTON_H__
#define __BOUNCE_BUTTON_H__

#include "cocos2d.h"

class BounceButton : public cocos2d::CCSprite
{
private:
    bool bouncing;
    float counter;
    
public:
    CC_SYNTHESIZE(int, mMapID, MapID);
    
  static BounceButton* create(const char * pFileName);
  virtual bool init(const char * pFileName);
  void onEnter();
  void onExit();
  void update(float pDt);
};

#endif /* defined(__landlord__Bounce_Button__) */
