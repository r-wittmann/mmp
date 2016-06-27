#include "HighscoreScene.h"
#include "MainMenuScene.h"

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

  
  int score = 3000; // TODO replace with actual score
  
  CCUserDefault *def=CCUserDefault::sharedUserDefault();
  long int high_score=0;
  if(score>high_score)
  {
    def->setIntegerForKey(HIGH_SCORE, score);
    //def->flush();
    //high_score=def->getIntegerForKey(HIGH_SCORE);
  }
  high_score=def->getIntegerForKey(HIGH_SCORE);
  
  char s[7];
  sprintf(s,"%ld", high_score);
  CCLabelTTF *high_label=CCLabelTTF::create(s, "arial.ttf", 20);
  high_label->setPosition(ccp(200, 200));
  this->addChild(high_label,2);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();
    
    
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
