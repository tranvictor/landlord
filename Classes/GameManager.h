//
//  GameManager.h
//  landlord
//
//  Created by HaLink on 2/24/14.
//
//

#ifndef landlord_GameManager_h
#define landlord_GameManager_h

class GameManager
{
private:
  static bool musicState;
  static bool soundState;
  static bool treeModeState;
  static bool fogModeState;
  static int  playerOneID;
  static int  playerTwoID;
  static int  mapIDTouched;

  static int  player1Score;
  static int  player2Score;
  static int  currentPlayer;
  static int  winPlayer;
  
  static int  nTrees;
  
  static int  nAxes;
  static int  nAxesOfPlayerOne;
  static int  nAxesOfPlayerTwo;
  static int  nStones;
  
  static bool isInPlayScene;
public:
  static bool getMusicState();
  static void setMusicState();
  
  static bool getSoundState();
  static void setSoundState();
  
  static bool getTreeModeState();
  static void setTreeModeState();
  
  static bool getFogModeState();
  static void setFogModeState();
  
  static void setPlayerOneID(int ID);
  static int  getPlayerOneID();
  
  static void setPlayerTwoID(int ID);
  static int  getPlayerTwoID();
  
  static void setMapIDTouched(int ID);
  static int  getMapIDTouched();

  static void initPlayersInfo();
  static void increaseScore(int currentPlayer);
  static int  getPlayerScore(int currentPlayer);
  static int  getCurrentPlayer();
  static void changeCurrentPlayer();
  static void setWinPlayer(int _currentPlayer);
  static int  getWinPlayer();
  
  static void setNumOfTrees(int pNumOfTrees);
  static int  getNumOfTrees();
  
  static void setNumOfAxes(int pNumOfAxes);
  static int  getNumOfAxes(int pCurrentPlayer);
  static void increaseNumOfAxes(int pCurrentPlayer);
  static void decreaseNumOfAxes(int pCurrentPlayer);
  
  static int  getNumOfStones();
  static void setNumOfStones(int pNumOfStones);
  
  static bool getIsInPlayScene();
  static void setIsInPlayScene(bool pValue);
};

#endif
