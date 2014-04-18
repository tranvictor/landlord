//
//  Sound Tests.m
//  landlord
//
//  Created by Tuan TQ on 4/18/14.
//
//

#import <SenTestingKit/SenTestingKit.h>
#import "cocos2d.h"
#import "CocosDenshion.h"
#import "SimpleAudioEngine.h"
#import "Sound.h"
#import "StartScene.h"

@interface Sound_Tests : SenTestCase

@end

@implementation Sound_Tests

- (void)setUp
{
  [super setUp];
  // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
  [super tearDown];
}

- (void) testInitialValues
{
  sound *sound;
  STAssertEquals(true, sound->getMusicState(), @"initial music state is on");
  STAssertEquals(true, sound->getSoundFxState(), @"initial soundFx state is on");
}

- (void) testPlayBackgroundMusic
{
  StartScene *start;
  start = StartScene::create();
  cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
  pDirector->runWithScene(start->scene());
  CocosDenshion::SimpleAudioEngine *pAudio = CocosDenshion::SimpleAudioEngine::sharedEngine();
  STAssertEquals(false, pAudio->isBackgroundMusicPlaying(), @"background music must be playing");
  
  sound *sound;
  sound->playBackgroundMusic();
  pAudio = CocosDenshion::SimpleAudioEngine::sharedEngine();
  STAssertFalse(pAudio->isBackgroundMusicPlaying() == true, @"background music must be playing");
}



@end
