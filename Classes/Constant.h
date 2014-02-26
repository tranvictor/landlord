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

// ChooseCharacterScene
#define NUMBER_CHARACTERS 8
#define C1_POS ccp(173.25, 813.45)
#define C2_POS ccp(485.489, 798.445)
#define C3_POS ccp(173.25, 340.866)
#define C4_POS ccp(485.489, 341.326)
#define C5_POS ccp(177.743,	793.425)
#define C6_POS ccp(489.982,	797.344)
#define C7_POS ccp(177.743,	333.692)
#define C8_POS ccp(489.982,	313.253)
#define BTN_BACK ccp(75, 69.869)
#define INDICATOR_POS ccp(290.631, 86.738)

enum eGround
{
  GR_BACKGROUND,
  GR_MIDDLEGROUND,
  GR_FOREGROUND
};

#endif
