#include "ScrollableMap.h"

USING_NS_CC;

bool ScrollableMap::init()
{
  if (!CCLayerRGBA::init())
  {
    return false;
  }
  
  // Threshold check to avoid taps provoking small residual movements that start scrolling
  mInitialMovementThreshold = 32;
  
  // Threshold check to avoid small residual movements on touch end
  // without intended movement
  mEndMovementThreshold = 16;
  
  mElapsedTime = 0;
  
  setAnchorPoint(CCPointZero);
  
  mMinXPos = -boundingBox().size.width + MAX_X_POS;
  mMaxXPos = 0;
  mMinYPos = -boundingBox().size.height + MAX_Y_POS;
  mMaxYPos = 0;
  
  mMaxZoomFactor = 1.0f;
  mMinZoomFactor = 1.0f;
  
  mZoomFactor = mMaxZoomFactor;
  setScale(mZoomFactor);
  
  mDragged = false;
  mDragging = false;
  mZooming = false;
  mInertialMoving = false;
  mInertialUpdating = false;
  mRubberbandShouldReturn = false;
  mAutoScrolling = false;
  mPreRubberbandPosition = CCPointZero;
  mMoveOffset = CCPointZero;
  mInertialMoveOffset = CCPointZero;
  mFirstTouchPoint = CCPointZero;
  
  scheduleUpdate();
  
  setTouchEnabled(true);
  
  return true;
}

void ScrollableMap::update(float pDt)
{
  mElapsedTime += pDt;
  if (mInertialUpdating) {
    updateInertialMoveOffset();
  }
  if (mInertialMoving) {
    moveByInertialMoveOffsetWithDeltaTime(pDt);
  }
  if (mRubberbandShouldReturn && !mDragging && !mInertialMoving) {
    doRubberbandReturn();
  }
}

void ScrollableMap::startAutoScroll()
{
  mAutoScrolling = true;
}

void ScrollableMap::endAutoScroll()
{
  mAutoScrolling = true;
}

// Upadte inertialMoveOffset based on moveOffset (calculated in ccTouchMoved)
// if the highest magnitude of the moveOffset is higher than
// the one from the last registered inertialMoveOffset -> update immediatly,
// else -> delayed update (in order to avoid losing inertia when lifting the finger at the end of a drag)
void ScrollableMap::updateInertialMoveOffset()
{
  static float lastUpdatedTime;
  static const float timeThreshold = 0.1;
  
  if (mElapsedTime > lastUpdatedTime + timeThreshold)
  {
    mInertialMoveOffset = mMoveOffset;
    lastUpdatedTime = mElapsedTime;
  }
  else
  {
    if (abs(mMoveOffset.x) > abs(mMoveOffset.y))
    {
      if (abs(mMoveOffset.x) > abs(mInertialMoveOffset.x))
      {
        mInertialMoveOffset = mMoveOffset;
        lastUpdatedTime = mElapsedTime;
      }
    }
    else {
      if (abs(mMoveOffset.y) > abs(mInertialMoveOffset.y))
      {
        mInertialMoveOffset = mMoveOffset;
        lastUpdatedTime = mElapsedTime;
      }
    }
  }
}

// Move the layer according to the inertialMoveOffset,
// reduce inertialMoveOffset progressively until threshold is reached
void ScrollableMap::moveByInertialMoveOffsetWithDeltaTime(float pDt)
{
  float movementThreshold = 0.01;
  float movementFactor = 0.4;
  float movementSlowdownFactor = 0.90;
  
  if (mRubberbandShouldReturn) {
    movementThreshold = 0.1;
    movementSlowdownFactor = 0.6;
  }
  
  if (abs(mInertialMoveOffset.x) <= movementThreshold &&
      abs(mInertialMoveOffset.y) <= movementThreshold)
  {
    mInertialMoving = true;
    mMoveOffset = mInertialMoveOffset = CCPointZero;
    
    // Round position at inertial movement end
    // to avoid partial-pixel positions
    setPosition(ccp(round(getPosition().x), round(getPosition().y)));
  }
  else
  {
    setPosition(ccpSub(getPosition(), ccpMult(mInertialMoveOffset, movementFactor)));
    
    // Reduce inertialMoveOffset according to movementSlowdownFactor
    // (not normalized by deltatime)
    mInertialMoveOffset = ccpMult(mInertialMoveOffset, movementSlowdownFactor);
  }
}

