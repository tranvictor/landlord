//
//  ChooseCharacterScene.cpp
//  landlord
//
//  Created by Tuan TQ on 2/26/14.
//
//

#include "ChooseCharacterScene.h"
#include "Constant.h"
#include "StartScene.h"
#include "ChooseMapScence.h"
#include "GameManager.h"

USING_NS_CC;


CCScene* ChooseCharacterScene::scene()
{
  CCScene* scene = CCScene::create();
  ChooseCharacterScene* layer = ChooseCharacterScene::create();
  scene->addChild(layer);

  return scene;
}

bool ChooseCharacterScene::init()
{
  if (!CCLayer::init())
  {
    return false;
  }

  mScreenSize = CCDirector::sharedDirector()->getWinSize();
  addBackground();
  addCharacter();
  addBackButton();

  mCharacterArr->retain();

  return true;
}

void ChooseCharacterScene::addBackground()
{
  CCSprite* background = CCSprite::create("Images/Game/Background/BG-character.png");
  CCLOG("%f %f", mScreenSize.width, mScreenSize.height);
  background->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  this->addChild(background, GR_BACKGROUND, CHOOSECHARACTER_BG_TAG);
}

void ChooseCharacterScene::addCharacter()
{
  mCharacterArr = CCArray::createWithCapacity(NUMBER_CHARACTERS/NUMBER_CHARACTERS_PER_SCENE);
  for (int i = 1; i <= NUMBER_CHARACTERS/NUMBER_CHARACTERS_PER_SCENE; ++i)
  {
    CCLayer* characterLayer = CCLayer::create();
    for (int j = 1; j <= NUMBER_CHARACTERS_PER_SCENE; ++j)
    {
      int characterID = j + NUMBER_CHARACTERS_PER_SCENE*(i - 1);
      CCString* characterName = (CCString::createWithFormat("Images/Game/Object/c%i.png", characterID));
      CCSprite* character = CCSprite::create(characterName->getCString());

      CCMenuItemSprite* characterItem = CCMenuItemSprite::create(character,
                                                                 character,
                                                                 this,
                                                                 menu_selector(ChooseCharacterScene::characterTouched));
      characterItem->setTag(characterID);
      CCMenu* menu = CCMenu::create(characterItem, NULL);
      switch (characterID) {
        case 1:
          menu->setPosition(C1_POS);
          break;
        case 2:
          menu->setPosition(C2_POS);
          break;
        case 3:
          menu->setPosition(C3_POS);
          break;
        case 4:
          menu->setPosition(C4_POS);
          break;
        case 5:
          menu->setPosition(C5_POS);
          break;
        case 6:
          menu->setPosition(C6_POS);
          break;
        case 7:
          menu->setPosition(C7_POS);
          break;
        case 8:
          menu->setPosition(C8_POS);
          break;
        default:
          CCLOG("No character set positon");
          break;
      }
      characterLayer->addChild(menu, GR_FOREGROUND, characterID);
    }
    mCharacterArr->addObject(characterLayer);
  }
  mCharacterArr->retain();

  mSlidingCharacterLayer = CCScrollLayer::nodeWithLayers(mCharacterArr, 0, "Images/Game/UI/greendot-08.png");
  mSlidingCharacterLayer->setPagesIndicatorPosition(ccp(mScreenSize.width/2, INDICATOR_POS_Y));
  this->addChild(mSlidingCharacterLayer, GR_FOREGROUND);
}

void ChooseCharacterScene::characterTouched(CCObject *pSender)
{
  CCMenuItemSprite* characterSelected = (CCMenuItemSprite*)pSender;
  mCharacterTouchedID = characterSelected->getTag();
  CCString* characterName;

  bool checkValid = false;

  mPlayer++;

  if (mPlayer == 1)
  {
    mCharacterChoseByPlayer1 = mCharacterTouchedID;
    characterName = CCString::createWithFormat("Images/Game/Object/c%i-blue.png", mCharacterTouchedID);
    checkValid = true;
    GameManager::setPlayerOneID(mCharacterTouchedID);
    CCLOG("Player 1 had chose character %i", GameManager::getPlayerOneID());
  }
  else if (mPlayer == 2 && mCharacterTouchedID != mCharacterChoseByPlayer1)
  {
    characterName = CCString::createWithFormat("Images/Game/Object/c%i-red.png", mCharacterTouchedID);
    checkValid = true;
    GameManager::setPlayerTwoID(mCharacterTouchedID);
    CCLOG("Player 2 had chose character %i", mCharacterTouchedID);
  }
  else if (mCharacterTouchedID == mCharacterChoseByPlayer1)
  {
    checkValid = false;
    mPlayer--;
    CCLOG("This character has been chose by Player 1");
  }
  else
  {
    CCLOG("Out of number of player!");
  }

  if (checkValid)
  {
    CCSprite* character = CCSprite::create(characterName->getCString());
    switch (mCharacterTouchedID) {
      case 1:
        character->setPosition(C1_POS);
        break;
      case 2:
        character->setPosition(C2_POS);
        break;
      case 3:
        character->setPosition(C3_POS);
        break;
      case 4:
        character->setPosition(C4_POS);
        break;
      case 5:
        character->setPosition(C5_POS);
        break;
      case 6:
        character->setPosition(C6_POS);
        break;
      case 7:
        character->setPosition(C7_POS);
        break;
      case 8:
        character->setPosition(C8_POS);
        break;
      default:
        CCLOG("No character set positon");
        break;
    }

    int layerIndex = mCharacterTouchedID/NUMBER_CHARACTERS_PER_SCENE;
    if (mCharacterTouchedID % NUMBER_CHARACTERS_PER_SCENE == 0)
    {
      layerIndex--;
    }
    CCLog("layerId = %d", layerIndex);
    ((CCLayer*)mCharacterArr->objectAtIndex(layerIndex))->addChild(character, GR_MIDDLEGROUND);
  }

  if (mPlayer == 2)
  {
    mCharacterArr->release();
    CCScene* newScene = CCTransitionCrossFade::create(0.5, ChooseMapScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
  }
}

void ChooseCharacterScene::addBackButton()
{
  CCSprite* back = CCSprite::create("Images/Game/UI/button-back.png");
  CCMenuItemSprite *backBtn = CCMenuItemSprite::create(back,
                                                       back,
                                                       this,
                                                       menu_selector(ChooseCharacterScene::buttonBackTouched));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(BTN_BACK);
  this->addChild(pMenu, GR_MIDDLEGROUND, CHOOSECHARACTER_BACKBTN_TAG);
}

void ChooseCharacterScene::buttonBackTouched(CCObject *pSender)
{
  CCLOG("Button back touched");
  CCScene* newScene = CCTransitionCrossFade::create(0.5, StartScene::scene());
  CCDirector::sharedDirector()->replaceScene(newScene);
}

CCArray* ChooseCharacterScene::getCharacterArr()
{
  return mCharacterArr;
}

CCScrollLayer* ChooseCharacterScene::getSlidingCharacterLayer()
{
  return mSlidingCharacterLayer;
}
