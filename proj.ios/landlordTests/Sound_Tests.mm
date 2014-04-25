//
//  Sound Tests.m
//  landlord
//
//  Created by Tuan TQ on 4/18/14.
//
//

#import <SenTestingKit/SenTestingKit.h>
#import "cocos2d.h"
#import "SimpleAudioEngine.h"
#import "Sound.h"
#import "StartScene.h"
#import "Constant.h"

@interface Sound_Tests : SenTestCase

@end

@implementation Sound_Tests
StartScene* startS;

- (void)setUp
{
  [super setUp];
  // Put setup code here. This method is called before the invocation of each test method in the class.
  startS = StartScene::create();
  cocos2d::CCDirector* director = cocos2d::CCDirector::sharedDirector();
  director->runWithScene(startS->scene());
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
  [super tearDown];
}

- (void) testPlayBackgroundMusic
{
  CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::sharedEngine();
  
  if (!sound::getMusicState())
    sound::toggleMusic();
  sound::playBackgroundMusic(MUSIC_BACKGROUND);
  audio = CocosDenshion::SimpleAudioEngine::sharedEngine();
  STAssertTrue(audio->isBackgroundMusicPlaying(), @"background music must be playing");
}


- (void) testToggleMusic
{
  bool pre = sound::getMusicState();
  sound::toggleMusic();
  STAssertTrue(pre != sound::getMusicState(), @"music state is turned to off");
  
  pre = sound::getMusicState();
  sound::toggleMusic();
  STAssertTrue(pre != sound::getMusicState(), @"music state is turned to on");
}

- (void) testToggleSoundFx
{
  bool pre = sound::getSoundFxState();
  sound::toggleSoundFx();
  STAssertTrue(pre != sound::getSoundFxState(), @"soundFx state is turned to off");
  
  pre = sound::getSoundFxState();
  sound::toggleSoundFx();
  STAssertTrue(pre != sound::getSoundFxState(), @"soundFx state is turned to on");
}

@end
