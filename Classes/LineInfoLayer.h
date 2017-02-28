#pragma once

#include "cocos2d.h"
#include "Line.h"
#include "ui\UIText.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class LineInfoLayer : public cocos2d::Layer
{
private:
	Line* line;
	Node* rootNode;
	bool nodeProcess();
	bool eventDispatch();
	virtual bool init(Line* line);
public:
	static LineInfoLayer* create(Line* line);

	Sprite *confirm, *cancel;
	Text *number, *cost,*speed,*blanking;

};

