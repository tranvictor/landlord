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
#import "GameManager.h"
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

- (void)testSoundFXTouched
{
  bool preVal = GameManager::getSoundState();
  setting->soundFxTouched(NULL);
  STAssertTrue(GameManager::getSoundState() != preVal, @"change sound state");
}

- (void)testTreeModeTouched
{
  bool preVal = GameManager::getTreeModeState();
  setting->treeModeTouched(NULL);
  STAssertTrue(GameManager::getTreeModeState() != preVal, @"change tree state");
}

- (void)testMusicTouched
{
  bool preVal = GameManager::getMusicState();
  setting->musicTouched(NULL);
  STAssertTrue(GameManager::getMusicState() != preVal, @"change music state");
}

- (void)testBackButtonTouched
{
  // TODO
}
@end
