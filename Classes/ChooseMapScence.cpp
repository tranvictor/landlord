//
//  ChooseMapScene.cpp
//  landlord
//
//  Created by Giap Nguyen on 4/25/14.
//
//

#include "ChooseMapScence.h"
#include "BounceButton.h"
#include "CustomTableViewCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool ChooseMapScene::init()
{
  if (!CCLayer::init())
  {
    return false;
  }
  mState = 1;
  
  sound::playBackgroundMusic(MUSIC_BACKGROUND);
  
  mScreenSize = CCDirector::sharedDirector()->getWinSize();
  CCLog("%f %f", mScreenSize.width, mScreenSize.height);
  
  addBackground();
  addSlidingLayers();
  addButtonBack();
  addButtonForward();
  mChooseCharacterLayer->addChild(mSymbolicCharacter);
  
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
  mBackground = CCSprite::create("Images/Game/Background/background_palax_enhanced.png");
  mBackground->setPosition(ccp(mBackground->getContentSize().width/2, mScreenSize.height/2));
  this->addChild(mBackground, GR_BACKGROUND);
  
  mTransparentBox = CCSprite::create("Images/Game/Background/transparent_box.png");
  mTransparentBox->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  this->addChild(mTransparentBox, GR_FOREGROUND);
}

void ChooseMapScene::addButtonBack()
{
  CCSprite *back = CCSprite::create("Images/Game/UI/leftNavigator.png");
  CCMenuItemSprite *backBtn =
    CCMenuItemSprite::create(back,
                             back,
                             this,
                             menu_selector(ChooseMapScene::buttonBackTouched));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(BTN_BACK_POS);
  this->addChild(pMenu, GR_FOREGROUND);
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
  this->addChild(pMenu, GR_FOREGROUND);
}

void ChooseMapScene::addSlidingLayers()
{
  mChooseCharacterLayer = createChooseCharaterLayer();
  mChooseCharacterLayer->setPosition(CCPointZero);

  mChooseMapLayer = createChooseMapLayer();
  mChooseMapLayer->setPosition(SCREEN_SIZE.width, 0);
  
  this->addChild(mChooseCharacterLayer, GR_FOREGROUND);
  this->addChild(mChooseMapLayer);

  mVs = BounceButton::create("Images/Game/UI/vsIcon-04.png");
  CCMenuItemSprite *backBtn = CCMenuItemSprite::create(mVs,
                                                       mVs,
                                                       this,
                                                       menu_selector(ChooseMapScene::switchCharacterSilde));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(VS_POS);
//  menu->setPosition(CCPointZero);
  mChooseCharacterLayer->addChild(pMenu, GR_FOREGROUND);
}

void ChooseMapScene::switchCharacterSilde(cocos2d::CCObject *pSender)
{
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  CREATE_MENU_ITEM_NO_CHANGE_SCENE();
  mSlideCharacter1->setTouchEnabled(!mSlideCharacter1->isTouchEnabled());
  mSlideCharacter2->setTouchEnabled(!mSlideCharacter2->isTouchEnabled());
  if (mSlideCharacter1->isTouchEnabled())
  {
    mChooseCharacterLayer->removeChildByTag(SYMBOLIC_CHARACTER_TAG);
    mSymbolicCharacter = CCSprite::create(CCString::createWithFormat("Images/Game/Object/c%i.png", mSlideCharacter2->getCurrentScreen() + 1)->getCString());
    mSymbolicCharacter->setOpacity(100);
    mSymbolicCharacter->setPosition(CHARACTER_RIGHT_LAYER_POS);
    mSymbolicCharacter->setTag(SYMBOLIC_CHARACTER_TAG);
    mChooseCharacterLayer->addChild(mSymbolicCharacter);
    
    mSlideCharacter1->setVisible(true);
    mSlideCharacter2->setVisible(false);
    addCharacterAura(mSlideCharacter1->getCurrentScreen() + 1, CHARACTER_LEFT_LAYER_POS);
  }
  else
  {
    mChooseCharacterLayer->removeChildByTag(SYMBOLIC_CHARACTER_TAG);
    mSymbolicCharacter = CCSprite::create(CCString::createWithFormat("Images/Game/Object/c%i.png", mSlideCharacter1->getCurrentScreen() + 1)->getCString());
    mSymbolicCharacter->setOpacity(100);
    mSymbolicCharacter->setPosition(CHARACTER_LEFT_LAYER_POS);
    mSymbolicCharacter->setTag(SYMBOLIC_CHARACTER_TAG);
    mChooseCharacterLayer->addChild(mSymbolicCharacter);
    
    mSlideCharacter1->setVisible(false);
    mSlideCharacter2->setVisible(true);
    addCharacterAura(mSlideCharacter2->getCurrentScreen() + 1, CHARACTER_RIGHT_LAYER_POS);
  }
}

void ChooseMapScene::addCharacterAura(int pCurrentCharater, cocos2d::CCPoint pPos)
{
  CCSprite* character = CCSprite::create(CCString::createWithFormat("Images/Game/Object/c%i.png", pCurrentCharater)->getCString());
  character->runAction(CCSequence::create(CCScaleTo::create(0.1, 1.15f),
                                          CCDelayTime::create(0.05f),
                                          CCScaleTo::create(0.1, 1.0f),
                                          CCCallFunc::create(this, callfunc_selector(ChooseMapScene::removeCharacterAura)),
                                          NULL));
  character->setPosition(pPos);
  this->addChild(character);
}

