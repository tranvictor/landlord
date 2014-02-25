//
//  Maps.cpp
//  landlord
//
//  Created by Giap Nguyen on 2/19/14.
//
//

#include "Maps.h"

USING_NS_CC;

Maps* Maps::create(const char* pFileName)
{
  Maps *map = new Maps();
  if (map && map->init(pFileName))
  {
    map->autorelease();
    return map;
  }
  else
  {
    CC_SAFE_DELETE(map);
    return NULL;
  }
}

bool Maps::init(const char *pFileName)
{
  if (!CCSprite::initWithFile(pFileName))
  {
    return false;
  }
  return true;
}
