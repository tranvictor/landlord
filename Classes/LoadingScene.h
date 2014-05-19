//
//  LoadingScene.h
//  landlord
//
//  Created by Giap Nguyen on 4/10/14.
//
//

#ifndef __landlord__LoadingScene__
#define __landlord__LoadingScene__

#include "cocos2d.h"
#include "Constant.h"
#include "Sound.h"
#include "ChooseMapScence.h"

class LoadingScene : public cocos2d::CCLayer
{
private:
  
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  void addItems();
  void addPlayButton();
  void addSettingButton();
  void playButtonTouched(cocos2d::CCObject* pSender);
  void settingButtonTouched(cocos2d::CCObject* pSender);
  void changeScene(cocos2d::CCObject* pData);
  CREATE_FUNC(LoadingScene);
};

#endif /* defined(__landlord__LoadingScene__) */
