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
#include "Sound.h"
#include "SimpleAudioEngine.h"

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
  
  CCLOG("PlayScene: %d %d", GameManager::getPlayerOneID(), GameManager::getPlayerTwoID());
  
  CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
  
  mScreenSize = CCDirector::sharedDirector()->getWinSize();
  setTouchEnabled(true);
  
  GameManager::initPlayersInfo();
//  addPlayGroud();
  makeMapScroll();
//  tilesArr->retain();
//  addFrameImg();
  addPauseButton();
  
  addPlayerOne();
//  addPlayerOneShadow();
  mTurnIndicatorLeft = createTurnIndicator(PLAYER_ONE_POS);
  mTurnIndicatorLeft->setVisible(true);
  
  mTurnIndicatorRight = createTurnIndicator(PLAYER_TWO_POS);
  
  addPlayerTwo();
//  addPlayerTwoShadow();
  addScoreLbn();
  addPausedLayer();
  GameManager::setIsInPlayScene(true);
  
  if (GameManager::getTreeModeState())
  {
//    CCLog("%d", GameManager::getTreeModeState());
    addTrees();
    addAxes();
    addStones();
  }
  
  setCooldownTime(100.0);
  srand(time(NULL));
  mRemindLayerLeft = setupRemindLayer("Images/Game/Object/bubble_blue.png", PLAYER_ONE_POS + ccp(320, 200), quote[rand() % (sizeof(quote)/sizeof(quote[0]))].c_str(), BLUE);
  mRemindLayerRight = setupRemindLayer("Images/Game/Object/bubble_red.png", PLAYER_TWO_POS + ccp(-320, 200), quote[rand() % (sizeof(quote)/sizeof(quote[0]))].c_str(), RED);
  
  schedule(schedule_selector(PlayScene::update));
  schedule(schedule_selector(PlayScene::cooldown));
  
  return true;
}

void PlayScene::addPauseButton()
{
  CCSprite* btn = CCSprite::create("Images/Game/UI/pauseButton-02.png");
  CCMenuItemSprite* btnPause =
    CCMenuItemSprite::create(btn,
                             btn,
                             this,
                             menu_selector(PlayScene::pauseButtonTouched));
  CCMenu* menu = CCMenu::create(btnPause, NULL);
  menu->setPosition(BTN_PAUSE_POS);
  addChild(menu, GR_FOREGROUND);
}

void PlayScene::addPlayGroud()
{
  CCSprite *ground = CCSprite::create("Images/Game/Background/gradientPlayScene.png");
  ground->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  addChild(ground, GR_FOREGROUND);
}

void PlayScene::addBackground()
{
  CCLayerColor* background = CCLayerColor::create(ccc4(46, 107, 229, 255));
  background->setPosition(CCPointZero);
  addChild(background, GR_BACKGROUND);
}

void PlayScene::addPlayerOne()
{
  mPlayerOneTag = GameManager::getPlayerOneID();
  CCLog("getPlayerOneID = %d", GameManager::getPlayerOneID());
  CCSprite *playerOne = CCSprite::create((CCString::createWithFormat("Images/Game/Object/c%i.png", mPlayerOneTag))->getCString());
  playerOne->setScale(0.8f);
  playerOne->setPosition(PLAYER_ONE_POS);
  this->addChild(playerOne, GR_FOREGROUND);
}

void PlayScene::addPlayerOneShadow()
{
  mPlayerOneShadow = CCSprite::create((CCString::createWithFormat("Images/Game/Object/c%i-blue.png", mPlayerOneTag))->getCString());
  mPlayerOneShadow->setScale(0.8f);
  mPlayerOneShadow->setPosition(PLAYER_ONE_POS);
  this->addChild(mPlayerOneShadow, GR_MIDDLEGROUND);  
}

void PlayScene::addPlayerTwo()
{
  mPlayerTwoTag = GameManager::getPlayerTwoID();
  CCSprite *playerTwo = CCSprite::create((CCString::createWithFormat("Images/Game/Object/c%i.png", mPlayerTwoTag))->getCString());
  playerTwo->setScale(0.8f);
  playerTwo->setPosition(PLAYER_TWO_POS);
  this->addChild(playerTwo, GR_FOREGROUND);
}

void PlayScene::addPlayerTwoShadow()
{
  mPlayerTwoShadow = CCSprite::create((CCString::createWithFormat("Images/Game/Object/c%i-red.png", mPlayerTwoTag))->getCString());
  mPlayerTwoShadow->setScale(0.8f);
  mPlayerTwoShadow->setPosition(PLAYER_TWO_POS);
  this->addChild(mPlayerTwoShadow, GR_MIDDLEGROUND);
  mPlayerTwoShadow->setVisible(false);
}

