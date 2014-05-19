//
//  SettingScene.h
//  landlord
//
//  Created by HaLink on 2/20/14.
//
//

#ifndef landlord_SettingScene_h
#define landlord_SettingScene_h

#include "cocos2d.h"

class SettingScene : public cocos2d::CCLayer
{
private:
  cocos2d::CCSize screenSize;
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  void addBackground();
  void addSoundFxButton();
  void addMusicButton();
  void addTreeModeButton();
  void addBackButton();
  void addFogModeButton();
  
  void soundFxTouched(cocos2d::CCObject *pSender);
  void musicTouched(cocos2d::CCObject *pSender);
  void treeModeTouched(cocos2d::CCObject *pSender);
  void backButtonTouched(cocos2d::CCObject *pSender);
  void fogModeTouched(cocos2d::CCObject *pSender);
  void changeScene(cocos2d::CCObject* pData);
  CREATE_FUNC(SettingScene);
};


#endif
