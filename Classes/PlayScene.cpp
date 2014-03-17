//
//  PlayScene.cpp
//  landlord
//
//  Created by Giap Nguyen on 2/24/14.
//
//

#include "PlayScene.h"
#include "WinScene.h"
#include "GameManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* PlayScene::scene()
{
  // 'scene' is an autorelease object
  CCScene *scene = CCScene::create();
  
  // 'layer' is an autorelease object
  PlayScene *layer = PlayScene::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !CCLayer::init() )
  {
    return false;
  }
  
  mScreenSize = CCDirector::sharedDirector()->getWinSize();
  setTouchEnabled(true);
  
  GameManager::initPlayersInfo();
//  addPlayGroud();
  makeMapScroll();
//  tilesArr->retain();
//  addFrameImg();
  addPauseButton();
  
  addPlayerOne();
  addPlayerOneShadow();
  addPlayerTwo();
  addPlayerTwoShadow();
  addScoreLbn();
  schedule(schedule_selector(PlayScene::update));
  
  return true;
}

void PlayScene::addPauseButton()
{
  CCSprite* btn = CCSprite::create("PlayScene/button-pause.png");
  CCMenuItemSprite* btnPause = CCMenuItemSprite::create(btn, btn, this, menu_selector(PlayScene::pauseButtonTouched));
  CCMenu* pMenu = CCMenu::create(btnPause, NULL);
  pMenu->setPosition(BTN_PAUSE_POS);
  addChild(pMenu);
}

void PlayScene::addPlayGroud()
{
  CCSprite *ground = CCSprite::create("PlayScene/background-playscene.png");
  ground->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  addChild(ground);
}

void PlayScene::addPlayerOne()
{
  mPlayerOneTag = GameManager::getPlayerOneID();
  CCLog("getPlayerOneID = %d", GameManager::getPlayerOneID());
  CCSprite *playerOne = CCSprite::create((CCString::createWithFormat("PlayScene/c%i.png", mPlayerOneTag))->getCString());
  playerOne->setScale(0.8f);
  playerOne->setPosition(PLAYER_ONE_POS);
  this->addChild(playerOne, GR_MIDDLEGROUND);
}

void PlayScene::addPlayerOneShadow()
{
  mPlayerOneShadow = CCSprite::create((CCString::createWithFormat("ChooseCharacterScene/c%i-blue.png", mPlayerOneTag))->getCString());
  mPlayerOneShadow->setScale(0.8f);
  mPlayerOneShadow->setPosition(PLAYER_ONE_POS);
  this->addChild(mPlayerOneShadow, GR_BACKGROUND);
}

void PlayScene::addPlayerTwo()
{
  mPlayerTwoTag = GameManager::getPlayerTwoID();
  CCSprite *playerTwo = CCSprite::create((CCString::createWithFormat("PlayScene/c%i.png", mPlayerTwoTag))->getCString());
  playerTwo->setScale(0.8f);
  playerTwo->setPosition(PLAYER_TWO_POS);
  this->addChild(playerTwo, GR_MIDDLEGROUND);
}

void PlayScene::addPlayerTwoShadow()
{
  mPlayerTwoShadow = CCSprite::create((CCString::createWithFormat("ChooseCharacterScene/c%i-red.png", mPlayerTwoTag))->getCString());
  mPlayerTwoShadow->setScale(0.8f);
  mPlayerTwoShadow->setPosition(PLAYER_TWO_POS);
  this->addChild(mPlayerTwoShadow, GR_BACKGROUND);
  mPlayerTwoShadow->setVisible(false);
}