void PlayScene::makeMapScroll()
{
  mTileMap = CCTMXTiledMap::create(CCString::createWithFormat("Images/Map/map%d.tmx",
                                                              GameManager::getMapIDTouched())->getCString());

  this->addChild(mTileMap, GR_MIDDLEGROUND);

  mTileMap->setPosition(ccp(0, 0));
  mMapLayer = mTileMap->layerNamed("tile");
  
  CCSize s = mMapLayer->getLayerSize();
  CCSprite* tile;// = CCSprite::create();
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
//        CCLog("gid %d", PAIR_FUNC(i, j));
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
  CCSprite* scoreBoardPlayscene = CCSprite::create("Images/Game/UI/scorePanel.png");
  scoreBoardPlayscene->setPosition(ccp(SCREEN_SIZE.width/2,
                                       scoreBoardPlayscene->getContentSize().height/2));
//  CCSprite* scoreP1 = CCSprite::create("Images/Game/UI/scoreP1.png");
//  scoreP1->setPosition(LBN_SCORE_PLAYER1_POS);
  mLbnScorePlayer1 = CCLabelTTF::create("  0      0", "ordin", 50);
  mLbnScorePlayer1->setHorizontalAlignment(kCCTextAlignmentCenter);
  mLbnScorePlayer1->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
  mLbnScorePlayer1->setColor(BLUE);
  mLbnScorePlayer1->setPosition(ccp(PLAYER_ONE_POS.x + 20, 35));
  scoreBoardPlayscene->addChild(mLbnScorePlayer1);

  
  // counting player1 score
//  sprintf(mScoreBuffer, "%i", GameManager::getPlayerScore(true));
//  mLbnScorePlayer1->setString(mScoreBuffer);
  
//  CCSprite* scoreP2 = CCSprite::create("Images/Game/UI/scoreP2.png");
//  scoreP2->setPosition(LBN_SCORE_PLAYER2_POS);
  mLbnScorePlayer2 = CCLabelTTF::create("0      0", "ordin", 50);
  mLbnScorePlayer2->setHorizontalAlignment(kCCTextAlignmentCenter);
  mLbnScorePlayer2->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
  mLbnScorePlayer2->setColor(RED);
  mLbnScorePlayer2->setPosition(ccp(PLAYER_TWO_POS.x - 20, 35));
  scoreBoardPlayscene->addChild(mLbnScorePlayer2);
  this->addChild(scoreBoardPlayscene, GR_FOREGROUND);
  
  // counting player2 score
//  sprintf(mScoreBuffer, "%i", GameManager::getPlayerScore(false));
//  mLbnScorePlayer2->setString(mScoreBuffer);
}

void PlayScene::pauseButtonTouched(CCObject* pSender)
{
  CCLog("paused touched");
  // TODO
  CCDirector::sharedDirector()->pause();
  mRemindLayerLeft->setVisible(false);
  mRemindLayerRight->setVisible(false);
  mPausedLayer->setVisible(true);
  mTileMap->setVisible(false);
  unschedule(schedule_selector(PlayScene::cooldown));
  sound::playSoundFx(SFX_BUTTON_TOUCH);
}

void PlayScene::addFrameImg()
{
  CCSprite *frame = CCSprite::create("PlayScene/frame-01.png");
  frame->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  addChild(frame);
}

bool PlayScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  unschedule(schedule_selector(PlayScene::cooldown));
  schedule(schedule_selector(PlayScene::cooldown));
  
  mIsScrolling = false;
  setCooldownTime(100.0);
  
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
  
  TileInfo *tileInfo;// = new TileInfo();
  CCSprite *sp;// = CCSprite::create();
//  CCSize s = mMapLayer->getLayerSize();

  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    tileInfo = mTileInfoVector.at(i);
    sp = tileInfo->getTile();
    
    if (!mIsScrolling && sp && sp->boundingBox().containsPoint(mBeginLocationToMap))
    {
      sound::playSoundFx(SFX_TOUCH_TILE);
      mCurTile = i;
      if (mTileInfoVector.at(mCurTile)->getHasTree())
      {
        if (GameManager::getNumOfAxes(GameManager::getCurrentPlayer()) > 0)
        {
          appearAxePop(tileInfo, sp);
        }
      }
      else if (mTileInfoVector.at(mCurTile)->getHasStone())
      {
        sound::playSoundFx(SFX_UHOH);
      }
      else
      {
        appearPops(tileInfo, sp);
      }
    }
  }
}

void PlayScene::moveMap(float offsetX, float offsetY)
{
  float posX = mTileMap->getPosition().x + offsetX;
  float posY = mTileMap->getPosition().y + offsetY;
  // uncomment it. So now, player can scroll very freelyyyyyyy
  
//  if (posX > 0)
//    posX = 0;
//  if (posX < getBound().x)
//    posX = getBound().x;
//  if (posY > 0)
//    posY = 0;
//  if (posY < getBound().y)
//  {
//    posY = getBound().y;
//  }
  mTileMap->setPosition(ccp(posX, posY));
}

