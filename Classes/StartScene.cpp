//
//  StartScene.cpp
//  landlord
//
//  Created by HaLink on 2/19/14.
//
//

#include "StartScene.h"
#include "CloudAnimation.h"

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
  CCSprite *background = CCSprite::create("Mainscene/MainsceneBackground.png");
  
  CCLOG("%f %f", screenSize.width, screenSize.height);
  
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  
  this->addChild(background, 0);
  
  //CCSprite *background = CCSprite::create("CloudAnimation/Mainscene-Background-blanksky.png");
  
//  CCSprite* cloud = CloudAnimation::create(cloudSpeed);
//  cloud->setPosition(ccp(-150, 800));
//  
//  this->addChild(cloud, 1);
//  
//  cloudSpeed = 2;
//  
//  CCSprite* cloud1 = CloudAnimation::create(cloudSpeed);
//  cloud1->setPosition(ccp(-150, 600));
//  
//  this->addChild(cloud1, 2);
  
}

void StartScene::addPlayButton()
{
  CCSprite *play = CCSprite::create("Mainscene/buttonPlay.png");
  
  CCMenuItemSprite *playBtn = CCMenuItemSprite::create(play, play, this,
                                                         menu_selector(StartScene::playButtonTouched));
//  playBtn->setPosition(BTN_PLAY);
  
  CCMenu *playMenu = CCMenu::create(playBtn, NULL);
  
  playMenu->setPosition(BTN_PLAY);
  
  this->addChild(playMenu,1);
}

void StartScene::addSettingsButton()
{
  CCSprite *settings = CCSprite::create("Mainscene/buttonSetting.png");
  
  CCMenuItemSprite *settingBtn = CCMenuItemSprite::create(settings,settings,
                                                          this,
                                                          menu_selector(StartScene::settingsButtonTouched));
//  settingBtn->setPosition(BTN_SETTINGS);
  
  CCMenu *settingMenu = CCMenu::create(settingBtn, NULL);
  
  settingMenu->setPosition(BTN_SETTINGS);
  
  this->addChild(settingMenu, 2);
}
  


void StartScene::playButtonTouched(CCObject *pSender)
{
  CCLOG("Play button touched");
}

void StartScene::settingsButtonTouched(CCObject *pSender)
{
  CCLOG("Settings button touched");
}