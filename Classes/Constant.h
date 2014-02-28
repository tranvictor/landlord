//
//  Constant.h
//  landlord
//
//  Created by Giap Nguyen on 2/19/14.
//
//

#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include "cocos2d.h"

USING_NS_CC;
//  the gap between dot of indicator
#define GAP_BETWEEN_DOT 37.78f

#define SCREEN_SIZE     CCDirector::sharedDirector()->getWinSize()
// ChooseMapScene
#define BTN_RANDOM_POS  ccp(320, 245)
#define BTN_BACK_POS    ccp(49, 46)
#define NUMBER_MAPS     10
#define MAP_CENTER_POS  ccp(320, 357)
#define MAP_CENTER_X    320
#define MAP_CENTER_Y    779
#define MAP_WIDTH       328
#define DISTANCE_BETWEEN_MAPS   444
#define GREEN_DOT_Y     419

// PlayScene
#define BTN_PAUSE_POS   ccp(320, 158.27)
#define MAP_POS ccp(320.5, 657.338)
#define PLAYER_ONE_POS  ccp(97.192, 142.551)
#define PLAYER_TWO_POS  ccp(543.762, 142.551)
#define LBN_SCORE_PLAYER1_POS   ccp(109.114, 37.093)
#define LBN_SCORE_PLAYER2_POS   ccp(531.229, 37.093)

// ChooseCharacterScene
#define NUMBER_CHARACTERS 8
#define NUMBER_CHARACTERS_PER_SCENE 4
#define C1_POS ccp(173.25, 813.45)
#define C2_POS ccp(485.489, 798.445)
#define C3_POS ccp(173.25, 340.866)
#define C4_POS ccp(485.489, 341.326)
#define C5_POS ccp(177.743,	793.425)
#define C6_POS ccp(489.982,	797.344)
#define C7_POS ccp(177.743,	333.692)
#define C8_POS ccp(489.982,	313.253)
#define BTN_BACK ccp(75, 69.869)
#define INDICATOR_POS_Y 86.738

// WinScene
#define BTN_REPLAY_POS      ccp(84, 80)
#define BTN_SHARE_POS       ccp(330, 236)
#define WINNER_POS          ccp(320, 654)


enum eGround
{
  GR_BACKGROUND,
  GR_MIDDLEGROUND,
  GR_FOREGROUND
};

#endif
