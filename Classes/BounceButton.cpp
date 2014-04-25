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

