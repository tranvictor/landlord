//
//  ChooseMapScene_Test.m
//  landlord
//
//  Created by Giap Nguyen on 4/18/14.
//
//

#import <SenTestingKit/SenTestingKit.h>
#import "ChooseMapScence.h"
#import "cocos2d.h"
#import "GameManager.h"

@interface ChooseMapScene_Test : SenTestCase

@end

@implementation ChooseMapScene_Test

ChooseMapScene *chooseMap;

- (void)setUp
{
  [super setUp];
  chooseMap = ChooseMapScene::create();
  cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
  pDirector->runWithScene(chooseMap->scene());
  // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
  // Put teardown code here. This method is called after the invocation of each test method in the class.
  chooseMap = NULL;
  CC_SAFE_DELETE(chooseMap);
  [super tearDown];
}

- (void)testChooseMapExists
{
  STAssertTrue(chooseMap != NULL, @"choosemap should not be null");
}

- (void)testMapTouched
{
  chooseMap->mapTouched(((CCLayer*)chooseMap->getMapArr()->objectAtIndex(2))->getChildByTag(2));
  STAssertTrue(GameManager::getMapIDTouched() == 1, @"choose map 1");
  
}
@end
