#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "ChooseMapScence.h"
#include "StartScene.h"
#include "PlayScene.h"
#include "ChooseCharacterScene.h"
#include "WinScene.h"
#include "SettingScene.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  CCDirector* pDirector = CCDirector::sharedDirector();
  CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
  
  pDirector->setOpenGLView(pEGLView);
	
  // turn on display FPS
  pDirector->setDisplayStats(true);
  CCSize designResolutionSize = cocos2d::CCSizeMake(1136, 640);
  std::vector<std::string> searchPaths;
  
//  if (pDirector->getWinSize().height == 960)
//  {
//    // iPhone 4/4S
//    pDirector->setContentScaleFactor(2);
//    searchPaths.push_back("hd");
//  }
//  else if (pDirector->getWinSize().height == 1136)
//  {
//    // iPhone 5
//    pDirector->setContentScaleFactor(2);
//    searchPaths.push_back("iphone-5");
//    designResolutionSize = cocos2d::CCSizeMake(568, 320);
//  }
  
  searchPaths.push_back("iphone-5");
  pEGLView->setDesignResolutionSize(designResolutionSize.width,
                                    designResolutionSize.height,
                                    kResolutionNoBorder);
  
  CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
  
  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);
  
  // create a scene. it's an autorelease object
  //    CCScene *pScene = HelloWorld::scene();
  CCScene *pScene = LoadingScene::scene();

//  CCScene *pScene = StartScene::scene();
    // run
  pDirector->runWithScene(pScene);

  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
     CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
