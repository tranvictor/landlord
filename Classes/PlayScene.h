//
//  PlayScene.h
//  landlord
//
//  Created by Giap Nguyen on 2/24/14.
//
//

#ifndef __PLAYSCENE_H__
#define __PLAYSCENE_H__

#include "cocos2d.h"
#include "ScrollableMap.h"
#include "Constant.h"

class PlayScene : public cocos2d::CCLayer
{
  int playerOneTag, playerTwoTag;
  ScrollableMap* scrollMap;
  cocos2d::CCSize screenSize;
  cocos2d::CCLabelTTF *lbnScorePlayer1;
  cocos2d::CCLabelTTF *lbnScorePlayer2;
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  void addPauseButton();
  void addPlayGroud();
  void addPLayerOne();
  void addPlayerTwo();
  void addScoreLbn();
  
  void makeMapScroll();
  void pauseButtonTouched();
    
  CREATE_FUNC(PlayScene);
};

#endif /* defined(__landlord__PlayScene__) */
