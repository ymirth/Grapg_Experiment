#pragma once
#ifndef DAG_H
#define DAG_H
#include<iostream>
#include<utility>
#include<string>
#include<queue>
#include<set>
#include<vector>
#include<functional>
#include<list>
#include"HEAP.h"
#define M 1000
pair<int, int> Min;
using namespace std;
struct Adj
{
	int dis;
	int time;
	string city;
};
class Vertex
{
public:
	string city;
	list<Adj> adjacency;
	Vertex* path;
	int dist;
	int time;
	bool known;	
};

typedef pair<int, int> Cost;
struct comp
{
	bool operator()(Cost c1, Cost c2)
	{
		return c1.first > c2.first;
	}
};
class DAGCity
{
private:
	vector<Vertex> G;
	vector<int> TimeCost;
	vector<int> DistanceCost;
	vector<int> preT;
	vector<int> preD;
	Heap Tcost;
	Heap Dcost;
	int V;
	int E;
public:
	DAGCity(){}
	DAGCity(int v,int e):V(v),E(e)
	{
		Tcost.SetSize(v);
		Dcost.SetSize(v);
		creat(v, e);
		for (int i = 0; i < V; ++i)
		{
			G[i].known = false;
			G[i].path = NULL;
		}
	}
	int findindex(string temp) const
	{
		for (int i = 0; i < V; ++i)
		{
			if (G[i].city == temp) return i;
		}
		return -1;
	}
	
	Vertex& operator[](string temp)
	{
		return G[findindex(temp)];
	}
	
