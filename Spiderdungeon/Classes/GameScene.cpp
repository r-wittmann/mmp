#include <iostream>

#include "GameScene.h"
#include "MainMenuScene.h"

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
    this->addChild(menu, 1);
    
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
