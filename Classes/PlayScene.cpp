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
#include "SimpleAI.h"

USING_NS_CC;
USING_NS_CC_EXT;

std::vector<TileInfo*> PlayScene::tileInfoVector;

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
  setTouchEnabled(true);
  
//  addPlayGroud();
  makeMapScroll();
//  tilesArr->retain();
//  addFrameImg();
//  addPauseButton();
//  addPLayerOne();
//  addPlayerTwo();
//  addScoreLbn();
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
  ground->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  addChild(ground);
}

void PlayScene::addPLayerOne()
{
  playerOneTag = GameManager::getPlayerOneID();
  CCLog("getPlayerOneID = %d", GameManager::getPlayerOneID());
  CCSprite *playerOne = CCSprite::create((CCString::createWithFormat("PlayScene/c%i.png", playerOneTag))->getCString());
  playerOne->setScale(0.8f);
  playerOne->setPosition(PLAYER_ONE_POS);
  this->addChild(playerOne);
}

void PlayScene::addPlayerTwo()
{
  playerTwoTag = GameManager::getPlayerTwoID();
  CCSprite *playerTwo = CCSprite::create((CCString::createWithFormat("PlayScene/c%i.png", playerTwoTag))->getCString());
  playerTwo->setScale(0.8f);
  playerTwo->setPosition(PLAYER_TWO_POS);
  this->addChild(playerTwo);
}

void PlayScene::makeMapScroll()
{
  tileMap = CCTMXTiledMap::create("PlayScene/map01.tmx");

  this->addChild(tileMap);

  tileMap->setPosition(ccp(0, 0));
  mapLayer = tileMap->layerNamed("map01");
  
  CCSize s = mapLayer->getLayerSize();
  CCSprite* tile = CCSprite::create();
  popsArr = CCArray::createWithCapacity(NUMBER_EDGE_AVAILABLE);
  popsArr->retain();

  for (int i = 0; i < s.width; ++i)
  {
    for (int j = 0; j < s.height; ++j)
    {
      tile = mapLayer->tileAt(ccp(i, j));
      if (!tile);
//        CCLog("tile is null");
      else
      {
        TileInfo *tileInfo = new TileInfo();
        tileInfo->setTile(tile);
        tileInfo->setGID(PAIR_FUNC(i, j));
        CCLog("gid %d", PAIR_FUNC(i, j));
        tileInfoVector.push_back(tileInfo);
        tileInfo->setGridX(i);
        tileInfo->setGridY(j);
      
        if (j > 0 && mapLayer->tileAt(ccp(i, j-1)))
        {
          tileInfo->setGIDTileUp(PAIR_FUNC(i, j-1));
        }
        
        if (j < s.height-1 && mapLayer->tileAt(ccp(i, j+1)))
        {
          tileInfo->setGIDTileDown(PAIR_FUNC(i, j+1));
        }

        if (i > 0 && mapLayer->tileAt(ccp(i-1, j)))
        {
          tileInfo->setGIDTileLeft(PAIR_FUNC(i-1, j));
        }

        if (i < s.width-1 && mapLayer->tileAt(ccp(i+1, j)))
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
  CCScene* newScene = CCTransitionSlideInR::create(0.5, WinScene::scene());
  CCDirector::sharedDirector()->replaceScene(newScene);
}

void PlayScene::addFrameImg()
{
  CCSprite *frame = CCSprite::create("PlayScene/frame-01.png");
  frame->setPosition(ccp(screenSize.width/2, screenSize.height/2));
  addChild(frame);
}

bool PlayScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  mIsScrolling = false;
  
  beginLocation = pTouch->getLocation();
  beginLocation = this->convertToNodeSpace(beginLocation);
  beginLocationToMap = tileMap->convertToNodeSpace(beginLocation);
  
  return true;
}

void PlayScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  mIsScrolling = true;
  
  CCPoint touchLocation = pTouch->getLocation();
  touchLocation = this->convertToNodeSpace(touchLocation);
  CCPoint touchLocationToMap = tileMap->convertToNodeSpace(touchLocation);
  
  float offsetX = touchLocation.x - beginLocation.x;
  float offsetY = touchLocation.y - beginLocation.y;
  moveMap(offsetX, offsetY);

  beginLocation = touchLocation;
  beginLocationToMap = touchLocationToMap;
}

void PlayScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
  if (popsArr->count() > 0)
  {
    for (int i = 0; i < popsArr->count(); ++i)
    {
      ((CCMenuItemSprite*)popsArr->objectAtIndex(i))->removeFromParent();
      CCLog("remove %d", i);
    }
    popsArr->removeAllObjects();
  }
  TileInfo *tileInfo = new TileInfo();
  CCSprite *sp = CCSprite::create();
//  CCSize s = mapLayer->getLayerSize();

  for (int i = 0; i < tileInfoVector.size(); ++i)
  {
    tileInfo = tileInfoVector.at(i);
    sp = tileInfo->getTile();
    
    if (!mIsScrolling && sp && sp->boundingBox().containsPoint(beginLocationToMap))
    {
      curTile = i;
      if (tileInfo->getEdgeBottomSts() == STS_AVAILABLE && !tileInfo->getHasBottomPop())
      {
        CCSprite* pop = CCSprite::create("PlayScene/button-pause.png");
        CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
        popsArr->addObject(item);
        CCMenu *edgePop = CCMenu::create(item, NULL);
        item->setTag(TAG_EDGE_BOTTOM);
        edgePop->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width/2, sp->getPositionY() - pop->getContentSize().height/2));
        tileMap->addChild(edgePop);
      }
      if (tileInfo->getEdgeTopSts() == STS_AVAILABLE && !tileInfo->getHasTopPop())
      {
        CCSprite* pop = CCSprite::create("PlayScene/button-pause.png");
        CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
        popsArr->addObject(item);
        CCMenu *edgePop = CCMenu::create(item, NULL);
        item->setTag(TAG_EDGE_TOP);
        edgePop->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width/2, sp->getPositionY() + sp->getContentSize().height + pop->getContentSize().height/2));
        tileMap->addChild(edgePop);
      }
      if (tileInfo->getEdgeLeftSts() == STS_AVAILABLE && !tileInfo->getHasLeftPop())
      {
        CCSprite* pop = CCSprite::create("PlayScene/button-pause.png");
        CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
        popsArr->addObject(item);
        CCMenu *edgePop = CCMenu::create(item, NULL);
        item->setTag(TAG_EDGE_LEFT);
        edgePop->setPosition(ccp(sp->getPositionX() - pop->getContentSize().width/2, sp->getPositionY() + sp->getContentSize().height/2));
        tileMap->addChild(edgePop);
      }
      if (tileInfo->getEdgeRightSts() == STS_AVAILABLE && !tileInfo->getHasRightPop())
      {
        CCSprite* pop = CCSprite::create("PlayScene/button-pause.png");
        CCMenuItemSprite* item = CCMenuItemSprite::create(pop, pop, this, menu_selector(PlayScene::chooseEdgeEnded));
        popsArr->addObject(item);
        CCMenu *edgePop = CCMenu::create(item, NULL);
        item->setTag(TAG_EDGE_RIGHT);
        edgePop->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width + pop->getContentSize().width/2, sp->getPositionY() + sp->getContentSize().height/2));
        tileMap->addChild(edgePop);
      }
    }
  }
}

