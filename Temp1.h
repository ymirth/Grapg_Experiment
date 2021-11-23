#pragma once
#ifndef DAG_H
#define DAG_H
#include<iostream>
#include<string>
#include<queue>
#include<set>
#include<vector>
#include<list>
#include"HEAP.h"
#define M 1000
using namespace std;
struct Adj
{
	int dis;
	int time;
	string city;
};
struct Vertex
{
	string city;
	list<Adj> adjacency;
};

class DAGCity
{
private:
	vector<Vertex> G;
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
	Vertex& FindMinT(Heap h,int& co)
	{
		priority_queue<Consume,greater<Consume>> reslut;
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
		Consume tep= reslut.top();
		co = tep.cost;
		return G[tep.position];
	}
	int FindMinTindex(Heap h)
	{
		priority_queue<Consume, greater<Consume>> reslut;
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
		Consume tep = reslut.top();
		return tep.position;
	}
	void DejskT(string k1,string k2)
	{
		for (int i = 0; i < V; ++i)
		{
			Tcost[i].cost = INFINITY;
		}
		Tcost.emplace(0,findindex(k1));
		while (!Tcost.empty())
		{
			int co;
			Vertex v = FindMinT(Tcost,co);
			Tcost.emplace(co, findindex(v.city));
		}
	}
	void DejskD(string k1, string k2)
	{
		for (int i = 0; i <= V; ++i)
		{
			Dcost[i].cost = INFINITY;
		}
	}
};

#endif // 
