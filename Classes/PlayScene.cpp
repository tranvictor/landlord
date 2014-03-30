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
#include "Tree.h"
#include "Axe.h"
#include "Stone.h"

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
  
//  addTrees();
  addAxes();
//  addStones();
  
  schedule(schedule_selector(PlayScene::update));
  
  return true;
}

void PlayScene::addPauseButton()
{
  CCSprite* btn = CCSprite::create("Images/Game/UI/button-pause.png");
  CCMenuItemSprite* btnPause = CCMenuItemSprite::create(btn, btn, this, menu_selector(PlayScene::pauseButtonTouched));
  CCMenu* pMenu = CCMenu::create(btnPause, NULL);
  pMenu->setPosition(BTN_PAUSE_POS);
  addChild(pMenu);
}

void PlayScene::addPlayGroud()
{
  CCSprite *ground = CCSprite::create("Images/Game/Background/BG-play.png");
  ground->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  addChild(ground);
}

void PlayScene::addPlayerOne()
{
  mPlayerOneTag = GameManager::getPlayerOneID();
  CCLog("getPlayerOneID = %d", GameManager::getPlayerOneID());
  CCSprite *playerOne = CCSprite::create((CCString::createWithFormat("Images/Game/Object/c%i.png", mPlayerOneTag))->getCString());
  playerOne->setScale(0.8f);
  playerOne->setPosition(PLAYER_ONE_POS);
  this->addChild(playerOne, GR_MIDDLEGROUND);
}

void PlayScene::addPlayerOneShadow()
{
  mPlayerOneShadow = CCSprite::create((CCString::createWithFormat("Images/Game/Object/c%i-blue.png", mPlayerOneTag))->getCString());
  mPlayerOneShadow->setScale(0.8f);
  mPlayerOneShadow->setPosition(PLAYER_ONE_POS);
  this->addChild(mPlayerOneShadow, GR_BACKGROUND);
}

void PlayScene::addPlayerTwo()
{
  mPlayerTwoTag = GameManager::getPlayerTwoID();
  CCSprite *playerTwo = CCSprite::create((CCString::createWithFormat("Images/Game/Object/c%i.png", mPlayerTwoTag))->getCString());
  playerTwo->setScale(0.8f);
  playerTwo->setPosition(PLAYER_TWO_POS);
  this->addChild(playerTwo, GR_MIDDLEGROUND);
}

void PlayScene::addPlayerTwoShadow()
{
  mPlayerTwoShadow = CCSprite::create((CCString::createWithFormat("Images/Game/Object/c%i-red.png", mPlayerTwoTag))->getCString());
  mPlayerTwoShadow->setScale(0.8f);
  mPlayerTwoShadow->setPosition(PLAYER_TWO_POS);
  this->addChild(mPlayerTwoShadow, GR_BACKGROUND);
  mPlayerTwoShadow->setVisible(false);
}

void PlayScene::makeMapScroll()
{
  mTileMap = CCTMXTiledMap::create("Images/Map/map01.tmx");

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
  CCSprite* scoreP1 = CCSprite::create("Images/Game/UI/scoreP1.png");
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
  
  CCSprite* scoreP2 = CCSprite::create("Images/Game/UI/scoreP2.png");
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
    removePopups();
  }
  if (mIsAxePopVisible == true)
  {
    mAxePop->setVisible(false);
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
      if (mTileInfoVector.at(mCurTile)->getHasTree())
      {
        if (Axe::getNumOfAxes(GameManager::getCurrentPlayer()) > 0)
        {
          appearAxePop(tileInfo, sp);
        }
      }
      else if (mTileInfoVector.at(mCurTile)->getHasStone())
      {
        //  doing nothing
      }
      else
      {
        appearPops(tileInfo, sp);
      }
    }
  }
}

