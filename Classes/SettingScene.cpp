//
//  SettingScene.cpp
//  landlord
//
//  Created by HaLink on 2/20/14.
//
//

#include "SettingScene.h"
#include "StartScene.h"
#include "Sound.h"
#include "GameManager.h"

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
  CCSprite* background = CCSprite::create("Images/Game/Background/BG-setting.png");
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  
  this->addChild(background, 0);
}

void SettingScene::addSoundFxButton()
{
  CCMenuItem* uncheckedBtn = CCMenuItemImage::create("Images/Game/UI/buttonUncheck.png",
                                                     "Images/Game/UI/buttonChecked.png",
                                                     NULL,
                                                     NULL);
  CCMenuItem* checkedBtn = CCMenuItemImage::create("Images/Game/UI/buttonChecked.png",
                                                   "Images/Game/UI/buttonUncheck.png",
                                                   NULL,
                                                   NULL);
  
  CCMenuItem* state1 = CCMenuItem::create();
  CCMenuItem* state2 = CCMenuItem::create();
  
  if(GameManager::getSoundState()){
    state1 = checkedBtn;
    state2 = uncheckedBtn;
  } else
  {
    state1 = uncheckedBtn;
    state2 = checkedBtn;
  }
  
  
  CCMenuItemToggle* soundFxToggle = CCMenuItemToggle::createWithTarget(this,
                                                                       menu_selector(SettingScene::soundFxTouched),
                                                                       state1,
                                                                       state2,
                                                                       NULL);
  CCMenu* soundFx = CCMenu::create();
  soundFx->addChild(soundFxToggle);
  soundFx->setPosition(BTN_SOUND);
  
  this->addChild(soundFx, 1);
}

void SettingScene::addMusicButton()
{
  CCMenuItem* uncheckedBtn = CCMenuItemImage::create("Images/Game/UI/buttonUncheck.png",
                                                     "Images/Game/UI/buttonChecked.png",
                                                     NULL,
                                                     NULL);
  CCMenuItem* checkedBtn = CCMenuItemImage::create("Images/Game/UI/buttonChecked.png",
                                                   "Images/Game/UI/buttonUncheck.png",
                                                   NULL,
                                                   NULL);
  
  CCMenuItem* state1 = CCMenuItem::create();
  CCMenuItem* state2 = CCMenuItem::create();
  
  if(GameManager::getMusicState()){
    state1 = checkedBtn;
    state2 = uncheckedBtn;
  } else
  {
    state1 = uncheckedBtn;
    state2 = checkedBtn;
  }
  
  CCMenuItemToggle* musicToggle = CCMenuItemToggle::createWithTarget(this,
                                                                     menu_selector(SettingScene::musicTouched),
                                                                     state1,
                                                                     state2,
                                                                     NULL);
  CCMenu* music = CCMenu::create();
  music->addChild(musicToggle);
  music->setPosition(BTN_MUSIC);
  
  this->addChild(music, 2);
}

void SettingScene::addTreeModeButton()
{
  CCMenuItem* uncheckedBtn = CCMenuItemImage::create("Images/Game/UI/buttonUncheck.png",
                                                     "Images/Game/UI/buttonChecked.png",
                                                     NULL,
                                                     NULL);
  CCMenuItem* checkedBtn = CCMenuItemImage::create("Images/Game/UI/buttonChecked.png",
                                                   "Images/Game/UI/buttonUncheck.png",
                                                   NULL,
                                                   NULL);
  
  CCMenuItem* state1 = CCMenuItem::create();
  CCMenuItem* state2 = CCMenuItem::create();
  
  if(GameManager::getTreeModeState()){
    state1 = checkedBtn;
    state2 = uncheckedBtn;
  } else
  {
    state1 = uncheckedBtn;
    state2 = checkedBtn;
  }
  
  CCMenuItemToggle* treeToggle = CCMenuItemToggle::createWithTarget(this,
                                                                    menu_selector(SettingScene::treeModeTouched),
                                                                    state1,
                                                                    state2,
                                                                    NULL);
  CCMenu* tree = CCMenu::create();
  tree->addChild(treeToggle);
  tree->setPosition(BTN_TREE);
  
  this->addChild(tree, 2);
}

void SettingScene::addBackButton()
{
  CCSprite *backBtn = CCSprite::create("Images/Game/UI/buttonBack.png");
  
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
  sound::playSoundFx();
  sound::toggleSoundFx();
  GameManager::setSoundState();
}

void SettingScene::musicTouched(CCObject *pSender)
{
  CCLog("music Touched");
  sound::playSoundFx();
  sound::toggleMusic();
  GameManager::setMusicState();
}

void SettingScene::treeModeTouched(CCObject *pSender)
{
  CCLog("Tree Touched");
  sound::playSoundFx();
  GameManager::setTreeModeState();
}

void SettingScene::backButtonTouched(CCObject *pSender)
{
  CCLog("Back Button Touched");
  sound::playSoundFx();
  
  //Set Scene Transition
  CCScene* newScene = CCTransitionSlideInR::create(0.5, StartScene::scene());
  
  CCDirector::sharedDirector()->replaceScene(newScene);
  //CCDirector::sharedDirector()->popScene();
}