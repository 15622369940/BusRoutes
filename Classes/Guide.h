#pragma once

#include "MyNode.h"
#include "City.h"
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <sstream>
#include <math\Quaternion.h>
#include <cocos2d.h>

/*
����ˣ�
ʹ��line[n][n];
p[j]��¼ǰ����
can[j]��¼��ǰѭ���ýڵ��Ƿ��ɳڹ���
�ֱ��ȡS��T���ڵ���·���ֱ�Ϊm��n�������棻
ѭ��m��S��ÿһ����·��Ϊ��ʼ�ڵ㣬ʹ�õϽ�˹�����㷨�ɳ���·���ѣ�����˳��ʹ����·������Ѱַ��˳��ֵΪ���ѣ�
ÿ��ѭ��ʹ���ϴ����µĵϽ�˹�������飬����can���������������ݣ�
ѭ�������Ƚ�n���ڵ㲢������С�ķѣ�����p���鷢����С�ķ�·��������line�е�ֵȷ��������վ�㣻
�㷨������

��죺
Ȩֵ�ӻ��Ѹ���Ϊվ������*�ٶȣ�
ʹ�á�����ˡ����㷨��
*/

USING_NS_CC;

 class Guide {
	static const int NoEdge = 99999;
	static const int NoParent = -1;
	City* city;
	/**
	* no_nodes վ�����ֵ����ڽӾ�������λ�õ�ӳ��
	* no_lines ��������ŵ����ڽӾ�������λ�õ�ӳ��
	* */
	const map<string, int>* no_nodes;
	const map<int, int>* no_lines;
	/**
	* nodes �洢���е�վ��
	* lines �洢���еĳ˳�·��
	* */
	const NodeTree* nodes;
	const vector<Line*>* lines;
	/**
	* n_nodes վ��ĸ���
	* n_lines ������·������
	* */
	const int n_nodes, n_lines;
	/**
	* node_matrix վ���ڽӾ���
	* line_matrix ������·�ڽӾ���
	* */
	int **node_matrix;
	int **node_distance_matrix;
	string **line_matrix;
	vector<string>* temp_guide_nodes;

 public:
	 Guide(City* city):
		 n_nodes(city->n_nodes), n_lines(city->n_lines)
	 {
		this->city = city;
		this->no_lines = city->no_lines;
		this->no_nodes = city->no_nodes;
		this->nodes = city->nodes;
		this->lines = city->lines;
		temp_guide_nodes = new vector<string>();
	}

	void preprocess() {
		if (city->isEmpty())
			return;
		processLineMatrix();
		processNodeMatrix();
		processNodeDistanceMatrix();
	}

	//�洢·�߽���ڵ������
 private :
	 void processTempSequence(string target,int line_number)
	 {
		 if (temp_guide_nodes->size() == 0)
			 return;
		 Line* line = city->getLine(line_number);
		 int index;
		 bool reverse = false;
		 string start = temp_guide_nodes->at(temp_guide_nodes->size() - 1);
		 for (index = 0; index < line->getNodes()->size(); index++)
		 {
			 if (line->getNodes()->at(index).compare(start) == 0)
				 break;
			 else if (line->getNodes()->at(index).compare(target) == 0)
				 reverse = true;
		 }
		 if (!reverse)
		 {
			 for (index++; index < line->getNodes()->size(); index++)
			 {
				 temp_guide_nodes->push_back(line->getNodes()->at(index));
				 if (line->getNodes()->at(index).compare(target) == 0)
					 break;
			 }
		 }
		 else
		 {
			 for (index--; index >= 0; index--)
			 {
				 temp_guide_nodes->push_back(line->getNodes()->at(index));
				 if (line->getNodes()->at(index).compare(target) == 0)
					 break;
			 }
		 }

	 }

	 void processLineMatrix() {
		line_matrix = new string*[n_lines];
		for (int i = 0; i < n_lines; i++) {
			line_matrix[i] = new string[n_lines];
		}
		queue<const NodeTree*>* _nodes = new queue<const NodeTree*>();
		const NodeTree* _node_tree;
		MyNode* _node;
		_nodes->push(nodes);
		while (!_nodes->empty()) {
			_node_tree = _nodes->front();
			_nodes->pop();
			_node = _node_tree->node;
			if (_node_tree->leftChild != nullptr)
				_nodes->push(_node_tree->leftChild);
			if (_node_tree->rightChild != nullptr)
				_nodes->push(_node_tree->rightChild);

			int key1, key2;
			for (unsigned int i = 0; i < _node->getLines()->size() - 1; i++) {
				for (unsigned int j = i + 1; j < _node->getLines()->size(); j++) {
					key1 = no_lines->at(_node->getLines()->at(i));
					key2 = no_lines->at(_node->getLines()->at(j));
					line_matrix[key1][key2] = _node->getName();
					line_matrix[key2][key1] = _node->getName();
				}
			}

		}
	}

	//�洢�����ڵ�����������·����lines�����е�˳��
	void processNodeMatrix() {
		node_matrix = new int*[n_nodes];
		for (int i = 0; i < n_nodes; i++) {
			node_matrix[i] = new int[n_nodes];
		}

		for (int i = 0; i < n_nodes; i++) {
			for (int j = 0; j < n_nodes; j++) {
				node_matrix[i][j] = 0;
			}
		}

		vector<string>* _line_nodes;
		int key1, key2;
		for (int i = 0; i < n_lines; i++) {//�õ�ÿһ��·��
			_line_nodes = lines->at(i)->getNodes();
			for (unsigned int j = 0; j < _line_nodes->size() - 1; j++) {//�õ�ÿһ��վ�������
				key1 = no_nodes->at(_line_nodes->at(j));
				key2 = no_nodes->at(_line_nodes->at(j + 1));
				node_matrix[key1][key2] = lines->at(i)->getNumber();
				node_matrix[key2][key1] = node_matrix[key1][key2];
			}
			
		}

	}

	//�洢�ڵ��ľ���
	void processNodeDistanceMatrix() {
		node_distance_matrix = new int*[n_nodes];
		for (int i = 0; i < n_nodes; i++) {
			node_distance_matrix[i] = new int[n_nodes];
		}
		for (int i = 0; i < n_nodes; i++) {
			for (int j = 0; j < n_nodes; j++) {
				node_distance_matrix[i][j] = 0;
			}
		}
		MyNode *node1, *node2;
		for (int i = 0; i < n_nodes; i++)
			for (int j = 0; j < n_nodes; j++)
				if (node_matrix[i][j] != 0) {
					node1 = city->getNode(i);
					node2 = city->getNode(j);
					if (node1 == nullptr || node2 == nullptr) {
						//printf("can't find node in processNodeDistanceMatrix\n");
						//exit(EXIT_FAILURE);
					}
					int x2 = (node1->getX() - node2->getX())*(node1->getX() - node2->getX());
					int y2 = (node1->getY() - node2->getY())*(node1->getY() - node2->getY());
					node_distance_matrix[i][j] = (int)sqrt(x2 + y2);
					node_distance_matrix[j][i] = node_distance_matrix[i][j];
				}
	}

public:
	vector<string>* getGuideSequence()
	{
		return temp_guide_nodes;
	}

	string fast(string start_name, string end_name, bool wait) {

		if (city->getNode(start_name) == nullptr || city->getNode(end_name) == nullptr)
			return "";

		//preset

		int* cost = new int[n_nodes];
		int* p = new int[n_nodes];
		bool* used = new bool[n_nodes];
		for (int count = 0; count < n_nodes; count++) {
			cost[count] = NoEdge;
			p[count] = NoParent;
			used[count] = false;
		}

		int start_node_order = no_nodes->at(start_name);
		int end_node_order = no_nodes->at(end_name);

		cost[start_node_order] = 0;
		p[start_node_order] = start_node_order;

		//core arithmetic

		bool finished = false;

		while (!finished) {

			//����һ����С��û���ɳڹ��Ľڵ�
			int k = 0;
			int min = NoEdge;
			for (int i = 0; i < n_nodes; i++) {
				if (!used[i] && cost[i] < min) {
					k = i;
					min = cost[k];
				}
			}
			if (k == end_node_order)
				break;
			used[k] = true;

			int cost_temp = 0;
			for (int i = 0; i < n_nodes; i++) {
				if (node_matrix[k][i] != 0) {
					//�����ǰ�ڵ�����һ�ڵ�����·�� != ��ǰ�ڵ�������һ�ڵ�����·��
					if (k != start_node_order && wait && node_matrix[k][i] != node_matrix[p[k]][k]) {
						cost_temp = cost[k] + node_distance_matrix[k][i] / city->getLine(node_matrix[k][i])->getSpeed()
							+ city->getLine(node_matrix[k][i])->getBlanking();
					}
					else {
						cost_temp = cost[k] + node_distance_matrix[k][i] / city->getLine(node_matrix[k][i])->getSpeed();
					}
					if (cost[i] > cost_temp) {
						cost[i] = cost_temp;
						p[i] = k;
					}
				}
			}

			finished = true;
			for (int i = 0; i < n_nodes; i++)
				if (!used[i]) {
					finished = false;
					break;
				}
		}

		string fast_line = "";
		if (p[end_node_order] == NoParent) {
			//printf("No Such Way !\n");
			return fast_line;
		}

		stack<int>* line_sequence = new stack<int>();
		stack<string>* name_sequence = new stack<string>();
		name_sequence->push(end_name);

		// to be continued->->->

		int temp = end_node_order;
		while (temp != p[temp]) {
			line_sequence->push(city->getLine(node_matrix[p[temp]][temp])->getNumber());
			name_sequence->push(city->getNode(p[temp])->getName());
			temp = p[temp];
		}

		fast_line.clear();
		if (temp_guide_nodes)
			delete temp_guide_nodes;
		temp_guide_nodes = new vector<string>();

		int previous = line_sequence->top();
		line_sequence->pop();
		int line_number = previous;
		fast_line+="��";
		fast_line+=name_sequence->top();
		temp_guide_nodes->push_back(name_sequence->top());
		name_sequence->pop();
		fast_line+="��";
		fast_line+=Value(previous).asString();
		fast_line+="����";

		while (!name_sequence->empty()) {

			if (previous != line_number) {
				fast_line+="����";
				fast_line+=Value(line_number).asString();
				fast_line+="����";
				previous = line_number;
			}

			fast_line+="��";
			fast_line+=name_sequence->top();
			temp_guide_nodes->push_back(name_sequence->top());
			name_sequence->pop();
			if (!line_sequence->empty()) {
				line_number = line_sequence->top();
				line_sequence->pop();
			}


		}
		fast_line+="����Ŀ�ĵ�,������";
		fast_line+= Value(cost[end_node_order]).asString();
		fast_line+="����";


		return fast_line;
	}

	string cheap(string start_name, string end_name) {

		if (city->getNode(start_name) == nullptr || city->getNode(end_name) == nullptr)
			return "";

		//preset

		int* cost = new int[n_lines];
		int* p = new int[n_lines];
		bool* used = new bool[n_lines];
		for (int count = 0; count < n_lines; count++) {
			cost[count] = NoEdge;
			p[count] = NoParent;
			used[count] = false;
		}
		MyNode* start_node = city->getNode(start_name);
		int start_line_order = 0;
		Line* start_line = nullptr;
		MyNode* end_node = city->getNode(end_name);
		int end_line_order = 0;

		//core arithmetic

		for (unsigned int count_end = 0; count_end < end_node->getLines()->size(); count_end++)
			for (unsigned int count_start = 0; count_start < start_node->getLines()->size(); count_start++) {
				start_line_order = no_lines->at(start_node->getLines()->at(count_start));
				start_line = lines->at(start_line_order);
				end_line_order = no_lines->at(end_node->getLines()->at(count_end));

				for (int i = 0; i < n_lines; i++) {
					used[i] = false;
				}
				cost[start_line_order] = start_line->getCost();
				p[start_line_order] = start_line_order;

				bool finished = false;

				while (!finished) {
					//����һ����С��û���ɳڹ��Ľڵ�
					int k = 0;
					int min = NoEdge;
					for (int i = 0; i < n_lines; i++) {
						if (!used[i] && cost[i] < min) {
							k = i;
							min = cost[k];
						}
					}

					if (k == end_line_order)
						break;
					used[k] = true;

					for (int i = 0; i < n_lines; i++) {
						if (line_matrix[k][i] != "") {
							if (cost[i] > cost[k] + lines->at(i)->getCost()) {
								cost[i] = cost[k] + lines->at(i)->getCost();
								p[i] = k;
							}
						}
					}

					finished = true;
					for (int i = 0; i < n_lines; i++)
						if (!used[i]) {
							finished = false;
							break;
						}
				}

			}

		string cheap_line = "";
		if (p[end_line_order] == NoParent) {
			//printf("No Such Way !\n");
			return cheap_line;
		}

		//Start to build the result

		stack<int>* line_sequence = new stack<int>();
		stack<string>* name_sequence = new stack<string>();
		//need to find the cheapest way from the several ways that lead to terminal point
		int temp = NoEdge;	//�����Сֵ
		end_line_order = NoEdge;	//�����Сֵ�����ڵ�
		for (unsigned int count_end = 0; count_end < end_node->getLines()->size(); count_end++) {
			if (cost[no_lines->at(end_node->getLines()->at(count_end))] < temp) {
				end_line_order = no_lines->at(end_node->getLines()->at(count_end));
				temp = cost[end_line_order];
			}
		}
		name_sequence->push(end_name);

		temp = end_line_order;
		while (temp != p[temp]) {
			line_sequence->push(lines->at(temp)->getNumber());
			name_sequence->push(line_matrix[temp][p[temp]]);
			temp = p[temp];
		}

		line_sequence->push(lines->at(temp)->getNumber());
		name_sequence->push(start_node->getName());

		cheap_line.clear();
		if (temp_guide_nodes)
			delete temp_guide_nodes;
		temp_guide_nodes = new vector<string>();

		cheap_line+="��";
		cheap_line+=name_sequence->top();
		string pre_name = "";
		temp_guide_nodes->push_back(name_sequence->top());
		name_sequence->pop();
		while (!line_sequence->empty()) {
			if (pre_name.compare(name_sequence->top()))
			{
				cheap_line += "��";
				cheap_line += Value(line_sequence->top()).asString();
				cheap_line += "���ߵ�";
				cheap_line += name_sequence->top();
				processTempSequence(name_sequence->top(), line_sequence->top());
			}
			
			pre_name = name_sequence->top();
			line_sequence->pop();
			name_sequence->pop();
		}
		cheap_line+="����Ŀ�ĵ�,������";
		cheap_line+=Value(cost[end_line_order]).asString();
		cheap_line+="Ԫ";

		return cheap_line;
	}

};

