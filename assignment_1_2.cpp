#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
/***********霍夫曼树的节点***********/
class Node
{
public:
	long weight;
	int data;
	int max;
	int min;
	Node *left;
	Node *right;
	Node *parent;
};

class mycompare
{
	bool reverse;
public:
	mycompare(const bool &re = true)
	{
		reverse = re;
	}
	bool operator() (Node *a, Node *b) const
	{
		//优先队列，从小到大排列mycompare，按照weight的从小到大排列
		if(reverse) return(a->weight > b->weight);
		else {
			return (a->weight < b->weight);
			//从大到小排列
		}
	}
};

class Huffman
{
public:
	Huffman()
	{
		ifstream fin("4.txt");
		string line;
		stringstream stream;
		int cnt = 0;
		if(getline(fin, line))
		{
			stream << line;
			stream >> length;
		}

		while(getline(fin, line))
		{
			long temp;
			Node *enode = new Node;
			stream.clear();
			stream << line;
			stream >> temp;
			enode->data = cnt;
			enode->weight = temp;
			enode->max = 0;
			enode->min = 0;
			mypq.push(enode);
//			symbols.push_back(temp);
		}
	}
	int max(int a, int b)
	{
		return a > b ? a : b;
	}

	int min(int a, int b)
	{
		return a < b? a : b;
	}
	Node* CreateTree()
	{
		while(mypq.size() > 1)
		{
			Node *enode1 = new Node;
			Node *enode2 = new Node;
			Node *node = new Node;
			enode1 = mypq.top();
			mypq.pop();
			enode2 = mypq.top();
			mypq.pop();
			node->max = max( enode1->max, enode2->max ) + 1;
			node->min = min( enode1->min, enode2->min ) + 1;
			node->weight = enode1->weight + enode2->weight;
			node->left = enode1;
			enode1->parent = node;
			node->right = enode2;
			enode2->parent = node;
			mypq.push(node);		
		}
		
	//	Node root = new Node;
		root = mypq.top();
	//	mypq.pop();
		return root;
	}

public:
	Node* root = new Node;	//根节点
//	vector<long> symbols;
	int length;
	priority_queue<Node*, vector<Node*>, mycompare > mypq;//优先队列
	vector<Node*> huffmanTree;
};


int main()
{
	Huffman _huffman;
	cout << "max:" << _huffman.CreateTree()->max << endl;
	cout << "min:" << _huffman.CreateTree()->min << endl;
	return 0;
}
