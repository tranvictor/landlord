//
//  GameManager Tests.m
//  landlord
//
//  Created by Tuan TQ on 4/14/14.
//
//

#import <SenTestingKit/SenTestingKit.h>
#import "GameManager.h"

@interface GameManager_Tests : SenTestCase

@end

@implementation GameManager_Tests

- (void) testGetAndSetMusicState
{
  GameManager gameManager;
  STAssertEquals(true, gameManager.getMusicState(), @"initial music state is true");
  
  gameManager.setMusicState();
  STAssertEquals(false, gameManager.getMusicState(), @"change music state to false");
  
  gameManager.setMusicState();
  gameManager.setMusicState();
  STAssertEquals(false, gameManager.getMusicState(), @"change music state twice");
}

- (void) testGetAndSetSoundState
{
  GameManager gameManager;
  STAssertEquals(true, gameManager.getSoundState(), @"initial sound state is true");
  
  gameManager.setSoundState();
  STAssertEquals(false, gameManager.getSoundState(), @"change sound state to false");
  
  gameManager.setSoundState();
  gameManager.setSoundState();
  STAssertEquals(false, gameManager.getSoundState(), @"change sound state twice");
}

- (void) testGetAndSetTreeModeState
{
  GameManager gameManager;
  STAssertEquals(true, gameManager.getTreeModeState(), @"initial tree mode state is true");
  
  gameManager.setTreeModeState();
  STAssertEquals(false, gameManager.getTreeModeState(), @"change tree mode state to false");
  
  gameManager.setTreeModeState();
  gameManager.setTreeModeState();
  STAssertEquals(false, gameManager.getTreeModeState(), @"change tree mode state twice");
}

@end
