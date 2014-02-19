//
//  StartScene.h
//  landlord
//
//  Created by HaLink on 2/19/14.
//
//

#ifndef landlord_StartScene_h
#define landlord_StartScene_h

//constant for StartScene
#define BTN_PLAY ccp(320, 860)
#define BTN_SETTINGS ccp(80, 1056)

#include "cocos2d.h"

class StartScene : public cocos2d::CCLayer
{
private:
  cocos2d::CCSize screenSize;
  
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  void addBackground();
  void addPlayButton();
  void addSettingsButton();
  
  void playButtonTouched(cocos2d::CCObject *pSender);
  void settingsButtonTouched(cocos2d::CCObject *pSender);
  
  CREATE_FUNC(StartScene);
};

#endif
