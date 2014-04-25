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
  STAssertEquals(true, GameManager::getMusicState(), @"initial music state is true");
  
  GameManager::setMusicState();
  STAssertEquals(false, GameManager::getMusicState(), @"change music state to false");
  
  GameManager::setMusicState();
  GameManager::setMusicState();
  STAssertEquals(false, GameManager::getMusicState(), @"change music state twice");
}

- (void) testInitialSoundState
{
  ;
  STAssertEquals(true, GameManager::getSoundState(), @"initial sound state is true");
  
  GameManager::setSoundState();
  STAssertEquals(false, GameManager::getSoundState(), @"change sound state to false");
  
  GameManager::setSoundState();
  GameManager::setSoundState();
  STAssertEquals(false, GameManager::getSoundState(), @"change sound state twice");
}

- (void) testInitialTreeModeState
{
  ;
  STAssertEquals(true, GameManager::getTreeModeState(), @"initial tree mode state is true");
  
  GameManager::setTreeModeState();
  STAssertEquals(false, GameManager::getTreeModeState(), @"change tree mode state to false");
  
  GameManager::setTreeModeState();
  GameManager::setTreeModeState();
  STAssertEquals(false, GameManager::getTreeModeState(), @"change tree mode state twice");
}

- (void) testInitialPlayerOneID
{
  GameManager::setPlayerOneID(4);
  STAssertEquals(4, GameManager::getPlayerOneID(), @"set player one ID of 4");
}

- (void) testInitialPlayerTwoID
{
  GameManager::setPlayerTwoID(7);
  STAssertEquals(7, GameManager::getPlayerTwoID(), @"set player two ID of 7");
}

- (void) testIncreaseAndGetPlayerScore
{
  STAssertEquals(0, GameManager::getPlayerScore(PLAYER_ONE), @"initial player one score is 0");
  STAssertEquals(0, GameManager::getPlayerScore(PLAYER_TWO), @"initial player two score is 0");
  
  GameManager::increaseScore(PLAYER_ONE);
  STAssertEquals(1, GameManager::getPlayerScore(PLAYER_ONE), @"increase player one score to 1");
  
  GameManager::increaseScore(PLAYER_TWO);
  GameManager::increaseScore(PLAYER_TWO);
  STAssertEquals(2, GameManager::getPlayerScore(PLAYER_TWO), @"increase player two scores to 2");
}

- (void) testGetAndSetMapIDTouched
{
  STAssertEquals(-1, GameManager::getMapIDTouched(), @"invalid map ID");
  
  GameManager::setMapIDTouched(5);
  STAssertEquals(5, GameManager::getMapIDTouched(), @"set touched map ID is 5");
}

- (void) testInitialPlayersInfo
{
  GameManager::initPlayersInfo();
  
  STAssertEquals(0, GameManager::getPlayerScore(PLAYER_ONE), @"initial player one score is 0");
  STAssertEquals(0, GameManager::getPlayerScore(PLAYER_TWO), @"initial player two score is 0");
  STAssertEquals(PLAYER_ONE, GameManager::getCurrentPlayer(), @"initial current player is player one");
}

- (void) testGetAndChangeCurrentPlayer
{
  GameManager::initPlayersInfo();
  STAssertEquals(PLAYER_ONE, GameManager::getCurrentPlayer(), @"initial current player is 1");
  
  GameManager::changeCurrentPlayer();
  STAssertEquals(PLAYER_TWO, GameManager::getCurrentPlayer(), @"change current player to 2");
  
  GameManager::changeCurrentPlayer();
  GameManager::changeCurrentPlayer();
  STAssertEquals(PLAYER_TWO, GameManager::getCurrentPlayer(), @"change current player twice");
}

- (void) testGetAndSetWinPlayer
{
  GameManager::setWinPlayer(PLAYER_ONE);
  STAssertEquals(PLAYER_ONE, GameManager::getWinPlayer(), @"set win player is player one");
  
  GameManager::setWinPlayer(PLAYER_TWO);
  STAssertEquals(PLAYER_TWO, GameManager::getWinPlayer(), @"set win player is player two");
}

- (void) testGetAndSetNumOfTrees
{
  GameManager::setNumOfTrees(5);
  STAssertEquals(5, GameManager::getNumOfTrees(), @"number of trees is 5");
  
  GameManager::setNumOfTrees(10);
  GameManager::setNumOfTrees(7);
  STAssertEquals(7, GameManager::getNumOfTrees(), @"number of trees is 7");
}

- (void) testGetNumOfAxes
{
  GameManager::increaseNumOfAxes(PLAYER_ONE);
  GameManager::increaseNumOfAxes(PLAYER_TWO);
  GameManager::decreaseNumOfAxes(PLAYER_TWO);
  
  STAssertEquals(1, GameManager::getNumOfAxes(PLAYER_ONE), @"number of axes of player one is 1");
  STAssertEquals(0, GameManager::getNumOfAxes(PLAYER_TWO), @"number of axes of player two is 0");
}

- (void) testGetAndSetNumOfStones
{
  GameManager::setNumOfStones(6);
  STAssertEquals(6, GameManager::getNumOfStones(), @"number of stones is 6");
  
  GameManager::setNumOfStones(3);
  GameManager::setNumOfStones(4);
  STAssertEquals(4, GameManager::getNumOfStones(), @"number of stones is 4");
}

@end
