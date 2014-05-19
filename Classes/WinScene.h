//
//  WinScene.h
//  landlord
//
//  Created by Giap Nguyen on 2/26/14.
//
//

#ifndef __WINSCENE_H__
#define __WINSCENE_H__

#include "cocos2d.h"
#include "Constant.h"

class WinScene : public cocos2d::CCLayer
{
private:
  
public:
  cocos2d::CCSize screenSize;
  virtual bool init();
  static cocos2d::CCScene * scene();
  CREATE_FUNC(WinScene);
  
  void addBackground();
  void addMenu();
  void addButtonShare();
  void buttonShareTouched(cocos2d::CCObject* pSender);
  void addButtonReplay();
  void buttonReplayTouched(cocos2d::CCObject* pSender);
  
  void appearWinner();
  void changeScene(cocos2d::CCObject* pData);
};



#endif /* defined(__landlord__WinScene__) */
