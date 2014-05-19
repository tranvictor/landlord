//
//  WinScene.cpp
//  landlord
//
//  Created by Giap Nguyen on 2/26/14.
//
//

#include "WinScene.h"
#include "ChooseMapScence.h"
#include "GameManager.h"
#include "Sound.h"
#include "Constant.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool WinScene::init()
{
  if (!CCLayer::init())
  {
    return false;
  }

  screenSize = CCDirector::sharedDirector()->getWinSize();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
  sound::playBackgroundMusic(MUSIC_WON);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);
  addBackground();
  addMenu();
  addButtonShare();
  addButtonReplay();
  appearWinner();

  return true;
}

CCScene* WinScene::scene()
{
  CCScene *scene = CCScene::create();
  WinScene *layer = WinScene::create();
  scene->addChild(layer);

  return scene;
}

void WinScene::addBackground()
{
  CCSprite *background = CCSprite::create("Images/Game/Background/winBg.png");
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  this->addChild(background, GR_FOREGROUND, WIN_BG_TAG);
}

void WinScene::addMenu()
{
  CCSprite *menu = CCSprite::create("Images/Game/UI/menuButton.png");
  menu->setPosition(BTN_MENU_POS);
  this->addChild(menu, GR_FOREGROUND);
}


void WinScene::addButtonShare()
{
  CCSprite *share = CCSprite::create("Images/Game/UI/fbButton.png");
  CCMenuItemSprite *shareBtn =
    CCMenuItemSprite::create(share,
                             share,
                             this,
                             menu_selector(WinScene::buttonShareTouched));
  CCMenu* pMenu = CCMenu::create(shareBtn, NULL);
  pMenu->setPosition(BTN_SHARE_POS);
  this->addChild(pMenu, GR_FOREGROUND, WIN_SHAREBTN_TAG);
}

void WinScene::addButtonReplay()
{
  CCSprite *replay = CCSprite::create("Images/Game/UI/ReplayButton.png");
  CCMenuItemSprite *replayBtn =
    CCMenuItemSprite::create(replay,
                             replay,
                             this,
                             menu_selector(WinScene::buttonReplayTouched));
  CCMenu* pMenu = CCMenu::create(replayBtn, NULL);
  pMenu->setPosition(BTN_REPLAY_POS);
  this->addChild(pMenu, GR_FOREGROUND, WIN_REPLAYBTN_TAG);
}

void WinScene::buttonShareTouched(cocos2d::CCObject *pSender)
{
  CCLog("button share touched");
  CREATE_MENU_ITEM_NO_CHANGE_SCENE();
}

void WinScene::buttonReplayTouched(cocos2d::CCObject *pSender)
{
  CCLog("button replay touched");
  CREATE_MENU_ITEM(WinScene, ChooseMapScene, CCTransitionCrossFade);
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void WinScene::appearWinner()
{
  int winnerID;
  if (GameManager::getWinPlayer() == PLAYER_ONE)
  {
    winnerID = GameManager::getPlayerOneID();
  }
  else
  {
    winnerID = GameManager::getPlayerTwoID();
  }
  CCString *winnerName = CCString::createWithFormat("Images/Game/Object/c%i.png",
                                                    winnerID);
  CCSprite *winner = CCSprite::create(winnerName->getCString());

  winner->setPosition(WINNER_START_POS);

  CCAction * act1 = CCMoveTo::create(1, WINNER_POS);
  winner->runAction(act1);

  addChild(winner, GR_BACKGROUND);
}

void WinScene::changeScene(cocos2d::CCObject *pData)
{
  CCDirector::sharedDirector()->replaceScene((CCTransitionScene*)pData);
}