void PlayScene::makeMapScroll()
{
  mTileMap = CCTMXTiledMap::create("Tiled map/demo-map.tmx");

  this->addChild(mTileMap);

  mTileMap->setPosition(ccp(0, 0));
  mMapLayer = mTileMap->layerNamed("map01");
  
  CCSize s = mMapLayer->getLayerSize();
  CCSprite* tile = CCSprite::create();
  mPopsArr = CCArray::createWithCapacity(NUMBER_EDGE_AVAILABLE);
  mPopsArr->retain();

  for (int i = 0; i < s.width; ++i)
  {
    for (int j = 0; j < s.height; ++j)
    {
      tile = mMapLayer->tileAt(ccp(i, j));
      if (!tile);
//        CCLog("tile is null");
      else
      {
        TileInfo *tileInfo = new TileInfo();
        tileInfo->setTile(tile);
        tileInfo->setGID(PAIR_FUNC(i, j));
        CCLog("gid %d", PAIR_FUNC(i, j));
        mTileInfoVector.push_back(tileInfo);
        
        if (j > 0 && mMapLayer->tileAt(ccp(i, j-1)))
        {
          tileInfo->setGIDTileUp(PAIR_FUNC(i, j-1));
        }
        
        if (j < s.height-1 && mMapLayer->tileAt(ccp(i, j+1)))
        {
          tileInfo->setGIDTileDown(PAIR_FUNC(i, j+1));
        }

        if (i > 0 && mMapLayer->tileAt(ccp(i-1, j)))
        {
          tileInfo->setGIDTileLeft(PAIR_FUNC(i-1, j));
        }

        if (i < s.width-1 && mMapLayer->tileAt(ccp(i+1, j)))
        {
          tileInfo->setGIDTileRight(PAIR_FUNC(i+1, j));
        }
      }
    }
  }
}

void PlayScene::addScoreLbn()
{
  CCSprite* scoreP1 = CCSprite::create("PlayScene/scoreP1.png");
  scoreP1->setPosition(LBN_SCORE_PLAYER1_POS);
  mLbnScorePlayer1 = CCLabelTTF::create("0", "ordin", 50);
  mLbnScorePlayer1->setHorizontalAlignment(kCCTextAlignmentCenter);
  mLbnScorePlayer1->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
  mLbnScorePlayer1->setColor(ccBLUE);
  mLbnScorePlayer1->setPosition(ccp(scoreP1->getPositionX(), scoreP1->getPositionY()));
  scoreP1->addChild(mLbnScorePlayer1);
  this->addChild(scoreP1, GR_FOREGROUND);
  
  // demo counting player1 score
  sprintf(mScoreBuffer, "%i", GameManager::getPlayerScore(true));
  mLbnScorePlayer1->setString(mScoreBuffer);
  
  CCSprite* scoreP2 = CCSprite::create("PlayScene/scoreP2.png");
  scoreP2->setPosition(LBN_SCORE_PLAYER2_POS);
  mLbnScorePlayer2 = CCLabelTTF::create("0", "ordin", 50);
  mLbnScorePlayer2->setHorizontalAlignment(kCCTextAlignmentCenter);
  mLbnScorePlayer2->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
  mLbnScorePlayer2->setColor(ccRED);
  mLbnScorePlayer2->setPosition(ccp(scoreP1->getPositionX(), scoreP1->getPositionY()));
  scoreP2->addChild(mLbnScorePlayer2);
  this->addChild(scoreP2, GR_FOREGROUND);
  
  // demo counting player2 score
  sprintf(mScoreBuffer, "%i", GameManager::getPlayerScore(false));
  mLbnScorePlayer2->setString(mScoreBuffer);
}

void PlayScene::pauseButtonTouched()
{
  CCLog("paused touched");
  CCScene* newScene = CCTransitionSlideInR::create(0.5, WinScene::scene());
  CCDirector::sharedDirector()->replaceScene(newScene);
}

void PlayScene::addFrameImg()
{
  CCSprite *frame = CCSprite::create("PlayScene/frame-01.png");
  frame->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  addChild(frame);
}

bool PlayScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  mIsScrolling = false;
  
  mBeginLocation = pTouch->getLocation();
  mBeginLocation = this->convertToNodeSpace(mBeginLocation);
  mBeginLocationToMap = mTileMap->convertToNodeSpace(mBeginLocation);
  
  return true;
}

void PlayScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  mIsScrolling = true;
  
  CCPoint touchLocation = pTouch->getLocation();
  touchLocation = this->convertToNodeSpace(touchLocation);
  CCPoint touchLocationToMap = mTileMap->convertToNodeSpace(touchLocation);
  
  float offsetX = touchLocation.x - mBeginLocation.x;
  float offsetY = touchLocation.y - mBeginLocation.y;
  moveMap(offsetX, offsetY);

  mBeginLocation = touchLocation;
  mBeginLocationToMap = touchLocationToMap;
}


void PlayScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  if (mPopsArr->count() > 0)
  {
    for (int i = 0; i < mPopsArr->count(); ++i)
    {
      ((CCMenuItemSprite*)mPopsArr->objectAtIndex(i))->removeFromParent();
      CCLog("remove %d", i);
    }
    mPopsArr->removeAllObjects();
  }
  TileInfo *tileInfo = new TileInfo();
  CCSprite *sp = CCSprite::create();
//  CCSize s = mMapLayer->getLayerSize();

  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    tileInfo = mTileInfoVector.at(i);
    sp = tileInfo->getTile();
    
    if (!mIsScrolling && sp && sp->boundingBox().containsPoint(mBeginLocationToMap))
    {
      mCurTile = i;
      if (tileInfo->getEdgeBottomSts() == STS_AVAILABLE && !tileInfo->getHasBottomPop())
      {
        appearBottomPop(tileInfo, sp);
      }
      if (tileInfo->getEdgeTopSts() == STS_AVAILABLE && !tileInfo->getHasTopPop())
      {
        appearTopPop(tileInfo, sp);
      }
      if (tileInfo->getEdgeLeftSts() == STS_AVAILABLE && !tileInfo->getHasLeftPop())
      {
        appearLeftPop(tileInfo, sp);
      }
      if (tileInfo->getEdgeRightSts() == STS_AVAILABLE && !tileInfo->getHasRightPop())
      {
        appearRightPop(tileInfo, sp);
      }
    }
  }
}

void PlayScene::chooseEdgeEnded(cocos2d::CCObject *pSender)
{
  CCMenuItemSprite* pop = (CCMenuItemSprite*)pSender;
  pop->setVisible(false);
  CCSprite *edge = CCSprite::create("PlayScene/edge.png");
  
  TileInfo *tileInfo = mTileInfoVector.at(mCurTile);

//  CCSprite *sp = tileInfo->getTile();
  CCLog("curTile = %d", mCurTile);
  
  if (pop->getTag() == TAG_EDGE_BOTTOM)
  {
    addBottomEdge(tileInfo, edge);
  }
  else if (pop->getTag() == TAG_EDGE_TOP)
  {
    addTopEdge(tileInfo, edge);
  }
  else if (pop->getTag() == TAG_EDGE_LEFT)
  {
    addLeftEdge(tileInfo, edge);
  }
  else if (pop->getTag() == TAG_EDGE_RIGHT )
  {
    addRightEdge(tileInfo, edge);
  }
  tileInfo->setNumberEdgeAvailale(tileInfo->getNumberEdgeAvailale()-1);
  CCLog("tileInfo->getNumberEdgeAvailale() = %d", tileInfo->getNumberEdgeAvailale());
  
  CCLog("Current Player is %i", GameManager::getCurrentPlayer());
  
  bool checkIncreasingScore = false;
  
  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    if (mTileInfoVector.at(i)->getNumberEdgeAvailale() == 0 && mTileInfoVector.at(i)->getBelongToPlayer() == 0)
    {
      GameManager::increaseScore(GameManager::getCurrentPlayer());
      checkIncreasingScore = true;
      sprintf(mScoreBuffer, "%i", GameManager::getPlayerScore(GameManager::getCurrentPlayer()));
      if (GameManager::getCurrentPlayer() == PLAYER_ONE)
      {
        mTileInfoVector.at(i)->setBelongToPlayer(1);
        mTileInfoVector.at(i)->getTile()->setColor(ccBLUE);
        mLbnScorePlayer1->setString(mScoreBuffer);
      }
      else
      {
        mTileInfoVector.at(i)->setBelongToPlayer(2);
        mTileInfoVector.at(i)->getTile()->setColor(ccRED);
        mLbnScorePlayer2->setString(mScoreBuffer);
      }
    }
  }
  
  if (!checkIncreasingScore)
  {
    if (GameManager::getCurrentPlayer() == PLAYER_ONE)
    {
      mPlayerOneShadow->setVisible(false);
      mPlayerTwoShadow->setVisible(true);
    }
    else
    {
      mPlayerTwoShadow->setVisible(false);
      mPlayerOneShadow->setVisible(true);
    }
    
    GameManager::changeCurrentPlayer();
  }
   
  for (int i = 0; i < mPopsArr->count(); ++i)
  {
    ((CCMenuItemSprite*)mPopsArr->objectAtIndex(i))->removeFromParent();
    CCLog("remove %d", i);
  }
  mPopsArr->removeAllObjects();
}

void PlayScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void PlayScene::moveMap(float offsetX, float offsetY)
{
  float posX = mTileMap->getPosition().x + offsetX;
  float posY = mTileMap->getPosition().y + offsetY;
  if (posX > 0)
    posX = 0;
  if (posX < getBound().x)
    posX = getBound().x;
  if (posY > 0)
    posY = 0;
  if (posY < getBound().y)
  {
    posY = getBound().y;
  }
  mTileMap->setPosition(ccp(posX, posY));
}

CCPoint PlayScene::getBound()
{
  float mapWidth = mTileMap->getTileSize().width * mTileMap->getMapSize().width;
  float mapHeight = mTileMap->getTileSize().height * mTileMap->getMapSize().height;
  
  // should caculate the bounding of map position
  return ccp(mScreenSize.width - mapWidth, mScreenSize.height - mapHeight);
}

void PlayScene::addGlowEffect(CCSprite* sprite,
                   const ccColor3B& colour,
                   const CCSize& size)
{
  CCPoint pos = ccp(sprite->getPositionX(),
                    sprite->getPositionY());

  CCSprite* glowSprite = CCSprite::create("PlayScene/edge.png");
  glowSprite->setColor(colour);
  glowSprite->setPosition(pos);
  glowSprite->setRotation(sprite->getRotation());
  _ccBlendFunc f = {GL_ONE, GL_ONE};
  glowSprite->setBlendFunc(f);
  addChild(glowSprite, GR_FOREGROUND);
  // Run some animation which scales a bit the glow
  
  CCSequence* s1 =
    CCSequence::create(
      CCScaleTo::create(0.9f, size.width, size.height),
      CCScaleTo::create(0.9f, size.width*0.75f, size.height*0.75f),
      NULL);
  
  CCRepeatForever* r = CCRepeatForever::create(s1);
  glowSprite->runAction(r);
}

PlayScene::~PlayScene()
{
    mPopsArr->release();
}

void PlayScene::update(float pdT)
{
  if (GameManager::getPlayerScore(GameManager::getCurrentPlayer()) >= 3)
  {
    GameManager::setWinPlayer(GameManager::getCurrentPlayer());
    CCScene* newScene = CCTransitionSlideInR::create(0.5, WinScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
  }
}

void PlayScene::addBottomEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge)
{
  CCSprite *sp = pTileInfo->getTile();
  pTileInfo->setHasBottomPop(true);
  
  pEdge->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width/2, sp->getPositionY()));
  
  mTileMap->addChild(pEdge, GR_FOREGROUND);
  pTileInfo->setEdgeBottomSts(STS_NOT_AVAILABLE);
  
  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    if (mTileInfoVector.at(i)->getGID() == pTileInfo->getGIDTileDown())
    {
      mTileInfoVector.at(i)->setHasTopPop(true);
      mTileInfoVector.at(i)->setEdgeTopSts(STS_NOT_AVAILABLE);
      mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
    }
  }
}

