//
//  ChooseMapScene.cpp
//  landlord
//
//  Created by Giap Nguyen on 4/25/14.
//
//

#include "ChooseMapScence.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool ChooseMapScene::init()
{
  if (!CCLayer::init())
  {
    return false;
  }
  mState = 1;
  
  mScreenSize = CCDirector::sharedDirector()->getWinSize();
  CCLog("%f %f", mScreenSize.width, mScreenSize.height);
  
  addBackground();
  
  addButtonBack();
  addButtonForward();
  
  addSlidingLayers();
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
  CCSprite *background = CCSprite::create("Images/Game/Background/chooseBg-01.png");
  background->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  this->addChild(background, GR_BACKGROUND);
}

void ChooseMapScene::addButtonBack()
{
  CCSprite *back = CCSprite::create("Images/Game/UI/leftNavigator.png");
  CCMenuItemSprite *backBtn = CCMenuItemSprite::create(back,
                                                       back,
                                                       this,
                                                       menu_selector(ChooseMapScene::buttonBackTouched));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(BTN_BACK_POS);
  this->addChild(pMenu, GR_BACKGROUND);
}

void ChooseMapScene::addButtonForward()
{
  CCSprite *back = CCSprite::create("Images/Game/UI/rightNavigator.png");
  CCMenuItemSprite *backBtn = CCMenuItemSprite::create(back,
                                                       back,
                                                       this,
                                                       menu_selector(ChooseMapScene::buttonForwardTouched));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(BTN_FORWARSD_POS);
  this->addChild(pMenu, GR_BACKGROUND);
}

void ChooseMapScene::addSlidingLayers()
{
  mChooseCharacterLayer = createChooseCharaterLayer();
  mChooseCharacterLayer->setPosition(CCPointZero);
  mChooseCharacterLayer->setTouchEnabled(true);
  
  mChooseMapLayer = createChooseMapLayer();
  mChooseMapLayer->setPosition(SCREEN_SIZE.width, 0);
  
  randomCharacter(NULL);
  
  this->addChild(mChooseCharacterLayer, GR_FOREGROUND);
  this->addChild(mChooseMapLayer);

  mVs = CCSprite::create("Images/Game/UI/vsIcon-04.png");
  mVs->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  mVs->setPosition(VS_POS);
//  mChooseCharacterLayer->addChild(mVs, GR_FOREGROUND);
  
  CCMenu* menu = CCMenu::create(CCMenuItemSprite::create(mVs, mVs, this, menu_selector(ChooseMapScene::randomCharacter)), NULL);
//  menu->setPosition(0, 0);
  
  mChooseCharacterLayer->addChild(menu);
}

void ChooseMapScene::ccTouchBegin(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  CCLog("xx");
  
  if (mVs->boundingBox().containsPoint(pTouch->getLocation()))
  {
    sound::playSoundFx(SFX_TOUCH_TILE);
    randomCharacter(NULL);
  }
}