CCPoint PlayScene::getBound()
{
  float mapWidth = mTileMap->getTileSize().width * mTileMap->getMapSize().width;
  float mapHeight = mTileMap->getTileSize().height * mTileMap->getMapSize().height;
  
  // should caculate the bounding of map position
  return ccp(mScreenSize.width - mapWidth, mScreenSize.height - mapHeight);
}

void PlayScene::chooseEdgeEnded(cocos2d::CCObject *pSender)
{
  sound::playSoundFx(SFX_TOUCH_POP);
  CCMenuItemSprite* pop = (CCMenuItemSprite*)pSender;
  pop->setVisible(false);
  CCSprite *edge = CCSprite::create("Images/Game/Object/edge.png");
  
  TileInfo *tileInfo = mTileInfoVector.at(mCurTile);

//  CCSprite *sp = tileInfo->getTile();
//  CCLog("curTile = %d", mCurTile);
  
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
//  CCLog("tileInfo->getNumberEdgeAvailale() = %d", tileInfo->getNumberEdgeAvailale());
  
  CCLog("Current Player is %i", GameManager::getCurrentPlayer());
  
  bool checkIncreasingScore = false;
  
  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    if (mTileInfoVector.at(i)->getNumberEdgeAvailale() == 0
        && mTileInfoVector.at(i)->getBelongToPlayer() == 0
        && mTileInfoVector.at(i)->getHasTree() == false
        && mTileInfoVector.at(i)->getHasStone() == false)
    {
      GameManager::increaseScore(GameManager::getCurrentPlayer());
      checkIncreasingScore = true;
//      sprintf(mScoreBuffer, "%i", GameManager::getPlayerScore(GameManager::getCurrentPlayer()));
      if (GameManager::getCurrentPlayer() == PLAYER_ONE)
      {
        mTileInfoVector.at(i)->setBelongToPlayer(1);
        addHouse("Images/Game/Object/blueHouse.png", i);
        mLbnScorePlayer1->setString(mScoreBuffer);
      }
      else
      {
        mTileInfoVector.at(i)->setBelongToPlayer(2);
        addHouse("Images/Game/Object/redHouse.png", i);
        mLbnScorePlayer2->setString(mScoreBuffer);
      }
      if (mTileInfoVector.at(i)->getHasAxe())
      {
        sound::playSoundFx(SFX_PICKUP_AXE);
        GameManager::increaseNumOfAxes(GameManager::getCurrentPlayer());
        CCLog("PlayScene: axe collected.......... should have animation!!!!");
        if (GameManager::getCurrentPlayer() == PLAYER_ONE)
          addAxeAnimation(PLAYER_ONE_POS, i);
        else
          addAxeAnimation(PLAYER_TWO_POS, i);
      }
    }
  }
  
  if (!checkIncreasingScore)
  {
    changePlayer();
  }
  removePopups();
}

void PlayScene::addAxeAnimation(cocos2d::CCPoint pPos, int pIndex)
{
  CCSprite* axe = CCSprite::create("Images/Game/Object/axe-02.png");
  axe->setPosition(mTileInfoVector.at(pIndex)->getTile()->getPosition()
                   + ccp(mTileInfoVector.at(pIndex)->getTile()->getContentSize().width/2,
                         mTileInfoVector.at(pIndex)->getTile()->getContentSize().height));
  axe->runAction(
   CCSequence::create(
    CCMoveBy::create(0.3f, ccp(0, 50)),
    CCFadeIn::create(0.3f),
    CCEaseBackOut::create(CCMoveTo::create(0.7f, pPos)),
    CCFadeOut::create(0.2),
    CCCallFuncN::create(this, callfuncN_selector(PlayScene::removeAxe)),
    NULL));
  mTileMap->addChild(axe, GR_FOREGROUND);
}

void PlayScene::removeAxe(cocos2d::CCObject *pSender)
{
  ((CCSprite*)pSender)->removeFromParent();
}

void PlayScene::addHouse(const char *pFileName, int pIndex)
{
  CCSprite* house = CCSprite::create(pFileName);
  house->setPosition(mTileInfoVector.at(pIndex)->getTile()->getPosition()
                     + ccp(mTileInfoVector.at(pIndex)->getTile()->getContentSize().width/2,
                           mTileInfoVector.at(pIndex)->getTile()->getContentSize().height/2 + 20));
//  house->setAnchorPoint(ccp(-0.5, -0.5));
  house->setScale(0.2f);
  house->runAction(CCSequence::create(
//                                    CCMoveBy::create(0.3f, ccp(0, -20)),
                                      CCScaleTo::create(0.2, 1.0f),
                                      NULL));
  mTileMap->addChild(house, GR_MIDDLEGROUND);
}

