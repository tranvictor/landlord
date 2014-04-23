//
//  GameManager Tests.m
//  landlord
//
//  Created by Tuan TQ on 4/14/14.
//
//

#import <SenTestingKit/SenTestingKit.h>
#import "GameManager.h"
#import "Constant.h"
#import "cocos2d.h"

@interface GameManager_Tests : SenTestCase

@end

@implementation GameManager_Tests

- (void) testInitialMusicState
{
  GameManager gameManager;
  STAssertEquals(true, gameManager.getMusicState(), @"initial music state is true");
  
  gameManager.setMusicState();
  STAssertEquals(false, gameManager.getMusicState(), @"change music state to false");
  
  gameManager.setMusicState();
  gameManager.setMusicState();
  STAssertEquals(false, gameManager.getMusicState(), @"change music state twice");
}

- (void) testInitialSoundState
{
  GameManager gameManager;
  STAssertEquals(true, gameManager.getSoundState(), @"initial sound state is true");
  
  gameManager.setSoundState();
  STAssertEquals(false, gameManager.getSoundState(), @"change sound state to false");
  
  gameManager.setSoundState();
  gameManager.setSoundState();
  STAssertEquals(false, gameManager.getSoundState(), @"change sound state twice");
}

- (void) testInitialTreeModeState
{
  GameManager gameManager;
  STAssertEquals(true, gameManager.getTreeModeState(), @"initial tree mode state is true");
  
  gameManager.setTreeModeState();
  STAssertEquals(false, gameManager.getTreeModeState(), @"change tree mode state to false");
  
  gameManager.setTreeModeState();
  gameManager.setTreeModeState();
  STAssertEquals(false, gameManager.getTreeModeState(), @"change tree mode state twice");
}

- (void) testInitialPlayerOneID
{
  GameManager gameManager;
  STAssertEquals(-1, gameManager.getPlayerOneID(), @"initial player one ID is -1");
  
  gameManager.setPlayerOneID(4);
  STAssertEquals(4, gameManager.getPlayerOneID(), @"set player one ID of 4");
}

- (void) testInitialPlayerTwoID
{
  GameManager gameManager;
  STAssertEquals(-1, gameManager.getPlayerTwoID(), @"initial player two ID is -1");
  
  gameManager.setPlayerTwoID(7);
  STAssertEquals(7, gameManager.getPlayerTwoID(), @"set player two ID of 7");
}

- (void) testIncreaseAndGetPlayerScore
{
  GameManager gameManager;
  STAssertEquals(0, gameManager.getPlayerScore(PLAYER_ONE), @"initial player one score is 0");
  STAssertEquals(0, gameManager.getPlayerScore(PLAYER_TWO), @"initial player two score is 0");
  
  gameManager.increaseScore(PLAYER_ONE);
  STAssertEquals(1, gameManager.getPlayerScore(PLAYER_ONE), @"increase player one score to 1");
  
  gameManager.increaseScore(PLAYER_TWO);
  gameManager.increaseScore(PLAYER_TWO);
  STAssertEquals(2, gameManager.getPlayerScore(PLAYER_TWO), @"increase player two scores to 2");
}

- (void) testGetAndSetMapIDTouched
{
  GameManager gameManager;
  STAssertEquals(-1, gameManager.getMapIDTouched(), @"invalid map ID");
  
  gameManager.setMapIDTouched(5);
  STAssertEquals(5, gameManager.getMapIDTouched(), @"set touched map ID is 5");
}

- (void) testInitialPlayersInfo
{
  GameManager gameManager;
  gameManager.initPlayersInfo();
  
  STAssertEquals(0, gameManager.getPlayerScore(PLAYER_ONE), @"initial player one score is 0");
  STAssertEquals(0, gameManager.getPlayerScore(PLAYER_TWO), @"initial player two score is 0");
  STAssertEquals(PLAYER_ONE, gameManager.getCurrentPlayer(), @"initial current player is player one");
}

- (void) testGetAndChangeCurrentPlayer
{
  GameManager gameManager;
  gameManager.initPlayersInfo();
  STAssertEquals(PLAYER_ONE, gameManager.getCurrentPlayer(), @"initial current player is 1");
  
  gameManager.changeCurrentPlayer();
  STAssertEquals(PLAYER_TWO, gameManager.getCurrentPlayer(), @"change current player to 2");
  
  gameManager.changeCurrentPlayer();
  gameManager.changeCurrentPlayer();
  STAssertEquals(PLAYER_TWO, gameManager.getCurrentPlayer(), @"change current player twice");
}

- (void) testGetAndSetWinPlayer
{
  GameManager gameManager;
  gameManager.setWinPlayer(PLAYER_ONE);
  STAssertEquals(PLAYER_ONE, gameManager.getWinPlayer(), @"set win player is player one");
  
  gameManager.setWinPlayer(PLAYER_TWO);
  STAssertEquals(PLAYER_TWO, gameManager.getWinPlayer(), @"set win player is player two");
}

- (void) testGetAndSetNumOfTrees
{
  GameManager gameManager;
  
  gameManager.setNumOfTrees(5);
  STAssertEquals(5, gameManager.getNumOfTrees(), @"number of trees is 5");
  
  gameManager.setNumOfTrees(10);
  gameManager.setNumOfTrees(7);
  STAssertEquals(7, gameManager.getNumOfTrees(), @"number of trees is 7");
}

- (void) testGetNumOfAxes
{
  GameManager gameManager;
  gameManager.increaseNumOfAxes(PLAYER_ONE);
  gameManager.increaseNumOfAxes(PLAYER_TWO);
  gameManager.decreaseNumOfAxes(PLAYER_TWO);
  
  STAssertEquals(1, gameManager.getNumOfAxes(PLAYER_ONE), @"number of axes of player one is 1");
  STAssertEquals(0, gameManager.getNumOfAxes(PLAYER_TWO), @"number of axes of player two is 0");
}

- (void) testGetAndSetNumOfStones
{
  GameManager gameManager;
  
  gameManager.setNumOfStones(6);
  STAssertEquals(6, gameManager.getNumOfStones(), @"number of stones is 6");
  
  gameManager.setNumOfStones(3);
  gameManager.setNumOfStones(4);
  STAssertEquals(4, gameManager.getNumOfStones(), @"number of stones is 4");
}

@end
