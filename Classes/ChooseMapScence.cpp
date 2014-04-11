//
//  ChooseMapScence.cpp
//  landlord
//
//  Created by Giap Nguyen on 2/19/14.
//
//

#include "ChooseMapScence.h"
#include "cocos2d.h"
#include "ChooseCharacterScene.h"
#include "PlayScene.h"
#include "GameManager.h"

USING_NS_CC;

bool ChooseMapScene::init()
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

CCScene* ChooseMapScene::scene()
{
  CCScene *scene = CCScene::create();
  ChooseMapScene *layer = ChooseMapScene::create();
  scene->addChild(layer);
  
  return scene;
}

void ChooseMapScene::addBackground()
{
  CCSprite *background = CCSprite::create("Images/Game/Background/BG-islands.png");
  background->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  this->addChild(background, GR_BACKGROUND);
}

void ChooseMapScene::addButtonRandom()
{
  CCSprite *random = CCSprite::create("Images/Game/UI/button-random.png");
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
  CCSprite *back = CCSprite::create("Images/Game/UI/button-back.png");
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
  mMapArr = CCArray::createWithCapacity(NUMBER_MAPS);
  for (int i = 1; i <= NUMBER_MAPS; ++i)
  {
    CCMenu *menu = CCMenu::create(NULL);
    CCString *mapName = (CCString::createWithFormat("Images/Map/map-0%i.png", i));
    CCMenuItemImage *map = CCMenuItemImage::create(mapName->getCString(), mapName->getCString(), this, menu_selector(ChooseMapScene::mapTouched));
    map->setTag(i);
    menu->addChild(map);
    menu->setPosition(CCPointMake(MAP_CENTER_X, MAP_CENTER_Y));
    
    CCLayer *mapLayer = CCLayer::create();
    mapLayer->addChild(menu);
    
    mMapArr->addObject(mapLayer);
  }
//  mSlidingMap = CCScrollLayer::nodeWithLayers(mMapArr, - mScreenSize.width - (NUMBER_MAPS-1)*DISTANCE_BETWEEN_MAPS, "ChooseMapScene/greendot-08.png");
  mSlidingMap = CCScrollLayer::nodeWithLayers(mMapArr, 0, "Images/Game/UI/greendot-08.png");
  mSlidingMap->setPagesIndicatorPosition(ccp(mScreenSize.width/2, GREEN_DOT_Y));
  this->addChild(mSlidingMap, GR_FOREGROUND);
}

void ChooseMapScene::mapTouched(CCObject *pSender)
{
  CCMenuItemImage* mapSelected = (CCMenuItemImage*)pSender;
  mMapTouchedID = mapSelected->getTag();
  CCLog("map %i choosed", mMapTouchedID);
  GameManager::setMapIDTouched(mMapTouchedID);
  CCScene* playScene = CCTransitionCrossFade::create(SCENE_TRANSITION_TIME, PlayScene::scene());
  CCDirector::sharedDirector()->replaceScene(playScene);

}


void ChooseMapScene::buttonRandomTouched(cocos2d::CCObject *pSender)
{
  CCLog("button random touched");
  srand (time(NULL));
  int withIndex = ((int)random())%NUMBER_MAPS+1;
  CCLog("r = %i", withIndex);
  mSlidingMap->moveToPage(withIndex-1);
}

void ChooseMapScene::buttonBackTouched(cocos2d::CCObject *pSender)
{
  CCLog("button back touched");
  CCScene* chooCharacterScene = CCTransitionCrossFade::create(SCENE_TRANSITION_TIME, ChooseCharacterScene::scene());
  CCDirector::sharedDirector()->replaceScene(chooCharacterScene);

}
