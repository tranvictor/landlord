#ifndef __ScrollableMap_SCENE_H__
#define __ScrollableMap_SCENE_H__

#include "cocos2d.h"

#define TAG_SCROLL_ACTION 131
#define SCROLL_DURATION 0.3

enum eCCEaseInOut
{
  CCEIO_NONE,
  CCEIO_EASE_IN,
  CCEIO_EASE_OUT,
  CCEIO_EASE_IN_OUT
};

const float MAX_X_POS = 640;
const float MAX_Y_POS = 1136;
const float MIN_Y_POS = 0;

class ScrollableMap : public cocos2d::CCLayerRGBA
{
  const static bool enableRubberbandScrolling = false;
  
  // Structs
  cocos2d::CCPoint mMoveOffset;
  cocos2d::CCPoint mInertialMoveOffset;
  cocos2d::CCPoint mPreRubberbandPosition;
  cocos2d::CCPoint mFirstTouchPoint;
  
  // Variables
  int mEndMovementThreshold;
  float mElapsedTime;
  bool mInertialUpdating, mInertialMoving, mDragging, mZooming;
  bool mRubberbandShouldReturn;
  double mZoomFactor;
  
  short int mMinXPos, mMaxXPos, mMinYPos, mMaxYPos;
  
  // Synthesized variables
  CC_SYNTHESIZE(bool, mDragged, Dragged);
  CC_SYNTHESIZE(bool, mAutoScrolling, AutoScrolling);
  CC_SYNTHESIZE(double, mMaxZoomFactor, MaxZoomFactor);
  CC_SYNTHESIZE(double, mMinZoomFactor, MinZoomFactor);
  CC_SYNTHESIZE(int, mInitialMovementThreshold, InitialMovementThreshold);

  // Private functions
  void startAutoScroll();
  
public:
  virtual bool init();
  virtual void registerWithTouchDispatcher();

  void update(float pDt);
  
  void endAutoScroll();
  
  void updateInertialMoveOffset();
  void moveByInertialMoveOffsetWithDeltaTime(float pDt);
  void doRubberbandReturn();
  
  void scrollToPoint(const cocos2d::CCPoint& pPoint);
  void scrollToPoint(const cocos2d::CCPoint& pPoint, float pDuration);
  void scrollToPoint(const cocos2d::CCPoint& pPoint, float pDuration,
                     eCCEaseInOut pEaseInOut);
                     
  cocos2d::CCFiniteTimeAction* scrollActionToPoint(const cocos2d::CCPoint& pPoint);
  cocos2d::CCFiniteTimeAction* scrollActionToPoint(const cocos2d::CCPoint& pPoint,
                                                   float pDuration);
  cocos2d::CCFiniteTimeAction* scrollActionToPoint(const cocos2d::CCPoint& pPoint,
                                                   float pDuration,
                                                   eCCEaseInOut pEaseInOut);
  
  bool scrolledToPoint(cocos2d::CCPoint pPoint, float pThreshold);
  
  virtual void setPosition(const cocos2d::CCPoint& pPosition,
                           bool pWithRubberband);
  
  void updateParametersWithTouches(cocos2d::CCSet *pTouches);
  
  bool scrolledAtTop();
  bool scrolledAtBottom();
  
  // Touch handlers
  virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
  virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
  virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
  virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

  // Override 
  virtual void setScale(float pScale);
  virtual void setContentSize(const cocos2d::CCSize& contentSize);
  virtual void setPosition(const cocos2d::CCPoint& pPosition);
  CREATE_FUNC(ScrollableMap);

};

#endif
