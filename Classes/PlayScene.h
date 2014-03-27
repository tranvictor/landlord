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
#include "GameManager.h"

class PlayScene : public cocos2d::CCLayer
{
  int                 mPlayerOneTag, mPlayerTwoTag;
//  cocos2d::extension::CCScrollView *scrollMap;
//  CCLayerPanZoom*     mController;
  
  cocos2d::CCSize     mScreenSize;
  cocos2d::CCLabelTTF *mLbnScorePlayer1;
  cocos2d::CCLabelTTF *mLbnScorePlayer2;
  char                mScoreBuffer[10];
  
  CCPoint             mBeginLocation;
  // beginLocation in tilemap co-ordinate
  CCPoint             mBeginLocationToMap;
  
  CCTMXTiledMap*      mTileMap;
  CCTMXLayer*         mMapLayer;
  CCTMXObjectGroup*   mTileEdges;
  bool                mIsScrolling = false;
  cocos2d::CCArray*   mEdgeArrTop;
  cocos2d::CCArray*   mEdgeArrBottom;
  cocos2d::CCArray*   mEdgeArrLeft;
  cocos2d::CCArray*   mEdgeArrRight;
  
  cocos2d::CCArray*   mPopsArr;
  std::vector<TileInfo*>  mTileInfoVector;
  
  int                 mCurTile = 0;
//  int                 mNumPop = NUMBER_EDGE_AVAILABLE;
  
  CCSprite*           mPlayerOneShadow;
  CCSprite*           mPlayerTwoShadow;
  
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  ~PlayScene();
  
  void addPauseButton();
  void addPlayGroud();
  void addPlayerOne();
  void addPlayerOneShadow();
  void addPlayerTwo();
  void addPlayerTwoShadow();
  void addScoreLbn();
  void addFrameImg();
  
  void makeMapScroll();
  void pauseButtonTouched();
  void moveMap(float pOffsetX, float pOffsetY);
  void addGlowEffect(CCSprite *pSprite,
                     const ccColor3B& pColour,
                     const CCSize& pSize);
  
  void addBottomEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge);
  void addTopEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge);
  void addLeftEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge);
  void addRightEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge);
  
  void appearBottomPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp);
  void appearTopPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp);
  void appearLeftPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp);
  void appearRightPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp);
  
  void addTrees();
  void addAxes();
  
  CCPoint getBound();
  
  virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
  void registerWithTouchDispatcher();
  void chooseEdgeEnded(cocos2d::CCObject *pSender);
  CREATE_FUNC(PlayScene);
  void update(float pdT);
  
};

#endif /* defined(__landlord__PlayScene__) */
