#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
/*
**	迭代的方法, running time: 0.000982s
*/

/*********节点数据存储**********/
class Node
{
public:
	long weight; //权重
	int index;   //索引值
};
/***********max-weight independent set****************/
class WIS
{
public:
	WIS()   //构造函数
	{
		ifstream fin("mwis.txt");
		string line;
		stringstream stream;
		int cnt = 0;
		if(getline(fin, line))
		{
			stream.clear();
			stream << line;
			stream >> length;
		}
		initWis();
		while(getline(fin, line))
		{	
			long temp;
			stream.clear();
			stream << line;
			stream >> temp;
			nodes[cnt].index = cnt;
			nodes[cnt].weight = temp;
			cnt++;
		}
	}
/*************初始化每一步的最大权重****************/	
	void initWis()
	{
		nodes.resize(length);
		sum.resize(length);
		weights.resize(length);
		for(int i = 0; i < length; i++)
		{
			weights[i] = 0;
		}
	}
	
	long dynamic()
	{
		long a, b, temp;
		a = nodes[0].weight;
		if(nodes[1].weight > nodes[0].weight)
		{
			b = nodes[1].weight;
		} else {
			b = nodes[0].weight;
		}
		for(int i = 2; i < length; i++)		
		{
		//	a = nodes[i-2].weight;
		//	b = nodes[i-1].weight;
			if(a+nodes[i].weight > b)
			{
				temp = b;
				b = a+nodes[i].weight;
				a = temp;
			} else {
				a = b;
			}	
		}
		
		return b;
	}




public:
	int length;   //节点总数目
	vector<Node> nodes ;
	vector<long> weights;//每一步的最大权重
	vector< vector<long> > sum; //存储每一步的最大权重的点
	vector<int> path;  //max-weight independent set

};

int main()
{
	clock_t start, end;
	start = clock();
	WIS wis;
	cout << "max_weight_of_IS:" << wis.dynamic() << endl;
	end = clock();
	cout << "running time:" << (double)(end-start)/CLOCKS_PER_SEC << "s" <<  endl;
	return 0;
}


