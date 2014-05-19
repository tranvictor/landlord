//
//  BounceButton.cpp
//  landlord
//
//  Created by Hoang Ha on 4/25/14.
//
//

#include "BounceButton.h"

USING_NS_CC;

BounceButton* BounceButton::create(const char * pFileName)
{
    BounceButton *bounceButton = new BounceButton();
    if (bounceButton && bounceButton->init(pFileName))
    {
        bounceButton->autorelease();
        return bounceButton;
    }
    else
    {
        CC_SAFE_DELETE(bounceButton);
        return NULL;
    }
}

bool BounceButton::init(const char * pFileName)
{
    if (!CCSprite::initWithFile(pFileName))
    {
        return false;
    }
    return true;
}

void BounceButton::onEnter()
{
  CCNode::onEnter();
  counter = 0.0f;
  bouncing = true;
  this->scheduleUpdate();
}

void BounceButton::update(float dt)
{
  if (bouncing)
  {
    counter += dt;
    this->setScaleX((sin(counter * 3) + 1)/2.0 * 0.1 + 1);
    this->setScaleY((cos(counter * 3) + 1)/2.0 * 0.1 + 1);
    if (counter > M_PI*500){
      counter = 0;
    }
  }
}

void BounceButton::onExit()
{
  CCNode::onExit();
  this->unscheduleUpdate();
}
