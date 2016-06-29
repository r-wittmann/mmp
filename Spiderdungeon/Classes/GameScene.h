#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
  
    virtual bool init();
    
    // variables needed for click and drag calculations
    private: bool mouseDown = false;
    private: float clickPositionX;
    private: float clickPositionY;
    private: float distance;
    private: float angle;
        
    // a selector callback
    void pauseGame(cocos2d::Ref* sender);
    void goToMainMenuScene(cocos2d::Ref* sender);
    
    void mouseDragged(cocos2d::Event* event, cocos2d::Sprite* canonBody, cocos2d::Sprite* canonStick);
    void mouseReleased(cocos2d::Event* event);
    void mouseClicked(cocos2d::Event* event, cocos2d::Sprite* canonStick, cocos2d::Sprite* canonBody);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

  
};

#endif
