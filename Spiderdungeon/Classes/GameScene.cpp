#include <iostream>

#include "chipmunk.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include <cmath>
#include <math.h>

USING_NS_CC;
using namespace std;
using namespace cocos2d;

Scene* GameScene::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::createWithPhysics();
  scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); // TODO delete
  scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -350.0f)); // TODO delete
  
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
    
    auto menuButton = MenuItemImage::create(
                                            "Buttons/mainMenuButtonSmall.png",
                                            "Buttons/mainMenuButtonSmall.png",
                                            CC_CALLBACK_1(GameScene::goToMainMenuScene, this));


    auto menu = Menu::create(menuButton, NULL);
    menu->setPosition(Point(origin.x + visibleSize.width - (menuButton->getContentSize().width / 2 + 5),
                            origin.y + 25));
    this->addChild(menu, 2);
    
    //add highscore label
    highScoreLabel = Label::createWithTTF("Score: " + to_string(scoreCount), "fonts/Marker Felt.ttf", 24);
    highScoreLabel->setAnchorPoint(Point(0, 1));
    highScoreLabel->setPosition(Point(origin.x + 10,
                                      origin.y + visibleSize.height - 10));
    this->addChild(highScoreLabel, 1);

    
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
  
  
  // Physics
  
  // Creating a static body
  auto groundBody = PhysicsBody::createBox(
                                           Size(visibleSize.width, 50.0f),
                                           PhysicsMaterial(0.1f, 1.0f, 0.0f)
                                           );
  groundBody->setDynamic(false);
  
  // Attaching a body to a sprite
  auto _ground = Sprite::create("Level_LandschftBaum/Level_Baum_ohneBaum.png");
  _ground->setPosition(Vec2(visibleSize.width / 2, 50.0f));
  _ground->setOpacity(1);
  this->addChild(_ground);
  
  
 
  auto _goldenSpider = Sprite::create("Spinne/Spinne_gold.png");
  auto spiderBody = PhysicsBody::createBox(
	  Size(70.0f, 70.0f),
	  PhysicsMaterial(0.1f, 1.0f, 0.0f)
  );
  spiderBody->setDynamic(false);
  spiderBody->setContactTestBitmask(0xFFFFFFFF);
  _goldenSpider->setPhysicsBody(spiderBody);
  _goldenSpider->setAnchorPoint(Point(1.0, 1.0));
  _goldenSpider->setScale(0.17f);
  _goldenSpider->setPosition(Vec2(visibleSize.width+5, visibleSize.height+30));
  _goldenSpider->setTag(20);
  
  // load the Sprite Sheet
  auto spritecache = SpriteFrameCache::getInstance();

 

  auto spiderBlackBody = PhysicsBody::createBox(
	  Size(70.0f, 70.0f),
	  PhysicsMaterial(0.1f, 1.0f, 0.0f)
  );
  // the .plist file can be generated with any of the tools mentioned below
  spritecache->addSpriteFramesWithFile("Spinne/Spinne.plist");
  Vector<SpriteFrame*> animFrames;
  animFrames.reserve(18);
  char str[100];
  for (int i = 1; i <= 18; i++)
  {
	  if (i < 10) {
		  sprintf(str, "Spinne0%d.png", i);
	  }
	  else {
		  sprintf(str, "Spinne%d.png", i);
	  }

	  animFrames.pushBack(spritecache->getSpriteFrameByName(str));
  }

  // create the animation out of the frames
  Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
  Animate* animate = Animate::create(animation);
  auto _Spider = Sprite::createWithSpriteFrame(animFrames.front());
  spiderBlackBody->setDynamic(false);
  _Spider->setPhysicsBody(spiderBlackBody);
  _Spider->setAnchorPoint(Point(0.0, 0.0));
  _Spider->setScale(0.17f);
  _Spider->setPosition(Vec2(visibleSize.width /2, visibleSize.height + 30));
  this->addChild(_Spider, 2);

  //Spider_line:
  CCSprite *spiderString = Sprite::create("res/pix2.png");
  _Spider->addChild(spiderString, -1);
  _Spider->runAction(RepeatForever::create(animate));
  spiderString->setPosition(Vec2(135, 950));
  spiderString->setScaleX(0.05f);
  spiderString->setScaleY(4.2);
  spiderString->setTag(40);
  auto spiderStringSize = spiderString->getContentSize();
  auto stringBody = PhysicsBody::createBox(Size(spiderStringSize.width, spiderStringSize.height),
	  PhysicsMaterial(0.1f, 1.0f, 0.0f));
  spiderString->setPhysicsBody(stringBody);
  stringBody->setDynamic(false);
  stringBody->setContactTestBitmask(0xFFFFFFFF);

  //Animation

  auto moveTo = MoveTo::create(10, Vec2(visibleSize.width /2, 0));
  auto moveTo2 = MoveTo::create(10, Vec2(visibleSize.width / 2, visibleSize.height));
  auto delay = DelayTime::create(2);
  auto seq = Sequence::create(moveTo, delay, moveTo2, nullptr);
  seq->setTag(1);
