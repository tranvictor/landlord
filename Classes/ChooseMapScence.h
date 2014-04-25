//
//  ChooseMapScene.h
//  landlord
//
//  Created by Giap Nguyen on 4/25/14.
//
//

#ifndef __CHOOSEMAPSCENE_H__
#define __CHOOSEMAPSCENE_H__

#include "cocos2d.h"
#include "CCScrollLayer.h"
#include "CCScrollLayerHorizontal.h"
#include "Constant.h"
#include "Sound.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "ChooseCharacterScene.h"
#include "StartScene.h"
#include "CCScrollView.h"

class ChooseMapScene : public cocos2d::CCLayer
{
private:
  cocos2d::CCSize   mScreenSize;
  int               mMapTouchedID;
  CCScrollLayer*    mSlidingMap;
  int mState;
  
  cocos2d::CCLayer* mChooseCharacterLayer;
  cocos2d::CCLayer* mChooseMapLayer;
  CCScrollLayerHorizontal* mSlideCharacter1;
  CCScrollLayerHorizontal* mSlideCharacter2;
  CCSprite*         mVs;
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  CREATE_FUNC(ChooseMapScene);
  
  CC_SYNTHESIZE(cocos2d::CCArray*, mArr, Arr);
  CC_SYNTHESIZE(cocos2d::CCArray*, mCharacterArr, CharacterArr);
  CC_SYNTHESIZE(cocos2d::CCArray*, mMapArr, MapArr);
  
  void addBackground();
  
  void buttonRandomTouched(cocos2d::CCObject *pSender);
  void addButtonBack();
  void buttonBackTouched(cocos2d::CCObject *pSender);
  
  void addButtonForward();
  void buttonForwardTouched(cocos2d::CCObject *pSender);
  
  void addSlidingLayers();
  cocos2d::CCLayer* createChooseCharaterLayer();
  
  cocos2d::CCLayer* createChooseMapLayer();
  void mapTouched(cocos2d::CCObject *pSender);
  
  ~ChooseMapScene();
  CCAction* changePage(cocos2d::CCPoint pPos);
  void randomCharacter(cocos2d::CCObject *pSender);
  void ccTouchBegin(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  
  void registerWithTouchDispatcher();
};


#endif /* defined(__landlord__ChooseMapScene_horizonal__) */
