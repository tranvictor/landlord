//
//  SettingScene.h
//  landlord
//
//  Created by HaLink on 2/20/14.
//
//

#ifndef landlord_SettingScene_h
#define landlord_SettingScene_h

//CONSTANT

#define BTN_SOUND ccp(120, 286)
#define BTN_MUSIC ccp(120, 371.02)
#define BTN_TREE ccp(120, 168)
#define BTN_BACK cco(565, 68)

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
  
  void soundFxTouched(cocos2d::CCObject *pSender);
  void musicTouched(cocos2d::CCObject *pSender);
  void treeModeTouched(cocos2d::CCObject *pSender);
  
  CREATE_FUNC(SettingScene);
};


#endif