void PlayScene::changePlayer()
{
//  if (GameManager::getCurrentPlayer() == PLAYER_ONE)
//  {
////    mPlayerOneShadow->setVisible(false);
////    mPlayerTwoShadow->setVisible(true);
//    mTurnIndicatorLeft->setVisible(true);
//    
//  }
//  else
//  {
////    mPlayerTwoShadow->setVisible(false);
////    mPlayerOneShadow->setVisible(true);
//    addTurnIndicator(PLAYER_TWO_POS);
//  }
  mTurnIndicatorLeft->setVisible(!mTurnIndicatorLeft->isVisible());
  mTurnIndicatorRight->setVisible(!mTurnIndicatorRight->isVisible());
  GameManager::changeCurrentPlayer();
}

void PlayScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
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
  int nTileFull = GameManager::getPlayerScore(PLAYER_ONE)
                  + GameManager::getPlayerScore(PLAYER_TWO)
                  + GameManager::getNumOfStones();
  if (GameManager::getNumOfAxes(GameManager::getCurrentPlayer()) == 0
      && (nTileFull + GameManager::getNumOfTrees() == mTileInfoVector.size()))
  {
    this->changePlayer();
    CCLOG("PlayScene: dead state.............. should have a popup to warning player!!!");
  }
  sprintf(mScoreBuffer,
          "  %i      %i",
          GameManager::getPlayerScore(PLAYER_ONE),
          GameManager::getNumOfAxes(PLAYER_ONE));
  mLbnScorePlayer1->setString(
    CCString::createWithFormat("  %i      %i",
                               GameManager::getPlayerScore(PLAYER_ONE),
                               GameManager::getNumOfAxes(PLAYER_ONE))->getCString());
  
  sprintf(mScoreBuffer,
          "%i      %i",
          GameManager::getNumOfAxes(PLAYER_TWO),
          GameManager::getPlayerScore(PLAYER_TWO));
  mLbnScorePlayer2->setString(
    CCString::createWithFormat("%i      %i",
                               GameManager::getNumOfAxes(PLAYER_TWO),
                               GameManager::getPlayerScore(PLAYER_TWO))->getCString());
  
  if (nTileFull == mTileInfoVector.size())
  {
    eCurrentPlayer winPlayer =
      GameManager::getPlayerScore(PLAYER_ONE) > GameManager::getPlayerScore(PLAYER_TWO) ? PLAYER_ONE : PLAYER_TWO;
    unscheduleUpdate();
    unschedule(schedule_selector(PlayScene::cooldown));
    GameManager::setWinPlayer(winPlayer);
    CCScene* newScene = CCTransitionCrossFade::create(0.5, WinScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
  }

}

void PlayScene::addBottomEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge)
{
  CCSprite *sp = pTileInfo->getTile();
  pTileInfo->setHasBottomPop(true);
  
  pEdge->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width/2, sp->getPositionY()));
  pEdge->setScale(0.1f);
  pEdge->runAction(CCScaleTo::create(0.1, 1.2f));
  mTileMap->addChild(pEdge, GR_MIDDLEGROUND);
  pTileInfo->setEdgeBottomStatus(STS_NOT_AVAILABLE);
  
  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    if (mTileInfoVector.at(i)->getGID() == pTileInfo->getGIDTileDown())
    {
      mTileInfoVector.at(i)->setHasTopPop(true);
      mTileInfoVector.at(i)->setEdgeTopStatus(STS_NOT_AVAILABLE);
      mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
    }
  }
}

void PlayScene::addTopEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge)
{
  CCSprite *tileSprite = pTileInfo->getTile();
  pTileInfo->setHasTopPop(true);
  
  pEdge->setPosition(ccp(tileSprite->getPositionX() + tileSprite->getContentSize().width/2,
                         tileSprite->getPositionY() + tileSprite->getContentSize().height));
  pEdge->setScale(0.1f);
  pEdge->runAction(CCScaleTo::create(0.1, 1.2f));

  mTileMap->addChild(pEdge, GR_MIDDLEGROUND);
  pTileInfo->setEdgeTopStatus(STS_NOT_AVAILABLE);
  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    if (mTileInfoVector.at(i)->getGID() == pTileInfo->getGIDTileUp())
    {
      mTileInfoVector.at(i)->setHasBottomPop(true);
      mTileInfoVector.at(i)->setEdgeBottomStatus(STS_NOT_AVAILABLE);
      mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
    }
  }
}

void PlayScene::addLeftEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge)
{
  CCSprite *tileSprite = pTileInfo->getTile();
  pTileInfo->setHasLeftPop(true);
  
  pEdge->setRotation(90);
  pEdge->setPosition(ccp(tileSprite->getPositionX(),
                         tileSprite->getPositionY() + tileSprite->getContentSize().height/2));
  pEdge->setScale(0.1f);
  pEdge->runAction(CCScaleTo::create(0.1, 1.2f));

  mTileMap->addChild(pEdge, GR_MIDDLEGROUND);
  pTileInfo->setEdgeLeftStatus(STS_NOT_AVAILABLE);
  
  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    if (mTileInfoVector.at(i)->getGID() == pTileInfo->getGIDTileLeft())
    {
      mTileInfoVector.at(i)->setHasRightPop(true);
      mTileInfoVector.at(i)->setEdgeRightStatus(STS_NOT_AVAILABLE);
      mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
    }
  }
}

