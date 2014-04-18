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

USING_NS_CC;

bool WinScene::init()
{
  if (!CCLayer::init())
  {
    return false;
  }

  screenSize = CCDirector::sharedDirector()->getWinSize();

  addBackground();
  addMask();
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
  CCSprite *background = CCSprite::create("Images/Game/Background/BG-win.png");
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  this->addChild(background, GR_BACKGROUND, WIN_BG_TAG);
}

void WinScene::addMask()
{
  CCSprite *mask = CCSprite::create("Images/Game/Background/BG-mask-winscene.png");
  mask->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  this->addChild(mask, GR_FOREGROUND, WIN_MASK_TAG);
}


void WinScene::addButtonShare()
{
  CCSprite *share = CCSprite::create("Images/Game/UI/button-share.png");
  CCMenuItemSprite *shareBtn = CCMenuItemSprite::create(share,
                                                         share,
                                                         this,
                                                         menu_selector(WinScene::buttonShareTouched));
  CCMenu* pMenu = CCMenu::create(shareBtn, NULL);
  pMenu->setPosition(BTN_SHARE_POS);
  this->addChild(pMenu, WIN_SHAREBTN_TAG);
}

void WinScene::addButtonReplay()
{
  CCSprite *replay = CCSprite::create("Images/Game/UI/button-replay.png");
  CCMenuItemSprite *replayBtn = CCMenuItemSprite::create(replay,
                                                       replay,
                                                       this,
                                                       menu_selector(WinScene::buttonReplayTouched));
  CCMenu* pMenu = CCMenu::create(replayBtn, NULL);
  pMenu->setPosition(BTN_REPLAY_POS);
  this->addChild(pMenu, WIN_REPLAYBTN_TAG);
}

void WinScene::buttonShareTouched(cocos2d::CCObject *pSender)
{
  CCLog("button share touched");
}

void WinScene::buttonReplayTouched(cocos2d::CCObject *pSender)
{
  CCLog("button replay touched");
  CCScene* newScene = CCTransitionCrossFade::create(0.5, ChooseMapScene::scene());
  CCDirector::sharedDirector()->runWithScene(newScene);

}

void WinScene::appearWinner()
{
  // Get from manager
//  int arr[2] = {GameManager::getPlayerOneID(), GameManager::getPlayerTwoID()};
//  srand (time(NULL));
//  int i = arr[rand()%2];
  int winnerID;
  if (GameManager::getWinPlayer() == PLAYER_ONE)
  {
    winnerID = GameManager::getPlayerOneID();
  }
  else
  {
    winnerID = GameManager::getPlayerTwoID();
  }
  CCString *winnerName = CCString::createWithFormat("Images/Game/Object/c%i.png", winnerID);
  CCSprite *winner = CCSprite::create(winnerName->getCString());

  winner->setPosition(WINNER_START_POS);

  CCAction * act1 = CCMoveTo::create(1, WINNER_POS);
  winner->runAction(act1);

  addChild(winner, GR_MIDDLEGROUND);
}
