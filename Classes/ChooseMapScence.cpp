//
//  ChooseMapScence.cpp
//  landlord
//
//  Created by Giap Nguyen on 2/19/14.
//
//

#include "ChooseMapScence.h"
#include "cocos2d.h"
#include "SlidingMenu.h"

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
  makeSlidingMap();
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
  CCSprite *random = CCSprite::create("ChooseMapScene/button-random.png");
//  randomBtn->setAnchorPoint(ccp(0.5,0.5));
//  random->setPosition(BTN_RANDOM_POS);
//  CCLog("%f %f", random->getPositionX(), random->getPositionY());
  CCMenuItemSprite *randomBtn = CCMenuItemSprite::create(random,
                                                         random,
                                                         this,
                                                         menu_selector(ChooseMapScene::buttonRandomTouched));
  CCMenu* pMenu = CCMenu::create(randomBtn, NULL);
  pMenu->setPosition(BTN_RANDOM_POS);
  this->addChild(pMenu, 1);
}

void ChooseMapScene::addButtonBack()
{
  CCSprite *back = CCSprite::create("ChooseMapScene/button-back.png");
//  backBtn->setPosition(BTN_BACK_POS);
//  CCLog("%f %f", backBtn->getPositionX(), backBtn->getPositionY());
  CCMenuItemSprite *backBtn = CCMenuItemSprite::create(back,
                                                         back,
                                                         this,
                                                       menu_selector(ChooseMapScene::buttonBackTouched));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(BTN_BACK_POS);
  this->addChild(pMenu, 1);
}

void ChooseMapScene::makeSlidingMap()
{
  maps = CCArray::createWithCapacity(NUMBER_LEVELS);
  for(int i = 1; i <= NUMBER_LEVELS; i++){
    CCString *mapName = CCString::createWithFormat("ChooseMapScene/map-0%i.png", i);
    Maps *map = Maps::create(mapName->getCString());
    map->setMapID(i);
    CCLog("%i", map->getMapID());
    CCMenuItemSprite *mapItem = CCMenuItemSprite::create(map,
                                                         map,
                                                         this,
                                                         menu_selector(ChooseMapScene::mapTouched));
    mapItem->setTag(i);
    maps->addObject(mapItem);
  }
  
  SlidingMenuGrid *grid = SlidingMenuGrid::menuWithArray(maps, 1, 1, MAP_CENTER_POS, ccp(444, 0)); // distance between 2 maps - not working
  
  grid->SetSwipeDeadZone(30.0f);
  this->addChild(grid);
}


void ChooseMapScene::mapTouched(CCObject* pSender)
{
  CCMenuItem* menuItem = (CCMenuItem*)pSender;
  CCLog("map %i choosed", menuItem->getTag());
}


void ChooseMapScene::buttonRandomTouched(cocos2d::CCObject *pSender)
{
  CCLog("button random touched");
}

void ChooseMapScene::buttonBackTouched(cocos2d::CCObject *pSender)
{
  CCLog("button back touched");
}