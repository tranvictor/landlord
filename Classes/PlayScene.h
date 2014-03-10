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
#include "TileInfo.h"

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
  bool mIsScrolling = false;
  cocos2d::CCArray *mEdgeArrTop;
  cocos2d::CCArray *mEdgeArrBottom;
  cocos2d::CCArray *mEdgeArrLeft;
  cocos2d::CCArray *mEdgeArrRight;
  
  cocos2d::CCArray *popsArr;
  std::vector<TileInfo*> tileInfoVector;
  int curTile = 0;
  int numPop = NUMBER_EDGE_AVAILABLE;
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  ~PlayScene();
  
  void addPauseButton();
  void addPlayGroud();
  void addPLayerOne();
  void addPlayerTwo();
  void addScoreLbn();
  void addFrameImg();
  
  void makeMapScroll();
  void pauseButtonTouched();
  void moveMap(float offsetX, float offsetY);
  void addGlowEffect(CCSprite* sprite,
                                const ccColor3B& colour,
                     const CCSize& size);
  
  CCPoint getBound();
  
  virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  void registerWithTouchDispatcher();
  void chooseEdgeEnded(cocos2d::CCObject *pSender);
  CREATE_FUNC(PlayScene);
};

#endif /* defined(__landlord__PlayScene__) */
