#include "CCScrollLayerHorizontal.h"
//#include "CCTouchHandler.h"
//#include "GLES-Render.h"


#include <assert.h>
#include "Constant.h"

USING_NS_CC;

//namespace cocos2d
//{
enum
{
  kCCScrollLayerHorizontalStateIdle,
  kCCScrollLayerHorizontalStateSliding,
};

CCScrollLayerHorizontal::CCScrollLayerHorizontal()
: m_pDelegate(NULL), m_pLayers(NULL), m_bStealingTouchInProgress(false), m_pScrollTouch(NULL), m_iState(kCCScrollLayerHorizontalStateIdle)

{
}

CCScrollLayerHorizontal::~CCScrollLayerHorizontal()
{
  CC_SAFE_RELEASE(m_pLayers);
  m_pDelegate = NULL;
  this->setCustomPageIndicators(NULL);
}

unsigned int CCScrollLayerHorizontal::getTotalScreens() const
{
  return m_pLayers->count();
}

CCScrollLayerHorizontal* CCScrollLayerHorizontal::nodeWithLayers(CCArray* layers, int widthOffset)
{
  CCScrollLayerHorizontal* pRet = new CCScrollLayerHorizontal();
  if (pRet && pRet->initWithLayers(layers, widthOffset))
  {
    pRet->autorelease();
    return pRet;
  }
  else
  {
    CC_SAFE_DELETE(pRet);
    return NULL;
  }
}

CCScrollLayerHorizontal* CCScrollLayerHorizontal::nodeWithLayers(cocos2d::CCArray *layers, int widthOffset, const char * pageSpriterameName)
{
  CCScrollLayerHorizontal* layer = CCScrollLayerHorizontal::nodeWithLayers(layers, widthOffset);
  if (layers == NULL) {
    CCLog("null");
  }
  layer->setCustomPageIndicators(CCNode::create());
  
  // use default position
  layer->customPageIndicators->setPosition(layer->getPagesIndicatorPosition());
  
  // create sprites
  float n = (float)layer->getTotalScreens(); // << total point
  float d = GAP_BETWEEN_DOT;    //<< distance between points
  for (int i = 0; i < layer->getTotalScreens(); ++i)
  {
    CCSprite *pageSprite = CCSprite::create(pageSpriterameName);
    pageSprite->setPosition(ccp(d*((float)i - 0.5f*(n-1.0f)), 0));
    layer->customPageIndicators->addChild(pageSprite);
  }
  layer->addChild(layer->getCustomPageIndicators());
  layer->schedule(schedule_selector(CCScrollLayerHorizontal::updatePageIndicators));
  
  return layer;
}

bool CCScrollLayerHorizontal::initWithLayers(CCArray* layers, int widthOffset)
{
  if (!CCLayer::init())
    return false;
  CC_ASSERT(layers && layers->count());
  
  setTouchEnabled(true);
  
  m_bStealTouches = true;
  
  // Set default minimum touch length to scroll.
  m_fMinimumTouchLengthToSlide = 30.0f;
  m_fMinimumTouchLengthToChangePage = 100.0f;
  
  m_fMarginOffset = CCDirector::sharedDirector()->getWinSize().height;
  
  // Show indicator by default.
  m_bShowPagesIndicator = true;
  m_tPagesIndicatorPosition = getPagesIndicatorPosition();// ccp(0.5f * m_obContentSize.width, ceilf(m_obContentSize.height / 8.0f));
  
  // Set up the starting variables
  m_uCurrentScreen = 0;
  
  // Save offset.
  m_fPagesWidthOffset = (float)widthOffset;
  
  // Save array of layers.
  //		m_pLayers = CCArray::createWithArray(layers);
  m_pLayers = CCArray::createWithCapacity(layers->count());
  m_pLayers->addObjectsFromArray(layers);
  
  layers->release();
  m_pLayers->retain();
  
  updatePages();
  
  return true;
}

