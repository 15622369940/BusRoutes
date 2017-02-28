#pragma once

#include <string>
#include <iostream>
#include<fstream>  
#include<iomanip>

#include <vector>
#include <map>

#include "MyNode.h"
#include "Line.h"


using namespace std;
USING_NS_CC;

class Guide;
class CityMap;

/*
�洢��Ϣ+Ԥ����
��City��
������������¼���е�վ�㣻
ÿ��վ��node����һ��vector�������澭����վ�����·��ţ�
��·������������·��ÿ��node�����ţ�·�ߣ����������ѣ��ٶȣ�������Ѱַ��λ��·����ĸ�����·��ȷ��������n��
ȫ��������ɺ�->����line[n][n]Ϊ����ͼ���������վ�㣬˫��ѭ��������·����¼��line�У�
�����·�ڽӾ��󣬽ڵ�ʹ��������վ��node��x��y�����н�����Ԥ�������

bool Save��City city�������洢����ģ�ͣ�
City Load��string path����������һ�����ļ��д洢�ĳ���ģ�ͣ�
MyNode get��string node����������վ�����ƻ�ȡվ�㣻
bool add��string node��int x��int y��int line����������µ�վ�㣬���Ѵ��ڣ�������ֵ���֣������µ���·������Ƿ��ظ�������վ����Ϣ�У�
*/

class City {
	friend class Guide;
	friend class CityMap;
private :
	map<string, int>* no_nodes;
	map<int, int>* no_lines;
	NodeTree* nodes;
	vector<Line*>* lines;
	int n_nodes, n_lines;

	static City* city;
	City() {
		no_nodes = new map<string, int>();
		no_lines = new map<int, int>();

		nodes = new NodeTree();
		lines = new vector<Line*>();

		n_nodes = 0;
		n_lines = 0;
	}

	NodeTree* get(NodeTree* _root, string name, bool create) {
		if (!create && _root == nullptr)
			return nullptr;
		else if (_root->node == nullptr) {
			return _root;
		}

		if (_root->node->getName().compare(name) == 0)
		{
			return _root;
		}
		else if (_root->node->getName().compare(name) > 0) {
			if (_root->leftChild == nullptr && create)
				_root->leftChild = new NodeTree();
			return get(_root->leftChild, name, create);
		}
		else if (_root->node->getName().compare(name) < 0)
		{
			if (_root->rightChild == nullptr && create)
				_root->rightChild = new NodeTree();
			return get(_root->rightChild, name, create);
		}
		CCLOGERROR("codes error exists");
		//exit(EXIT_FAILURE);
		return nullptr;
	}
public:
	static City* Instance() {
		if (City::city == nullptr)
			City::city = new City();
		return City::city;
	}

	void reset()
	{
		if (city != nullptr)
			delete city;
		city = new City();
	}

	bool isEmpty() {
		return City::Instance()->getNode(0) == nullptr;
	}

	MyNode* getNode(string name) {
		NodeTree *target = get(nodes, name, false);
		if (target == nullptr)
			return nullptr;
		return target->node;
	}

	MyNode* getNode(int index) {
		MyNode* target_node = nullptr;
		if (no_nodes->size() != 0)
		{
			map<string, int>::iterator iter;
			for (iter = no_nodes->begin(); iter != no_nodes->end(); ++iter)
				if (iter->second == index) {
					target_node = this->getNode(iter->first);
					break;
				}
		}

		return target_node;
	}

	 Line* getLine(int number) {
		return lines->at(no_lines->at(number));
	}

	//addLine() first , then addNode() 's turn , or an exception may happen->
	 void addLine(int number, int speed, int blanking, int cost) {
		Line* line = new Line(number, speed, blanking, cost);
		lines->push_back(line);
		no_lines->insert(map<int,int>::value_type(number, n_lines));
		this->n_lines++;
	}

	 bool addNode(string name, int x, int y) {
		NodeTree* tree = get(this->nodes, name, true);
		if (tree->node != nullptr && tree->node->getX() == x && tree->node->getY() == y) {
			tree->node->addLine(lines->at(lines->size() - 1)->getNumber());
			lines->at(lines->size() - 1)->addNode(name);
		}
		else if (tree->node != nullptr) {
			return false;
		}
		else {
			tree->node = new MyNode(name, x, y);
			tree->node->addLine(lines->at(lines->size() - 1)->getNumber());
			no_nodes->insert(map<string, int>::value_type(name, n_nodes));
			this->n_nodes++;
			lines->at(lines->size() - 1)->addNode(name);
		}
		return true;
	}

	 bool addNode(string name) {
		 NodeTree* tree = get(this->nodes, name, true);
		 if (tree->node != nullptr) {
			 tree->node->addLine(lines->at(lines->size() - 1)->getNumber());
			 lines->at(lines->size() - 1)->addNode(name);
		 }
		 else{
			 return false;
		 }
		 return true;
	 }

};