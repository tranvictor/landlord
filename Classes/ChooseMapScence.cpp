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

void ChooseMapScene::makeSlidingMap()
{
  mapArr = CCArray::createWithCapacity(NUMBER_MAPS);
  for(int i = 1; i <= NUMBER_MAPS; i++)
  {
    CCString *mapName = CCString::createWithFormat("ChooseMapScene/map-0%i.png", i);
    Maps *map = Maps::create(mapName->getCString());
//    CCLog("mapID = %i", );
    CCMenuItemSprite *mapItem = CCMenuItemSprite::create(map,
                                                         map,
                                                         this,
                                                         menu_selector(ChooseMapScene::mapTouched));
    mapItem->setTag(i);
    mapArr->addObject(mapItem);
  }
  
  slidingMap = SlidingMenuGrid::menuWithArray(mapArr, 1, 1, MAP_CENTER_POS, ccp(444, 0)); // distance between 2 maps - not working
  
  slidingMap->SetSwipeDeadZone(30.0f);
  CCLabelTTF *lbnMap;
  
  for (int i = 1; i <= NUMBER_MAPS; ++i)
  {
    lbnMap = CCLabelTTF::create((CCString::createWithFormat("%i/%i", i, NUMBER_MAPS))->getCString(),"Arial", 40);
    lbnMap->setColor(ccWHITE);
    lbnMap->setPosition(ccp(screenSize.width/2+screenSize.width*(i-1), screenSize.height/2 - 100));
//    this->addChild(lbnMap, 10);
//    lbnMap->setParent((CCNode*)mapArr->objectAtIndex(i+1));
    slidingMap->setPageLabel(i, lbnMap);
  }
  this->addChild(slidingMap);
}

// make silding maps with CCScrollView

//void ChooseMapScene::makeSlidingMap()
//{
//  CCString *mapName;
//  CCLayer *mapLayer = CCLayer::create();
//
//  for (int i = 1; i < NUMBER_MAPS; i++)
//  {
//    mapName = CCString::createWithFormat("ChooseMapScene/map-0%i.png", i);
//    CCSprite *mapSprite = CCSprite::create(mapName->getCString());
//    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(mapSprite, mapSprite, this, menu_selector(ChooseMapScene::mapTouched));
//    mapArr->addObject(menuItem);
//    mapLayer->addChild(menuItem);
//  }
//  mapLayer->setContentSize(CCSize(screenSize.width + MAP_WIDTH*NUMBER_MAPS + (NUMBER_MAPS-1)*DISTANCE_BETWEEN_MAPS, screenSize.height));
//  slidingMap = CCScrollView::create(CCSize(screenSize.width, screenSize.height), mapLayer);
//  slidingMap->setBounceable(false);
////  slidingMap = CCScrollView::create(CCSize(screenSize.width + MAP_WIDTH*NUMBER_MAPS + (NUMBER_MAPS-1)*DISTANCE_BETWEEN_MAPS , screenSize.height));
//  this->addChild(slidingMap, GR_FOREGROUND);
//}


void ChooseMapScene::mapTouched(CCObject* pSender)
{
  CCMenuItem* mapItem = (CCMenuItem*)pSender;
  mapTouchedID = mapItem->getTag();
//  mapTouched->setMapID(mapTouchedID);
  CCLog("map %i choosed", mapTouchedID);
}


void ChooseMapScene::buttonRandomTouched(cocos2d::CCObject *pSender)
{
  CCLog("button random touched");
  int r = ((int)random())%10+1;
  CCLog("r = %i", r);
  slidingMap->gotoPage(r, true);
}

void ChooseMapScene::buttonBackTouched(cocos2d::CCObject *pSender)
{
  CCLog("button back touched");
}

//void ChooseMapScene::scrollViewDidScroll(CCScrollView* view)
//{
//  
//}
//
//void ChooseMapScene::scrollViewDidZoom(CCScrollView* view)
//{
//  
//}
