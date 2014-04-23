//
//  ChooseCharacterScene Tests.m
//  landlord
//
//  Created by Tuan TQ on 4/18/14.
//
//

#import <SenTestingKit/SenTestingKit.h>
#import "ChooseCharacterScene.h"
#import "cocos2d.h"
#import "cocos-ext.h"
#import "Constant.h"
#import "GameManager.h"

@interface ChooseCharacterScene_Tests : SenTestCase

@end

@implementation ChooseCharacterScene_Tests

ChooseCharacterScene *character;

- (void)setUp
{
  [super setUp];
  // Put setup code here. This method is called before the invocation of each test method in the class.
  character = ChooseCharacterScene::create();
  cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
  pDirector->runWithScene(character->scene());
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
  character = NULL;
  CC_SAFE_DELETE(character);
  [super tearDown];
}

- (void) testAddBackground
{
  CCObject *obj = character->getChildByTag(CHOOSECHARACTER_BG_TAG);
  STAssertTrue(obj != NULL, @"background added");
  STAssertTrue(((CCSprite*)obj)->getPosition().equals(CENTER_POS), @"background position");
}

- (void) testAddBackButton
{
  CCObject *obj = character->getChildByTag(CHOOSECHARACTER_BACKBTN_TAG);
  STAssertTrue(obj != NULL, @"button back added");
  STAssertTrue(((CCMenu*)obj)->getPosition().equals(BTN_BACK), @"button back position");
}

- (void) testAddCharactersToLayer
{
  CCArray* arr = character->getCharacterArr();
  arr->retain();
  
  CCObject *obj = arr->objectAtIndex(0);
  STAssertTrue(((CCLayer*)obj) != NULL, @"layer 0 is not NULL");
  
  STAssertTrue(((CCLayer*)obj)->getChildByTag(1) != NULL , @"character 1 is not NULL");
  STAssertTrue(((CCLayer*)obj)->getChildByTag(2) != NULL , @"character 2 is not NULL");
  STAssertTrue(((CCLayer*)obj)->getChildByTag(3) != NULL , @"character 3 is not NULL");
  STAssertTrue(((CCLayer*)obj)->getChildByTag(4) != NULL , @"character 4 is not NULL");
  
  obj = arr->objectAtIndex(1);
  STAssertTrue(((CCLayer*)obj) != NULL, @"layer 1 is not NULL");
  STAssertTrue(((CCLayer*)obj)->getChildByTag(5) != NULL , @"character 5 is not NULL");
  STAssertTrue(((CCLayer*)obj)->getChildByTag(6) != NULL , @"character 6 is not NULL");
  STAssertTrue(((CCLayer*)obj)->getChildByTag(7) != NULL , @"character 7 is not NULL");
  STAssertTrue(((CCLayer*)obj)->getChildByTag(8) != NULL , @"character 8 is not NULL");
  
  arr->release();
}

- (void) testCharactersPosition
{
  CCArray* arr = character->getCharacterArr();
  arr->retain();
  
  CCObject *obj = arr->objectAtIndex(0);
  CCNode *chrt = ((CCLayer*)obj)->getChildByTag(1);
  STAssertTrue(((CCMenu*)chrt)->getPosition().equals(C1_POS), @"position of character 1 is C1_POS");
  chrt = ((CCLayer*)obj)->getChildByTag(2);
  STAssertTrue(((CCMenu*)chrt)->getPosition().equals(C2_POS), @"position of character 2 is C2_POS");
  chrt = ((CCLayer*)obj)->getChildByTag(3);
  STAssertTrue(((CCMenu*)chrt)->getPosition().equals(C3_POS), @"position of character 3 is C3_POS");
  chrt = ((CCLayer*)obj)->getChildByTag(4);
  STAssertTrue(((CCMenu*)chrt)->getPosition().equals(C4_POS), @"position of character 4 is C4_POS");
  
  obj = arr->objectAtIndex(1);
  chrt = ((CCLayer*)obj)->getChildByTag(5);
  STAssertTrue(((CCMenu*)chrt)->getPosition().equals(C5_POS), @"position of character 5 is C5_POS");
  chrt = ((CCLayer*)obj)->getChildByTag(6);
  STAssertTrue(((CCMenu*)chrt)->getPosition().equals(C6_POS), @"position of character 6 is C6_POS");
  chrt = ((CCLayer*)obj)->getChildByTag(7);
  STAssertTrue(((CCMenu*)chrt)->getPosition().equals(C7_POS), @"position of character 7 is C7_POS");
  chrt = ((CCLayer*)obj)->getChildByTag(8);
  STAssertTrue(((CCMenu*)chrt)->getPosition().equals(C8_POS), @"position of character 8 is C8_POS");
  
  arr->release();
}

- (void) testButtonBackTouched
{
  character->buttonBackTouched(NULL);
  CCScene *startScene = CCDirector::sharedDirector()->getRunningScene();
  STAssertTrue(startScene != NULL, @"touching back button should turn to start scene");
}

- (void) test2PlayersChooseSameCharacter
{
  character->characterTouched(((CCLayer *)character->getCharacterArr()->objectAtIndex(0))->getChildByTag(3));
  character->characterTouched(((CCLayer *)character->getCharacterArr()->objectAtIndex(0))->getChildByTag(3));
  STAssertTrue(GameManager::getPlayerTwoID() == -1, @"2 players cannot choose same character");
}

- (void) testChooseCharactersAndChangeScene
{
  character->characterTouched(((CCLayer *)character->getCharacterArr()->objectAtIndex(0))->getChildByTag(1));
  character->characterTouched(((CCLayer *)character->getCharacterArr()->objectAtIndex(1))->getChildByTag(5));
  STAssertTrue(GameManager::getPlayerOneID() == 1, @"get id of the 1st character");
  STAssertTrue(GameManager::getPlayerTwoID() == 5, @"get id of the 2nd character");
  CCScene *chooseMapScene = CCDirector::sharedDirector()->getRunningScene();
  STAssertTrue(chooseMapScene != NULL, @"after 2 players choose 2 different characters, game should turn to chooseMap scene");
}

@end
