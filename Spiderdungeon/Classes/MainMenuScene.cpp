#include "GameScene.h"
#include "MainMenuScene.h"
#include "HighscoreScene.h"
//#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene       = Scene::create();

    // 'layer' is an autorelease object
    auto layer       = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();

    

    // create play button and position relative to menu object
    auto playButton = MenuItemImage::create(
                                            "Buttons/startGameButton.png",
                                            "Buttons/startGameButton.png",
                                            CC_CALLBACK_1(MainMenuScene::goToGameScene, this));
    
    playButton->setPosition(Point::ZERO);
    
    // create highscore button and position relative to menu object
    auto highscoreButton = MenuItemImage::create(
                                            "Buttons/highscoreButton.png",
                                            "Buttons/highscoreButton.png",
                                            CC_CALLBACK_1(MainMenuScene::goToHighscoreScene, this));
    
    highscoreButton->setPosition(Point(0, 0 - playButton->getContentSize().height - 10));
    
    // create exit button and position relative to menu object
    auto exitButton  = MenuItemImage::create(
                                             "Buttons/exitGameButton.png",
                                             "Buttons/exitGameButton.png",
                                             CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    
    exitButton->setPosition(Point(0, 0 - highscoreButton->getContentSize().height - 10 - playButton->getContentSize().height - 10));
    

    // create menu, it's an autorelease object, and add buttons to it
    auto menu = Menu::create(playButton, highscoreButton, exitButton, NULL);
    menu->setPosition(Point(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - 100));
    this->addChild(menu, 1);

    
    // create and initialize a main menu label

    auto label       = Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height - 10));

    // add the label as a child to this layer
    this->addChild(label, 1);

    return true;
}

// exit game function
void MainMenuScene::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// start game function
void MainMenuScene::goToGameScene(Ref* sender)
{
    auto scene = GameScene::createScene();
  
    Director::getInstance()->replaceScene(scene);
}

// highscore function
void MainMenuScene::goToHighscoreScene(Ref* sender)
{
    auto scene = HighscoreScene::createScene();
    
    Director::getInstance()->replaceScene(scene);
}