void PlayScene::chooseEdgeEnded(cocos2d::CCObject *pSender)
{
  CCMenuItemSprite* pop = (CCMenuItemSprite*)pSender;
  pop->setVisible(false);
  CCSprite *edge = CCSprite::create("Images/Game/Object/edge.png");
  
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
    if (mTileInfoVector.at(i)->getNumberEdgeAvailale() == 0 && mTileInfoVector.at(i)->getBelongToPlayer() == 0 && mTileInfoVector.at(i)->getHasTree() == false && mTileInfoVector.at(i)->getHasStone() == false)
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
      if (tileInfo->getHasAxe())
      {
        Axe::increaseNumOfAxes(GameManager::getCurrentPlayer());
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
   
  removePopups();
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

  CCSprite* glowSprite = CCSprite::create("Images/Game/Object/edge.png");
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
  mTreesArr->release();
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

void PlayScene::appearPops(TileInfo* pTileInfo, cocos2d::CCSprite *pSp)
{
  if (pTileInfo->getEdgeBottomSts() == STS_AVAILABLE && !pTileInfo->getHasBottomPop())
  {
    appearBottomPop(pTileInfo, pSp);
  }
  if (pTileInfo->getEdgeTopSts() == STS_AVAILABLE && !pTileInfo->getHasTopPop())
  {
    appearTopPop(pTileInfo, pSp);
  }
  if (pTileInfo->getEdgeLeftSts() == STS_AVAILABLE && !pTileInfo->getHasLeftPop())
  {
    appearLeftPop(pTileInfo, pSp);
  }
  if (pTileInfo->getEdgeRightSts() == STS_AVAILABLE && !pTileInfo->getHasRightPop())
  {
    appearRightPop(pTileInfo, pSp);
  }
}

void PlayScene::appearBottomPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp)
{
  CCSprite* pop = CCSprite::create("Images/Game/UI/button-pause.png");
  CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_BOTTOM);
  edgePop->setPosition(ccp(pSp->getPositionX() + pSp->getContentSize().width/2, pSp->getPositionY() - pop->getContentSize().height/2));
  mTileMap->addChild(edgePop, GR_FOREGROUND);
}

void PlayScene::appearTopPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp)
{
  CCSprite* pop = CCSprite::create("Images/Game/UI/button-pause.png");
  CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_TOP);
  edgePop->setPosition(ccp(pSp->getPositionX() + pSp->getContentSize().width/2, pSp->getPositionY() + pSp->getContentSize().height + pop->getContentSize().height/2));
  mTileMap->addChild(edgePop, GR_FOREGROUND);
}

void PlayScene::appearLeftPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp)
{
  CCSprite* pop = CCSprite::create("Images/Game/UI/button-pause.png");
  CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_LEFT);
  edgePop->setPosition(ccp(pSp->getPositionX() - pop->getContentSize().width/2, pSp->getPositionY() + pSp->getContentSize().height/2));
  mTileMap->addChild(edgePop, GR_FOREGROUND);
}

void PlayScene::appearRightPop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp)
{
  CCSprite* pop = CCSprite::create("Images/Game/UI/button-pause.png");
  CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_RIGHT);
  edgePop->setPosition(ccp(pSp->getPositionX() + pSp->getContentSize().width + pop->getContentSize().width/2, pSp->getPositionY() + pSp->getContentSize().height/2));
  mTileMap->addChild(edgePop, GR_FOREGROUND);
}

void PlayScene::removePopups()
{
  for (int i = 0; i < mPopsArr->count(); ++i)
  {
    ((CCMenuItemSprite*)mPopsArr->objectAtIndex(i))->removeFromParent();
    CCLog("remove %d", i);
  }
  mPopsArr->removeAllObjects();
}

void PlayScene::addTrees()
{
  int numberOfTrees = rand() % 3 + 4;
  mTreesArr = CCArray::createWithCapacity(numberOfTrees);
  mTreesArr->retain();
  CCLog("Number of Trees is %i", numberOfTrees);
  Tree::setNumOfTrees(numberOfTrees);
  for (int i = 0; i < numberOfTrees; i++)
  {
    int r;
    do
    {
      r = rand() % mTileInfoVector.size();
    } while (mTileInfoVector.at(r)->getHasTree());
    CCLog("Tile at %i has a tree", r);
    mTileInfoVector.at(r)->setHasTree(true);
    mTileInfoVector.at(r)->setHasItem(true);
    
    CCSprite* tree = CCSprite::create("Images/Game/Object/tree.png");
    mTreesArr->addObject(tree);
    tree->setTag(r);
    tree->setPosition(ccp(mTileInfoVector.at(r)->getTile()->getPositionX() + mTileInfoVector.at(r)->getTile()->getContentSize().width/2, mTileInfoVector.at(r)->getTile()->getPositionY() + mTileInfoVector.at(r)->getTile()->getContentSize().height/2 + tree->getContentSize().height/4));
    mTileMap->addChild(tree);
  }
}

void PlayScene::addAxes()
{
  int numberOfAxes = Tree::getNumOfTrees();
  CCLog("Number of Axes is %i", numberOfAxes);
  Tree::setNumOfTrees(numberOfAxes);
  for (int i = 0; i < numberOfAxes; i++)
  {
    int r;
    do
    {
      r = rand() % mTileInfoVector.size();
    } while (mTileInfoVector.at(r)->getHasItem());
    CCLog("Tile at %i has a axe", r);
    mTileInfoVector.at(r)->setHasAxe(true);
    mTileInfoVector.at(r)->setHasItem(true);
    mTileInfoVector.at(r)->getTile()->setColor(ccBLACK);
  }
}

