//
//  ChooseMapScene.cpp
//  landlord
//
//  Created by Giap Nguyen on 4/25/14.
//
//

#include "ChooseMapScence.h"
#include "BounceButton.h"
#include "CustomTableViewCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool ChooseMapScene::init()
{
  if (!CCLayer::init())
  {
    return false;
  }
  mState = 1;
  
  mScreenSize = CCDirector::sharedDirector()->getWinSize();
  CCLog("%f %f", mScreenSize.width, mScreenSize.height);
  
  addBackground();
  
  addButtonBack();
  addButtonForward();
  
  addSlidingLayers();
  return true;
}

CCScene* ChooseMapScene::scene()
{
  CCScene *scene = CCScene::create();
  ChooseMapScene *layer = ChooseMapScene::create();
  scene->addChild(layer);
  
  return scene;
}

void ChooseMapScene::addBackground()
{
  CCSprite *background = CCSprite::create("Images/Game/Background/chooseBg.png");
  background->setPosition(ccp(mScreenSize.width/2, mScreenSize.height/2));
  this->addChild(background, GR_BACKGROUND);
}

void ChooseMapScene::addButtonBack()
{
  CCSprite *back = CCSprite::create("Images/Game/UI/leftNavigator.png");
  CCMenuItemSprite *backBtn = CCMenuItemSprite::create(back,
                                                       back,
                                                       this,
                                                       menu_selector(ChooseMapScene::buttonBackTouched));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(BTN_BACK_POS);
  this->addChild(pMenu, GR_BACKGROUND);
}

void ChooseMapScene::addButtonForward()
{
  CCSprite *back = CCSprite::create("Images/Game/UI/rightNavigator.png");
  CCMenuItemSprite *backBtn = CCMenuItemSprite::create(back,
                                                       back,
                                                       this,
                                                       menu_selector(ChooseMapScene::buttonForwardTouched));
  CCMenu* pMenu = CCMenu::create(backBtn, NULL);
  pMenu->setPosition(BTN_FORWARSD_POS);
  this->addChild(pMenu, GR_BACKGROUND);
}

void ChooseMapScene::addSlidingLayers()
{
  mChooseCharacterLayer = createChooseCharaterLayer();
  mChooseCharacterLayer->setPosition(CCPointZero);
  mChooseCharacterLayer->setTouchEnabled(true);

  mChooseMapLayer = createChooseMapLayer();
  mChooseMapLayer->setPosition(SCREEN_SIZE.width, 0);
  
//  srand(time(NULL));
//  int charater1 = rand() % NUMBER_CHARACTERS + 1;
//  int charater2;
//  while (charater2 == charater1)
//    charater2 = rand() % NUMBER_CHARACTERS + 1;
//  mSlideCharacter1->selectPage(charater1 - 1);
//  mSlideCharacter2->selectPage(charater2 - 1);
//  GameManager::setPlayerOneID(charater1);
//  GameManager::setPlayerTwoID(charater2);
  
  this->addChild(mChooseCharacterLayer, GR_FOREGROUND);
  this->addChild(mChooseMapLayer);

  mVs = BounceButton::create("Images/Game/UI/vsIcon-04.png");
  mVs->setPosition(VS_POS);
  mChooseCharacterLayer->addChild(mVs, GR_FOREGROUND);
  
//  CCMenu* menu = CCMenu::create(CCMenuItemSprite::create(mVs, mVs, this, menu_selector(ChooseMapScene::randomCharacter)), NULL);
//  menu->setPosition(VS_POS);
  
//  mChooseCharacterLayer->addChild(menu);
}

void ChooseMapScene::cooldown()
{
  float now = getCooldownTime();
  //  CCLog("%f", now);
  setCooldownTime(now - 0.3);
  if (now <= 0)
  {
    CCDirector::sharedDirector()->pause();
  }
}

void ChooseMapScene::randomCharacter(cocos2d::CCObject *pSender)
{
  sound::playSoundFx(SFX_TOUCH_POP);
  srand(time(NULL));
  int charater1 = rand() % NUMBER_CHARACTERS + 1;
  int charater2;
  while (charater2 == charater1)
    charater2 = rand() % NUMBER_CHARACTERS + 1;
//  mSlideCharacter1->moveToPage(charater1 - 1);
//  mSlideCharacter2->moveToPage(charater2 - 1);
  
  GameManager::setPlayerOneID(charater1);
  GameManager::setPlayerTwoID(charater2);
  CCLog("%d %d", GameManager::getPlayerOneID(), GameManager::getPlayerTwoID());
  CCLog("%d %d", charater1, charater2);
}

CCArray* ChooseMapScene::createCharactersArray(CCPoint pPos)
{
  CCArray* characterArr = CCArray::createWithCapacity(NUMBER_CHARACTERS);
  for (int i = 1; i <= NUMBER_CHARACTERS; ++i)
  {
    CCLayer* characterLayer = CCLayer::create();
    
    CCSprite* character = CCSprite::create(CCString::createWithFormat("Images/Game/Object/c%i.png", i)->getCString());
    character->setPosition(pPos);
    characterLayer->addChild(character, GR_FOREGROUND, i);
    characterArr->addObject(characterLayer);
  }
  return characterArr;
}