void CCScrollLayerHorizontal::updatePages()
{
  // Loop through the array and add the screens if needed.
  int i = 0;
  CCObject* object = NULL;
  CCARRAY_FOREACH(m_pLayers, object)
  {
    CCLayer* layer = (CCLayer*)object;
    layer->setAnchorPoint(ccp(0,0));
    layer->setContentSize(CCDirector::sharedDirector()->getWinSize());
    layer->setPosition(ccp(0, (i * (m_obContentSize.height - m_fPagesWidthOffset))));
    if (!layer->getParent())
      addChild(layer);
    i++;
  }
}

// CCLayer Methods ReImpl

void CCScrollLayerHorizontal::visit()
{
  CCLayer::visit();	//< Will draw after glPopScene.
  
  if (m_bShowPagesIndicator)
  {
    int totalScreens = getTotalScreens();
    
    // Prepare Points Array
    float n = (float)totalScreens; //< Total points count in float.
    float pX = m_tPagesIndicatorPosition.y; //< Points y-coord in parent coord sys.
    float d = 16.0f; //< Distance between points.
    CCPoint* points = new CCPoint[totalScreens];
    for (int i = 0; i < totalScreens; ++i)
    {
      float pY = m_tPagesIndicatorPosition.y + d * ((float)i - 0.5f*(n-1.0f));
      points[i] = ccp(pX, pY);
    }
    
    // Set GL Values
    //			glEnable(GL_POINT_SMOOTH);
    GLboolean blendWasEnabled = glIsEnabled(GL_BLEND);
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ccPointSize(6.0f * CC_CONTENT_SCALE_FACTOR());
    
    // Draw Gray Points
    //			ccDrawColor4B(0x96,0x96,0x96,0xFF);
    //			ccDrawPoints( points, totalScreens );
    
    // Draw White Point for Selected Page
    //			ccDrawColor4B(0xFF,0xFF,0xFF,0xFF);
    //			ccDrawPoint(points[m_uCurrentScreen]);
    
    // Restore GL Values
    ccPointSize(3.0f);
    //			glDisable(GL_POINT_SMOOTH);
    if (! blendWasEnabled)
      glDisable(GL_BLEND);
    
    delete [] points;
  }
}

// Moving To / Selecting Pages

void CCScrollLayerHorizontal::moveToPageEnded()
{
  if (m_pDelegate)
    m_pDelegate->scrollLayerScrolledToPageNumber(this, m_uCurrentScreen);
}

unsigned int CCScrollLayerHorizontal::pageNumberForPosition(const CCPoint& position)
{
  float pageFloat = - m_obPosition.y / (m_obContentSize.height - m_fPagesWidthOffset);
  int pageNumber = (int)ceilf(pageFloat);
  if ((float)pageNumber - pageFloat  >= 0.5f)
    pageNumber--;
  
  pageNumber = MAX(0, pageNumber);
  pageNumber = MIN((int)m_pLayers->count() - 1, pageNumber);
  
  return (unsigned int)pageNumber;
}


CCPoint CCScrollLayerHorizontal::positionForPageWithNumber(unsigned int pageNumber)
{
  return ccp(0.0f, pageNumber * -1.f * (m_obContentSize.height - m_fPagesWidthOffset));
}

