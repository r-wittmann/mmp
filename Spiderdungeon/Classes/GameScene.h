#ifndef GameScene_h
#define GameScene_h

#include "chipmunk.h"
#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
  
  cpSpace* m_pSpace;
  
    virtual bool init();
	virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    private: cocos2d::Point visibleSize;
    private: cocos2d::Vec2 origin;
    
    private: int scoreCount = 0;
    private: cocos2d::Label* highScoreLabel;

    
    // variables needed for click and drag calculations
    private: bool mouseDown = false;
    private: float clickPositionX;
    private: float clickPositionY;
    private: float distance;
    private: float angle;
public:
	//cocos2d::Sprite* _ball;
	cocos2d::Map<int, cocos2d::Sprite*> _bubbles;
	std::map<int, cocos2d::Vector<cocos2d::Sprite*> > _linesPerBubble;
	int level;
	cocos2d::Sprite* _movingSpider;
	cocos2d::Sprite* _movingSpiderLine;

       
    // a selector callback
    void pauseGame(cocos2d::Ref* sender);
    void goToMainMenuScene(cocos2d::Ref* sender);
	void drawSpiderWeb(cocos2d::Ref* sender);
	void removeCertainElement(cocos2d::Ref* sender, int bubble_hit);
	void winLevel(cocos2d::Ref* sender);
	void dumpSpider(cocos2d::Ref * sender, cocos2d::Sprite * spiderLine);
	void addSpiderLineAgain(float dt);
	void test(Ref* sender);
	
    void mouseClicked(cocos2d::Event* event, cocos2d::Sprite* canonStick, cocos2d::Sprite* canonBody);
    void mouseDragged(cocos2d::Event* event, cocos2d::Sprite* canonStick, cocos2d::Sprite* canonBody);
    void mouseReleased(cocos2d::Event* event, cocos2d::Sprite* canonStick, cocos2d::Sprite* canonBody);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

  
};

#endif
