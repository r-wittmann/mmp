#ifndef HighscoreScene_h
#define HighscoreScene_h

#include "cocos2d.h"

class HighscoreScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
  
    virtual bool init();
    
    // a selector callback
    void ExitGame(cocos2d::Ref* sender);
    void goToMenuScene(cocos2d::Ref* sender);
    
    std::list<int> highscoreLines;

    
    // implement the "static create()" method manually
    CREATE_FUNC(HighscoreScene);

  
};

#endif
