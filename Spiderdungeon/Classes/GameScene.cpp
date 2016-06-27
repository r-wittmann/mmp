#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

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
