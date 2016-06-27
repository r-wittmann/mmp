#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
  
    virtual bool init();
    
    // a selector callback
    void pauseGame(cocos2d::Ref* sender);
    void goToMainMenuScene(cocos2d::Ref* sender);
    void click(cocos2d::Event* event);
    void move(cocos2d::Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

  
};

#endif
