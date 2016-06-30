#include <iostream>

#include "GameScene.h"
#include "MainMenuScene.h"
#include <cmath>
#include <math.h>

USING_NS_CC;
using namespace std;

cocos2d::Scene* GameScene::createScene()
{
  // 'scene' is an autorelease object
  auto scene = cocos2d::Scene::create();
  
  // 'layer' is an autorelease object
  auto layer = GameScene::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();
    
    // create pause button and position relative to menu object
    auto pauseButton = MenuItemImage::create(
                                            "Buttons/pauseButton.png",
                                            "Buttons/pauseButton.png",
                                            CC_CALLBACK_1(GameScene::pauseGame, this));
    
    pauseButton->setPosition(Point::ZERO);
    
    auto menuButton = MenuItemImage::create(
                                            "Buttons/mainMenuButtonSmall.png",
                                            "Buttons/mainMenuButtonSmall.png",
                                            CC_CALLBACK_1(GameScene::goToMainMenuScene, this));
    menuButton->setPosition(Point(pauseButton->getContentSize().width + 5, 0));

    auto menu = Menu::create(pauseButton, menuButton, NULL);
    menu->setPosition(Point(origin.x + visibleSize.width - (pauseButton->getContentSize().width + menuButton->getContentSize().width),
                            origin.y + pauseButton->getContentSize().height / 2 + 5));
    this->addChild(menu, 2);
    
    //add background
    auto background = Sprite::create("Level_LandschftBaum/Level_Baum_ohneBaum.png");
    background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 25));
    background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
    
    this->addChild(background, 0);
    
    //add Tree
    auto tree = Sprite::create("Level_LandschftBaum/Baum.png");
    tree->setPosition(Point(visibleSize.width - 20, visibleSize.height));
    tree->setScale(0.9);
    
    this->addChild(tree);
    
    //add small Tree
    auto smallTree = Sprite::create("Level_LandschftBaum/Baum.png");
    smallTree->setPosition(Point(50, visibleSize.height / 2));
    smallTree->setScale(0.3);
    
    this->addChild(smallTree);
    
    //create Canon
    auto canonBody = Sprite::create("Kanone/Kanone_Körper.png");
    canonBody->setScale(0.2);
    canonBody->setAnchorPoint(Point(0.5, 0.5));
    canonBody->setPosition(Point(origin.x + 100, origin.y + 70));
    this->addChild(canonBody, 3);
    
    auto canonStick = Sprite::create("Kanone/Kanonen_Stab.png");
    canonStick->setScale(0.2);
    canonStick->setAnchorPoint(Point(0.5, 0.5));
    canonStick->setPosition(Point(origin.x + 100, origin.y + 70));
    this->addChild(canonStick, 2);
    
    auto canonWheel = Sprite::create("Kanone/Kanonen_Rad.png");
    canonWheel->setScale(0.2);
    canonWheel->setPosition(Point(origin.x + 100, origin.y + 60));
    this->addChild(canonWheel, 4);
    
    auto clicklistener = EventListenerMouse::create();
    clicklistener->onMouseDown = CC_CALLBACK_1(GameScene::mouseClicked, this, canonStick, canonBody);
    clicklistener->onMouseMove = CC_CALLBACK_1(GameScene::mouseDragged, this, canonStick, canonBody);
    clicklistener->onMouseUp = CC_CALLBACK_1(GameScene::mouseReleased, this, canonStick, canonBody);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(clicklistener, this);

	GameScene::drawSpiderWeb(this);
    return true;
}

void GameScene::pauseGame(Ref* sender)
{
    //not implemented yet
}

void GameScene::goToMainMenuScene(Ref* sender)
{
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(scene);
}

void GameScene::mouseClicked(Event* event, Sprite* canonStick, Sprite* canonBody)
{
    EventMouse* e = (EventMouse*)event;
    mouseDown = true;
    clickPositionX = e->getCursorX();
    clickPositionY = e->getCursorY();
    GameScene::mouseDragged(e, canonStick, canonBody);
}

void GameScene::mouseDragged(Event* event, Sprite* canonStick, Sprite* canonBody)
{
    EventMouse* e = (EventMouse*)event;
    if (mouseDown) {
        float deltaAnchorDragX = canonBody->getPosition().x - e->getCursorX();
        float deltaAnchorDragY = canonBody->getPosition().y - e->getCursorY();
        float deltaAnchorClickX = canonBody->getPosition().x - clickPositionX;
        float deltaAnchorClickY = canonBody->getPosition().y - clickPositionY;
        
        float distanceAnchorDrag = sqrt(pow(deltaAnchorDragX, 2) + pow(deltaAnchorDragY, 2));
        float distanceAnchorClick = sqrt(pow(deltaAnchorClickX, 2) + pow(deltaAnchorClickY, 2));
        
        distance = min(abs(distanceAnchorDrag - distanceAnchorClick), 50.0f);

        canonStick->setAnchorPoint(Point(0.5 + distance * 0.015, 0.5));
        
        float pi = acos(-1);
        angle = atan(deltaAnchorDragY / deltaAnchorDragX) * 180 / pi;
        
        canonBody->setRotation(-angle);
        canonStick->setRotation(-angle);
        
    }
}

