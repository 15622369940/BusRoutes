#pragma once

#include "cocos2d.h"
#include "2d\CCDrawingPrimitives.h"
#include <vector>

#define CITY_MAX_X 100.0f
#define CITY_MAX_Y 150.0f

#define SCALE_MAX 3.0f
#define SCALE_MIN 1.0f

USING_NS_CC;
using namespace ui;
using namespace std;

class CityMap : public cocos2d::Layer
{
private:
	vector<LabelTTF*> list_lines;
	Size citySize;
	Node *picture_node;
	DrawNode* draw_node,*guide_draw;
	Layer *line_layer,*node_layer;
	bool nodeProcess();
	bool eventDispatch();
	void drawCity();
	void drawBusNode();
	void drawBusLine();
	float transPositionX(int x);
	float transPositionY(int y);
	Sprite* createNodeSprite();
	LabelTTF* createNodeLabel(string name);
public:
	vector<LabelTTF*> getList();
	virtual bool init();
	CREATE_FUNC(CityMap);
	void drawGuide(vector<string>* way);
	void clearDrawGuide();
	void drawGuide1(float dt);

	int current_draw_node;
	Point p1, p2;
	vector<string>* way;
};