void PlayScene::addStones()
{
  int numberOfStones = rand() % 4 + 3;
  CCLog("Number of Axes is %i", numberOfStones);
  Stone::setNumOfStones(numberOfStones);
  for (int i = 0; i < numberOfStones; i++)
  {
    int r;
    do
    {
      r = rand() % mTileInfoVector.size();
    } while (mTileInfoVector.at(r)->getHasItem());
    CCLog("Tile at %i has a stone", r);
    mTileInfoVector.at(r)->setHasStone(true);
    mTileInfoVector.at(r)->setHasItem(true);
    
    CCSprite* stone = CCSprite::create("Images/Game/Object/stone.png");
    stone->setTag(r);
    stone->setPosition(ccp(mTileInfoVector.at(r)->getTile()->getPositionX() + mTileInfoVector.at(r)->getTile()->getContentSize().width/2, mTileInfoVector.at(r)->getTile()->getPositionY() + mTileInfoVector.at(r)->getTile()->getContentSize().height/2));
    mTileMap->addChild(stone);
    
    for (int i = 0; i < mTileInfoVector.size(); ++i)
    {
      if (mTileInfoVector.at(i)->getGID() ==
          mTileInfoVector.at(r)->getGIDTileLeft())
      {
        mTileInfoVector.at(i)->setHasRightPop(true);
        mTileInfoVector.at(i)->setEdgeRightSts(STS_NOT_AVAILABLE);
        mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
      else if (mTileInfoVector.at(i)->getGID() ==
               mTileInfoVector.at(r)->getGIDTileRight())
      {
        mTileInfoVector.at(i)->setHasLeftPop(true);
        mTileInfoVector.at(i)->setEdgeLeftSts(STS_NOT_AVAILABLE);
        mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
      else if (mTileInfoVector.at(i)->getGID() ==
               mTileInfoVector.at(r)->getGIDTileUp())
      {
        mTileInfoVector.at(i)->setHasBottomPop(true);
        mTileInfoVector.at(i)->setEdgeBottomSts(STS_NOT_AVAILABLE);
        mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
      else if (mTileInfoVector.at(i)->getGID() ==
               mTileInfoVector.at(r)->getGIDTileDown())
      {
        mTileInfoVector.at(i)->setHasTopPop(true);
        mTileInfoVector.at(i)->setEdgeTopSts(STS_NOT_AVAILABLE);
        mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
    }
  }
}

void PlayScene::appearAxePop(TileInfo *pTileInfo, cocos2d::CCSprite *pSp)
{
  CCSprite* pop = CCSprite::create("Images/Game/Object/axe.png");
  mAxePop = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseAxeEnded));
  CCMenu *axePop = CCMenu::create(mAxePop, NULL);
  axePop->setPosition(ccp(pSp->getPositionX() + pSp->getContentSize().width/2, pSp->getPositionY() + pSp->getContentSize().height + pop->getContentSize().height/2));
  mTileMap->addChild(axePop);
  mIsAxePopVisible = true;
}

void PlayScene::chooseAxeEnded(cocos2d::CCObject *pSender)
{
  CCMenuItemSprite* pop = (CCMenuItemSprite*)pSender;
  pop->setVisible(false);
  mIsAxePopVisible = false;
  Axe::decreaseNumOfAxes(GameManager::getCurrentPlayer());
  mTileInfoVector.at(mCurTile)->setHasTree(false);
  removeTree();
  
  if (mTileInfoVector.at(mCurTile)->getNumberEdgeAvailale() == 0)
  {
    mTileInfoVector.at(mCurTile)->setBelongToPlayer(GameManager::getCurrentPlayer());
    GameManager::increaseScore(GameManager::getCurrentPlayer());
    sprintf(mScoreBuffer, "%i", GameManager::getPlayerScore(GameManager::getCurrentPlayer()));
    if (GameManager::getCurrentPlayer() == PLAYER_ONE)
    {
      mTileInfoVector.at(mCurTile)->getTile()->setColor(ccBLUE);
      mLbnScorePlayer1->setString(mScoreBuffer);
    }
    else
    {
      mTileInfoVector.at(mCurTile)->getTile()->setColor(ccRED);
      mLbnScorePlayer2->setString(mScoreBuffer);
    }
  }
}

void PlayScene::removeTree()
{
  for (int i = 0; i < mTreesArr->count(); i++)
  {
    CCSprite* tree = (CCSprite*) mTreesArr->objectAtIndex(i);
    if (tree->getTag() == mCurTile)
    {
      tree->setVisible(false);
      mTreesArr->removeObjectAtIndex(i);
    }
  }
}
