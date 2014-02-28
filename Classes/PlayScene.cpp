//
//  PlayScene.cpp
//  landlord
//
//  Created by Giap Nguyen on 2/24/14.
//
//

#include "PlayScene.h"

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
  
  screenSize = CCDirector::sharedDirector()->getWinSize();
  
  addPlayGroud();
  makeMapScroll();
  addFrameImg();
  addPauseButton();
  addPLayerOne();
  addPlayerTwo();
  addScoreLbn();
  
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
  ground->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  addChild(ground);
}

void PlayScene::addPLayerOne()
{
  playerOneTag = 1; // get from ChoosePlayerScene or GameManager
  CCSprite *playerOne = CCSprite::create((CCString::createWithFormat("PlayScene/c%i.png", playerOneTag))->getCString());
  playerOne->setScale(0.8f);
  playerOne->setPosition(PLAYER_ONE_POS);
  this->addChild(playerOne);
}

void PlayScene::addPlayerTwo()
{
  playerTwoTag = 3; // get from ChoosePlayerScene or GameManager
  CCSprite *playerTwo = CCSprite::create((CCString::createWithFormat("PlayScene/c%i.png", playerTwoTag))->getCString());
  playerTwo->setScale(0.8f);
  playerTwo->setPosition(PLAYER_TWO_POS);
  this->addChild(playerTwo);
}

void PlayScene::makeMapScroll()
{
  CCLayerColor *layer = CCLayerColor::create();
  layer->setContentSize(screenSize);
//  layer->setColor(ccRED);
//  layer->setPosition(CCPointMake(screenSize.width/2, screenSize.height/2));
//  addChild(layer);
  
  CCSprite *sp = CCSprite::create("PlayScene/map1.png");
  sp->setPosition(MAP_POS);
//
//  //  layer->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  layer->addChild(sp);
//  layer->setPosition(MAP_POS);
  scrollMap = CCScrollView::create(screenSize, layer);
  
//  scrollMap->setDirection(kCCScrollViewDirectionBoth);
////  scrollMap->setContentOffset(ccp(1136, 1135));
//  scrollMap->setBounceable(true);
////  scrollMap->setAnchorPoint(ccp(0.5, 0.5));
//  CCLog("%.0f %.0f", sp->getContentSize().width, sp->getContentSize().height);
//  scrollMap->setContentSize(sp->getContentSize());
  
  this->addChild(scrollMap);
//  tileMap = CCTMXTiledMap::create("PlayScene/map01.tmx");
//  addChild(tileMap);
//  tileMap->layerNamed("map1");

  
}

void PlayScene::addScoreLbn()
{
  CCSprite* scoreP1 = CCSprite::create("PlayScene/scoreP1.png");
  scoreP1->setPosition(LBN_SCORE_PLAYER1_POS);
  lbnScorePlayer1 = CCLabelTTF::create("0", "ordin", 50);
  lbnScorePlayer1->setHorizontalAlignment(kCCTextAlignmentCenter);
  lbnScorePlayer1->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
  lbnScorePlayer1->setColor(ccRED);
  lbnScorePlayer1->setPosition(ccp(scoreP1->getPositionX()+scoreP1->getContentSize().width/2, scoreP1->getPositionY()));
//  scoreP1->addChild(lbnScorePlayer1);
  this->addChild(scoreP1);
  
  CCSprite* scoreP2 = CCSprite::create("PlayScene/scoreP2.png");
  scoreP2->setPosition(LBN_SCORE_PLAYER2_POS);
  lbnScorePlayer2 = CCLabelTTF::create("0", "ordin", 50);
  lbnScorePlayer2->setHorizontalAlignment(kCCTextAlignmentCenter);
  lbnScorePlayer2->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
  lbnScorePlayer2->setColor(ccRED);
  lbnScorePlayer2->setPosition(ccp(scoreP2->getPositionX()+scoreP2->getContentSize().width/2, scoreP2->getPositionY()));
//  scoreP2->addChild(lbnScorePlayer2);
  this->addChild(scoreP2);
  
}

void PlayScene::pauseButtonTouched()
{
  CCLog("paused touched");
}

void PlayScene::addFrameImg()
{
  CCSprite *frame = CCSprite::create("PlayScene/frame-01.png");
  frame->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  addChild(frame);
}