void PlayScene::addRightEdge(TileInfo *pTileInfo, cocos2d::CCSprite *pEdge)
{
  CCSprite *tileSprite = pTileInfo->getTile();
  pTileInfo->setHasRightPop(true);
  
  pEdge->setRotation(90);
  pEdge->setPosition(ccp(tileSprite->getPositionX() + tileSprite->getContentSize().width,
                         tileSprite->getPositionY() + tileSprite->getContentSize().height/2));
  pEdge->setScale(0.1f);
  pEdge->runAction(CCScaleTo::create(0.1, 1.2f));

  mTileMap->addChild(pEdge, GR_MIDDLEGROUND);
  pTileInfo->setEdgeRightStatus(STS_NOT_AVAILABLE);
  
  for (int i = 0; i < mTileInfoVector.size(); ++i)
  {
    if (mTileInfoVector.at(i)->getGID() == pTileInfo->getGIDTileRight())
    {
      mTileInfoVector.at(i)->setHasLeftPop(true);
      mTileInfoVector.at(i)->setEdgeLeftStatus(STS_NOT_AVAILABLE);
      mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
    }
  }
}

void PlayScene::appearPops(TileInfo* pTileInfo, cocos2d::CCSprite *pSp)
{
  if (pTileInfo->getEdgeBottomStatus() == STS_AVAILABLE && !pTileInfo->getHasBottomPop())
  {
    appearBottomPop(pTileInfo, pSp);
  }
  if (pTileInfo->getEdgeTopStatus() == STS_AVAILABLE && !pTileInfo->getHasTopPop())
  {
    appearTopPop(pTileInfo, pSp);
  }
  if (pTileInfo->getEdgeLeftStatus() == STS_AVAILABLE && !pTileInfo->getHasLeftPop())
  {
    appearLeftPop(pTileInfo, pSp);
  }
  if (pTileInfo->getEdgeRightStatus() == STS_AVAILABLE && !pTileInfo->getHasRightPop())
  {
    appearRightPop(pTileInfo, pSp);
  }
}

void PlayScene::appearBottomPop(TileInfo *pTileInfo, cocos2d::CCSprite *pTileSprite)
{
  CCSprite* pop = CCSprite::create("Images/Game/UI/pointer_bottom.png");
  CCMenuItemSprite* item =
    CCMenuItemSprite::create(pop,
                             pop,
                             this,
                             menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_BOTTOM);
  edgePop->setPosition(ccp(pTileSprite->getPositionX() + pTileSprite->getContentSize().width/2,
                           pTileSprite->getPositionY()));
  edgePop->runAction(CCMoveBy::create(0.05f, ccp(0, -pTileSprite->getContentSize().height/2 - 4)));
  mTileMap->addChild(edgePop, GR_FOREGROUND);
}

void PlayScene::appearTopPop(TileInfo *pTileInfo, cocos2d::CCSprite *pTileSprite)
{
  CCSprite* pop = CCSprite::create("Images/Game/UI/pointer_top.png");
  CCMenuItemSprite* item =
    CCMenuItemSprite::create(pop,
                             pop,
                             this,
                             menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_TOP);
  edgePop->setPosition(ccp(pTileSprite->getPositionX() + pTileSprite->getContentSize().width/2,
                           pTileSprite->getPositionY() + pTileSprite->getContentSize().height));
  edgePop->runAction(CCMoveBy::create(0.05f, ccp(0, pTileSprite->getContentSize().height/2)));
  mTileMap->addChild(edgePop, GR_FOREGROUND);
}

void PlayScene::appearLeftPop(TileInfo *pTileInfo, cocos2d::CCSprite *pTileSprite)
{
  CCSprite* pop = CCSprite::create("Images/Game/UI/pointer_left.png");
  CCMenuItemSprite* item =
    CCMenuItemSprite::create(pop,
                             pop,
                             this,
                             menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_LEFT);
  edgePop->setPosition(ccp(pTileSprite->getPositionX(),
                           pTileSprite->getPositionY() + pTileSprite->getContentSize().height/2));
  edgePop->runAction(CCMoveBy::create(0.05f, ccp(-pTileSprite->getContentSize().width/2 - 8, 0)));
  mTileMap->addChild(edgePop, GR_FOREGROUND);
}

