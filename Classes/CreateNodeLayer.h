#pragma once

#include "cocos2d.h"
#include "ui\UITextField.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class CreateNode : public cocos2d::Layer
{
private:
	Node* rootNode;
public:
	virtual bool init();
	CREATE_FUNC(CreateNode);

	bool nodeProcess();
	bool eventDispatch();
	bool textFieldProcess(int th,const string name);

	Sprite *confirm, *cancel;
	TextField **save;
	
};

