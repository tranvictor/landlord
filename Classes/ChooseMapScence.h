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

class ChooseMapScene : public cocos2d::CCLayer
{
private:
  cocos2d::CCSize screenSize;
  
public:
  virtual bool init();
  static cocos2d::CCScene * scene();
  CREATE_FUNC(ChooseMapScene);
  
  void addBackground();
  void addButtonRandom();
  void addButtonBack();
};

#endif /* defined(__landlord__ChooseMapScence__) */
