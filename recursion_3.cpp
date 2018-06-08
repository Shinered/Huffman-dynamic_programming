#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
/*memorization ：递归加缓存优化，备忘录算法
 *如果不用缓存，时间是O(2^n)次方
 *用了缓存后，时间空间复杂度均为O(n)
 *V[n] = max(V[n-1], V[n-2] + vn.weight) 
 *Running time: 0.06s
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
		
	long recursion()
	{
		return dynamic(nodes);  //调用递归
	}
/******************递归+缓存******************/	
	long dynamic( vector<Node> &nodes1 )
	{
		int le = nodes1.size();
		//如果该节点的最大权重已经被计算过，则返回
		if(weights[le-1]) return weights[le-1];
		
		if( nodes1.size() == 1 )		
		{
			sum[0].push_back(nodes1[0].index + 1);
			weights[0] = nodes1[0].weight;
			return weights[0];   //返回节点数目为1的情况
		}

		if( nodes1.size() == 2 ) //节点数目为2的情况
		{
			if(nodes1[0].weight >= nodes1[1].weight)		
			{
				sum[1].push_back(nodes1[0].index + 1);
				weights[1] = nodes1[0].weight;

			} else {
				sum[1].push_back(nodes1[1].index + 1);
				weights[1] = nodes1[1].weight;
			}
			return weights[1];
		}
		
		int len = nodes1.size();
		vector<Node> temp2, temp1;
		temp2.insert( temp2.begin(), nodes1.begin(), nodes1.end() - 2 );
		temp1.insert( temp1.begin(), nodes1.begin(), nodes1.end() - 1 );
		long weight1 = dynamic(temp1); //上一步的最大权重
		long weight2 = dynamic(temp2) + nodes1[len-1].weight; //上上步的最大权重加当前节点权重值
		if( weight1 >= weight2 )
		{
			sum[len-1].insert(sum[len-1].begin(), sum[len-2].begin(), sum[len-2].end());
			weights[len-1] = weight1; //缓存
		} else {
			sum[len-1].insert(sum[len-1].begin(), sum[len-3].begin(), sum[len-3].end());
			sum[len-1].push_back(nodes1[len-1].index + 1); //存节点
			weights[len-1] = weight2;
		}
		return weights[len-1];
	}
/**********打印************/	
	void print()
	{
		ofstream fout;
		fout.open("output.txt");
		for(int i = 0; i < length; i++)
		{
			fout << i << "th:";
			for(int j = 0; j < sum[i].size(); j++)
			{
				fout << sum[i][j] << " ";
			}
			fout << " max_weight:" << weights[i] << endl;
		}


	}
/*************Reconstruction,得到最大权重独立集**********/
	void reconstruct()
	{
		int i = length - 1;
		while( i > 1)
		{
			if( weights[i-1] >= weights[i-2] + nodes[i].weight )
			{
				i--;
			} else {
				path.push_back(i);
				i = i-2;
			}
		}		
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
	cout << "max_weight_of_IS:" << wis.recursion()  << endl;
	wis.reconstruct();
	wis.print();
	end = clock();
	cout << "running time:" << (double)(end-start)/CLOCKS_PER_SEC << " s" << endl;
	return 0;

}