void PlayScene::addTopEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge)
{
  CCSprite *sp = pTileInfo->getTile();
  pTileInfo->setHasTopPop(true);
  
  pEdge->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width/2, sp->getPositionY() + sp->getContentSize().height));
  
  mTileMap->addChild(pEdge, GR_FOREGROUND);
  pTileInfo->setEdgeTopSts(STS_NOT_AVAILABLE);
  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    if (mTileInfoVector.at(i)->getGID() == pTileInfo->getGIDTileUp())
    {
      mTileInfoVector.at(i)->setHasBottomPop(true);
      mTileInfoVector.at(i)->setEdgeBottomSts(STS_NOT_AVAILABLE);
      mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
    }
  }
}

void PlayScene::addLeftEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge)
{
  CCSprite *sp = pTileInfo->getTile();
  pTileInfo->setHasLeftPop(true);
  
  pEdge->setRotation(90);
  pEdge->setPosition(ccp(sp->getPositionX(), sp->getPositionY() + sp->getContentSize().height/2));
  
  mTileMap->addChild(pEdge, GR_FOREGROUND);
  pTileInfo->setEdgeLeftSts(STS_NOT_AVAILABLE);
  
  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    if (mTileInfoVector.at(i)->getGID() == pTileInfo->getGIDTileLeft())
    {
      mTileInfoVector.at(i)->setHasRightPop(true);
      mTileInfoVector.at(i)->setEdgeRightSts(STS_NOT_AVAILABLE);
      mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
    }
  }
}

void PlayScene::addRightEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge)
{
  CCSprite *sp = pTileInfo->getTile();
  pTileInfo->setHasRightPop(true);
  
  pEdge->setRotation(90);
  pEdge->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width, sp->getPositionY() + sp->getContentSize().height/2));
  
  mTileMap->addChild(pEdge, GR_FOREGROUND);
  pTileInfo->setEdgeRightSts(STS_NOT_AVAILABLE);
  
  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    if (mTileInfoVector.at(i)->getGID() == pTileInfo->getGIDTileRight())
    {
      mTileInfoVector.at(i)->setHasLeftPop(true);
      mTileInfoVector.at(i)->setEdgeLeftSts(STS_NOT_AVAILABLE);
      mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
    }
  }
}

void PlayScene::appearBottomPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp)
{
  CCSprite* pop = CCSprite::create("PlayScene/button-pause.png");
  CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_BOTTOM);
  edgePop->setPosition(ccp(pSp->getPositionX() + pSp->getContentSize().width/2, pSp->getPositionY() - pop->getContentSize().height/2));
  mTileMap->addChild(edgePop);
}

void PlayScene::appearTopPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp)
{
  CCSprite* pop = CCSprite::create("PlayScene/button-pause.png");
  CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_TOP);
  edgePop->setPosition(ccp(pSp->getPositionX() + pSp->getContentSize().width/2, pSp->getPositionY() + pSp->getContentSize().height + pop->getContentSize().height/2));
  mTileMap->addChild(edgePop);
}

void PlayScene::appearLeftPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp)
{
  CCSprite* pop = CCSprite::create("PlayScene/button-pause.png");
  CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_LEFT);
  edgePop->setPosition(ccp(pSp->getPositionX() - pop->getContentSize().width/2, pSp->getPositionY() + pSp->getContentSize().height/2));
  mTileMap->addChild(edgePop);
}

void PlayScene::appearRightPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp)
{
  CCSprite* pop = CCSprite::create("PlayScene/button-pause.png");
  CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_RIGHT);
  edgePop->setPosition(ccp(pSp->getPositionX() + pSp->getContentSize().width + pop->getContentSize().width/2, pSp->getPositionY() + pSp->getContentSize().height/2));
  mTileMap->addChild(edgePop);
}

