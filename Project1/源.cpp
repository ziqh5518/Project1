/*
必做内容：
一个完整的系统应具有以下功能：
(1) I：初始化（Initialization）。从终端读入字符集大小n，以及n个字符和n个权值，
	建立霍夫曼树，并将它存于文件hfmTree中。
(2) E：编码（Encoding）。利用已建好的霍夫曼树（如不在内存，则从文件hfmTree中读入），对文件ToBeTran中的正文进行编码，然后将结果存入文件CodeFile中。
(3) D：译码（Decoding）。利用已建好的霍夫曼树将文件CodeFile中的代码进行译码，
	结果存入文件Textfile中。
================================================================================
(1) 编码结果以文本方式存储在文件Codefile中。
(2) 用户界面可以设计为“菜单”方式：显示上述功能符号，再加上“Q”，表示退出
	运行Quit。请用户键入一个选择功能符。此功能执行完毕后再显示此菜单，直至某次
	用户选择了“Q”为止。
(3) 在程序的一次执行过程中，第一次执行I，D或C命令之后，霍夫曼树已经在内存了，
	不必再读入。每次执行中不一定执行I命令，因为文件hfmTree可能早已建好。

*/

#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#define N 100

typedef struct
{
	char data;
	double weight;
	int lchild, rchild, parent;
}HTNode;

typedef struct
{
	char cd[N];	//存放当前结点的哈夫曼码
	int start;	//表示cd[start,n0]部分是哈夫曼码
}HCode;

//1、构造哈夫曼树
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

//2、根据哈夫曼树求哈夫曼编码
void CreateHCode(HTNode ht[], HCode hcd[], int n0)
{
	int i, f, c;
	HCode hc;
	for (i = 0; i < n0; i++)
	{
		hc.start = n0;
		c = i;
		f = ht[i].parent;
		while (f != -1)
		{
			if (ht[f].lchild == c)
				hc.cd[hc.start--] = '0';
			else
				hc.cd[hc.start--] = '1';
			c = f;
			f = ht[f].parent;
		}
		hc.start++;
		hcd[i] = hc;
	}
}

//3、初始化哈夫曼树并保存到文件中
void Initialization(string filename)
{
	int n = 0;
	cout << "请输入字符集中的字符个数：";
	cin >> n;

	HTNode ht[N] = {};
	HCode hcd[N] = {};

	for (int i = 0; i < n; i++)
	{
		cout << "输入字符" << i + 1 << ":";
		cin >> ht[i].data;
		cout << "输入字符" << i + 1 << "对应的权重：";
		cin >> ht[i].weight;
	}
	CreateHT(ht, n);
	CreateHCode(ht, hcd, n);

	ofstream ofs(filename);
	if (ofs.is_open())
	{
		ofs << n << endl;
		for (int i = 0; i < n; i++)
		{
			ofs << ht[i].data << " " << ht[i].weight << endl;
		}
		ofs.close();
	}
	else
	{
		cout << "文件打开失败！" << endl;
	}

}


//3、初始化哈夫曼树并保存到文件中 测试
int main()
{
	string filename = "hfmTree.txt";
	Initialization(filename);

	return 0;
}



//根据哈夫曼树求哈夫曼编码测试（通过）
//int main()
//{
//	HTNode ht[N];
//	HCode hcd[N];
//	ht[0].data = 'a';
//	ht[0].weight = 2;
//
//	ht[1].data = 'b';
//	ht[1].weight = 7;
//
//	ht[2].data = 'c';
//	ht[2].weight = 3;
//
//	ht[3].data = 'd';
//	ht[3].weight = 1;
//
//	ht[4].data = 'e';
//	ht[4].weight = 5;
//
//	CreateHT(ht, 5);
//	CreateHCode(ht, hcd, 5);
//
//	cout << hcd[3].cd[hcd->start] << " "
//		<< hcd[3].cd[hcd->start + 1] << " "
//		<< hcd[3].cd[hcd->start + 2] << " "
//		<< hcd[3].cd[hcd->start + 3];
//		
//
//	return 0;
//}

//

