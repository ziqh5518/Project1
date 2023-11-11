#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
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

//3��I����ʼ���������������浽�ļ���
void Initialization(string filename)
{
	int n = 0;
	cout << "�������ַ����е��ַ�������";
	cin >> n;

	HTNode ht[N] = {};
	HCode hcd[N] = {};

	for (int i = 0; i < n; i++)
	{
		char c;
		cout << "�����ַ�" << i + 1 << ":";
		//cin >> ht[i].data;
		getchar();
		cin.get(c);
		ht[i].data = c;
		if (ht[i].data == ' ')
			ht[i].data = '#';
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

//4��E�����룬���ļ�ToBeTran�����Ľ��б��룬����������ļ�CodeFile
void Encoding(string inputFile, string outputFile, string hfmTree)
{
	HCode hcd[N] = {};
	//��hfmTree�ļ��ж�������������Ϣ����ʼ����������
	ifstream ifs(hfmTree);
	int n;
	ifs >> n;
	HTNode ht[N] = {};
	for (int i = 0; i < n; i++)
	{
		ifs >> ht[i].data >> ht[i].weight;
		if (ht[i].data=='#')
		{
			ht[i].data = ' ';
		}
		cout << ht[i].data << " " << ht[i].weight << endl;
	}
	ifs.close();

	CreateHT(ht, n);
	CreateHCode(ht, hcd, n);
	
	//�������ļ�������ļ�
	ifstream ifsn(inputFile);
	ofstream ofsn(outputFile);

	if (ifsn.is_open() && ofsn.is_open())
	{
		//��ȡ�����ļ����ݲ����б��룬�����д������ļ�
		char ch;
		while (ifsn.get(ch))
		{
			for (int i = 0; i < n; i++)
			{
				if (ht[i].data == ch)
				{
					ofsn <<hcd[i].cd +( hcd[i].start); //?????!!!!!
					break;
				}
			}
		}
		ifsn.close();
		ofsn.close();

	}
	else
	{
		cout << "���������ļ���ʧ�ܣ�" << endl;
	}
}


//5��D�����룬�����Ѿ����õĹ��������ļ�CodeFile�еĴ���������룬���
//	�����ļ�Textfile��
void Decoding(string inputfile, string outfile, string hfmTree)
{
	HCode hcd[N] = {};
	//��hfmTree�ж����������Ϣ����ʼ����������
	ifstream  ifs(hfmTree);
	int n;
	ifs >> n;
	HTNode ht[N] = {};
	for (int i = 0; i < n; i++)
	{
		ifs >> ht[i].data >> ht[i].weight;
		if (ht[i].data == '#')
		{
			ht[i].data = ' ';
		}
	}
	
	ifs.close();

	CreateHT(ht, n);
	CreateHCode(ht, hcd, n);

	ifstream ifsn(inputfile);
	ofstream ofsn(outfile);

	string code;
	if (!ifsn)
	{
		cout << "�ļ��򿪴���" << endl;
	}
	else
	{
		int i = 0;
		int node = 2 * n - 2;
		char bit;
		while (ifsn.get(bit))
		{
			if (bit == '0')
			{
				node = ht[node].lchild;
			}
			else if (bit == '1')
			{
				node = ht[node].rchild;
			}
			if (ht[node].lchild == -1 && ht[node].rchild == -1)
			{
				ofsn << ht[node].data;
				node = 2 * n - 2;
			}
		}

		ifsn.close();
		ofsn.close();
	}
	
}

void UI()
{
	cout << "----------------------------------------------�����������������ϵͳ------------------------------------------" << endl<<endl;
	cout << "I����ʼ�����������������ļ���hfmTree.txt��"<<endl;
	cout << "E�����롣�����ļ���hfmTree.txt���е���Ϣ�ԡ�ToBeTrain.txt���ļ��е����Ľ��б��룬�������������ļ���CodeFile.txt����" << endl;
	cout << "D�����롣�����Ѿ����õĹ������������ļ���CodeFile.txt���е����ݽ������룬��������ļ���TextFile.txt����" << endl ;
	cout << "Q:�˳�ϵͳ��" << endl << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

void menu(char c, string filename, string inputFileName, string outputFileName, string newfile)
{
	switch (c)
	{
	case 'I':
		Initialization(filename);
		cout << "��������������ɣ�" << endl;
		break;

	case 'E':
		Encoding(inputFileName, outputFileName, filename);
		cout << "������ɣ�" << endl;
		break;

	case 'D':
		Decoding(outputFileName, newfile, filename);
		cout << "���������ɣ�" << endl;
		break;
	
	}
}

//3����ʼ���������������浽�ļ��� ����
int main()
{
	string filename = "hfmTree.txt";
	string inputFileName = "ToBeTran.txt";
	string outputFileName = "CodeFile.txt";
	string newfile = "Textfile.txt";
	UI();
	char c;
	cout << "��������Ҫѡ��Ĺ���" << endl;
	cin >> c;
	while (1)
	{
		if (c == 'q'||c == 'Q') {
			return 0;
		}
		system("cls");
		UI();
		menu(c, filename, inputFileName, outputFileName, newfile);
		cout << "��������Ҫѡ��Ĺ���" << endl;
		cin >> c;
		system("pause");
	}

	return 0;
}