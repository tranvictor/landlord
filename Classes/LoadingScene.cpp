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
  island->setPosition(ISLAND_POS);
//  island->setVisible(false);
//  island->runAction(
//                    CCSequence::create(
//                                       CCDelayTime::create(0.4f),
//                                       CCFadeOut::create(0.6f),
//                                       CCFadeOut::create(1.6f),
//                                       NULL));
  this->addChild(island, GR_FOREGROUND);
  
  CCSprite* landlord = CCSprite::create("Images/Game/Object/landlord.png");
  landlord->setPosition(LANDLORD_POS);
  addChild(landlord, GR_MIDDLEGROUND);
  
  CCSprite* sun = CCSprite::create("Images/Game/Object/sun-beam.png");
  sun->setPosition(CENTER_POS);
  sun->setScale(INITIAL_SUN_SCALE);
  sun->runAction(CCMoveTo::create(TIME_TO_SUN_MOVE, SUN_POS));
//  CCAction* repeateAction = CCRepeatForever::create(CCRotateBy::create(1,180));
//  mSelectedThong->runAction(repeateAction);
  sun->runAction(
                 CCSequence::create(
                                    CCScaleTo::create(TIME_TO_SUN_MOVE, FINAL_SUN_SCALE),
                                    NULL));
  sun->runAction(CCRepeatForever::create(CCRotateBy::create(TIME_TO_ROTATE_SUN, DELTA_ANGLE)));
  this->addChild(sun);
  
  CCSprite* mist = CCSprite::create("Images/Game/Object/myst-01.png");
  CCSprite* mist2 = CCSprite::create("Images/Game/Object/myst-02.png");
  background->runAction(CCFadeIn::create(TIME_TO_MYST_FADE_IN_OUT/2));
  mist->runAction(
    CCRepeatForever::create(
      CCSequence::create(
        CCFadeOut::create(TIME_TO_MYST_FADE_IN_OUT),
        CCFadeIn::create(TIME_TO_MYST_FADE_IN_OUT),
        NULL)));
  mist->setPosition(MYST_POS);
  mist2->runAction(
    CCRepeatForever::create(
      CCSequence::create(
        CCFadeIn::create(TIME_TO_MYST_FADE_IN_OUT),
        CCFadeOut::create(TIME_TO_MYST_FADE_IN_OUT),
        NULL)));
  mist2->setPosition(MYST_POS);
  this->addChild(mist, GR_MIDDLEGROUND);
  this->addChild(mist2, GR_MIDDLEGROUND);
  
  for (int i = -1; i <= NUMBER_CLOUDS; i++)
  {
    CCSprite* cloud = CCSprite::create("Images/Game/Object/cloud.png");
    cloud->setPosition(LANDLORD_POS+ ccp((landlord->getContentSize().width/2-40)*i, i*2));
//    cloud->runAction(<#cocos2d::CCAction *action#>)
//    cloud->setColor(ccRED);
    this->addChild(cloud, 100);
  }
}
