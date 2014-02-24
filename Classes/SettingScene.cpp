//
//  SettingScene.cpp
//  landlord
//
//  Created by HaLink on 2/20/14.
//
//

#include "SettingScene.h"
#include "StartScene.h"

USING_NS_CC;

CCScene *SettingScene::scene()
{
  CCScene *scene = CCScene::create();
  
  CCLayer *layer = SettingScene::create();
  
  scene->addChild(layer);
  
  return scene;
}

bool SettingScene::init()
{
  if(!CCLayer::init()){
    return false;
  }
  
  screenSize = CCDirector::sharedDirector()->getWinSize();
  
  addBackground();
  addSoundFxButton();
	addMusicButton();
  addTreeModeButton();
  addBackButton();
  
  return true;
}


void SettingScene::addBackground()
{
  CCSprite* background = CCSprite::create("SettingScene/backgroudSetting.png");
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  
  this->addChild(background, 0);
}

void SettingScene::addSoundFxButton()
{
  CCMenuItem* uncheckedBtn = CCMenuItemImage::create("SettingScene/buttonUncheck.png",
                                         "SettingScene/buttonChecked.png",
                                         NULL,
                                         NULL);
  CCMenuItem* checkedBtn = CCMenuItemImage::create("SettingScene/buttonChecked.png",
                                       "SettingScene/buttonUncheck.png",
                                       NULL,
                                       NULL);

  CCMenuItemToggle* soundFxToggle = CCMenuItemToggle::createWithTarget(this,
                                                             menu_selector(SettingScene::soundFxTouched),
                                                             checkedBtn,
                                                             uncheckedBtn,
                                                             NULL);
  CCMenu* soundFx = CCMenu::create();
  soundFx->addChild(soundFxToggle);
  soundFx->setPosition(BTN_SOUND);
  
  this->addChild(soundFx, 1);
}

void SettingScene::addMusicButton()
{
  CCMenuItem* uncheckedBtn = CCMenuItemImage::create("SettingScene/buttonUncheck.png",
                                                     "SettingScene/buttonChecked.png",
                                                     NULL,
                                                     NULL);
  CCMenuItem* checkedBtn = CCMenuItemImage::create("SettingScene/buttonChecked.png",
                                                   "SettingScene/buttonUncheck.png",
                                                   NULL,
                                                   NULL);

  CCMenuItemToggle* musicToggle = CCMenuItemToggle::createWithTarget(this,
                                                                     menu_selector(SettingScene::musicTouched),checkedBtn,
                                                                     uncheckedBtn,
                                                                     NULL);
  CCMenu* music = CCMenu::create();
  music->addChild(musicToggle);
  music->setPosition(BTN_MUSIC);
  
  this->addChild(music, 2);
}

void SettingScene::addTreeModeButton()
{
  CCMenuItem* uncheckedBtn = CCMenuItemImage::create("SettingScene/buttonUncheck.png",
                                                     "SettingScene/buttonChecked.png",
                                                     NULL,
                                                     NULL);
  CCMenuItem* checkedBtn = CCMenuItemImage::create("SettingScene/buttonChecked.png",
                                                   "SettingScene/buttonUncheck.png",
                                                   NULL,
                                                   NULL);
  
  CCMenuItemToggle* treeToggle = CCMenuItemToggle::createWithTarget(this,
                                                                     menu_selector(SettingScene::treeModeTouched),checkedBtn,
                                                                     uncheckedBtn,
                                                                     NULL);
  CCMenu* tree = CCMenu::create();
  tree->addChild(treeToggle);
  tree->setPosition(BTN_TREE);
  
  this->addChild(tree, 2);
}

void SettingScene::addBackButton()
{
  CCSprite *backBtn = CCSprite::create("SettingScene/buttonBack.png");
  
  CCMenuItem *back = CCMenuItemSprite::create(backBtn,
                                             backBtn,
                                             this,
                                             menu_selector(SettingScene::backButtonTouched));
  CCMenu *backButton = CCMenu::create();
  backButton->addChild(back);
  
  backButton->setPosition(BTN_BACK);
  
  this->addChild(backButton, 3);
}

void SettingScene::soundFxTouched(CCObject *pSender)
{
  CCLog("soundFx Touched");
}

void SettingScene::musicTouched(CCObject *pSender)
{
  CCLog("music Touched");
}

void SettingScene::treeModeTouched(CCObject *pSender)
{
  CCLog("Tree Touched");
}

void SettingScene::backButtonTouched(CCObject *pSender)
{
  CCLog("Back Button Touched");
  CCDirector::sharedDirector()->replaceScene(StartScene::scene());
}