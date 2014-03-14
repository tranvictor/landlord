//
//  ChooseMapScence.h
//  landlord
//
//  Created by Giap Nguyen on 2/19/14.
//
//

#ifndef __CHOOSEMAPSCENE_H__
#define __CHOOSEMAPSCENE_H__

#include "cocos2d.h"
#include "Constant.h"
#include "Maps.h"
#include "SlidingMenu.h"
//#include "cocos-ext.h"
#include "CCScrollLayer.h"

//using namespace cocos2d::extension;

class ChooseMapScene : public cocos2d::CCLayer
{
private:
  cocos2d::CCSize   mScreenSize;
  cocos2d::CCArray* mMapArr;
  int               mMapTouchedID;
  CCScrollLayer*    mSlidingMap;
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  CREATE_FUNC(ChooseMapScene);
  
  void addBackground();
  void addButtonRandom();
  void buttonRandomTouched(cocos2d::CCObject *pSender);
  void addButtonBack();
  void buttonBackTouched(cocos2d::CCObject *pSender);
  
  void makeSlidingMap();
  void mapTouched(cocos2d::CCObject *pSender);
};

#endif /* defined(__landlord__ChooseMapScence__) */
