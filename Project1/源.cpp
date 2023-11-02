/*
�������ݣ�
һ��������ϵͳӦ�������¹��ܣ�
(1) I����ʼ����Initialization�������ն˶����ַ�����Сn���Լ�n���ַ���n��Ȩֵ��
	�������������������������ļ�hfmTree�С�
(2) E�����루Encoding���������ѽ��õĻ����������粻���ڴ棬����ļ�hfmTree�ж��룩�����ļ�ToBeTran�е����Ľ��б��룬Ȼ�󽫽�������ļ�CodeFile�С�
(3) D�����루Decoding���������ѽ��õĻ����������ļ�CodeFile�еĴ���������룬
	��������ļ�Textfile�С�
================================================================================
(1) ���������ı���ʽ�洢���ļ�Codefile�С�
(2) �û�����������Ϊ���˵�����ʽ����ʾ�������ܷ��ţ��ټ��ϡ�Q������ʾ�˳�
	����Quit�����û�����һ��ѡ���ܷ����˹���ִ����Ϻ�����ʾ�˲˵���ֱ��ĳ��
	�û�ѡ���ˡ�Q��Ϊֹ��
(3) �ڳ����һ��ִ�й����У���һ��ִ��I��D��C����֮�󣬻��������Ѿ����ڴ��ˣ�
	�����ٶ��롣ÿ��ִ���в�һ��ִ��I�����Ϊ�ļ�hfmTree�������ѽ��á�

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
	char cd[N];	//��ŵ�ǰ���Ĺ�������
	int start;	//��ʾcd[start,n0]�����ǹ�������
}HCode;

//1�������������
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

//2�����ݹ������������������
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

//3����ʼ���������������浽�ļ���
void Initialization(string filename)
{
	int n = 0;
	cout << "�������ַ����е��ַ�������";
	cin >> n;

	HTNode ht[N] = {};
	HCode hcd[N] = {};

	for (int i = 0; i < n; i++)
	{
		cout << "�����ַ�" << i + 1 << ":";
		cin >> ht[i].data;
		cout << "�����ַ�" << i + 1 << "��Ӧ��Ȩ�أ�";
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
		cout << "�ļ���ʧ�ܣ�" << endl;
	}

}


//3����ʼ���������������浽�ļ��� ����
int main()
{
	string filename = "hfmTree.txt";
	Initialization(filename);

	return 0;
}



//���ݹ��������������������ԣ�ͨ����
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