// there are some magic numbers here, need transfer to Constant.h
CCLayer* ChooseMapScene::createChooseCharaterLayer()
{
  CCLayer* chooseCharacterLayer = CCLayer::create();
  
  // using CCScrollLayerVertical
//  CCArray* characterArr1 = createCharactersArray(CHARACTER_LEFT_LAYER_POS);
//  CCArray* characterArr2 = createCharactersArray(CHARACTER_RIGHT_LAYER_POS);
//  
//  mSlideCharacter1 = CCScrollLayerVertical::nodeWithLayers(characterArr1, 0);
//  
//  mSlideCharacter2 = CCScrollLayerVertical::nodeWithLayers(characterArr2, 0);
//
  
  // using CCTableView
  CCTableView* mSlideCharacter1 = CCTableView::create(this, CCSizeMake(209, 534));
  mSlideCharacter1->setDirection(kCCScrollViewDirectionVertical);
  mSlideCharacter1->setPosition(ccp(700, 52.688));
  mSlideCharacter1->setDelegate(this);
  mSlideCharacter1->setVerticalFillOrder(kCCTableViewFillTopDown);
  mSlideCharacter1->reloadData();
  chooseCharacterLayer->addChild(mSlideCharacter1, GR_FOREGROUND);
  
  CCTableView* mSlideCharacter2 = CCTableView::create(this, CCSizeMake(209, 534));
  mSlideCharacter2->setDirection(kCCScrollViewDirectionVertical);
  mSlideCharacter2->setPosition(ccp(227, 52.688));
  mSlideCharacter2->setDelegate(this);
  mSlideCharacter2->setVerticalFillOrder(kCCTableViewFillTopDown);
  mSlideCharacter2->reloadData();
  chooseCharacterLayer->addChild(mSlideCharacter2, GR_FOREGROUND);
  
  return chooseCharacterLayer;
}

void ChooseMapScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
  CCLOG("cell touched at index: %i", cell->getIdx() + 1);
//  (cell->getChildByTag(cell->getIdx()+1))->runAction(CCMoveTo::create(0.5, ccp(100, 261.662)));
//  cell->runAction(CCMoveTo::create(0.5, ccp(100, 261.662)));
}

CCSize ChooseMapScene::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
  return CCSizeMake(100, 534);
}

CCTableViewCell* ChooseMapScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
  CCTableViewCell *cell = table->cellAtIndex(idx); //table->dequeueCell();
  if (!cell)
  {
    cell = new CustomTableViewCell();
    cell->autorelease();
    CCSprite *sprite = CCSprite::create(CCString::createWithFormat("Images/Game/Object/c%i.png", idx + 1)->getCString());
    CCLOG("player 2 - %d", idx+1);
    GameManager::setPlayerTwoID(idx + 1);

    sprite->setPosition(ccp(100, 261.662));
    sprite->setTag(idx+1);
    cell->addChild(sprite);
  }
  
  return cell;
}

unsigned int ChooseMapScene::numberOfCellsInTableView(CCTableView *table)
{
  return NUMBER_CHARACTERS;
}


CCLayer* ChooseMapScene::createChooseMapLayer()
{
  CCLayer* chooseMapLayer = CCLayer::create();
  CCArray* mapArr = CCArray::createWithCapacity(NUMBER_MAPS);
  for (int i = 1; i <= NUMBER_MAPS; ++i)
  {
    CCLayer* mapLayer = CCLayer::create();
    
    CCSprite* map = CCSprite::create(CCString::createWithFormat("Images/Map/map%i.png", i)->getCString());
    map->setPosition(CENTER_POS);
    mapLayer->addChild(map, GR_FOREGROUND, i);
    mapArr->addObject(mapLayer);
  }
  mSlideMap = CCScrollLayerVertical::nodeWithLayers(mapArr,  0);

  chooseMapLayer->addChild(mSlideMap, GR_FOREGROUND, TAG_SLIDE_MAP);
  
  return chooseMapLayer;
}

void ChooseMapScene::buttonBackTouched(cocos2d::CCObject *pSender)
{
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  mState--;
  if (mState == 0)
  {
    CCScene* newScene = CCTransitionCrossFade::create(0.5, LoadingScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
  }
  else if (mState == 1)
  {
    mChooseMapLayer->runAction(changePage(ccp(SCREEN_SIZE.width, 0)));
    mChooseCharacterLayer->runAction(changePage(CCPointZero));
  }
}

void ChooseMapScene::buttonForwardTouched(cocos2d::CCObject *pSender)
{
  sound::playSoundFx(SFX_BUTTON_TOUCH);
  CCLog("state: %d", mState);
  mState++;
  if (mState == 3)
  {
    int id = mSlideMap->getCurrentScreen();
    GameManager::setMapIDTouched(id + 1);
    CCScene* newScene = CCTransitionCrossFade::create(0.5, PlayScene::scene());
    CCDirector::sharedDirector()->replaceScene(newScene);
  }
  else if (mState == 2)
  {
    mChooseMapLayer->runAction(changePage(CCPointZero));
    mChooseCharacterLayer->runAction(changePage(ccp(-SCREEN_SIZE.width, 0)));
  }
}

ChooseMapScene::~ChooseMapScene()
{
}

CCAction* ChooseMapScene::changePage(cocos2d::CCPoint pPos)
{
  float actionDuration = 1.0f;
  float bouncePeriod = 0.7f;
  CCAction* changePage =
    CCSequence::create(
     CCEaseElasticOut::create(
      CCMoveTo::create(actionDuration, pPos),
      bouncePeriod),
     NULL);
  return changePage;
}

