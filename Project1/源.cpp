#include<iostream>
using namespace std;
#define N 100

typedef struct
{
	char data;
	double weight;
	int lchild, rchild, parent;
}HTNode;

//构造哈夫曼树
void CreateHT(HTNode ht[], int n0)
{
	int i, k, lnode, rnode;
	double min1, min2;
	for (i = 0; i < 2 * n0 - 1; i++)
	{
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
	}
	for (i = n0; i <= 2 * n0 - 2; i++)
	{
		min1 = min2 = 32767;
		lnode = rnode = -1;
		for (k = 0; k <= i - 1; k++)
		{
			if (ht[k].parent == -1)
			{
				if (ht[k].weight < min1)
				{
					min2 = min1;
					rnode = lnode;
					min1 = ht[k].weight;
					lnode = k;
				}
				else if (ht[k].weight < min2)
				{
					min2 = ht[k].weight;
					rnode = k;
				}
			}
		}
		
		ht[i].weight = ht[lnode].weight + ht[rnode].weight;
		ht[i].lchild = lnode;
		ht[i].rchild = rnode;
		ht[lnode].parent = i;
		ht[rnode].parent = i;
	}
}


//构造哈夫曼树对应测试
int main()
{
	HTNode ht[N];
	ht[0].data = 'a';
	ht[0].weight = 2;

	ht[1].data = 'b';
	ht[1].weight = 7;

	ht[2].data = 'c';
	ht[2].weight = 3;

	ht[3].data = 'd';
	ht[3].weight = 1;

	ht[4].data = 'e';
	ht[4].weight = 5;

	CreateHT(ht,5);

	for (int i = 0; i < 7; i++)
		cout << ht[i].weight << " ";
	

	return 0;
}