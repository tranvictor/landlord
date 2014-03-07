//
//  TiledMap.cpp
//  landlord
//
//  Created by Tuan TQ on 3/6/14.
//
//

#include "TiledMap.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
  // 'scene' is an autorelease object
  CCScene *scene = CCScene::create();
  
  // 'layer' is an autorelease object
  HelloWorld *layer = HelloWorld::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
  if ( !CCLayer::init() )
  {
    return false;
  }
  
  _tileMap = new CCTMXTiledMap();
  _tileMap->initWithTMXFile("TileMap.tmx");
  _background = _tileMap->layerNamed("Background");
  
  this->addChild(_tileMap);
  
  return true;
}