void CCScrollLayerHorizontal::moveToPage(unsigned int pageNumber)
{
  if (pageNumber >= m_pLayers->count())
  {
    CCLOGERROR("CCScrollLayerHorizontal::moveToPage: %d - wrong page number, out of bounds.", pageNumber);
    return;
  }
  
  // animation 1
  //		CCAction* changePage =
  //			CCSequence::create(
  //					CCMoveTo::create(0.6f, positionForPageWithNumber(pageNumber)),
  //					CCCallFunc::create(this, callfunc_selector(CCScrollLayerHorizontal::moveToPageEnded)),
  //          NULL
  //				);
  
  // animation 2
  actionDuration = 1.0f;
  bouncePeriod = 0.7f;
  CCAction* changePage =
  CCSequence::create(
                     
                     CCCallFunc::create(this, callfunc_selector(CCScrollLayerHorizontal::moveToPageEnded)),
                     CCEaseElasticOut::create(
                                                    CCMoveTo::create(actionDuration, positionForPageWithNumber(pageNumber)), bouncePeriod),
                     NULL);
  
  // animation 3
  //    CCEaseBounce* action = CCEaseBounce::create(CCMoveTo::create(actionDuration*0.3f, positionForPageWithNumber(pageNumber)));
  //    CCAction* changePage =
  //      CCSequence::create(
  //        action,
  //        CCCallFunc::create(this, callfunc_selector(CCScrollLayerHorizontal::moveToPageEnded)),
  //        NULL);
  
  runAction(changePage);
  m_uCurrentScreen = pageNumber;
}

void CCScrollLayerHorizontal::selectPage(unsigned int pageNumber)
{
  if (pageNumber >= m_pLayers->count())
  {
    CCLOGERROR("CCScrollLayerHorizontal::selectPage: %d - wrong page number, out of bounds.", pageNumber);
    return;
  }
  
  setPosition(positionForPageWithNumber(pageNumber));
  m_uCurrentScreen = pageNumber;
  
}

// Dynamic Pages Control

void CCScrollLayerHorizontal::addPage(CCLayer* aPage)
{
  addPage(aPage, m_pLayers->count());
}

void CCScrollLayerHorizontal::addPage(CCLayer* aPage, unsigned int pageNumber)
{
  pageNumber = MIN(pageNumber, m_pLayers->count());
  pageNumber = MAX(pageNumber, 0);
  
  m_pLayers->insertObject(aPage, pageNumber);
  
  updatePages();
  moveToPage(m_uCurrentScreen);
}

void CCScrollLayerHorizontal::removePage(CCLayer* aPage)
{
  m_pLayers->removeObject(aPage);
  removeChild(aPage, true);
  
  updatePages();
  
  m_uCurrentScreen = MIN(m_uCurrentScreen, m_pLayers->count() - 1);
  moveToPage(m_uCurrentScreen);
}

void CCScrollLayerHorizontal::removePageWithNumber(unsigned int pageNumber)
{
  if (pageNumber < m_pLayers->count())
    removePage((CCLayer*)(m_pLayers->objectAtIndex(pageNumber)));
}

// Touches

// Register with more priority than CCMenu's but don't swallow touches
void CCScrollLayerHorizontal::registerWithTouchDispatcher()
{
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, false);
}

/** Hackish stuff - stole touches from other CCTouchDispatcher targeted delegates.
 Used to claim touch without receiving ccTouchBegan. */
void CCScrollLayerHorizontal::claimTouch(CCTouch* pTouch)
{
  CCTargetedTouchHandler* handler = (CCTargetedTouchHandler*)CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this);
  if (handler)
  {
    CCSet* claimedTouches = handler->getClaimedTouches();
    if (!claimedTouches->containsObject(pTouch))
    {
      claimedTouches->addObject(pTouch);
    }
    else
    {
      CCLOGERROR("CCScrollLayerHorizontal::claimTouch is already claimed!");
    }
  }
}

void CCScrollLayerHorizontal::cancelAndStoleTouch(CCTouch* pTouch, CCEvent* pEvent)
{
  // Throw Cancel message for everybody in TouchDispatcher.
  CCSet* touchSet = new CCSet();
  touchSet->addObject(pTouch);
  touchSet->autorelease();
  m_bStealingTouchInProgress = true;
  CCDirector::sharedDirector()->getTouchDispatcher()->touchesCancelled(touchSet, pEvent);
  m_bStealingTouchInProgress = false;
  
  //< after doing this touch is already removed from all targeted handlers
  
  // Squirrel away the touch
  claimTouch(pTouch);
}

void CCScrollLayerHorizontal::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
  // Do not cancel touch, if this method is called from cancelAndStoleTouch:
  if (m_bStealingTouchInProgress)
    return;
  
  if (m_pScrollTouch == pTouch)
  {
    m_pScrollTouch = NULL;
    selectPage(m_uCurrentScreen);
  }
}

