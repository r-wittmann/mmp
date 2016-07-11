#include "HighscoreScene.h"
#include "MainMenuScene.h"
#include <iostream>
#include <fstream>
#include <list>

USING_NS_CC;

const char *HIGH_SCORE="key1";

Scene* HighscoreScene::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();
  
  // 'layer' is an autorelease object
  auto layer = HighscoreScene::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}

bool HighscoreScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    std::string line;
    int i = 0;
    
    std::ifstream myfile ("highscore.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            highscoreLines.push_back(std::stoi(line));
            i++;
        }
        myfile.close();
    } else std::cout << "Unable to open file";
    highscoreLines.sort(std::greater<int>());
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();
    
    auto pos1 = Label::createWithTTF("1st: " + std::to_string(highscoreLines.front()), "fonts/Marker Felt.ttf", 16);
    pos1->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height/2 + 70 ));
    this->addChild(pos1, 1);
    
    highscoreLines.pop_front();
    
    auto pos2 = Label::createWithTTF("2nd: " + std::to_string(highscoreLines.front()), "fonts/Marker Felt.ttf", 16);
    pos2->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + 50 ));
    this->addChild(pos2, 1);
    
    highscoreLines.pop_front();
    
    auto pos3 = Label::createWithTTF("3rd: " + std::to_string(highscoreLines.front()), "fonts/Marker Felt.ttf", 16);
    pos3->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + 30 ));
    this->addChild(pos3, 1);

    highscoreLines.pop_front();
    
    auto pos4 = Label::createWithTTF("4th: " + std::to_string(highscoreLines.front()), "fonts/Marker Felt.ttf", 16);
    pos4->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + 10 ));
    this->addChild(pos4, 1);
    
    highscoreLines.pop_front();
    
    auto pos5 = Label::createWithTTF("5th: " + std::to_string(highscoreLines.front()), "fonts/Marker Felt.ttf", 16);
    pos5->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 -10 ));
    this->addChild(pos5, 1);
    
    
    // create main menu button and position relative to menu object
    auto menuButton = MenuItemImage::create(
                                            "Buttons/mainMenuButton.png",
                                            "Buttons/mainMenuButton.png",
                                            CC_CALLBACK_1(HighscoreScene::goToMenuScene, this));
    
    menuButton->setPosition(Point::ZERO);
    
    // create exit button and position relative to menu object
    auto exitButton = MenuItemImage::create(
                                                 "Buttons/exitGameButton.png",
                                                 "Buttons/exitGameButton.png",
                                                 CC_CALLBACK_1(HighscoreScene::ExitGame, this));
    
    exitButton->setPosition(Point(0, 0 - menuButton->getContentSize().height - 10));
    
    
    // create menu, it's an autorelease object, and add buttons to it
    auto menu = Menu::create(menuButton, exitButton, NULL);
    menu->setPosition(Point(origin.x + visibleSize.width / 2,
                            origin.y + menuButton->getContentSize().height + menuButton->getContentSize().height + 10));
    this->addChild(menu, 1);
    
    
    // create and initialize a highscores label
    
    auto label       = Label::createWithTTF("Highscores", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height - 10));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    return true;
}

// exit game function
void HighscoreScene::ExitGame(Ref* sender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// start game function
void HighscoreScene::goToMenuScene(Ref* sender)
{
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(scene);
}