// Performs rubberdband return action
void ScrollableMap::doRubberbandReturn()
{
  mPreRubberbandPosition = getPosition();
  
  if (mPreRubberbandPosition.x < mMinXPos)
    mPreRubberbandPosition.x = mMinXPos;
  if (mPreRubberbandPosition.y < mMinYPos)
    mPreRubberbandPosition.y = mMinYPos;
  if (mPreRubberbandPosition.x > mMaxXPos)
    mPreRubberbandPosition.x = mMaxXPos;
  if (mPreRubberbandPosition.y > mMaxYPos)
    mPreRubberbandPosition.y = mMaxYPos;
  
  mAutoScrolling = true;
  mRubberbandShouldReturn = false;
  CCAction *scrollAction = CCSequence::create(CCEaseOut::create(CCMoveTo::create(SCROLL_DURATION,
                                                                                 mPreRubberbandPosition),
                                                                4),
                                              CCCallFunc::create(this,
                                                                 callfunc_selector(ScrollableMap::endAutoScroll)),
                                              NULL);
  
  
  scrollAction->setTag(TAG_SCROLL_ACTION);
  runAction(scrollAction);
}

void ScrollableMap::scrollToPoint(const CCPoint& pPoint)
{
  scrollToPoint(pPoint, SCROLL_DURATION, CCEIO_EASE_IN_OUT);
}

void ScrollableMap::scrollToPoint(const CCPoint& pPoint, float pDuration)  
{
  scrollToPoint(pPoint, pDuration, CCEIO_EASE_IN_OUT);
}

void ScrollableMap::scrollToPoint(const CCPoint& pPoint, float pDuration, eCCEaseInOut pEaseInOut)
{
  stopActionByTag(TAG_SCROLL_ACTION);
  
  if (pDuration != 0)
  {
    runAction(scrollActionToPoint(pPoint, pDuration, pEaseInOut));
  }
  else
  {
    // Scale and invert axis
    CCPoint point;
    point = ccpMult(pPoint, -mZoomFactor);
    point.x += MAX_X_POS/2;
    point.y += MAX_Y_POS/2;
    
    mAutoScrolling = false;
    setPosition(point);
  }
}

CCFiniteTimeAction* ScrollableMap::scrollActionToPoint(const CCPoint& pPoint)
{
  return scrollActionToPoint(pPoint, SCROLL_DURATION);
}

CCFiniteTimeAction* ScrollableMap::scrollActionToPoint(const CCPoint& pPoint,
                                                       float pDuration)
{
  return scrollActionToPoint(pPoint, pDuration, CCEIO_EASE_IN_OUT);
}

CCFiniteTimeAction* ScrollableMap::scrollActionToPoint(const CCPoint& pPoint,
                                                       float pDuration,
                                                       eCCEaseInOut pEaseInOut)
{
  // Scale and invert axis
  CCPoint point = ccpMult(pPoint, -mZoomFactor);
  point.x += MAX_X_POS/2;
  point.y += MAX_Y_POS/2;
    
  mRubberbandShouldReturn = false;
  mInertialMoveOffset = CCPointZero;
  CCAction *scrollAction = NULL;
  
  switch (pEaseInOut) {
    case CCEIO_NONE:
      scrollAction = CCSequence::create(CCCallFunc::create(this, callfunc_selector(ScrollableMap::startAutoScroll)),
                                        CCMoveTo::create(pDuration, point),
                                        CCCallFunc::create(this, callfunc_selector(ScrollableMap::endAutoScroll)),
                                        NULL);
      break;
      
    case CCEIO_EASE_IN_OUT:
      scrollAction = CCSequence::create(CCCallFunc::create(this, callfunc_selector(ScrollableMap::startAutoScroll)),
                                        CCEaseInOut::create(CCMoveTo::create(pDuration, point), 2),
                                        CCCallFunc::create(this, callfunc_selector(ScrollableMap::endAutoScroll)),
                                        NULL);      
      break;
      
    case CCEIO_EASE_IN:
      scrollAction = CCSequence::create(CCCallFunc::create(this, callfunc_selector(ScrollableMap::startAutoScroll)),
                                        CCEaseIn::create(CCMoveTo::create(pDuration, point), 4),
                                        CCCallFunc::create(this, callfunc_selector(ScrollableMap::endAutoScroll)),
                                        NULL);
      break;
      
    case CCEIO_EASE_OUT:
    default:
      scrollAction = CCSequence::create(CCCallFunc::create(this, callfunc_selector(ScrollableMap::startAutoScroll)),
                                        CCEaseOut::create(CCMoveTo::create(pDuration, point), 4),
                                        CCCallFunc::create(this, callfunc_selector(ScrollableMap::endAutoScroll)),
                                        NULL);
      break;
  }
  
  scrollAction->setTag(TAG_SCROLL_ACTION);
  return (CCFiniteTimeAction*)scrollAction;
}

