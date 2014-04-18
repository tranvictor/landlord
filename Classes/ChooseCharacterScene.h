//
//  ChooseCharacterScene.h
//  landlord
//
//  Created by Tuan TQ on 2/26/14.
//
//

#ifndef __landlord__ChooseCharacterScene__
#define __landlord__ChooseCharacterScene__

#include "cocos2d.h"
#include "CCScrollLayer.h"

USING_NS_CC;

class ChooseCharacterScene : public cocos2d::CCLayer
{
private:
  CCSize          mScreenSize;
  CCArray*        mCharacterArr;
  CCScrollLayer*  mSlidingCharacterLayer;

  int             mCharacterTouchedID;
  int             mPlayer = 0;
  int             mCharacterChoseByPlayer1;

public:
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  virtual bool init();

  // there's no 'id' in cpp, so we recommend returning the class instance pointer
  static cocos2d::CCScene* scene();

  void addBackground();
  void addCharacter();
  void addBackButton();

  void buttonBackTouched(cocos2d::CCObject *pSender);
  void CharacterTouched(CCObject *pSender);
  
  CCArray getCharacterArr();
  CCScrollLayer getSlidingCharacterLayer();
  // implement the "static node()" method manually
  CREATE_FUNC(ChooseCharacterScene);
};

USING_NS_CC;

#endif /* defined(__landlord__ChooseCharacterScene__) */
