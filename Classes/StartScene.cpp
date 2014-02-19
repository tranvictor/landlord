//
//  StartScene.cpp
//  landlord
//
//  Created by HaLink on 2/19/14.
//
//

#include "StartScene.h"

USING_NS_CC;

CCScene *StartScene::scene()
{
  CCScene *scene = CCScene::create();
  
  CCLayer *layer = StartScene::create();
  
  scene->addChild(layer);
  
  return scene;
}

bool StartScene::init()
{
  if(!CCLayer::init() )
  {
    return false;
  }
  
  screenSize = CCDirector::sharedDirector()->getWinSize();
  
  addBackground();
  addPlayButton();
  addSettingsButton();
  
  return true;
}

void StartScene::addBackground()
{
  CCSprite *background = CCSprite::create("Default.png");
  
  CCLOG("%f %f", screenSize.width, screenSize.height);
  
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  
  this->addChild(background, 0);
}

void StartScene::addPlayButton()
{
  CCSprite *play = CCSprite::create("/Users/SCN/Desktop/Cocos2d-x-2.2.2/projects/landlord/Resources/Mainscene/buttonPlay.png");
  
  CCMenuItemSprite *playBtn = CCMenuItemSprite::create(play, play, this,
                                                         menu_selector(StartScene::playButtonTouched));
  playBtn->setPosition(BTN_PLAY);
  
//  CCMenu *playMenu = CCMenu::create(playBtn);
//  
//  playMenu->setPosition(BTN_PLAY);
  
  this->addChild(playBtn,1);
}

void StartScene::addSettingsButton()
{
  CCSprite *settings = CCSprite::create("/Users/SCN/Desktop/Cocos2d-x-2.2.2/projects/landlord/Resources/Mainscene/buttonSetting.png");
  
  CCMenuItemSprite *settingBtn = CCMenuItemSprite::create(settings,settings,
                                                          this,
                                                          menu_selector(StartScene::settingsButtonTouched));
  settingBtn->setPosition(BTN_SETTINGS);
  
  this->addChild(settingBtn);
}
  


void StartScene::playButtonTouched(CCObject *pSender)
{
  
}

void StartScene::settingsButtonTouched(CCObject *pSender)
{
}