#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Guide.h"
#include "City.h"
#include "NewCityScene.h"
#include "GuideLayerScene.h"

#include <iostream>
#include <sstream>
#include <string>
#include<fstream>  
#include<iomanip>

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    
    if ( !Layer::init() )
        return false;

    rootNode = CSLoader::createNode("StartLayer.csb");
    addChild(rootNode);

	if(!nodeProcess() || !eventDispatch())
		exit(EXIT_FAILURE);

    return true;
}

void HelloWorld::fastEditCity()
{
	City::Instance()->reset();
	City* city = City::Instance();
	city->addLine(2, 5, 10, 12);
	city->addNode("c", 10, 120);
	city->addNode("e", 20, 20);
	city->addNode("a", 30, 93);
	city->addNode("f", 93, 72);

	city->addLine(4, 5, 100, 0);
	city->addNode("c");
	city->addNode("s", 50, 26);
	city->addNode("h", 60, 132);
	city->addNode("j", 70, 66);

	city->addLine(3, 6, 10, 1);
	city->addNode("e");
	city->addNode("k", 80, 20);
	city->addNode("f");

	city->addLine(13, 6, 10, 7);
	city->addNode("j");
	city->addNode("k");
	city->addNode("a");
	city->addNode("r", 90, 27);
	city->addNode("oo", 35, 23);

	city->addLine(5, 5, 10, 2);
	city->addNode("a");
	city->addNode("b", 52, 117);
	city->addNode("d", 74, 123);

	city->addLine(1, 5, 10, 2);
	city->addNode("b");
	city->addNode("w", 22, 33);
	city->addNode("d");
	city->addNode("r");
	city->addNode("p", 5, 74);

	city->addLine(11, 5, 10, 22);
	city->addNode("bb", 75, 87);
	city->addNode("ww", 83, 90);
	city->addNode("d");
	city->addNode("s");
	city->addNode("p");
}

bool HelloWorld::nodeProcess() {
	if (rootNode == nullptr)
		return false;

	sprite1 = (Sprite*)rootNode->getChildByName("button_new");
	if (sprite1 == nullptr) {
		return false;
	}

	sprite2 = (Sprite*)rootNode->getChildByName("button_load");
	if (sprite2 == nullptr) {
		return false;
	}

	sprite3 = (Sprite*)rootNode->getChildByName("button_quit");
	if (sprite3 == nullptr) {
		return false;
	}

	return true;
}

bool HelloWorld::eventDispatch() {

	auto main_listener = EventListenerTouchOneByOne::create();
	main_listener->onTouchBegan = [this](Touch* t, Event* e)
	{
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (e->getCurrentTarget()->getName() == sprite1->getName())
			{
				Director::getInstance()->replaceScene(NewCityScene::createScene());
			}
			else if (e->getCurrentTarget()->getName() == sprite2->getName())
			{
				fastEditCity();
				Director::getInstance()->replaceScene(GuideLayerScene::createScene());
			}
			else if (e->getCurrentTarget()->getName() == sprite3->getName())
			{
				Director::getInstance()->end();
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(main_listener, sprite1);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(main_listener->clone(), sprite2);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(main_listener->clone(), sprite3);
	return true;
}