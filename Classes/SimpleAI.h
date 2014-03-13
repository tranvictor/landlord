//
//  SimpleAI.h
//  landlord
//
//  Created by HaLink on 3/12/14.
//
//

#ifndef landlord_SimpleAI_h
#define landlord_SimpleAI_h

#include "TileInfo.h"

class SimpleAI
{
private:
  static std::vector<int> queue;
  static int qfirst;
  static int qlast;
  
public:
  static std::vector<int> tileAccepted;
  static std::vector<TileInfo*> tileArr;
  
  static void initQueue();
  static void push(int pSender);
  static int pop();
  static bool qEmpty();
  static void Breath_First_Search(int ptileIndex_i, int ptileIndex_j);
};
#endif
