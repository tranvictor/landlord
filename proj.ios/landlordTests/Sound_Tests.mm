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
  sound *sound;
  sound->playBackgroundMusic();
  pAudio = CocosDenshion::SimpleAudioEngine::sharedEngine();
  STAssertTrue(pAudio->isBackgroundMusicPlaying(), @"background music must be playing");
}


- (void) testToggleMusic
{
  sound *sound;
  sound->toggleMusic();
  STAssertEquals(false, sound->getMusicState(), @"music state is turned to off");
  
  sound->toggleMusic();
  STAssertEquals(true, sound->getMusicState(), @"music state is turned to on");
}

- (void) testToggleSoundFx
{
  sound *sound;
  sound->toggleSoundFx();
  STAssertEquals(false, sound->getSoundFxState(), @"soundFx state is turned to off");
  
  sound->toggleSoundFx();
  STAssertEquals(true, sound->getSoundFxState(), @"soundFx state is turned to on");
}

@end