void ChooseMapScene::removeCharacterAura(cocos2d::CCObject *pSender)
{
  // TODO
  // just set visible because a bug on android with removeFromParent functions
  CCSprite* character = ((CCSprite*)pSender);
  this->removeChild(character, true);
  character->setVisible(false);
}

void ChooseMapScene::cooldown()
{
  float now = getCooldownTime();
  setCooldownTime(now - 0.3);
  if (now <= 0)
  {
    CCDirector::sharedDirector()->pause();
  }
}

CCArray* ChooseMapScene::createCharactersArray(CCPoint pPos)
{
  CCArray* characterArr = CCArray::createWithCapacity(NUMBER_CHARACTERS);
  for (int i = 1; i <= NUMBER_CHARACTERS; ++i)
  {
    CCLayer* characterLayer = CCLayer::create();

    CCSprite* character = CCSprite::create(CCString::createWithFormat("Images/Game/Object/c%i.png", i)->getCString());
    character->setPosition(pPos);
    characterLayer->addChild(character, GR_FOREGROUND, i);
    
    characterArr->addObject(characterLayer);
  }
  return characterArr;
}

// there are some magic numbers here, need transfer to Constant.h
CCLayer* ChooseMapScene::createChooseCharaterLayer()
{
  CCLayerColor* chooseCharacterLayer = CCLayerColor::create();
  
  // using CCScrollLayerVertical
  CCArray* characterArr1 = createCharactersArray(CHARACTER_LEFT_LAYER_POS);
  CCArray* characterArr2 = createCharactersArray(CHARACTER_RIGHT_LAYER_POS);
  
  mSlideCharacter1 = CCScrollLayerVertical::nodeWithLayers(characterArr1, 0);
  mSlideCharacter1->setTouchEnabled(true);
  mSlideCharacter1->selectPage(rand() % NUMBER_CHARACTERS);
  
  mSlideCharacter2 = CCScrollLayerVertical::nodeWithLayers(characterArr2, 0);
  mSlideCharacter2->setTouchEnabled(false);
  mSlideCharacter2->selectPage(rand() % NUMBER_CHARACTERS);
  mSlideCharacter2->setVisible(false);
  
  mSymbolicCharacter = CCSprite::create(CCString::createWithFormat("Images/Game/Object/c%i.png", mSlideCharacter2->getCurrentScreen() + 1)->getCString());
  mSymbolicCharacter->setPosition(CHARACTER_RIGHT_LAYER_POS);
  mSymbolicCharacter->setOpacity(100);
  mSymbolicCharacter->setTag(SYMBOLIC_CHARACTER_TAG);
  
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
    
    CCSprite* map = CCSprite::create(CCString::createWithFormat("Images/Map/map%i.png", i)->getCString());
    map->setPosition(CENTER_POS);
    mapLayer->addChild(map, GR_FOREGROUND, i);
    mapArr->addObject(mapLayer);
  }
  mSlideMap = CCScrollLayerVertical::nodeWithLayers(mapArr,  0);

  chooseMapLayer->addChild(mSlideMap, GR_FOREGROUND, TAG_SLIDE_MAP);
  
  return chooseMapLayer;
}

void ChooseMapScene::buttonBackTouched(cocos2d::CCObject *pSender)
{
  mSymbolicCharacter->setVisible(true);
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  mState--;
  if (mState == 0)
  {
    CREATE_MENU_ITEM(ChooseMapScene, LoadingScene, CCTransitionCrossFade);
  }
  else if (mState == 1)
  {
    CREATE_MENU_ITEM_NO_CHANGE_SCENE();
    mBackground->runAction(changePage(ccp(mBackground->getContentSize().width/2-90,
                                          SCREEN_SIZE.height/2)));
    mChooseMapLayer->runAction(changePage(ccp(SCREEN_SIZE.width, 0)));
    mChooseCharacterLayer->runAction(changePage(CCPointZero));
  }
}

void ChooseMapScene::buttonForwardTouched(cocos2d::CCObject *pSender)
{
  mSymbolicCharacter->setVisible(false);
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  CCLog("state: %d", mState);
  mState++;
  if (mState == 3)
  {
    int id = mSlideMap->getCurrentScreen();
    GameManager::setMapIDTouched(id + 1);
    
    GameManager::setPlayerOneID(mSlideCharacter1->getCurrentScreen() + 1);
    GameManager::setPlayerTwoID(mSlideCharacter2->getCurrentScreen() + 1);
    
    CREATE_MENU_ITEM(ChooseMapScene, PlayScene, CCTransitionCrossFade);
  }
  else if (mState == 2)
  {
    CREATE_MENU_ITEM_NO_CHANGE_SCENE();
    mBackground->runAction(changePage(ccp(SCREEN_SIZE.width - mBackground->getContentSize().width/2 + 90,
                                          SCREEN_SIZE.height/2)));

    mChooseMapLayer->runAction(changePage(CCPointZero));
    mChooseCharacterLayer->runAction(changePage(ccp(-SCREEN_SIZE.width, 0)));
  }
}

ChooseMapScene::~ChooseMapScene()
{
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

void ChooseMapScene::changeScene(cocos2d::CCObject *pData)
{
  CCDirector::sharedDirector()->replaceScene((CCTransitionScene*)pData);
}