void ScrollableMap::registerWithTouchDispatcher()
{
   CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, kCCMenuHandlerPriority+1);
}
void ScrollableMap::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
  stopActionByTag(TAG_SCROLL_ACTION);
  endAutoScroll();
  
	if (pTouches->count() == 1)
  {
    mFirstTouchPoint = ((CCTouch*)pTouches->anyObject())->getLocationInView();

		// single touch dragging needs to go here
    mInertialMoveOffset = mMoveOffset = ccp(0,0);
    
    mDragged = false;
    mDragging = false;
    mZooming = false;
    mInertialMoving = false;
    mInertialUpdating = true;
	}
  else if (pTouches->count() == 2)
  {
    mDragged = true;
    // When zooming, you are also dragging
    mDragging = true;
    mZooming = true;
	}
}

void ScrollableMap::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
  updateParametersWithTouches(pTouches);

  if (pTouches->count() == 1)
  {
    CCPoint currentTouch = ((CCTouch*)pTouches->anyObject())->getLocationInView();
  
    // Optimization: if dragging_, don't check threshold
    if (mDragging ||
        abs(currentTouch.x-mFirstTouchPoint.x) > mInitialMovementThreshold ||
        abs(currentTouch.y-mFirstTouchPoint.y) > mInitialMovementThreshold)
    {
      mDragged = mDragging = true;
      setPosition(ccpSub(getPosition(), mMoveOffset));
    }
  }
  else if (pTouches->count() == 2)
  {
    setPosition(ccpSub(getPosition(), mMoveOffset), false);
  }
}

void ScrollableMap::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
  // Do not update parameters if not dragging
  // (sometimes touchEnded position is different than touchBegan
  //  position without having called touchesMoved, in this cases
  //  we don't want to move the map)
  if (mDragging)
  {
    updateParametersWithTouches(pTouches);
  }
  
  // If all touches are being lifted, cancel inertialUpdating_
  // TODO check to see if it works with cocos2d-x
  if (true || pTouches->count() == 0)
  {
    mInertialUpdating = false;
  }
//  CCLog("Touches count: %d", pTouches->count());
  
  // Check if moveOffset is higher than the threshold before moving layer
  if (abs(mMoveOffset.x) > mEndMovementThreshold || abs(mMoveOffset.y) > mEndMovementThreshold)
  {
    if (pTouches->count() == 1)
      setPosition(ccpSub(getPosition(), mMoveOffset));
    else if (pTouches->count() == 2)
      setPosition(ccpSub(getPosition(), mMoveOffset), false);
  }
  
  // Check if inertialMoveOffset is higher than the threshold before enabling inertialMoving
  if (abs(mInertialMoveOffset.x) > mEndMovementThreshold || abs(mInertialMoveOffset.y) > mEndMovementThreshold) {
    mInertialMoving = true;
  }
  
  // Do not reset dragged_ as it is checked
  // on subclassed (void)ccTouchesEnded:(NSSet*)touches withEvent:(UIEvent *)event
  mDragging = false;
  mZooming = false;
}

void ScrollableMap::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
  mDragged = false;
  mDragging = false;
  mZooming = false;
}

