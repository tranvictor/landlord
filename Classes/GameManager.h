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
  static int  playerOneID;
  static int  playerTwoID;
  static int  mapIDTouched;

  static int player1Score;
  static int player2Score;
  static bool currentPlayer; // true = P1, false = P2
  static bool winPlayer;
  static int numberOfTilesChose;
public:
  static bool getMusicState();
  static void setMusicState();
  
  static bool getSoundState();
  static void setSoundState();
  
  static bool getTreeModeState();
  static void setTreeModeState();
  
  static void setPlayerOneID(int ID);
  static int getPlayerOneID();
  
  static void setPlayerTwoID(int ID);
  static int getPlayerTwoID();
  
  static void setMapIDTouched(int ID);
  static int getMapIDTouched();

  static void initPlayersInfo();
  static void increaseScore(bool currentPlayer);
  static int getPlayerScore(bool currentPlayer);
  static bool getCurrentPlayer();
  static void changeCurrentPlayer();
  static void setWinPlayer(bool _currentPlayer);
  static bool getWinPlayer();

};

#endif
