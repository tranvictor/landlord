//
//  ChooseMapScence.cpp
//  landlord
//
//  Created by Giap Nguyen on 2/19/14.
//
//

#include "ChooseMapScence.h"
#include "cocos2d.h"

USING_NS_CC;

bool ChooseMapScene::init()
{
  if (!CCLayer::init())
  {
    return false;
  }
  
  screenSize = CCDirector::sharedDirector()->getWinSize();
  CCLog("%f %f", screenSize.width, screenSize.height);
  
  addBackground();
  addButtonRandom();
  addButtonBack();
  return true;
}

CCScene* ChooseMapScene::scene()
{
  CCScene *scene = CCScene::create();
  
  ChooseMapScene *layer = ChooseMapScene::create();
  
  scene->addChild(layer);
  
  return scene;
}

void ChooseMapScene::addBackground()
{
  CCSprite *background = CCSprite::create("ChooseMapScene/background.png");
//  background->setScaleX(screenSize.width/background->getContentSize().width);
//  background->setScaleY(screenSize.height/background->getContentSize().height);
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  this->addChild(background, GR_BACKGROUND);
}

void ChooseMapScene::addButtonRandom()
{
  CCSprite *randomBtn = CCSprite::create("ChooseMapScene/button-random.png");
//  randomBtn->setAnchorPoint(ccp(0.5,0.5));
  randomBtn->setPosition(BTN_RANDOM_POS);
  CCLog("%f %f", randomBtn->getPositionX(), randomBtn->getPositionY());
  this->addChild(randomBtn, GR_FOREGROUND);
}

void ChooseMapScene::addButtonBack()
{
  CCSprite *backBtn = CCSprite::create("ChooseMapScene/button-back.png");
  backBtn->setPosition(BTN_BACK_POS);
  CCLog("%f %f", backBtn->getPositionX(), backBtn->getPositionY());
  this->addChild(backBtn, GR_FOREGROUND);
}

