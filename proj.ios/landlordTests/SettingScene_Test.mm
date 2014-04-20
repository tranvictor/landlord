//
//  StartScene_Test.m
//  landlord
//
//  Created by Giap Nguyen on 4/17/14.
//
//

#import <SenTestingKit/SenTestingKit.h>
#import "SettingScene.h"
#import "cocos2d.h"
#import "Sound.h"
#import "SimpleAudioEngine.h"
#import "Constant.h"

@interface SettingScene_Test : SenTestCase

@end

@implementation SettingScene_Test

SettingScene *setting;

- (void)setUp
{
  [super setUp];
  // Put setup code here. This method is called before the invocation of each test method in the class.
  setting = SettingScene::create();
  cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
  pDirector->runWithScene(setting->scene());
}

- (void)tearDown
{
  // Put teardown code here. This method is called after the invocation of each test method in the class.
  setting = NULL;
  CC_SAFE_DELETE(setting);
  [super tearDown];
}

- (void)testClassExists
{
  STAssertTrue(setting != NULL, @"instance creates from SettingScene should not be NULL");
}
@end