void PlayScene::chooseEdgeEnded(cocos2d::CCObject *pSender)
{
  CCMenuItemSprite* pop = (CCMenuItemSprite*)pSender;
  pop->setVisible(false);
  CCSprite *edge = CCSprite::create("PlayScene/edge.png");
  
  TileInfo *tileInfo = tileInfoVector.at(curTile);

  CCSprite *sp = tileInfo->getTile();
  CCLog("curTile = %d", curTile);
  
  if (pop->getTag() == TAG_EDGE_BOTTOM)
  {
    tileInfo->setHasBottomPop(true);
    
    edge->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width/2, sp->getPositionY()));

    tileMap->addChild(edge, GR_FOREGROUND);
    tileInfo->setEdgeBottomSts(STS_NOT_AVAILABLE);
    
    for (int i = 0; i < tileInfoVector.size(); ++i)
    {
      if (tileInfoVector.at(i)->getGID() == tileInfo->getGIDTileDown())
      {
        tileInfoVector.at(i)->setHasTopPop(true);
        tileInfoVector.at(i)->setEdgeTopSts(STS_NOT_AVAILABLE);
        tileInfoVector.at(i)->setNumberEdgeAvailale(tileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
    }
  }
  else if (pop->getTag() == TAG_EDGE_TOP)
  {
    tileInfo->setHasTopPop(true);
    
    edge->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width/2, sp->getPositionY() + sp->getContentSize().height));

    tileMap->addChild(edge, GR_FOREGROUND);
    tileInfo->setEdgeTopSts(STS_NOT_AVAILABLE);
    for (int i = 0; i < tileInfoVector.size(); ++i)
    {
      if (tileInfoVector.at(i)->getGID() == tileInfo->getGIDTileUp())
      {
        tileInfoVector.at(i)->setHasBottomPop(true);
        tileInfoVector.at(i)->setEdgeBottomSts(STS_NOT_AVAILABLE);
        tileInfoVector.at(i)->setNumberEdgeAvailale(tileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
    }
  }
  else if (pop->getTag() == TAG_EDGE_LEFT)
  {
    tileInfo->setHasLeftPop(true);
    
    edge->setRotation(90);
    edge->setPosition(ccp(sp->getPositionX(), sp->getPositionY() + sp->getContentSize().height/2));

    tileMap->addChild(edge, GR_FOREGROUND);
    tileInfo->setEdgeLeftSts(STS_NOT_AVAILABLE);
    
    for (int i = 0; i < tileInfoVector.size(); ++i)
    {
      if (tileInfoVector.at(i)->getGID() == tileInfo->getGIDTileLeft())
      {
        tileInfoVector.at(i)->setHasRightPop(true);
        tileInfoVector.at(i)->setEdgeRightSts(STS_NOT_AVAILABLE);
        tileInfoVector.at(i)->setNumberEdgeAvailale(tileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
    }
  }
  else if (pop->getTag() == TAG_EDGE_RIGHT )
  {
    tileInfo->setHasRightPop(true);
    
    edge->setRotation(90);
    edge->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width, sp->getPositionY() + sp->getContentSize().height/2));

    tileMap->addChild(edge, GR_FOREGROUND);
    tileInfo->setEdgeRightSts(STS_NOT_AVAILABLE);
    
    for (int i = 0; i < tileInfoVector.size(); ++i)
    {
      if (tileInfoVector.at(i)->getGID() == tileInfo->getGIDTileRight())
      {
        tileInfoVector.at(i)->setHasLeftPop(true);
        tileInfoVector.at(i)->setEdgeLeftSts(STS_NOT_AVAILABLE);
        tileInfoVector.at(i)->setNumberEdgeAvailale(tileInfoVector.at(i)->getNumberEdgeAvailale()-1);
      }
    }
  }
  tileInfo->setNumberEdgeAvailale(tileInfo->getNumberEdgeAvailale()-1);
  
  //Run Simple AI if needed
//  if(tileInfo->getNumberEdgeAvailale() == 0)
//  {
//    SimpleAI::Breath_First_Search(tileInfo->getGridX(), tileInfo->getGridY());
//  }
  
  CCLog("tileInfo->getNumberEdgeAvailale() = %d", tileInfo->getNumberEdgeAvailale());
  
//  if (tileInfo->getNumberEdgeAvailale() == 0)
//  {
//    sp->setColor(ccGRAY);
//  }
  
  for (int i = 0; i < popsArr->count(); ++i)
  {
    ((CCMenuItemSprite*)popsArr->objectAtIndex(i))->removeFromParent();
    CCLog("remove %d", i);
  }
  popsArr->removeAllObjects();
}

