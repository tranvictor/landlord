//
//  WinScene.cpp
//  landlord
//
//  Created by Giap Nguyen on 2/26/14.
//
//

#include "WinScene.h"

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
  CCSprite *background = CCSprite::create("WinScene/background-win.png");
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  this->addChild(background, GR_BACKGROUND);
}

void WinScene::addMask()
{
  CCSprite *mask = CCSprite::create("WinScene/mask.png");
  mask->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  this->addChild(mask, GR_FOREGROUND);
}


void WinScene::addButtonShare()
{
  CCSprite *share = CCSprite::create("WinScene/button-share.png");
  CCMenuItemSprite *shareBtn = CCMenuItemSprite::create(share,
                                                         share,
                                                         this,
                                                         menu_selector(WinScene::buttonShareTouched));
  CCMenu* pMenu = CCMenu::create(shareBtn, NULL);
  pMenu->setPosition(BTN_SHARE_POS);
  this->addChild(pMenu);
}

void WinScene::addButtonReplay()
{
  CCSprite *replay = CCSprite::create("WinScene/button-replay.png");
  CCMenuItemSprite *replayBtn = CCMenuItemSprite::create(replay,
                                                       replay,
                                                       this,
                                                       menu_selector(WinScene::buttonReplayTouched));
  CCMenu* pMenu = CCMenu::create(replayBtn, NULL);
  pMenu->setPosition(BTN_REPLAY_POS);
  this->addChild(pMenu);
}

void WinScene::buttonShareTouched(cocos2d::CCObject *pSender)
{
  CCLog("button share touched");
}

void WinScene::buttonReplayTouched(cocos2d::CCObject *pSender)
{
  CCLog("button replay touched");
}

void WinScene::appearWinner()
{
  CCSprite *winner = CCSprite::create("WinScene/c1.png");
  winner->setPosition(WINNER_POS);
  addChild(winner, GR_MIDDLEGROUND);
}

