//
//  ChooseCharacterScene.cpp
//  landlord
//
//  Created by Tuan TQ on 2/26/14.
//
//

#include "ChooseCharacterScene.h"
#include "Constant.h"

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
  
  return true;
}

void ChooseCharacterScene::addBackground()
{
  CCSprite* background = CCSprite::create("ChooseCharacterScene/Background.png");
  CCLOG("%f %f", screenSize.width, screenSize.height);
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  this->addChild(background, 0);
}

void ChooseCharacterScene::addCharacter()
{
  for (int i = 1; i <= NUMBER_CHARACTERS/2; ++i)
  {
    CCString* characterName = (CCString::createWithFormat("ChooseCharacterScene/c%i.png", i));
    CCSprite* character = CCSprite::create(characterName->getCString());
    
    CCMenuItemSprite* characterItem = CCMenuItemSprite::create(character,
                                                              character,
                                                              this,
                                                              menu_selector(ChooseCharacterScene::CharacterTouched));
    characterItem->setTag(i);
    
    CCMenu* pMenu = CCMenu::create(characterItem, NULL);
    switch (i) {
      case 1:
        pMenu->setPosition(C1_POS);
        break;
      case 2:
        pMenu->setPosition(C2_POS);
        break;
      case 3:
        pMenu->setPosition(C3_POS);
        break;
      case 4:
        pMenu->setPosition(C4_POS);
        break;
      default:
        CCLOG("No character set positon");
        break;
    }
    
    this->addChild(pMenu, 2);
  }
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
    characterName = CCString::createWithFormat("ChooseCharacterScene/c%i-1.png", characterTouchedID);
    checkValid = true;
    CCLOG("Player 1 had chose character %i", characterTouchedID);
  }
  else if (player == 2 && characterTouchedID != characterChoseByPlayer1)
  {
    characterName = CCString::createWithFormat("ChooseCharacterScene/c%i-2.png", characterTouchedID);
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
      default:
        CCLOG("No character set positon");
        break;
    }
    this->addChild(character, 1);
  }
}