void ScrollableMap::updateParametersWithTouches(cocos2d::CCSet *pTouches)
{
  if (pTouches->count() == 1)
  {
    CCTouch* touch = (CCTouch*) pTouches->anyObject();
    
    mMoveOffset = ccpSub(touch->getLocationInView(),
                         touch->getPreviousLocationInView());
    mMoveOffset.x *= -1;
	}
  else if (pTouches->count() == 2)
  {
    CCSetIterator it = pTouches->begin();
    
		CCTouch* firstTouch = (CCTouch*) (*it);
		CCTouch* secondTouch = (CCTouch*) (*(it++));
    
		CCPoint firstTouchLocation = firstTouch->getLocationInView();
		CCPoint secondTouchLocation = secondTouch->getLocationInView();
    
    CCPoint currentMiddlePoint = ccpLerp(firstTouchLocation, secondTouchLocation, 0.5);
    float currentDistance = ccpDistance(firstTouchLocation, secondTouchLocation);
    
    firstTouchLocation = firstTouch->getPreviousLocationInView();
    secondTouchLocation = secondTouch->getPreviousLocationInView();
    
    CCPoint previousMiddlePoint = ccpLerp(firstTouchLocation, secondTouchLocation, 0.5);
		float previousDistance = ccpDistance(firstTouchLocation, secondTouchLocation);
    
    //        CCLOG(@"currentDistance: %f, previousDistance: %f, currentDistance/ previousDistance: %f",currentDistance, previousDistance, currentDistance/previousDistance);
    //        CCLOG(@"currentMiddlePoint: %@, previousMiddlePoint: %@",NSStringFromCGPoint(currentMiddlePoint), NSStringFromCGPoint(previousMiddlePoint));
    
    mMoveOffset = ccpSub(currentMiddlePoint, previousMiddlePoint);
    mMoveOffset.x *= -1;
    
    mZoomFactor *= (currentDistance/previousDistance);
    // zoom in
    if (mZoomFactor > mMaxZoomFactor)
    {
      mZoomFactor = mMaxZoomFactor;
    }
    else if (mZoomFactor < mMinZoomFactor)
    {
      mZoomFactor = mMinZoomFactor;
    }
    // CCLOG(@"ScrollableMap ccTouchesMoved, 2 touches, zoomfactor: %f",zoomFactor_);
    
    double previousZoomFactor = getScale();
    
    setScale(mZoomFactor);
    setPosition(ccpAdd(ccpMult(ccpSub(getPosition(), currentMiddlePoint),
                                       mZoomFactor/previousZoomFactor), currentMiddlePoint));
	}
  
  // Round to avoid partial-pixel positions
  mMoveOffset = ccp(round(mMoveOffset.x), round(mMoveOffset.y));
}

// Overrides CCNode's setPosition:.
// Controls end of map limits and provides "rubber band" behaviour
void ScrollableMap::setPosition(const CCPoint& pPosition)
{
  setPosition(pPosition, enableRubberbandScrolling);
}

void ScrollableMap::setPosition(const cocos2d::CCPoint &pPosition, bool pWithRubberband)
{
  CCPoint position = pPosition;
  
  if (pWithRubberband)
  {
    if (position.x < mMinXPos || position.y < mMinYPos ||
        position.x > mMaxXPos || position.y > mMaxYPos)
    {
      position = ccpLerp(getPosition(), pPosition, 1/3.0);
      
      if (!mRubberbandShouldReturn && !mAutoScrolling) {
        mRubberbandShouldReturn = true;
      }
    }
  }
  else
  {
    if (position.x < mMinXPos)
      position.x = mMinXPos;
    if (position.y < mMinYPos)
      position.y = mMinYPos;
    if (position.x > mMaxXPos)
      position.x = mMaxXPos;
    if (position.y > mMaxYPos)
      position.y = mMaxYPos;
  }
  
  CCNode::setPosition(position);
}

void ScrollableMap::setScale(float pScale)
{
  CCNode::setScale(pScale);
  
  // Update zoomFactor if it's different from the desired scale
  if (mZoomFactor != pScale)
  {
    mZoomFactor = pScale;
  }
  
  // Update map bounds to reflect new scale
  mMinXPos = -boundingBox().size.width + MAX_X_POS;
  mMaxXPos = 0;
  mMinYPos = -boundingBox().size.height + MAX_Y_POS;
  mMaxYPos = 0;
}

void ScrollableMap::setContentSize(const cocos2d::CCSize &pContentSize)
{
  CCNode::setContentSize(pContentSize);
  
  mMinXPos = -boundingBox().size.width+MAX_X_POS;
  mMaxXPos = 0;
  mMinYPos = -boundingBox().size.height+MAX_Y_POS;
  mMaxYPos = 0;
}

bool ScrollableMap::scrolledAtTop()
{
  return getPositionY() <= MIN_Y_POS;
}

bool ScrollableMap::scrolledAtBottom()
{
  return getPositionY() >= MAX_Y_POS;
}

//TODO FIXME
bool ScrollableMap::scrolledToPoint(cocos2d::CCPoint pPoint, float pThreshold)
{
return true;
}