void PlayScene::appearRightPop(TileInfo *pTileInfo, cocos2d::CCSprite *pTileSprite)
{
  CCSprite* pop = CCSprite::create("Images/Game/UI/pointer_right.png");
  CCMenuItemSprite* item =
    CCMenuItemSprite::create(pop,
                             pop,
                             this,
                             menu_selector(PlayScene::chooseEdgeEnded));
  mPopsArr->addObject(item);
  CCMenu *edgePop = CCMenu::create(item, NULL);
  item->setTag(TAG_EDGE_RIGHT);
  edgePop->setPosition(ccp(pTileSprite->getPositionX() + pTileSprite->getContentSize().width,
                           pTileSprite->getPositionY() + pTileSprite->getContentSize().height/2));
  edgePop->runAction(CCMoveBy::create(0.05f, ccp(pTileSprite->getContentSize().width/2, 0)));
  mTileMap->addChild(edgePop, GR_FOREGROUND);
}

void PlayScene::removePopups()
{
  for (int i = 0; i < mPopsArr->count(); ++i)
  {
    ((CCMenuItemSprite*)mPopsArr->objectAtIndex(i))->removeFromParent();
//    CCLog("remove %d", i);
  }
  mPopsArr->removeAllObjects();
}

void PlayScene::addTrees()
{
  int numberOfTrees = RANDOM_NUMBER_OF_TREES;
  mTreesArr = CCArray::createWithCapacity(numberOfTrees);
  mTreesArr->retain();
//  CCLog("Number of Trees is %i", numberOfTrees);
  GameManager::setNumOfTrees(numberOfTrees);
  srand(time(NULL));
  for (int i = 0; i < numberOfTrees; i++)
  {
    int indexOfTileToAddTree;
    do
    {
      indexOfTileToAddTree = rand() % mTileInfoVector.size();
    } while (mTileInfoVector.at(indexOfTileToAddTree)->getHasTree());
//    CCLog("Tile at %i has a tree", indexOfTileToAddTree);
    mTileInfoVector.at(indexOfTileToAddTree)->setHasTree(true);
    mTileInfoVector.at(indexOfTileToAddTree)->setHasItem(true);
    
    CCSprite* tree = CCSprite::create("Images/Game/Object/tree.png");
    mTreesArr->addObject(tree);
    tree->setTag(indexOfTileToAddTree);
    tree->setPosition(ccp(mTileInfoVector.at(indexOfTileToAddTree)->getTile()->getPositionX()
                          + mTileInfoVector.at(indexOfTileToAddTree)->getTile()->getContentSize().width/2,
                          mTileInfoVector.at(indexOfTileToAddTree)->getTile()->getPositionY()
                          + mTileInfoVector.at(indexOfTileToAddTree)->getTile()->getContentSize().height/2
                          + tree->getContentSize().height/4));
    mTileMap->addChild(tree, GR_FOREGROUND);
  }
}

void PlayScene::addAxes()
{
  int numOfAxes = GameManager::getNumOfTrees();
//  CCLog("Number of Axes is %i", numOfAxes);
  GameManager::setNumOfTrees(numOfAxes);
  srand(time(NULL));
  for (int i = 0; i < numOfAxes; i++)
  {
    int indexOfTileToAddAxe;
    do
    {
      indexOfTileToAddAxe = rand() % mTileInfoVector.size();
    } while (mTileInfoVector.at(indexOfTileToAddAxe)->getHasItem());
//    CCLog("Tile at %i has a axe", indexOfTileToAddAxe);
    mTileInfoVector.at(indexOfTileToAddAxe)->setHasAxe(true);
    mTileInfoVector.at(indexOfTileToAddAxe)->setHasItem(true);
//    mTileInfoVector.at(indexOfTileToAddAxe)->getTile()->setColor(ccBLACK);
  }
}

