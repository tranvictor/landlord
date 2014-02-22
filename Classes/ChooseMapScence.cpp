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
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  this->addChild(background, GR_BACKGROUND);
}

void ChooseMapScene::addButtonRandom()
{
  CCSprite *random = CCSprite::create("ChooseMapScene/button-random.png");
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
  CCMenuItemSprite *backBtn = CCMenuItemSprite::create(back,
                                                         back,
                                                         this,
                                                       menu_selector(ChooseMapScene::buttonBackTouched));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(BTN_BACK_POS);
  this->addChild(pMenu, 1);
}

// use CCScrollLayer
void ChooseMapScene::makeSlidingMap()
{
  mapArr = CCArray::createWithCapacity(NUMBER_MAPS);
  for (int i = 1; i <= NUMBER_MAPS; ++i)
  {
    CCMenu *menu = CCMenu::create(NULL);
    CCString *mapName = (CCString::createWithFormat("ChooseMapScene/map-0%i.png", i));
    CCMenuItemImage *map = CCMenuItemImage::create(mapName->getCString(), mapName->getCString(), this, menu_selector(ChooseMapScene::mapTouched));
    map->setTag(i);
    menu->addChild(map);
    menu->setPosition(CCPointMake(MAP_CENTER_X, MAP_CENTER_Y));
    
    CCLayer *mapLayer = CCLayer::create();
    mapLayer->addChild(menu);
    
    mapArr->addObject(mapLayer);
  }
  slidingMap = CCScrollLayer::nodeWithLayers(mapArr, screenSize.width + (NUMBER_MAPS-1)*DISTANCE_BETWEEN_MAPS, "ChooseMapScene/greendot-08.png");
  slidingMap->setPagesIndicatorPosition(ccp(screenSize.width/2, GREEN_DOT_Y));
  this->addChild(slidingMap, GR_FOREGROUND);
}

void ChooseMapScene::mapTouched(CCObject* pSender)
{
  CCMenuItemImage* mapSelected = (CCMenuItemImage*)pSender;
  mapTouchedID = mapSelected->getTag();
//  mapTouchedID = slidingMap->getCurrentScreen();
  CCLog("map %i choosed", mapTouchedID);
}


void ChooseMapScene::buttonRandomTouched(cocos2d::CCObject *pSender)
{
  CCLog("button random touched");
  int r = ((int)random())%10+1;
  CCLog("r = %i", r);
  slidingMap->moveToPage(r-1);
}

void ChooseMapScene::buttonBackTouched(cocos2d::CCObject *pSender)
{
  CCLog("button back touched");
}