	void creat(int v, int e)
	{
		V = v;
		E = e;
		for (int i = 0; i < E; ++i)
		{
			Vertex temp;
			string vertex;   //出发结点
			Adj adj;         //相邻结点
			cin >> vertex >> adj.city >> adj.dis >> adj.time;
			int flag = 0;     //标志邻接表中是否存在顶点1 vertex
			int sec = 0;      //标志邻接表中是否存在顶点2 adj
			for (int i = 0; i < G.size(); ++i)
			{//若邻接表中存在结点名为vertex时
				if (vertex == G[i].city)
				{
					flag = 1;			
					G[i].adjacency.push_back(adj);
					break;
				}
			}
			for (int i = 0; i < G.size(); ++i)
			{//检查邻接表中是否存在结点名字为adj.city
				if (adj.city == G[i].city)
				{
					sec = 1;
					break;
				}
			}
			if (adj.city != vertex && sec == 0)
			{ //不存在adj.city
				Vertex vadj;
				list<Adj> nulllist;
				vadj.adjacency = nulllist;
				vadj.city = adj.city;
				G.push_back(vadj);
			}
			if (flag == 0)
			{ //不存在vertex
				temp.city = vertex;         
				temp.adjacency.push_back(adj);
				G.push_back(temp);
			}

		}
	}
	void Ttraverse()
	{
		for (int i = 0; i < G.size(); ++i)
		{
			if (G[i].adjacency.empty()) cout << G[i].city ;
			else
			{
				list<Adj>::iterator it = G[i].adjacency.begin();
				for (; it != G[i].adjacency.end(); ++it)
				{
					cout << G.at(i).city << "- >" << (*it).city ;
				}
			}
			cout << endl;
		}

	}
	void FindMinT(Heap h)
	{
		/*priority_queue<Consume, greater<Consume>> reslut;
		for (int i = 1; i <= h.Size(); ++i)
		{
			int po = h[1].position;
			list<Adj>::iterator it;
			it = G[po].adjacency.begin();

			int cos = (*it).time;
			string cc = (*it).city;
			while (it != G[po].adjacency.end())
			{
				if ((*it).time < cos)
				{
					cos = (*it).time;
					cc = (*it).city;
				}
				++it;
			}
			Consume temp;
			temp.cost = cos;
			temp.position = findindex(cc);
			reslut.push(temp);
			
		}
		*/
		/*Consume tep = reslut.top();
		pair<int, int> Min;
		Min.first = tep.position;   //（w,u)最小时，u在G中的位置
		Min.second = tep.cost;      //（w,u)最小值
		return Min;*/
	
	}
	void FindMinTime(Heap& h)
	{
		
		for (int i = 1; i <= h.Size(); ++i)
		{
			cout << h[i].position << endl;
		}
		//priority_queue<Consume, greater<Consume>> reslut;
		for (int i = 1; i <= h.Size(); ++i)
		{
			int po = h[i].position;     //最小位置的结点
			cout << "PO=" << po << endl;
			int precost = h[i].cost;
			cout << "PO.cost=" << h[i].cost << endl;
			if (G[po].known==0)
			{//未被访问过
				G[po].known = true;
				cout <<  "年后";
				list<Adj>::iterator it; 
				it = G[po].adjacency.begin();   //用it遍历选中的G[po]的邻居

				//辅助变量
				int cos = (*it).time;   //用于存储最小权值(时间)
				string cc = (*it).city; //用于存储到达h[i]结点最短时间可到达的城市名称
				cout << cc;
				while (it != G[po].adjacency.end())    //遍历链表寻找最小权值
				{
					//cout << (*it).time;
					if ((*it).time < cos)
					{
						cos = (*it).time;
						cc = (*it).city;
						cout << cc;
					}

					int place = findindex(cc);  //( h[i],v)最小时，v在图G位置
					cout << "PLACE::" << place;
					int p = h.find(place);      //( h[i],v)最小时，v在堆Heap的位置
					if (cos + precost < h[p].cost)   //若小于原来算出的cost，则更新堆
						h.emplace(cos + precost, place);   //更新堆中的距离
					for (int i = 1; i <= h.Size(); ++i)
					{
						cout << h[i].position << "  " <<h[i].cost<< endl;
					}
					++it;
				}
				
				/*
				*Consume temp;
				*temp.cost = cos;
				*temp.position = findindex(cc);
				*reslut.push(temp);
				*/
			}
			else
			{
				continue;
			}
		}
		//Consume tep = reslut.top();
		//return tep.position;
		cout << h[2].cost << "  " << h[3].position;
	}
	inline bool CheckAccess()
	{
		for (int i = 0; i < V; ++i)
		{
			if (G[i].known == false) return 1;
		}
		return 0;
	}
	void DejskT(string k1,string k2)
	{
		
		for (int i = 0; i < V; ++i)
		{//初始化
			G[i].time = INT_MAX;
		}
		//cout << "place 1=" << findindex(k1);
		//Tcost.emplace(0,findindex(k1));//第一个元素入堆
		//G[findindex(k1)].known = true;
		//cout << "你好" << endl;
		//FindMinTime(Tcost);
		//while (CheckAccess())
		//{
			//Vertex v = G[FindMinT(Tcost).first];     //(u,v)最小时
			//v.known = true;
			//list<Adj>::iterator it = v.adjacency.begin();
			//for (int i = 0; i < V; ++i)
			//{
			//	int index = findindex((*it).city);
			//	if (!G[index].known)
			//	{
			//		int cvw = (*it).time;
			 //       if(
			//	}
			//}
			//Tcost.emplace(FindMinT(Tcost).second, FindMinT(Tcost).first);
		//}
		int StartPlace = findindex(k1);//起始位置
		cout << "StartPlace= " << StartPlace << endl;
		G[StartPlace].known = true;//标记访问过
		priority_queue<pair<int, int>,vector<pair<int, int>>,comp> cost;

		pair<int, int> temp;
		G[StartPlace].time = 0;   //起始位置消耗时间为0
		temp = make_pair(0, StartPlace);
		cost.push(temp);
		while (CheckAccess())
		{
			pair<int, int> c;   //辅助pair变量，用于存储cost堆顶元素
			c = cost.top();
			int minplace = c.second;
			cout << "minplace = " << minplace << endl;
			Vertex& v = G[minplace];   // smallest unknown distance vertex
			v.known = true;           //标记访问
			cost.pop();

			if (!G[minplace].adjacency.empty())
			{
				list<Adj> templist = G[minplace].adjacency;  //对每一个与v相邻的元素遍历
				list<Adj>::iterator it = templist.begin();   //相邻的第一个邻居

				for (; it != templist.end(); ++it)
				{
					int adjplace = findindex((*it).city);  //邻居在表G中的位置
					cout << "adjplace =" << adjplace << endl;
					if (G[adjplace].known == false)
					{
						pair<int, int> p;         //辅助pair变量，用于存储邻居的信息
						int cvw = (*it).time;     //从v到达邻居的消耗
						if (v.time + cvw < G[adjplace].time)
						{//若新的路径消耗小，则在找到邻居的位置，更新，到达该结点的消耗
							G[adjplace].time = v.time + cvw;
							cout << "更新消耗，时间为：" << G[adjplace].time << endl;
							G[adjplace].path = &v;
						}
						p = make_pair(G[adjplace].time, adjplace);
						cost.push(p);   //每一个邻居入堆，用于寻找最小的结点
					}
				}
			}
			else continue;
		}

		showtime(k2);

	}
	void showtime(string k2)
	{
		cout << "到达"<<k2<<"耗时为：" << G[findindex(k2)].time << endl;
		cout << "路径为：" << endl;
		Path(k2);
	}
	void Path(string k2)
	{
		int index = findindex(k2);
		if (!G[index].path)
		{
			cout << G[index].city ;
			return;
		}
		Path(G[index].path->city);
		cout<< "- >" <<G[index].city;
	}
	void DejskD(string k1, string k2)
	{
		for (int i = 0; i <= V; ++i)
		{
			Dcost[i].cost =INT_MAX;
		}
	}
};

#endif // 

