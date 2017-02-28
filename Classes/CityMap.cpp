#include "CityMap.h"
#include "cocostudio/CocoStudio.h"
#include "ui\UIListView.h"
#include "City.h"
#include "Line.h"
#include "MyNode.h"

bool CityMap::init()
{

	if (!Layer::init())
		return false;

	list_lines = vector<LabelTTF*>();

	picture_node = CSLoader::createNode("CityLayer.csb");
	line_layer = Layer::create();
	node_layer = Layer::create();

	citySize = picture_node->getContentSize();

	line_layer->setContentSize(citySize);
	node_layer->setContentSize(citySize);

	addChild(picture_node);
	addChild(line_layer);
	addChild(node_layer);


	draw_node = DrawNode::create();
	guide_draw = DrawNode::create();
	line_layer->addChild(draw_node);
	line_layer->addChild(guide_draw);

	if (!nodeProcess() || !eventDispatch())
		exit(EXIT_FAILURE);

	drawCity();

	return true;
}

bool CityMap::nodeProcess() {
	if (picture_node == nullptr)
		return false;

	return true;
}

bool CityMap::eventDispatch() {
	
	((ListView*)getParent())->getBackGroundColor();

	//((ListView*)getParent())->setInnerContainerSize(Size(1000,1000));
	
	return true;
}

void CityMap::drawCity() {
	if (City::Instance()->isEmpty())
		return;
	drawBusLine();
	drawBusNode();
}

void CityMap::drawBusNode() {
	City* city = City::Instance();

	MyNode* target_node = nullptr;
	float x, y;
	map<string, int>::iterator iter;
	for (iter = city->no_nodes->begin(); iter != city->no_nodes->end(); ++iter)
	{
		target_node = city->getNode(iter->first);
		x = transPositionX(target_node->getX());
		y = transPositionY(target_node->getY());
		auto sprite = createNodeSprite();
		auto label = createNodeLabel(target_node->getName());
		sprite->setPosition(x, y);
		label->setPosition(x, y + sprite->getContentSize().height / 2);
		node_layer->addChild(sprite);
		node_layer->addChild(label);
	}
			
}

void CityMap::drawBusLine() {
	City* city = City::Instance();
	Color3B line_color;
	draw_node->setLineWidth(3);
	for (int i = 0; i < city->n_lines; i++) 
	{
		line_color = Color3B(random(10,255), random(10, 255), random(10, 255));
		draw_node->setColor(line_color);
		Line* line = city->lines->at(i);
		auto label = LabelTTF::create();
		label->setString(Value(line->getNumber()).asString());
		label->setFontSize(40);
		label->setFontFillColor(line_color);
		list_lines.push_back(label);

		Point p1(0, 0), p2(0, 0);
		for (int j = 0; j < line->getNodes()->size(); j++)
		{
			MyNode* node = City::Instance()->getNode(line->getNodes()->at(j));
			p2.x = transPositionX(node->getX());
			p2.y = transPositionY(node->getY());
			if (p1.x != 0 || p1.y != 0)
			{
				draw_node->drawLine(p1,p2,ccc4FFromccc3B(line_color));
			}	
			p1.x = p2.x;
			p1.y = p2.y;
		}
	}
}

vector<LabelTTF*> CityMap::getList()
{ 
	return list_lines; 
}

float CityMap::transPositionX(int x) {
	if(x <= 0 || x > CITY_MAX_X)
		return 0;
	return (x / CITY_MAX_X)*citySize.width;
}

float CityMap::transPositionY(int y) {
	if (y <= 0 || y > CITY_MAX_Y)
		return 0;
	return (y / CITY_MAX_Y)*citySize.height;
}

Sprite * CityMap::createNodeSprite()
{
	auto node_sprite = Sprite::create("res/point.png");
	node_sprite->setAnchorPoint(Point(0.5f, 0));
	
	return node_sprite;
}

LabelTTF * CityMap::createNodeLabel(string name)
{
	auto node_name = LabelTTF::create();
	node_name->setString(name);
	node_name->setFontSize(30);
	node_name->setFontFillColor(Color3B::RED);

	return node_name;
}

void CityMap::drawGuide(vector<string>* way) {
	this->way = way;
	p1 = Point(0, 0);
	current_draw_node = 0;
	schedule(schedule_selector(CityMap::drawGuide1),1.0f,way->size(),1.0f);
}

void CityMap::clearDrawGuide() {
	guide_draw->clear();
}

void CityMap::drawGuide1(float dt) {
	if (current_draw_node >= way->size())
		return;
	MyNode* node = City::Instance()->getNode(way->at(current_draw_node++));
	p2.x = transPositionX(node->getX());
	p2.y = transPositionY(node->getY());
	if (p1.x != 0 || p1.y != 0)
	{
		guide_draw->drawSegment(p1, p2, 5, Color4F::BLACK);
	}
	p1.x = p2.x;
	p1.y = p2.y;
}
