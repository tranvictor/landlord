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
//  addTempSlide();
//  showPagesIndicator(true);
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
//  Maps *mapSprite;
//  CCLayer *mapLayer = CCLayer::create();
  for (int i = 1; i <= NUMBER_MAPS; ++i)
  {
//    Maps *mapSprite = Maps::create(CCString::createWithFormat("ChooseMapScene/map-0%i.png", i)->getCString());
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
  slidingMap = CCScrollLayer::nodeWithLayers(mapArr, screenSize.width + (NUMBER_MAPS-1)*DISTANCE_BETWEEN_MAPS);
  slidingMap->setPagesIndicatorPosition(ccp(screenSize.width/2, screenSize.height/3));
  this->addChild(slidingMap, GR_FOREGROUND);
}

//void ChooseMapScene::makeSlidingMap()
//{
//  mapArr = CCArray::createWithCapacity(NUMBER_MAPS);
//  for(int i = 1; i <= NUMBER_MAPS; i++)
//  {
//    CCString *mapName = CCString::createWithFormat("ChooseMapScene/map-0%i.png", i);
//    Maps *mapSprite = Maps::create(mapName->getCString());
////    CCLog("mapID = %i", );
//    CCMenuItemSprite *mapItem = CCMenuItemSprite::create(mapSprite,
//                                                         mapSprite,
//                                                         this,
//                                                         menu_selector(ChooseMapScene::mapTouched));
//    mapItem->setPosition(MAP_CENTER_POS);
//    CCLayer *mapLayer = CCLayer::create();
////    mapLayer->addChild(mapItem);
//    mapItem->setTag(i);
////    slidingMap->addPage(mapLayer, i);
//    mapArr->addObject(mapItem);
//  }
//
////  slidingMap = SlidingMenuGrid::create(mapArr, MAP_WIDTH);
//  
//  slidingMap = SlidingMenuGrid::menuWithArray(mapArr, 1, 1, MAP_CENTER_POS, ccp(444, 0)); // distance between 2 maps - not working
//  
//  slidingMap->SetSwipeDeadZone(30.0f);
//  slidingMap->showPagesIndicator(true);
//  
////  for (int i = 1; i <= NUMBER_MAPS; ++i)
////  {
////    lbnMap = CCLabelTTF::create((CCString::createWithFormat("%i/%i", i, NUMBER_MAPS))->getCString(),"ordin", 40);
//////    lbnMap->setDirty(true);
////    lbnMap->setColor(ccc3(57, 181, 74));  //green
//////    CCLog("%i", slidingMap->getCurrentPage());
////    lbnMap->setPosition(ccp(screenSize.width/2+screenSize.width*(i-1), screenSize.height/2 - 150));
//////    this->addChild(lbnMap, 10);
//////    lbnMap->setParent((CCNode*)mapArr->objectAtIndex(i+1));
////    slidingMap->setPageLabel(i, lbnMap);
////  }
////  slidingMap->setShowPagesIndicator(true);
//  this->addChild(slidingMap);
//}

//// make silding maps with CCScrollView
//
////void ChooseMapScene::makeSlidingMap()
////{
////  CCString *mapName;
////  CCLayer *mapLayer = CCLayer::create();
////
////  for (int i = 1; i <= NUMBER_MAPS; i++)
////  {
////    mapName = CCString::createWithFormat("ChooseMapScene/map-0%i.png", i);
////    CCSprite *mapSprite = CCSprite::create(mapName->getCString());
////    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(mapSprite, mapSprite, this, menu_selector(ChooseMapScene::mapTouched));
////    menuItem->setPosition(ccp(screenSize.width/2 + (i-1)*DISTANCE_BETWEEN_MAPS, MAP_CENTER_Y));
//////    CCMenu* pMenu = CCMenu::create(menuItem, NULL);
//////    mapArr->addObject(menuItem);
//////    mapLayer->addChild(pMenu, 10);
////    mapLayer->addChild(menuItem);
////  }
////  mapLayer->setContentSize(CCSize(screenSize.width + (NUMBER_MAPS-1)*DISTANCE_BETWEEN_MAPS, screenSize.height));
//////  slidingMap = CCScrollView::create(CCSizeMake(screenSize.width, screenSize.height), mapLayer);
//////  slidingMap->setBounceable(false);
//////  this->addChild(slidingMap, GR_FOREGROUND);
////}


void ChooseMapScene::mapTouched(CCObject* pSender)
{
  CCMenuItemImage* mapSelected = (CCMenuItemImage*)pSender;
  mapTouchedID = mapSelected->getTag();
  CCLog("map %i choosed", mapTouchedID);
}


void ChooseMapScene::buttonRandomTouched(cocos2d::CCObject *pSender)
{
  CCLog("button random touched");
  int r = ((int)random())%10+1;
  CCLog("r = %i", r);
//  slidingMap->gotoPage(r, true);
  slidingMap->moveToPage(r-1);
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
//
//void ChooseMapScene::addTempSlide()
//{
//  CCLayer *layer = CCLayer::create();
//  CCLabelTTF *label = CCLabelTTF::create("String", "Arial", 24);
//  label->setPosition(ccp(screenSize.width/2, screenSize.height/2));
//  layer->addChild(label);
//  
//  CCLayer *layer1 = CCLayer::create();
//  CCLabelTTF *label1 = CCLabelTTF::create("String1", "Arial", 24);
//  label1->setPosition(ccp(screenSize.width/2, screenSize.height/2));
//  layer1->addChild(label1);
//  
//  CCScrollLayer *scroll = CCScrollLayer::nodeWithLayers(CCArray::create(layer, layer1, NULL), screenSize.width*2);
//  scroll->setShowPagesIndicator(true);
//  scroll->setPagesIndicatorPosition(ccp(screenSize.width/2, 500));
//  addChild(scroll);
//}
