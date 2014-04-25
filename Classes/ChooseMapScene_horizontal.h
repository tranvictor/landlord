//
//  ChooseMapScene_horizontal.h
//  landlord
//
//  Created by Giap Nguyen on 4/25/14.
//
//

#ifndef __CHOOSEMAPSCENE_HORIZONTAL_H__
#define __CHOOSEMAPSCENE_HORIZONTAL_H__

#include "cocos2d.h"
#include "CCScrollLayer.h"
#include "Constant.h"
#include "Sound.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "ChooseCharacterScene.h"

class ChooseMapScene_horizontal : public cocos2d::CCLayer
{
private:
  cocos2d::CCSize   mScreenSize;
  int               mMapTouchedID;
  CCScrollLayer*    mSlidingMap;
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  CREATE_FUNC(ChooseMapScene_horizontal);
  
  CC_SYNTHESIZE(cocos2d::CCArray*, mMapArr, MapArr);
  
  void addBackground();
  void addButtonRandom();
  void buttonRandomTouched(cocos2d::CCObject *pSender);
  void addButtonBack();
  void buttonBackTouched(cocos2d::CCObject *pSender);
  
  void makeSlidingMap();
  void mapTouched(cocos2d::CCObject *pSender);
};


#endif /* defined(__landlord__ChooseMapScene_horizontal_horizontal_horizontal_horizontal_horizonal__) */
