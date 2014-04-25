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

class LoadingScene : public cocos2d::CCLayer
{
private:
  
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  void addItems();
  
  CREATE_FUNC(LoadingScene);
};

#endif /* defined(__landlord__LoadingScene__) */
