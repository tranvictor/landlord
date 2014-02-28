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
public:
  static bool getMusicState();
  static void setMusicState();
  static bool getSoundState();
  static void setSoundState();
  static bool getTreeModeState();
  static void setTreeModeState();
};

#endif