_Spider->runAction(RepeatForever::create(seq));


 
  this->addChild(_goldenSpider,6);
  auto contactListener = EventListenerPhysicsContact::create();
  contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	GameScene	  ::drawSpiderWeb(this);
    return true;
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
      
        angle = atan(deltaAnchorDragY / deltaAnchorDragX);
        
        canonBody->setRotation(CC_RADIANS_TO_DEGREES(-angle));
        canonStick->setRotation(CC_RADIANS_TO_DEGREES(-angle));
        
    }
}

void GameScene::mouseReleased(Event* event, Sprite* canonStick, Sprite* canonBody)
{
    mouseDown = false;
  
  // call function to fire canonball with angle and distance (distance is between 0 and 50)
  
  // Creating a dynamic body
  auto ballBody = PhysicsBody::createCircle(
                                            100.0f,
                                            PhysicsMaterial(0.1f, 0.2f, 0.0f)
                                            );
  ballBody->setMass(10.0f);
  ballBody->setContactTestBitmask(0xFFFFFFFF);
  
  auto _canonball = Sprite::create("Kanone/Kanonen_Ball.png");
  _canonball->setScale(0.05);
  _canonball->setPosition(Point(origin.x + 100, origin.y + 95));
  this->addChild(_canonball, 1);
  
  _canonball->setPhysicsBody(ballBody);
  
  // Applying a force
  Vec2 force = Vec2(cos(angle) * distance * 100, sin(angle) * distance * 100);
  
  _canonball->getPhysicsBody()->applyImpulse(force);
  
    cout << "Angle: ";
    cout << angle;
    cout << " Force: ";
    cout << distance * 2;
    cout << "%\n";
    
    // move canon back to original position
    canonStick->setAnchorPoint(Point(0.5, 0.5));
    auto rotateBody = RotateTo::create(2 * abs(CC_RADIANS_TO_DEGREES(angle)) /90, 0);
    auto rotateStick = RotateTo::create(2 * abs(CC_RADIANS_TO_DEGREES(angle)) / 90, 0);
    canonBody->runAction(rotateBody);
    canonStick->runAction(rotateStick);
    
}
void GameScene::drawSpiderWeb(Ref* sender) {
	//MessageBox(NULL, "contact");
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto winSize = Director::getInstance()->getVisibleSize();
	if (level) {
		level += 5;
	}
	else {
		level = 25;
	}
	// 3
	_bubbles = Map<int, Sprite*>(level);
	
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
		_ball->setTag(10);
    auto ballBody = PhysicsBody::createCircle(_ball->getContentSize().width / 2,
                                             PhysicsMaterial(0.1f, 1.0f, 0.0f)
                                             );
    ballBody->setDynamic(false);
	ballBody->setContactTestBitmask(0xFFFFFF);
    _ball->addComponent(ballBody);
		_bubbles.insert(i, _ball);
		this->addChild(_ball,4);
		//int rowPos = i % 3;
		angle = angle + (M_PI / 8);
		if ((i % 5) == 4) {
			angle = M_PI;
			r = r + 30;
		}

	}
	for (int i = 0; i < level; i++) {
		Vector<Sprite*> linesVec(2);
		if ((i % 5) < 4) {
			cocos2d::Vec2 firstBubble = _bubbles.at(i)->getPosition();
			cocos2d::Vec2 secondBubble = _bubbles.at(i + 1)->getPosition();

			cocos2d::Vec2 diff = ccpSub(firstBubble, secondBubble);
			float rads = atan2f(diff.y, diff.x);
			float degs = -CC_RADIANS_TO_DEGREES(rads);
            float dist = ccpDistance(firstBubble, secondBubble);
            
			CCSprite *line = Sprite::create("res/pix.png");
            auto lineBody = PhysicsBody::createBox(Size(0.5, 0.1), PhysicsMaterial(0.1f, 1.0f, 0.0f));
            
            line->setPhysicsBody(lineBody);

			line->setAnchorPoint(ccp(0.0f, 0.5f));
			line->setPosition(secondBubble);
			line->setScaleX(dist + dist*0.50);
			line->setRotation(degs);
            lineBody->setDynamic(false);
      
			this->addChild(line, 3);
			linesVec.pushBack(line);

		}
		if (i < 5) {
			cocos2d::Vec2 firstBubble = ccp(originX, originY);
			cocos2d::Vec2 secondBubble = _bubbles.at(i)->getPosition();

			cocos2d::Vec2 diff = ccpSub(firstBubble, secondBubble);
			float rads = atan2f(diff.y, diff.x);
			float degs = -CC_RADIANS_TO_DEGREES(rads);
			float dist = ccpDistance(firstBubble, secondBubble);
            
			CCSprite *line = Sprite::create("res/pix.png");
			auto lineBody = PhysicsBody::createBox(Size(0.5, 0.1), PhysicsMaterial(0.1f, 1.0f, 0.0f));
            
            line->setPhysicsBody(lineBody);

            line->setAnchorPoint(ccp(0.0f, 0.5f));
			line->setPosition(secondBubble);
			line->setScaleX(dist + dist*0.50);
			line->setRotation(degs);
            lineBody->setDynamic(false);
			
            this->addChild(line, 3);
            linesVec.pushBack(line);
		}
		else {
			cocos2d::Vec2 firstBubble = _bubbles.at(i - 5)->getPosition();
			cocos2d::Vec2 secondBubble = _bubbles.at(i)->getPosition();

			cocos2d::Vec2 diff = ccpSub(firstBubble, secondBubble);
			float rads = atan2f(diff.y, diff.x);
			float degs = -CC_RADIANS_TO_DEGREES(rads);
			float dist = ccpDistance(firstBubble, secondBubble);
			
            CCSprite *line = Sprite::create("res/pix.png");
            auto lineBody = PhysicsBody::createBox(Size(0.5, 0.1), PhysicsMaterial(0.1f, 1.0f, 0.0f));
            
            line->setPhysicsBody(lineBody);

			line->setAnchorPoint(ccp(0.0f, 0.5f));
			line->setPosition(secondBubble);
			line->setScaleX(dist + dist*0.50);
			line->setRotation(degs);
            lineBody->setDynamic(false);
			
            this->addChild(line, 3);
            linesVec.pushBack(line);

		}

		_linesPerBubble[i] = linesVec;
	}
}
void GameScene::removeCertainElement(Ref* sender, int bubble_hit) {
	try {
	//	MessageBox(NULL, "Contact!!!?");
		if (bubble_hit < level) {
			//_bubbles.at(bubble_hit)->setOpacity(bubble_hit);
			_bubbles.at(bubble_hit)->removeFromParent();
			
			Vector<Sprite *> linesVec = _linesPerBubble.at(bubble_hit);
			Vector<Sprite *> linesVecPrev = _linesPerBubble.at(bubble_hit-1);
			for (auto sp : linesVec) {
				cout << sp->getName();
				sp->removeFromParent();
			}
			auto Prev = linesVecPrev.front();
			Prev->setOpacity(0);
			Prev->removeFromParent();
		}
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
}
bool GameScene::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == 10)
		{
			
				if (dynamic_cast<Sprite*>(nodeA)) { //It is Sprite 
					Sprite *target = dynamic_cast<Sprite*>(nodeA);
					//Do whatever you like
					std::vector<int> keys = _bubbles.keys(target);
					for (auto key : keys) {
						GameScene::removeCertainElement(this, key);
					}
				}
				scoreCount += 10;
			
		}
		else if (nodeB->getTag() == 10)
		{
			
			if (dynamic_cast<Sprite*>(nodeB)) { //It is Sprite 
				Sprite *target = dynamic_cast<Sprite*>(nodeB);
				//Do whatever you like
				std::vector<int> keys = _bubbles.keys(target);
				for (auto key : keys) {
					GameScene::removeCertainElement(this, key);
				}
			}
			scoreCount += 10;
		
		}
		if (nodeA->getTag() == 20) {
			GameScene::winLevel(this);
		}
		else if (nodeB->getTag() == 20) {
			GameScene::winLevel(this);
		}
		if (nodeA->getTag() == 40) {
			if (dynamic_cast<Sprite*>(nodeA)) { //It is Sprite 
				Sprite *target = dynamic_cast<Sprite*>(nodeA);
				GameScene::dumpSpider(this, target);
			}
			return false;
			
		}
		else if (nodeB->getTag() == 40) {
			if (dynamic_cast<Sprite*>(nodeB)) { //It is Sprite 
				Sprite *target = dynamic_cast<Sprite*>(nodeB);
				GameScene::dumpSpider(this, target);
				return false;
			}
			
		}

	}


    // count score
   
    highScoreLabel->setString("Score: " + to_string(scoreCount));
    
	return true;
}
void GameScene::winLevel(Ref *sender) {
	try{
	for (int i = 0; i < level; i++) {
		if (_bubbles.at(i)) {
			GameScene::removeCertainElement(this, i);
		}
		_bubbles.erase(i);
		_linesPerBubble.erase(i);
	}
	
		GameScene::drawSpiderWeb(this);
	
	

}
catch (const std::out_of_range& oor) {
	std::cerr << "Out of Range error: " << oor.what() << '\n';
}
}
void GameScene::dumpSpider(cocos2d::Ref * sender, cocos2d::Sprite * spiderLine) {
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto spider = spiderLine->getParent();
	auto fallDown = MoveTo::create(0, Vec2(visibleSize.width / 2, 0));
	auto newSpiderLine = spiderLine;
	spiderLine->retain();
	spiderLine->removeFromParent();
	auto moveDown = MoveTo::create(10, Vec2(visibleSize.width/ 2, 0));
	auto moveTo2 = MoveTo::create(10, Vec2(visibleSize.width / 2, visibleSize.height));
	auto moveUp = MoveTo::create(0, Vec2(visibleSize.width / 2, visibleSize.height +30));
	auto delay = DelayTime::create(2);
	auto delay2 = DelayTime::create(3);
	//auto seq = Sequence::create( moveDown, delay, moveTo2, delay->clone(), nullptr);
	auto seq2 = Sequence::create(fallDown, moveUp, nullptr);
	auto seq = spider->getActionByTag(1);
	spider->stopActionByTag(1);
	spider->runAction(seq2);
	spider->stopActionByTag(1);

	spider->addChild(spiderLine);
	spiderLine->release();


}