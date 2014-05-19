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
#include "CCScrollLayerVertical.h"
#include "Constant.h"
#include "Sound.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "ChooseCharacterScene.h"
#include "StartScene.h"
#include "CCScrollView.h"
#include "LoadingScene.h"
#include "cocos-ext.h"

class ChooseMapScene : public cocos2d::CCLayer
{
private:
  cocos2d::CCSize   mScreenSize;
  int               mMapTouchedID;
  CCScrollLayer*    mSlidingMap;
  int mState;
  CCSprite*         mBackground;
  
  cocos2d::CCLayer* mChooseCharacterLayer;
  cocos2d::CCLayer* mChooseMapLayer;
  CCScrollLayerVertical* mSlideCharacter1;
  CCScrollLayerVertical* mSlideCharacter2;
//  cocos2d::extension::CCTableView* mSlideCharacter1;
//  cocos2d::extension::CCTableView* mSlideCharacter2;
  CCSprite*         mVs;
  CCScrollLayerVertical* mSlideMap;
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  CREATE_FUNC(ChooseMapScene);
  
  CC_SYNTHESIZE(cocos2d::CCArray*, mArr, Arr);
  CC_SYNTHESIZE(cocos2d::CCArray*, mCharacterArr, CharacterArr);
  CC_SYNTHESIZE(cocos2d::CCArray*, mMapArr, MapArr);
  CC_SYNTHESIZE(float, mCooldownTime, CooldownTime);
  
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
  
  cocos2d::CCArray* createCharactersArray(cocos2d::CCPoint pPos);
  
  ~ChooseMapScene();
  CCAction* changePage(cocos2d::CCPoint pPos);
  void cooldown();
  void switchCharacterSilde(cocos2d::CCObject *pSender);
  
  void changeScene(cocos2d::CCObject* pData);
  void addCharacterAura(int pCurrentCharater, cocos2d::CCPoint pPos);
  void removeCharacterAura(cocos2d::CCObject* pSender);
};


#endif /* defined(__landlord__ChooseMapScene_horizonal__) */
