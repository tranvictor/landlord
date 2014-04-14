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
  STAssertEquals(true, gameManager.getMusicState(), @"initial count is true");
  
  gameManager.setMusicState();
  STAssertEquals(false, gameManager.getMusicState(), @"change music state to false");
  
  gameManager.setMusicState();
  gameManager.setMusicState();
  STAssertEquals(false, gameManager.getMusicState(), @"change music state 2 times");
}

@end