void GameScene::mouseReleased(Event* event, Sprite* canonStick, Sprite* canonBody)
{
    mouseDown = false;
    // call function to fire canonball with angle and distance (distance is between 0 and 50)
    cout << "Angle: ";
    cout << angle;
    cout << " Force: ";
    cout << distance * 2;
    cout << "%\n";
    
    // move canon back to original position
    canonStick->setAnchorPoint(Point(0.5, 0.5));
    auto rotateBody = RotateTo::create(2 * abs(angle) /90, 0);
    auto rotateStick = RotateTo::create(2 * abs(angle) / 90, 0);
    canonBody->runAction(rotateBody);
    canonStick->runAction(rotateStick);
    
}
void GameScene::drawSpiderWeb(Ref* sender) {
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto winSize = Director::getInstance()->getVisibleSize();
	auto level = 25;
	// 3
	_bubbles = Map<int, Sprite*>(25);
	
	float originX = winSize.width;
	float originY = winSize.height+25;
	int r = originX - originX*0.9;
	float angle = M_PI;
	float X; float Y;
	for (int i = 0; i < level; i++) {
		X = originX + cos(angle)*r;
		Y = originY + sin(angle) *r;
		_ball = Sprite::create("res/puck.png");
		_ball->setScale(0.75);
		_ball->setPosition(Vec2(X, Y));
		_bubbles.insert(i, _ball);
		this->addChild(_ball,4);
		//int rowPos = i % 3;
		angle = angle + (M_PI / 8);
		if ((i % 5) == 4) {
			angle = M_PI;
			r = r + 30;
		}

	}
	std::vector<int> mapKeyVec;
	mapKeyVec = _bubbles.keys();
	for (int i = 0; i < level; i++) {
		if ((i % 5) < 4) {
			cocos2d::Vec2 firstBubble = _bubbles.at(i)->getPosition();
			cocos2d::Vec2 secondBubble = _bubbles.at(i + 1)->getPosition();

			cocos2d::Vec2 diff = ccpSub(firstBubble, secondBubble);
			float rads = atan2f(diff.y, diff.x);
			float degs = -CC_RADIANS_TO_DEGREES(rads);
			float dist = ccpDistance(firstBubble, secondBubble);
			CCSprite *line = Sprite::create("res/pix.png");
			line->setAnchorPoint(ccp(0.0f, 0.5f));
			line->setPosition(secondBubble);
			line->setScaleX(dist + dist*0.50);
			line->setRotation(degs);
			this->addChild(line, 3);
		}
		if (i < 5) {
			cocos2d::Vec2 firstBubble = ccp(originX, originY);
			cocos2d::Vec2 secondBubble = _bubbles.at(i)->getPosition();

			cocos2d::Vec2 diff = ccpSub(firstBubble, secondBubble);
			float rads = atan2f(diff.y, diff.x);
			float degs = -CC_RADIANS_TO_DEGREES(rads);
			float dist = ccpDistance(firstBubble, secondBubble);
			CCSprite *line = Sprite::create("res/pix.png");
			line->setAnchorPoint(ccp(0.0f, 0.5f));
			line->setPosition(secondBubble);
			line->setScaleX(dist + dist*0.50);
			line->setRotation(degs);
			this->addChild(line, 3);
		}
		else {
			cocos2d::Vec2 firstBubble = _bubbles.at(i-5)->getPosition();
			cocos2d::Vec2 secondBubble = _bubbles.at(i)->getPosition();

			cocos2d::Vec2 diff = ccpSub(firstBubble, secondBubble);
			float rads = atan2f(diff.y, diff.x);
			float degs = -CC_RADIANS_TO_DEGREES(rads);
			float dist = ccpDistance(firstBubble, secondBubble);
			CCSprite *line = Sprite::create("res/pix.png");
			line->setAnchorPoint(ccp(0.0f, 0.5f));
			line->setPosition(secondBubble);
			line->setScaleX(dist + dist*0.50);
			line->setRotation(degs);
			this->addChild(line, 3);
		}
		
	}
	

}