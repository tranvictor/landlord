//
//  SettingScene.cpp
//  landlord
//
//  Created by HaLink on 2/20/14.
//
//

#include "SettingScene.h"
#include "LoadingScene.h"
#include "Sound.h"
#include "GameManager.h"
#include "Constant.h"
#include "LoadingScene.h"

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
  addMusicButton();
  addSoundFxButton();
  addFogModeButton();
  addTreeModeButton();
  addBackButton();
  
  return true;
}


void SettingScene::addBackground()
{
  CCSprite* background = CCSprite::create(
                                 "Images/Game/Background/optionBg.png");
  background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  
  this->addChild(background, GR_BACKGROUND);
}

void SettingScene::addSoundFxButton()
{
  CCMenuItem* uncheckedBtn =
    CCMenuItemImage::create(
                            "Images/Game/UI/sfxButton1.png",
                            "Images/Game/UI/sfxButton2.png",
                            NULL,
                            NULL);
  CCMenuItem* checkedBtn =
    CCMenuItemImage::create(
      "Images/Game/UI/sfxButton2.png",
      "Images/Game/UI/sfxButton1.png",
      NULL,
      NULL);
  
  CCMenuItem* state1;// = CCMenuItem::create();
  CCMenuItem* state2;// = CCMenuItem::create();
  
  if(GameManager::getSoundState())
  {
    state1 = checkedBtn;
    state2 = uncheckedBtn;
  } else
  {
    state1 = uncheckedBtn;
    state2 = checkedBtn;
  }
  
  
  CCMenuItemToggle* soundFxToggle =
    CCMenuItemToggle::createWithTarget(this,
                                       menu_selector(SettingScene::soundFxTouched),
                                       state1,
                                       state2,
                                       NULL);
  CCMenu* soundFx = CCMenu::create();
  soundFx->addChild(soundFxToggle);
  soundFx->setPosition(BTN_SOUND);
  
  this->addChild(soundFx, GR_FOREGROUND);
}

void SettingScene::addMusicButton()
{
  CCMenuItem* uncheckedBtn =
    CCMenuItemImage::create(
                            "Images/Game/UI/soundButton2.png",
                            "Images/Game/UI/soundButton1.png",
                            NULL,
                            NULL);
  CCMenuItem* checkedBtn =
    CCMenuItemImage::create(
                            "Images/Game/UI/soundButton1.png",
                            "Images/Game/UI/soundButton2.png",
                            NULL,
                            NULL);
  
  CCMenuItem* state1;// = CCMenuItem::create();
  CCMenuItem* state2;// = CCMenuItem::create();
  
  if(GameManager::getMusicState())
  {
    state1 = checkedBtn;
    state2 = uncheckedBtn;
  } else
  {
    state1 = uncheckedBtn;
    state2 = checkedBtn;
  }
  
  CCMenuItemToggle* musicToggle =
    CCMenuItemToggle::createWithTarget(this,
                                      menu_selector(SettingScene::musicTouched),
                                                    state1,
                                                    state2,
                                                    NULL);
  CCMenu* music = CCMenu::create();
  music->addChild(musicToggle);
  music->setPosition(BTN_MUSIC);
  
  this->addChild(music, GR_MIDDLEGROUND);
}

void SettingScene::addTreeModeButton()
{
  CCMenuItem* uncheckedBtn =
    CCMenuItemImage::create(
                           "Images/Game/UI/treModeButton2.png",
                           "Images/Game/UI/treModeButton1.png",
                           NULL,
                           NULL);
  CCMenuItem* checkedBtn =
    CCMenuItemImage::create(
                           "Images/Game/UI/treModeButton1.png",
                           "Images/Game/UI/treModeButton2.png",
                           NULL,
                           NULL);
  
  CCMenuItem* state1;// = CCMenuItem::create();
  CCMenuItem* state2;// = CCMenuItem::create();
  
  if(GameManager::getTreeModeState())
  {
    state1 = checkedBtn;
    state2 = uncheckedBtn;
  } else
  {
    state1 = uncheckedBtn;
    state2 = checkedBtn;
  }
  
  CCMenuItemToggle* treeToggle =
    CCMenuItemToggle::createWithTarget(this,
                                       menu_selector(SettingScene::treeModeTouched),
                                       state1,
                                       state2,
                                       NULL);
  CCMenu* tree = CCMenu::create();
  tree->addChild(treeToggle);
  tree->setPosition(BTN_TREE);
  this->addChild(tree, GR_FOREGROUND);
}

void SettingScene::addFogModeButton()
{
  CCMenuItem* uncheckedBtn =
    CCMenuItemImage::create(
                            "Images/Game/UI/fogButton2.png",
                            "Images/Game/UI/fogButton1.png",
                            NULL,
                            NULL);
  CCMenuItem* checkedBtn =
    CCMenuItemImage::create(
                            "Images/Game/UI/fogButton1.png",
                            "Images/Game/UI/fogButton2.png",
                            NULL,
                            NULL);
  
  CCMenuItem* state1;// = CCMenuItem::create();
  CCMenuItem* state2;// = CCMenuItem::create();
  
  if(GameManager::getTreeModeState())
  {
    state1 = checkedBtn;
    state2 = uncheckedBtn;
  } else
  {
    state1 = uncheckedBtn;
    state2 = checkedBtn;
  }
  
  CCMenuItemToggle* fogToggle =
    CCMenuItemToggle::createWithTarget(this,
                                       menu_selector(SettingScene::fogModeTouched),
                                       state1,
                                       state2,
                                       NULL);
  CCMenu* fog = CCMenu::create();
  fog->addChild(fogToggle);
  fog->setPosition(BTN_FOG_POS);
  this->addChild(fog, GR_MIDDLEGROUND);
}

void SettingScene::addBackButton()
{
  CCSprite *backBtn = CCSprite::create("Images/Game/UI/backButton.png");
  
  CCMenuItem *back =
    CCMenuItemSprite::create(backBtn,
                             backBtn,
                             this,
                             menu_selector(
                             SettingScene::backButtonTouched));
  CCMenu *backButton = CCMenu::create();
  backButton->addChild(back);
  
  backButton->setPosition(SETTING_BTN_BACK);
  
  this->addChild(backButton, 3);
}

void SettingScene::soundFxTouched(CCObject *pSender)
{
  CCLog("soundFx Touched");
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  sound::toggleSoundFx();
  GameManager::setSoundState();
}

void SettingScene::musicTouched(CCObject *pSender)
{
  CCLog("music Touched");
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  sound::toggleMusic();
  sound::playBackgroundMusic(MUSIC_BACKGROUND);
  GameManager::setMusicState();
}

void SettingScene::treeModeTouched(CCObject *pSender)
{
  CCLog("Tree Touched");
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  GameManager::setTreeModeState();
}

void SettingScene::fogModeTouched(CCObject *pSender)
{
  CCLog("Fog Touched");
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  GameManager::setFogModeState();
}

void SettingScene::backButtonTouched(CCObject *pSender)
{
  CCLog("Back Button Touched");
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  
  //Set Scene Transition
  CCScene* newScene = CCTransitionSlideInR::create(0.5, LoadingScene::scene());
  CCDirector::sharedDirector()->replaceScene(newScene);
  //CCDirector::sharedDirector()->popScene();
}