bool CCScrollLayerHorizontal::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
  if (!m_pScrollTouch)
    m_pScrollTouch = pTouch;
  else
    return false;
  
  CCPoint touchPoint = pTouch->getLocationInView();
  touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
  
  m_fStartSwipe = touchPoint.y;
  m_iState = kCCScrollLayerHorizontalStateIdle;
  
  return true;
}

void CCScrollLayerHorizontal::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
  if(m_pScrollTouch != pTouch)
    return;
  
  CCPoint touchPoint = pTouch->getLocationInView();
  touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
  
  // If finger is dragged for more distance then minimum - start sliding and cancel pressed buttons.
  // Of course only if we not already in sliding mode
  if ((m_iState != kCCScrollLayerHorizontalStateSliding)
			&& (fabsf(touchPoint.y - m_fStartSwipe) >= m_fMinimumTouchLengthToSlide))
  {
    m_iState = kCCScrollLayerHorizontalStateSliding;
    
    // Avoid jerk after state change.
    m_fStartSwipe = touchPoint.y;
    
    if (m_bStealTouches)
      cancelAndStoleTouch(pTouch, pEvent);
    
    if (m_pDelegate)
      m_pDelegate->scrollLayerScrollingStarted(this);
  }
  
  if (m_iState == kCCScrollLayerHorizontalStateSliding)
  {
    float desiredY = (m_uCurrentScreen * -1.f * (m_obContentSize.height - m_fPagesWidthOffset)) + touchPoint.y - m_fStartSwipe;
    unsigned int page = pageNumberForPosition(ccp(0, desiredY));
    float offset = desiredY - positionForPageWithNumber(page).y;
    if ((page == 0 && offset > 0) || (page == m_pLayers->count() - 1 && offset < 0))
      offset -= m_fMarginOffset * (offset / CCDirector::sharedDirector()->getWinSize().height);
    else
      offset = 0;
    setPosition(ccp(0, desiredY - offset));
  }
}

void CCScrollLayerHorizontal::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
  if(m_pScrollTouch != pTouch)
    return;
  
  m_pScrollTouch = NULL;
  
  CCPoint touchPoint = pTouch->getLocationInView();
  touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
  
  unsigned int selectedPage = m_uCurrentScreen;
  float delta = touchPoint.y - m_fStartSwipe;
  if (fabs(delta) >= m_fMinimumTouchLengthToChangePage)
  {
    selectedPage = pageNumberForPosition(m_obPosition);
    if (selectedPage == m_uCurrentScreen)
    {
      if (delta < 0.f && selectedPage < m_pLayers->count() - 1)
        selectedPage++;
      else if (delta > 0.f && selectedPage > 0)
        selectedPage--;
    }
  }
  moveToPage(selectedPage);
}
//}

CCScrollLayerHorizontal* CCScrollLayerHorizontal::nodeWithLayers(cocos2d::CCArray *layers, int widthOffset, float duration, float bouncePeriod)
{
  CCScrollLayerHorizontal *layer = CCScrollLayerHorizontal::nodeWithLayers(layers, widthOffset);
  layer->setActionDuration(duration);
  layer->setBouncePeriod(bouncePeriod);
  return layer;
}

void CCScrollLayerHorizontal::updatePageIndicators()
{
  customPageIndicators->setPosition(ccp(getPagesIndicatorPosition().x, getPagesIndicatorPosition().y - getPosition().y));
  for (int i = 0; i < customPageIndicators->getChildren()->count(); i++)
  {
    CCSprite *indicator = (CCSprite*)customPageIndicators->getChildren()->objectAtIndex(i);
    
    // none current page are semi-transparent
    if (i == this->getCurrentScreen())
    {
      indicator->setOpacity(255);
    } else
    {
      indicator->setOpacity(100);
    }
  }
}
