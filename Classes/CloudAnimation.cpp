//
//  CloudAnimation.cpp
//  landlord
//
//  Created by HaLink on 2/25/14.
//
//

#include "CloudAnimation.h"

USING_NS_CC;

CCSprite *CloudAnimation::sprite()
{
  CCSprite* sprite = CloudAnimation::create();
  
  return sprite;
};

bool CloudAnimation::init()
{
  if(!CCSprite::init())
  {
    return false;
  }
  
  CCSprite* sprite = CCSprite::create("CloudAnimation/cloud.png");
  
  CCActionInterval* act1 = CCMoveBy::create(3, ccp(640,0));
  
  sprite->runAction(CCRepeatForever::create(act1));
  
  this->addChild(sprite);
  
  return true;
}