void PlayScene::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void PlayScene::moveMap(float offsetX, float offsetY)
{
  float posX = tileMap->getPosition().x + offsetX;
  float posY = tileMap->getPosition().y + offsetY;
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
  tileMap->setPosition(ccp(posX, posY));
}

CCPoint PlayScene::getBound()
{
  float mapWidth = tileMap->getTileSize().width * tileMap->getMapSize().width;
  float mapHeight = tileMap->getTileSize().height * tileMap->getMapSize().height;
  
  // should caculate the bounding of map position
  return ccp(screenSize.width - mapWidth, screenSize.height - mapHeight);
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
    popsArr->release();
}

void PlayScene::update(float pdT)
{
  for (int i = 0; i < tileInfoVector.size(); ++i)
  {
    if (tileInfoVector.at(i)->getNumberEdgeAvailale() == 0)
    {
      tileInfoVector.at(i)->setNumberEdgeAvailale(-1);
      tileInfoVector.at(i)->getTile()->setColor(ccGRAY);
      SimpleAI::Breath_First_Search(tileInfoVector.at(i)->getGridX(), tileInfoVector.at(i)->getGridY());
      break;
    }
  }
  
  for (int i=0; i<tileInfoVector.size(); i++)
  {
    if (tileInfoVector.at(i)->getNumberEdgeAvailale() == 0)
    {
    //Bottom
      CCSprite *edge1 = CCSprite::create("PlayScene/edge.png");
    
      TileInfo *tileInfo = tileInfoVector.at(i);
    
      CCSprite *sp = tileInfo->getTile();
    
      edge1->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width/2, sp->getPositionY()));
      tileMap->addChild(edge1, GR_FOREGROUND);
    //Top
      CCSprite *edge2 = CCSprite::create("PlayScene/edge.png");
      edge2->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width/2, sp->getPositionY()+sp->getContentSize().height));
      tileMap->addChild(edge2, GR_FOREGROUND);
    //Left
      CCSprite *edge3 = CCSprite::create("PlayScene/edge.png");
      edge3->setRotation(90);
      edge3->setPosition(ccp(sp->getPositionX(), sp->getPositionY()+sp->getContentSize().height/2));
      tileMap->addChild(edge3, GR_FOREGROUND);
    //Right
      CCSprite *edge4 = CCSprite::create("PlayScene/edge.png");
      edge4->setRotation(90);
      edge4->setPosition(ccp(sp->getPositionX() + sp->getContentSize().width, sp->getPositionY()+sp->getContentSize().height/2));
      tileMap->addChild(edge4, GR_FOREGROUND);
    }
  }
}

CCTMXTiledMap PlayScene::getTileMap()
{
  return *tileMap;
}

std::vector<TileInfo*> PlayScene::getTileInfoVector()
{
  return tileInfoVector;
}
