#pragma once
#ifndef HEAP_H
#define HEAP_H
#define M 1000
using namespace std;
struct Consume
{
	int cost;
	int position;
	bool operator<(const Consume& a) const
	{
		return cost < a.cost; //大顶堆
	}
};
class Heap
{
private:
	int size;
	Consume* H = new Consume[M];
public:
	Heap() :size(0) {}
	int Size()
	{
		return size;
	}
	void SetSize(int n)
	{
		size = n;
	}
	inline bool compare(Consume c1, Consume c2)
	{
		return c1.cost < c2.cost;
	}
	int LChild(int i)
	{
		return 2 * i;
	}
	int RChild(int i)
	{
		return 2 * i + 1;
	}
	void PercDown(int& index, const int elem)
	{//向下渗透
		//cout << "index=" << index << " " << "elem=" << elem << endl;
		if (2 * index > size)
		{
			H[index].cost = elem;
			return;
		}
		else if (2 * index == size)
		{//只有一个孩子
			if (elem > H[size].cost)
				swap(H[index], H[size]);  //交换两个元素
			else H[index].cost = elem;
			return;
		}
		else if (2 * index < size)
		{//有两个孩子
			int j = H[2 * index].cost < H[2 * index + 1].cost ? 2 * index : 2 * index + 1;
			if (H[j].cost < elem)
			{
				H[index] = H[j];          //孩子上移
				PercDown(j, elem); //向下递归
			}
			else
			{
				H[index].cost = elem;
				return;
			}
		}
	}
	void PercUp(int index, const int elem)
	{//向上渗透
		if (index == 1)
		{
			H[1].cost = elem;
			return;
		}
		else if (elem < H[index / 2].cost)
		{//elem < 它的双亲
			H[index] = H[index / 2];        //双亲下移
			return PercUp(index / 2, elem);
		}
		else if (elem >= H[index / 2].cost)
		{//elem > 它的双亲
			H[index].cost = elem;
			return;
		}
	}


	void Insert(const int& C, const int& index)
	{//插入操作
		++size;
		H[size].cost = C;
		H[size].position = index;
		PercUp(size, C);
	}
	void DeleteMin()
	{
		H[1] = H[size];
		--size;
		int e = 1;
		PercDown(e, H[1].cost);
	}
	bool empty()
	{
		return size == 0;
	}
	void emplace(const int& C, const int& index)
	{
		this->DeleteMin();
		this->Insert(C, index);
	}
	Consume& operator[](int x)
	{
		return this->H[x];
	}
};
#endif // !HEAP_H
