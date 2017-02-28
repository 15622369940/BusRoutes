#pragma once

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class NewCityScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(NewCityScene);

	bool nodeProcess();
	bool eventDispatch();

	Sprite *sprite1, *sprite2,*back_line;
	Node* rootNode;
	bool touchable;
};