void PlayScene::addStones()
{
  int numOfStones = rand() % 4 + 3;
  if (mTileInfoVector.size() % 2 == numOfStones % 2)
  {
    numOfStones++;
  }
  GameManager::setNumOfStones(numOfStones);
  srand(time(NULL));
  for (int i = 0; i < numOfStones; i++)
  {
    int indexOfTileToAddStone;
    do
    {
      indexOfTileToAddStone = rand() % mTileInfoVector.size();
    } while (mTileInfoVector.at(indexOfTileToAddStone)->getHasItem());
//    CCLog("Tile at %i has a stone", indexOfTileToAddStone);
    mTileInfoVector.at(indexOfTileToAddStone)->setHasStone(true);
    mTileInfoVector.at(indexOfTileToAddStone)->setHasItem(true);
    
    CCSprite* stone = CCSprite::create("Images/Game/Object/stone.png");
    stone->setTag(indexOfTileToAddStone);
    stone->setPosition(ccp(mTileInfoVector.at(indexOfTileToAddStone)->getTile()->getPositionX()
                           + mTileInfoVector.at(indexOfTileToAddStone)->getTile()->getContentSize().width/2,
                           mTileInfoVector.at(indexOfTileToAddStone)->getTile()->getPositionY()
                           + mTileInfoVector.at(indexOfTileToAddStone)->getTile()->getContentSize().height/2));
    mTileMap->addChild(stone, GR_MIDDLEGROUND);
    
    for (int i = 0; i < mTileInfoVector.size(); ++i)
    {
      if (mTileInfoVector.at(i)->getGID() ==
          mTileInfoVector.at(indexOfTileToAddStone)->getGIDTileLeft())
      {
        mTileInfoVector.at(i)->setHasRightPop(true);
        mTileInfoVector.at(i)->setEdgeRightStatus(STS_NOT_AVAILABLE);
        mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
      else if (mTileInfoVector.at(i)->getGID() ==
               mTileInfoVector.at(indexOfTileToAddStone)->getGIDTileRight())
      {
        mTileInfoVector.at(i)->setHasLeftPop(true);
        mTileInfoVector.at(i)->setEdgeLeftStatus(STS_NOT_AVAILABLE);
        mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
      else if (mTileInfoVector.at(i)->getGID() ==
               mTileInfoVector.at(indexOfTileToAddStone)->getGIDTileUp())
      {
        mTileInfoVector.at(i)->setHasBottomPop(true);
        mTileInfoVector.at(i)->setEdgeBottomStatus(STS_NOT_AVAILABLE);
        mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
      else if (mTileInfoVector.at(i)->getGID() ==
               mTileInfoVector.at(indexOfTileToAddStone)->getGIDTileDown())
      {
        mTileInfoVector.at(i)->setHasTopPop(true);
        mTileInfoVector.at(i)->setEdgeTopStatus(STS_NOT_AVAILABLE);
        mTileInfoVector.at(i)->setNumberEdgeAvailale(mTileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
    }
  }
}

void PlayScene::appearAxePop(TileInfo *pTileInfo, cocos2d::CCSprite *pTileSprite)
{
  CCSprite* pop = CCSprite::create("Images/Game/Object/axe-02.png");
  mAxePop = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseAxeEnded));
  CCMenu *axePop = CCMenu::create(mAxePop, NULL);
  axePop->setPosition(ccp(pTileSprite->getPositionX()
                          + pTileSprite->getContentSize().width/2,
                          pTileSprite->getPositionY()
                          + pTileSprite->getContentSize().height
                          + pop->getContentSize().height/2));
  mTileMap->addChild(axePop, GR_FOREGROUND);
  mIsAxePopVisible = true;
}

void PlayScene::chooseAxeEnded(cocos2d::CCObject *pSender)
{
  sound::playSoundFx(SFX_TOUCH_POP);
  CCMenuItemSprite* pop = (CCMenuItemSprite*)pSender;
  pop->setVisible(false);
  mIsAxePopVisible = false;
  GameManager::decreaseNumOfAxes(GameManager::getCurrentPlayer());
  mTileInfoVector.at(mCurTile)->setHasTree(false);
  removeTree();
  
  if (mTileInfoVector.at(mCurTile)->getNumberEdgeAvailale() == 0)
  {
    mTileInfoVector.at(mCurTile)->setBelongToPlayer(GameManager::getCurrentPlayer());
    GameManager::increaseScore(GameManager::getCurrentPlayer());
//    sprintf(mScoreBuffer, "%i", GameManager::getPlayerScore(GameManager::getCurrentPlayer()));
    if (GameManager::getCurrentPlayer() == PLAYER_ONE)
    {
      addHouse("Images/Game/Object/blueHouse.png", mCurTile);
      mLbnScorePlayer1->setString(mScoreBuffer);
    }
    else
    {
      addHouse("Images/Game/Object/redHouse.png", mCurTile);
      mLbnScorePlayer2->setString(mScoreBuffer);
    }
  }
}

void PlayScene::removeTree()
{
  sound::playSoundFx(SFX_CUT_TREE);
  for (int i = 0; i < mTreesArr->count(); i++)
  {
    CCSprite* tree = (CCSprite*) mTreesArr->objectAtIndex(i);
    if (tree->getTag() == mCurTile)
    {
      tree->setVisible(false);
      mTreesArr->removeObjectAtIndex(i);
    }
  }
  GameManager::setNumOfTrees(GameManager::getNumOfTrees() - 1);
}

CCLayer* PlayScene::setupRemindLayer(const char* pFileName,
                                 cocos2d::CCPoint pPos,
                                 const char* pContent,
                                 cocos2d::ccColor3B pColor)
{
  CCLayer* Reminder = CCLayer::create();
  CCSprite* btn = CCSprite::create(pFileName);
  CCMenuItemSprite* item =
    CCMenuItemSprite::create(btn,
                             btn,
                             this,
                             menu_selector(PlayScene::onResume));
  item->setPosition(pPos);
  CCMenu* menu = CCMenu::create(item, NULL);
  Reminder->addChild(menu);
  Reminder->setVisible(false);
  menu->setPosition(CCPointZero);
  this->addChild(Reminder, GR_FOREGROUND);
  
  CCLabelTTF* label = CCLabelTTF::create(pContent, "fonts/Marker Felt.ttf", 48);
  label->setHorizontalAlignment(kCCTextAlignmentLeft);
  label->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
  label->setColor(pColor);
  label->setPosition(pPos + ccp(0, 35));
  Reminder->addChild(label, GR_FOREGROUND);
  return Reminder;
}

void PlayScene::onResume(cocos2d::CCObject* pSender)
{
  sound::playSoundFx(SFX_BUTTON_TOUCH);
//  mReminder->setVisible(false);
  mRemindLayerLeft->setVisible(false);
  mRemindLayerRight->setVisible(false);
  setCooldownTime(100.0);
  CCDirector::sharedDirector()->resume();
}

void PlayScene::cooldown()
{
  float now = getCooldownTime();
//  CCLog("%f", now);
  setCooldownTime(now - 0.3);
  if (now <= 0)
  {
//    mReminder->setVisible(true);
    if (GameManager::getCurrentPlayer() == PLAYER_ONE)
    {
      mRemindLayerRight->setVisible(true);
      mRemindLayerLeft->setVisible(false);
    }
    else
    {
      mRemindLayerRight->setVisible(false);
      mRemindLayerLeft->setVisible(true);
    }
    CCDirector::sharedDirector()->pause();
  }
}

void PlayScene::changeScene(cocos2d::CCObject *pData)
{
  CCDirector::sharedDirector()->replaceScene((CCTransitionScene*)pData);
}

void PlayScene::addPausedLayer()
{
  mPausedLayer = CCLayer::create();
  CCSprite* pausedTitle = CCSprite::create("Images/Game/UI/paused_title.png");
  pausedTitle->setPosition(PAUSED_TITLE_POS);
  mPausedLayer->addChild(pausedTitle);
  
  CCSprite* btn = CCSprite::create("Images/Game/UI/paused_resume.png");
  CCMenuItemSprite* paused =
  CCMenuItemSprite::create(btn,
                           btn,
                           this,
                           menu_selector(PlayScene::resumeButtonTouched));
  CCMenu* menu = CCMenu::create(paused, NULL);
  menu->setPosition(PAUSED_RESUME_POS);
  mPausedLayer->addChild(menu);
  
  btn = CCSprite::create("Images/Game/UI/paused_option.png");
  paused = CCMenuItemSprite::create(btn,
                           btn,
                           this,
                           menu_selector(PlayScene::optionButtonTouched));
  menu = CCMenu::create(paused, NULL);
  menu->setPosition(PAUSED_OPTION_POS);
  mPausedLayer->addChild(menu);
  
  btn = CCSprite::create("Images/Game/UI/paused_replay.png");
  paused = CCMenuItemSprite::create(btn,
                                    btn,
                                    this,
                                    menu_selector(PlayScene::replayButtonTouched));
  menu = CCMenu::create(paused, NULL);
  menu->setPosition(PAUSED_REPLAY_POS);
  mPausedLayer->addChild(menu);
  
  mPausedLayer->setVisible(false);
  this->addChild(mPausedLayer, 6);
}

void PlayScene::resumeButtonTouched(cocos2d::CCObject* pSender)
{
  CREATE_MENU_ITEM_NO_CHANGE_SCENE();
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  mPausedLayer->setVisible(false);
  mTileMap->setVisible(true);
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  setCooldownTime(100.0);
  schedule(schedule_selector(PlayScene::cooldown));
  CCDirector::sharedDirector()->resume();
}

void PlayScene::optionButtonTouched(cocos2d::CCObject* pSender)
{
  CREATE_MENU_ITEM_NO_CHANGE_SCENE();
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  unscheduleUpdate();
  unschedule(schedule_selector(PlayScene::cooldown));
  CCScene* newScene = CCTransitionFade::create(0.5, SettingScene::scene());
  CCDirector::sharedDirector()->pushScene(newScene);
  CCDirector::sharedDirector()->resume();
}

void PlayScene::replayButtonTouched(cocos2d::CCObject* pSender)
{
  CREATE_MENU_ITEM_NO_CHANGE_SCENE();
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  unscheduleUpdate();
  unschedule(schedule_selector(PlayScene::cooldown));
  CCScene* newScene = CCTransitionFade::create(0.5, ChooseMapScene::scene());
  CCDirector::sharedDirector()->replaceScene(newScene);
  CCDirector::sharedDirector()->resume();
}

CCSprite* PlayScene::createTurnIndicator(CCPoint pPos)
{
  CCSprite* turnIndicator = CCSprite::create("Images/Game/Object/turn_idicator.png");
  turnIndicator->setPosition(pPos + ccp(0, 180));
  turnIndicator->runAction(CCFlipX::create(true));
  turnIndicator->setVisible(false);
  this->addChild(turnIndicator, GR_FOREGROUND, TAG_TURN_INDICATOR);
  return turnIndicator;
}
