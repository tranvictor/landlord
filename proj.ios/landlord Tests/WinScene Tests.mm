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

@interface WinScene_Tests : SenTestCase

@end

@implementation WinScene_Tests

WinScene *win;

- (void)setUp
{
  [super setUp];
  // Put setup code here. This method is called before the invocation of each test method in the class.
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
  win->addBackground();
  CCObject *obj = win->getChildByTag(WIN_BG_TAG);
  STAssertTrue(obj != NULL, @"background added");
  STAssertTrue(((CCSprite*)obj)->getPosition().equals(CCPoint(SCREEN_SIZE.width/2, SCREEN_SIZE.height/2)), @"background position");
}


@end
