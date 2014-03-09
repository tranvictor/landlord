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
#include "Constant.h"
#include "cocos-ext.h"
#include "CCLayerPanZoom.h"

class PlayScene : public cocos2d::CCLayer
{
  int playerOneTag, playerTwoTag;
//  cocos2d::extension::CCScrollView *scrollMap;
  CCLayerPanZoom *controller;
  
  cocos2d::CCSize screenSize;
  cocos2d::CCLabelTTF *lbnScorePlayer1;
  cocos2d::CCLabelTTF *lbnScorePlayer2;
  
  CCPoint beginLocation;
  CCPoint beginLocationToMap; // beginLocation in tilemap co-ordinate
  
  CCTMXTiledMap *tileMap;
  CCTMXLayer    *mapLayer;
  CCTMXObjectGroup *mTileEdges;
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  
  void addPauseButton();
  void addPlayGroud();
  void addPLayerOne();
  void addPlayerTwo();
  void addScoreLbn();
  void addFrameImg();
  
  void makeMapScroll();
  void pauseButtonTouched();
  void moveMap(float offsetX, float offsetY);
  CCPoint getBound();
  
  virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
  virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
  virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
  void registerWithTouchDispatcher();
  CREATE_FUNC(PlayScene);
};

#endif /* defined(__landlord__PlayScene__) */
