#include "LineInfoLayer.h"
#include "cocostudio/CocoStudio.h"
#include "GuideLayerScene.h"

#include "Guide.h"

LineInfoLayer* LineInfoLayer::create(Line* line)
{
	auto layer = new LineInfoLayer();
	if (layer && layer->init(line))
		layer->autorelease();
	else
	{
		delete layer;
		layer = nullptr;
	}
	return layer;

}

bool LineInfoLayer::init(Line* line)
{

	if (!Layer::init())
		return false;

	this->line = line;

	rootNode = CSLoader::createNode("LineInfoLayer.csb");
	addChild(rootNode);

	if (!nodeProcess() || !eventDispatch())
		exit(EXIT_FAILURE);

	return true;
}

bool LineInfoLayer::nodeProcess() {
	if (rootNode == nullptr)
		return false;

	confirm = (Sprite*)rootNode->getChildByName("button_confirm");
	if (confirm == nullptr) {
		return false;
	}

	cancel = (Sprite*)rootNode->getChildByName("button_cancel");
	if (cancel == nullptr) {
		return false;
	}

	number = (Text*)rootNode->getChildByName("line_number");
	if (number == nullptr) {
		return false;
	}
	number->setString(Value(line->getNumber()).asString());
	cost = (Text*)rootNode->getChildByName("line_cost");
	if (cost == nullptr) {
		return false;
	}
	cost->setString(Value(line->getCost()).asString());
	speed = (Text*)rootNode->getChildByName("line_speed");
	if (speed == nullptr) {
		return false;
	}
	speed->setString(Value(line->getSpeed()).asString());
	blanking = (Text*)rootNode->getChildByName("line_blanking");
	if (blanking == nullptr) {
		return false;
	}
	blanking->setString(Value(line->getBlanking()).asString());

	return true;
}

bool LineInfoLayer::eventDispatch() {
	auto line_info_confirm_listener = EventListenerTouchOneByOne::create();
	line_info_confirm_listener->onTouchBegan = [this](Touch* t, Event* e)
	{

		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (e->getCurrentTarget()->getName() == confirm->getName() || 
				e->getCurrentTarget()->getName() == cancel->getName())
			{
				((GuideLayerScene*)getParent())->touchable = true;
				removeFromParentAndCleanup(true);
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(line_info_confirm_listener->clone(), confirm);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(line_info_confirm_listener->clone(), cancel);

	return true;
}



