//
//  Sound.h
//  landlord
//
//  Created by HaLink on 2/23/14.
//
//

#ifndef landlord_Sound_h
#define landlord_Sound_h

class sound
{
private:
  static bool music;
  static bool soundFx;
  
public:
  static void playBackgroundMusic();
  static void playSoundFx();
  static void toggleMusic();
  static void toggleSoundFx();
};

#endif
