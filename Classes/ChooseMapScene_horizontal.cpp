//
//  ChooseMapScene_horizontal.cpp
//  landlord
//
//  Created by Giap Nguyen on 4/25/14.
//
//

#include "ChooseMapScene_horizontal.h"

USING_NS_CC;

bool ChooseMapScene_horizontal::init()
{
  if (!CCLayer::init())
  {
    return false;
  }
  
  mScreenSize = CCDirector::sharedDirector()->getWinSize();
  CCLog("%f %f", mScreenSize.width, mScreenSize.height);
  
  addBackground();
  addButtonRandom();
  addButtonBack();
  makeSlidingMap();
  return true;
}

CCScene* ChooseMapScene_horizontal::scene()
{
  CCScene *scene = CCScene::create();
  ChooseMapScene_horizontal *layer = ChooseMapScene_horizontal::create();
  scene->addChild(layer);
  
  return scene;
}

void ChooseMapScene_horizontal::addBackground()
{
  CCSprite *background = CCSprite::create("Images/Game/Background/BG-islands.png");
  background->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  this->addChild(background, GR_BACKGROUND);
}

void ChooseMapScene_horizontal::addButtonRandom()
{
  CCSprite *random = CCSprite::create("Images/Game/UI/button-random.png");
  CCMenuItemSprite *randomBtn = CCMenuItemSprite::create(random,
                                                         random,
                                                         this,
                                                         menu_selector(ChooseMapScene_horizontal::buttonRandomTouched));
  CCMenu* pMenu = CCMenu::create(randomBtn, NULL);
  pMenu->setPosition(BTN_RANDOM_POS);
  this->addChild(pMenu, GR_BACKGROUND);
}

void ChooseMapScene_horizontal::addButtonBack()
{
  CCSprite *back = CCSprite::create("Images/Game/UI/button-back.png");
  CCMenuItemSprite *backBtn = CCMenuItemSprite::create(back,
                                                       back,
                                                       this,
                                                       menu_selector(ChooseMapScene_horizontal::buttonBackTouched));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(BTN_BACK_POS);
  this->addChild(pMenu, GR_BACKGROUND);
}

// use CCScrollLayer
void ChooseMapScene_horizontal::makeSlidingMap()
{
  mMapArr = CCArray::createWithCapacity(NUMBER_MAPS);
  for (int i = 1; i <= NUMBER_MAPS; ++i)
  {
    CCMenu *menu = CCMenu::create(NULL);
    CCString *mapName = (CCString::createWithFormat("Images/Map/map-0%i.png", i));
    CCMenuItemImage *map = CCMenuItemImage::create(mapName->getCString(), mapName->getCString(), this, menu_selector(ChooseMapScene_horizontal::mapTouched));
    map->setTag(i);
    menu->addChild(map);
    menu->setPosition(CCPointMake(MAP_CENTER_X, MAP_CENTER_Y));
    
    CCLayer *mapLayer = CCLayer::create();
    mapLayer->addChild(menu);
    
    mMapArr->addObject(mapLayer);
  }
  //  mSlidingMap = CCScrollLayer::nodeWithLayers(mMapArr, - mScreenSize.width - (NUMBER_MAPS-1)*DISTANCE_BETWEEN_MAPS, "ChooseMapScene_horizontal/greendot-08.png");
  mSlidingMap = CCScrollLayer::nodeWithLayers(mMapArr, 0, "Images/Game/UI/greendot-08.png");
  mSlidingMap->setPagesIndicatorPosition(ccp(mScreenSize.width/2, GREEN_DOT_Y));
  this->addChild(mSlidingMap, GR_FOREGROUND);
}

void ChooseMapScene_horizontal::mapTouched(CCObject *pSender)
{
  sound::playSoundFx(SFX_CHOOSE_MAP);
  CCMenuItemImage* mapSelected = (CCMenuItemImage*)pSender;
  mMapTouchedID = mapSelected->getTag();
  CCLog("map %i choosed", mMapTouchedID);
  GameManager::setMapIDTouched(mMapTouchedID);
  CCScene* newScene = CCTransitionCrossFade::create(0.5, PlayScene::scene());
  CCDirector::sharedDirector()->replaceScene(newScene);
}

void ChooseMapScene_horizontal::buttonRandomTouched(cocos2d::CCObject *pSender)
{
  CCLog("button random touched");
  sound::playSoundFx(SFX_RANDOM_MAP);
  srand (time(NULL));
  int r = ((int)random()) % 10 + 1;
  CCLog("r = %i", r);
  mSlidingMap->moveToPage(r - 1);
}

void ChooseMapScene_horizontal::buttonBackTouched(cocos2d::CCObject *pSender)
{
  CCLog("button back touched");
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  CCScene* newScene = CCTransitionCrossFade::create(0.5, ChooseCharacterScene::scene());
  CCDirector::sharedDirector()->replaceScene(newScene);
  
}
