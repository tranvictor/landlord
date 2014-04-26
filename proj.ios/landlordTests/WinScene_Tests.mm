//
//  WinScene Tests.m
//  landlord
//
//  Created by Tuan TQ on 4/18/14.
//
//

#import <SenTestingKit/SenTestingKit.h>
#import "WinScene.h"
#import "cocos2d.h"
#import "GameManager.h"

@interface WinScene_Tests : SenTestCase

@end

@implementation WinScene_Tests

WinScene *win;

- (void)setUp
{
  [super setUp];
  // Put setup code here. This method is called before the invocation of each test method in the class.
  GameManager::setPlayerOneID(1);
  GameManager::setPlayerTwoID(3);
  win = WinScene::create();
  cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
  pDirector->runWithScene(win->scene());
}

- (void)tearDown
{
  // Put teardown code here. This method is called after the invocation of each test method in the class.
  [super tearDown];
  win = NULL;
  CC_SAFE_DELETE(win);
}

- (void) testAddBackground
{
  CCObject *obj = win->getChildByTag(WIN_BG_TAG);
  STAssertTrue(obj != NULL, @"background added");
  STAssertTrue(((CCSprite*)obj)->getPosition().equals(CCPoint(SCREEN_SIZE.width/2, SCREEN_SIZE.height/2)), @"background is center of the screen");
}

//- (void) testAddMask
//{
//  CCObject *obj = win->getChildByTag(WIN_MASK_TAG);
//  STAssertTrue(obj != NULL, @"mask added");
//  STAssertTrue(((CCSprite*)obj)->getPosition().equals(CCPoint(SCREEN_SIZE.width/2, SCREEN_SIZE.height/2)), @"mask is center of the screen");
//}

- (void) testAddButtonShare
{
  CCObject *obj = win->getChildByTag(WIN_SHAREBTN_TAG);
  STAssertTrue(obj != NULL, @"button share added");
  STAssertTrue(((CCMenu*)obj)->getPosition().equals(BTN_SHARE_POS), @"button share position must be BTN_SHARE_POS");
}

- (void) testButtonShareTouched
{
  
}

- (void) testAddButtonReplay
{
  CCObject *obj = win->getChildByTag(WIN_REPLAYBTN_TAG);
  STAssertTrue(obj != NULL, @"button replay added");
  STAssertTrue(((CCMenu*)obj)->getPosition().equals(BTN_REPLAY_POS), @"button share position must be BTN_REPLAY_POS");
}

- (void) testButtonReplayTouched
{
  
}

@end
