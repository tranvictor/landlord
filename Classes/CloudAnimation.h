//
//  CloudAnimation.h
//  landlord
//
//  Created by HaLink on 2/25/14.
//
//

#ifndef landlord_CloudAnimation_h
#define landlord_CloudAnimation_h

#include "cocos2d.h"

class CloudAnimation : public cocos2d::CCSprite
{
private:
public:
  virtual bool init();
  static cocos2d::CCSprite* sprite();
  
  CREATE_FUNC(CloudAnimation);
};

#endif