void ChooseMapScene::registerWithTouchDispatcher()
{
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void ChooseMapScene::randomCharacter(cocos2d::CCObject *pSender)
{
  sound::playSoundFx(SFX_TOUCH_POP);
  srand(time(NULL));
  int charater1 = rand() % NUMBER_CHARACTERS + 1;
  int charater2;
  while (charater2 == charater1)
    charater2 = rand() % NUMBER_CHARACTERS + 1;
  mSlideCharacter1->moveToPage(charater1 - 1);
  mSlideCharacter2->moveToPage(charater2 - 1);
  
  GameManager::setPlayerOneID(charater1);
  GameManager::setPlayerTwoID(charater2);
  CCLog("%d %d", GameManager::getPlayerOneID(), GameManager::getPlayerTwoID());
  CCLog("%d %d", charater1, charater2);
}

CCLayer* ChooseMapScene::createChooseCharaterLayer()
{
  CCLayer* chooseCharacterLayer = CCLayer::create();
  CCArray* characterArr1 = CCArray::createWithCapacity(NUMBER_CHARACTERS);
  CCArray* characterArr2 = CCArray::createWithCapacity(NUMBER_CHARACTERS);
  for (int i = 1; i <= NUMBER_CHARACTERS; ++i)
  {
    CCLayer* characterLayer = CCLayer::create();
    
    CCSprite* character = CCSprite::create(CCString::createWithFormat("Images/Game/Object/c%i.png", i)->getCString());
    character->setPosition(CHARACTER_RIGHT_LAYER_POS);
    characterLayer->addChild(character, GR_FOREGROUND, i);
//    characterLayer->setPosition(-SCREEN_SIZE.width/2, 0);
    characterArr1->addObject(characterLayer);
  }

  for (int i = 1; i <= NUMBER_CHARACTERS; ++i)
  {
    CCLayer* characterLayer = CCLayer::create();
    
    CCSprite* character = CCSprite::create(CCString::createWithFormat("Images/Game/Object/c%i.png", i)->getCString());
    character->setPosition(CHARACTER_LEFT_LAYER_POS);
    characterLayer->addChild(character, GR_FOREGROUND, i);
//    characterLayer->setPosition(SCREEN_SIZE.width/2, 0);
    characterArr2->addObject(characterLayer);
  }
  
  mSlideCharacter1 = CCScrollLayerHorizontal::nodeWithLayers(characterArr1, 0);

  mSlideCharacter2 = CCScrollLayerHorizontal::nodeWithLayers(characterArr2, 0);
  
  chooseCharacterLayer->addChild(mSlideCharacter1, GR_FOREGROUND);
  chooseCharacterLayer->addChild(mSlideCharacter2, GR_FOREGROUND);
  
  return chooseCharacterLayer;
}

CCLayer* ChooseMapScene::createChooseMapLayer()
{
  CCLayer* chooseMapLayer = CCLayer::create();
  CCArray* mapArr = CCArray::createWithCapacity(NUMBER_MAPS);
  for (int i = 1; i <= NUMBER_MAPS; ++i)
  {
    CCLayer* mapLayer = CCLayer::create();
    
    CCSprite* map = CCSprite::create(CCString::createWithFormat("Images/Map/map-0%i.png", i)->getCString());
    map->setPosition(CENTER_POS);
    mapLayer->addChild(map, GR_FOREGROUND, i);
    mapArr->addObject(mapLayer);
  }
  CCScrollLayerHorizontal* slideMap = CCScrollLayerHorizontal::nodeWithLayers(mapArr, 0);

  chooseMapLayer->addChild(slideMap, GR_FOREGROUND, TAG_SLIDE_MAP);
  
  return chooseMapLayer;
}

void ChooseMapScene::buttonBackTouched(cocos2d::CCObject *pSender)
{
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  mState--;
  CCLog("%d", mState);
  if (mState == 0)
  {
    CCScene* newScene = CCTransitionCrossFade::create(0.5, LoadingScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
  }
  else if (mState == 1)
  {
    mChooseMapLayer->runAction(changePage(ccp(SCREEN_SIZE.width, 0)));
    mChooseCharacterLayer->runAction(changePage(CCPointZero));
  }
}

void ChooseMapScene::buttonForwardTouched(cocos2d::CCObject *pSender)
{
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  CCLog("%d", mState);
  mState++;
  if (mState == 3)
  {
//    int id = mChooseMapLayer->getChildByTag(TAG_SLIDE_MAP)->getChildByTag(i)
//    GameManager::setMapIDTouched();
    CCScene* newScene = CCTransitionCrossFade::create(0.5, PlayScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
  }
  else if (mState == 2)
  {
    mChooseMapLayer->runAction(changePage(CCPointZero));
    mChooseCharacterLayer->runAction(changePage(ccp(-SCREEN_SIZE.width, 0)));
  }
}

ChooseMapScene::~ChooseMapScene()
{
//  mArr->release(); /
}

CCAction* ChooseMapScene::changePage(cocos2d::CCPoint pPos)
{
  float actionDuration = 1.0f;
  float bouncePeriod = 0.7f;
  CCAction* changePage =
    CCSequence::create(
     CCEaseElasticOut::create(
      CCMoveTo::create(actionDuration, pPos),
      bouncePeriod),
     NULL);
  return changePage;
}

