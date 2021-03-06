#ifndef MainMenuScene_h
#define MainMenuScene_h

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* sender);
    void goToGameScene(cocos2d::Ref* sender);
    void goToHighscoreScene(cocos2d::Ref* sender);
  
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};

#endif
