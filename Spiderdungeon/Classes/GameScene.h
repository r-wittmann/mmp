#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
  
    virtual bool init();
    
    private: cocos2d::Point visibleSize;
    private: cocos2d::Vec2 origin;
    
    // variables needed for click and drag calculations
    private: bool mouseDown = false;
    private: float clickPositionX;
    private: float clickPositionY;
    private: float distance;
    private: float angle;
public:
	cocos2d::Sprite* _ball;
	cocos2d::Map<int, cocos2d::Sprite*> _bubbles;
        
    // a selector callback
    void pauseGame(cocos2d::Ref* sender);
    void goToMainMenuScene(cocos2d::Ref* sender);
	void drawSpiderWeb(cocos2d::Ref* sender);
    
    void mouseClicked(cocos2d::Event* event, cocos2d::Sprite* canonStick, cocos2d::Sprite* canonBody);
    void mouseDragged(cocos2d::Event* event, cocos2d::Sprite* canonStick, cocos2d::Sprite* canonBody);
    void mouseReleased(cocos2d::Event* event, cocos2d::Sprite* canonStick, cocos2d::Sprite* canonBody);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

  
};

#endif
