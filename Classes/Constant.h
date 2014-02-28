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

// WinScene
#define BTN_REPLAY_POS      ccp(84, 80)
#define BTN_SHARE_POS       ccp(330, 236)
#define WINNER_POS      ccp(320, 654)


enum eGround
{
  GR_BACKGROUND,
  GR_MIDDLEGROUND,
  GR_FOREGROUND
};

#endif
