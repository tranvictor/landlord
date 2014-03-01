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
  
  screenSize = CCDirector::sharedDirector()->getWinSize();
  addBackground();
  addCharacter();
  addBackButton();
  
  characterArr->retain();
  
  return true;
}

void ChooseCharacterScene::addBackground()
{
  CCSprite* background = CCSprite::create("ChooseCharacterScene/Background.png");
  CCLOG("%f %f", screenSize.width, screenSize.height);
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  this->addChild(background, GR_BACKGROUND);
}

void ChooseCharacterScene::addCharacter()
{
  characterArr = CCArray::createWithCapacity(NUMBER_CHARACTERS/NUMBER_CHARACTERS_PER_SCENE);
  for (int i = 1; i <= NUMBER_CHARACTERS/NUMBER_CHARACTERS_PER_SCENE; ++i)
  {
    CCLayer* characterLayer = CCLayer::create();
    for (int j = 1; j <= NUMBER_CHARACTERS_PER_SCENE; ++j)
    {
      int characterID = j + NUMBER_CHARACTERS_PER_SCENE*(i - 1);
      CCString* characterName = (CCString::createWithFormat("ChooseCharacterScene/c%i.png", characterID));
      CCSprite* character = CCSprite::create(characterName->getCString());
      
      CCMenuItemSprite* characterItem = CCMenuItemSprite::create(character,
                                                                 character,
                                                                 this,
                                                                 menu_selector(ChooseCharacterScene::CharacterTouched));
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
      characterLayer->addChild(menu, GR_FOREGROUND);
    }
    characterArr->addObject(characterLayer);
  }
  characterArr->retain();
  
  slidingCharacterLayer = CCScrollLayer::nodeWithLayers(characterArr, 0, "ChooseMapScene/greendot-08.png");
  slidingCharacterLayer->setPagesIndicatorPosition(ccp(screenSize.width/2, INDICATOR_POS_Y));
  this->addChild(slidingCharacterLayer, GR_FOREGROUND);
}

void ChooseCharacterScene::CharacterTouched(CCObject *pSender)
{
  CCMenuItemSprite* characterSelected = (CCMenuItemSprite*)pSender;
  characterTouchedID = characterSelected->getTag();
  CCString* characterName;
  
  bool checkValid = false;
  
  player++;
  
  if (player == 1)
  {
    characterChoseByPlayer1 = characterTouchedID;
    characterName = CCString::createWithFormat("ChooseCharacterScene/c%i-blue-02.png", characterTouchedID);
    checkValid = true;
    CCLOG("Player 1 had chose character %i", characterTouchedID);
  }
  else if (player == 2 && characterTouchedID != characterChoseByPlayer1)
  {
    characterName = CCString::createWithFormat("ChooseCharacterScene/c%i-red-02.png", characterTouchedID);
    checkValid = true;
    CCLOG("Player 2 had chose character %i", characterTouchedID);
  }
  else if (characterTouchedID == characterChoseByPlayer1)
  {
    checkValid = false;
    player--;
    CCLOG("This character has been chose by Player 1");
  }
  else
  {
    CCLOG("Out of number of player!");
  }
  
  if (checkValid)
  {
    CCSprite* character = CCSprite::create(characterName->getCString());
    switch (characterTouchedID) {
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

    int layerIndex = characterTouchedID/NUMBER_CHARACTERS_PER_SCENE;
    if (characterTouchedID % NUMBER_CHARACTERS_PER_SCENE == 0) {
      layerIndex--;
    }
    ((CCLayer* )characterArr->objectAtIndex(layerIndex))->addChild(character, GR_MIDDLEGROUND);    
  }
  
  if (player == 2)
  {
    CCScene* newScene = CCTransitionCrossFade::create(0.5, ChooseMapScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
  }
}

void ChooseCharacterScene::addBackButton()
{
  CCSprite *back = CCSprite::create("ChooseMapScene/button-back.png");
  CCMenuItemSprite *backBtn = CCMenuItemSprite::create(back,
                                                       back,
                                                       this,
                                                       menu_selector(ChooseCharacterScene::buttonBackTouched));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(BTN_BACK);
  this->addChild(pMenu, GR_MIDDLEGROUND);
}

void ChooseCharacterScene::buttonBackTouched()
{
  CCLOG("Button back touched");
  CCScene* newScene = CCTransitionCrossFade::create(0.5, StartScene::scene());
  
  
  CCDirector::sharedDirector()->replaceScene(newScene);
}
