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

#define SCREEN_SIZE             CCDirector::sharedDirector()->getWinSize()
#define CENTER_POS              ccp(SCREEN_SIZE.width/2, SCREEN_SIZE.height/2)
// ChooseMapScene
#define BTN_RANDOM_POS          ccp(320, 245)
#define BTN_BACK_POS            ccp(49, 46)
#define NUMBER_MAPS             10
#define MAP_CENTER_POS          ccp(320, 357)
#define MAP_CENTER_X            320
#define MAP_CENTER_Y            779
#define MAP_WIDTH               328
#define DISTANCE_BETWEEN_MAPS   444
#define GREEN_DOT_Y             419

// PlayScene
#define BTN_PAUSE_POS           ccp(320, 158.27)
#define MAP_POS                 ccp(320.5, 657.338)
#define PLAYER_ONE_POS          ccp(97.192, 142.551)
#define PLAYER_TWO_POS          ccp(543.762, 142.551)
#define LBN_SCORE_PLAYER1_POS   ccp(109.114, 37.093)
#define LBN_SCORE_PLAYER2_POS   ccp(531.229, 37.093)
#define NUMBER_EDGE_AVAILABLE   4
#define PAIR_FUNC(a,b)          (int)(0.5*(a+b)*(a+b+1)+b)  // return the unique number from a, b

// ChooseCharacterScene
#define NUMBER_CHARACTERS       8
#define NUMBER_CHARACTERS_PER_SCENE 4
#define C1_POS                  ccp(173.25, 813.45)
#define C2_POS                  ccp(485.489, 798.445)
#define C3_POS                  ccp(173.25, 340.866)
#define C4_POS                  ccp(485.489, 341.326)
#define C5_POS                  ccp(177.743,	793.425)
#define C6_POS                  ccp(489.982,	797.344)
#define C7_POS                  ccp(177.743,	333.692)
#define C8_POS                  ccp(489.982,	313.253)
#define BTN_BACK                ccp(75, 69.869)
#define INDICATOR_POS_Y         86.738

// WinScene
#define BTN_REPLAY_POS          ccp(84, 80)
#define BTN_SHARE_POS           ccp(330, 236)
#define WINNER_START_POS        ccp(320, 654-400)
#define WINNER_POS              ccp(320, 654)

// Sound
#define SFX_BUTTON_TOUCH        "Sound/SFX/ui-button-tap.aac"
#define MUSIC_BACKGROUND        "Sound/Music/music-in-game.wav"
#define SFX_CHARACTER_SELECT    "Sound/SFX/ui-character-select.aac"
#define SFX_RANDOM_MAP          "Sound/SFX/sfx-random-map.aac"
#define SFX_CHOOSE_MAP          "Sound/SFX/sfx-choose-map.aac"
#define SFX_TOUCH_TILE          "Sound/SFX/sfx-touch-tile.aac"
#define SFX_TOUCH_POP           "Sound/SFX/sfx-touch-pop.wav"
#define SFX_CONGRATULATION      "Sound/SFX/sfx-congratulate.acc"
#define MUSIC_LEVEL_WON         "Sound/Music/music_level-won.mp3"

enum eGround
{
  GR_BACKGROUND,
  GR_MIDDLEGROUND,
  GR_FOREGROUND
};

enum eStartSceneTag
{
  BTN_SETTINGS_TAG,
  START_BG_TAG,
  BTN_PLAY_TAG
};

enum eTag
{
  TG_TILE
};

enum eTagEdge
{
  TAG_EDGE_TOP,
  TAG_EDGE_BOTTOM,
  TAG_EDGE_LEFT,
  TAG_EDGE_RIGHT
};

enum eEdgeStatus
{
  STS_AVAILABLE,
  STS_NOT_AVAILABLE,
};

enum eCurrentPlayer
{
  PLAYER_ONE = 1,
  PLAYER_TWO = 2,
};

enum eChooseCharacterSceneTags
{
  CHOOSECHARACTER_BG_TAG,
  CHOOSECHARACTER_BACKBTN_TAG,
};

enum eWinSceneTags
{
  WIN_BG_TAG,
  WIN_MASK_TAG,
  WIN_SHAREBTN_TAG,
  WIN_REPLAYBTN_TAG,
};

#endif
