//
//  CloudAnimation.cpp
//  landlord
//
//  Created by HaLink on 2/25/14.
//
//

#include "CloudAnimation.h"

USING_NS_CC;

CloudAnimation* CloudAnimation::create(int pCloudSpeed)
{
  CloudAnimation *cloud = new CloudAnimation();
  if (cloud && cloud->init(pCloudSpeed))
    {
    cloud->autorelease();
    return cloud;
    }
  else
    {
    CC_SAFE_DELETE(cloud);
    return NULL;
    }
}

bool CloudAnimation::init(int pCloudSpeed)
{
  if(!CCSprite::init())
  {
    return false;
  }
  
  CCSprite* sprite = CCSprite::create("CloudAnimation/cloud.png");
  
  CCActionInterval* act1 = CCMoveBy::create(pCloudSpeed, ccp(1000,0));
  
  CCActionInterval* act2 = CCMoveBy::create(pCloudSpeed, ccp(-1000, 0));
  
  CCSequence * newSequence = CCSequence::create(act1, act2);
  
  sprite->runAction(CCRepeatForever::create(newSequence));
  
  this->addChild(sprite);
  
  return true;
}
