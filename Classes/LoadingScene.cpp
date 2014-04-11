//
//  LoadingScene.cpp
//  landlord
//
//  Created by Giap Nguyen on 4/10/14.
//
//

#include "LoadingScene.h"
USING_NS_CC;

CCScene *LoadingScene::scene()
{
  CCScene *scene = CCScene::create();
  
  CCLayer *layer = LoadingScene::create();
  
  scene->addChild(layer);
  
  return scene;
}

bool LoadingScene::init()
{
  if(!CCLayer::init() )
  {
    return false;
  }
  
  addItems();
  
  return true;
}

void LoadingScene::addItems()
{
  CCSprite* background = CCSprite::create("Images/Game/Object/loadingbg.png");
  background->setPosition(CENTER_POS);
  addChild(background, GR_BACKGROUND);
  
  CCSprite* island = CCSprite::create("Images/Game/Object/island.png");
  island->setPosition(CENTER_POS);
//  island->setVisible(false);
//  island->runAction(
//                    CCSequence::create(
//                                       CCDelayTime::create(0.4f),
//                                       CCFadeOut::create(0.6f),
//                                       CCFadeOut::create(1.6f),
//                                       NULL));
  this->addChild(island, GR_FOREGROUND);
  
  CCSprite* landlord = CCSprite::create("Images/Game/Object/landlord.png");
  landlord->setPosition(ccp(SCREEN_SIZE.width/2, SCREEN_SIZE.height/2 + island->getContentSize().height/3.5));
  addChild(landlord, GR_MIDDLEGROUND);
  
  CCSprite* sun = CCSprite::create("Images/Game/Object/sun-beam.png");
  sun->setPosition(CENTER_POS);
  sun->setScale(0.3f);
  sun->runAction(CCMoveTo::create(2.5f, CENTER_POS + ccp(0, 100)));
//  CCAction* repeateAction = CCRepeatForever::create(CCRotateBy::create(1,180));
//  mSelectedThong->runAction(repeateAction);
  sun->runAction(
                 CCSequence::create(
                                    CCScaleTo::create(2.5, 1.0),
                                    NULL));
  sun->runAction(CCRepeatForever::create(CCRotateBy::create(1, 30)));
  this->addChild(sun);
  
}
