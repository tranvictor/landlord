//
//  StartScene_Test.m
//  landlord
//
//  Created by Giap Nguyen on 4/17/14.
//
//

#import <SenTestingKit/SenTestingKit.h>
#import "StartScene.h"
#import "cocos2d.h"
#import "Sound.h"
#import "SimpleAudioEngine.h"
#import "Constant.h"

@interface StartScene_Test : SenTestCase

@end

@implementation StartScene_Test

StartScene *start;

- (void)setUp
{
  [super setUp];
  // Put setup code here. This method is called before the invocation of each test method in the class.
  start = StartScene::create();
  cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
  pDirector->runWithScene(start->scene());
}

- (void)tearDown
{
  // Put teardown code here. This method is called after the invocation of each test method in the class.
  start = NULL;
  CC_SAFE_DELETE(start);
  [super tearDown];
}

- (void)testClassExists
{
  STAssertTrue(start != NULL, @"instance creates from StartScene should not be NULL");
}

- (void)testBackgroundMusicIsOn
{
//  STAssertTrue(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying(), @"music is playing with Sound/background.wav");
}

- (void)testHasBackgroundLayer
{
  CCObject *obj = start->getChildByTag(START_BG_TAG);
  STAssertTrue(obj != NULL, @"start scene has background layer");
  STAssertTrue(((CCSprite*)obj)->getPosition().equals(CENTER_POS), @"backgound is at the center of screen");
}

- (void)testSettingsButtonExists
{
  CCObject *settings = start->getChildByTag(BTN_SETTINGS_TAG);
  STAssertTrue(settings != NULL, @"start scene must has a setting button");
};

- (void)testSettingButtonTouched
{
  // TODO
}

- (void)testPlayButtonExists
{
  CCObject *play = start->getChildByTag(BTN_PLAY_TAG);
  STAssertTrue(play != NULL, @"touch play button should change game scene to PlayScene");
}

- (void)testPlayButtonTouched
{
  // TODO
}

@end

