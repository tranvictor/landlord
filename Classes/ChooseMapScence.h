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

class ChooseMapScene : public cocos2d::CCLayer //, public CCScrollViewDelegate
{
private:
  cocos2d::CCSize screenSize;
  cocos2d::CCArray *mapArr;
//  Maps* ;
  int mapTouchedID;
//  SlidingMenuGrid *slidingMap;
//  CCScrollView *slidingMap;
  CCScrollLayer *slidingMap;
  
public:
  virtual bool init();
//  virtual void scrollViewDidScroll(CCScrollView* view);
//  virtual void scrollViewDidZoom(CCScrollView* view);
  static cocos2d::CCScene * scene();
  CREATE_FUNC(ChooseMapScene);
  
  void addBackground();
  void addButtonRandom();
  void buttonRandomTouched(cocos2d::CCObject* pSender);
  void addButtonBack();
  void buttonBackTouched(cocos2d::CCObject* pSender);
  
  void makeSlidingMap();
  void mapTouched(cocos2d::CCObject* pSender);
  
//  void addTempSlide();
};

#endif /* defined(__landlord__ChooseMapScence__) */
