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

//3、I：初始化哈夫曼树并保存到文件中
void Initialization(string filename)
{
	int n = 0;
	cout << "请输入字符集中的字符个数：";
	cin >> n;

	HTNode ht[N] = {};
	HCode hcd[N] = {};

	for (int i = 0; i < n; i++)
	{
		char c;
		cout << "输入字符" << i + 1 << ":";
		//cin >> ht[i].data;
		getchar();
		cin.get(c);
		ht[i].data = c;
		if (ht[i].data == ' ')
			ht[i].data = '#';
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

//4、E：编码，对文件ToBeTran中正文进行编码，将结果存入文件CodeFile
void Encoding(string inputFile, string outputFile, string hfmTree)
{
	HCode hcd[N] = {};
	//从hfmTree文件中读出哈夫曼树信息并初始化哈夫曼树
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
	
	//打开输入文件和输出文件
	ifstream ifsn(inputFile);
	ofstream ofsn(outputFile);

	if (ifsn.is_open() && ofsn.is_open())
	{
		//读取输入文件内容并进行编码，将结果写入输出文件
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
		cout << "输入或输出文件打开失败！" << endl;
	}
}


//5、D：译码，利用已经建好的哈夫曼表将文件CodeFile中的代码进行译码，结果
//	存入文件Textfile中
void Decoding(string inputfile, string outfile, string hfmTree)
{
	HCode hcd[N] = {};
	//从hfmTree中读入哈夫曼信息并初始化哈夫曼树
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
		cout << "文件打开错误！" << endl;
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
	cout << "----------------------------------------------哈夫曼编码译码操作系统------------------------------------------" << endl<<endl;
	cout << "I：初始化哈夫曼树。存入文件【hfmTree.txt】"<<endl;
	cout << "E：编码。利用文件【hfmTree.txt】中的信息对【ToBeTrain.txt】文件中的正文进行编码，并将结果输出到文件【CodeFile.txt】中" << endl;
	cout << "D：译码。利用已经建好的哈夫曼树，将文件【CodeFile.txt】中的内容进行译码，结果存入文件【TextFile.txt】中" << endl ;
	cout << "Q:退出系统。" << endl << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

void menu(char c, string filename, string inputFileName, string outputFileName, string newfile)
{
	switch (c)
	{
	case 'I':
		Initialization(filename);
		cout << "哈夫曼树创建完成！" << endl;
		break;

	case 'E':
		Encoding(inputFileName, outputFileName, filename);
		cout << "编码完成！" << endl;
		break;

	case 'D':
		Decoding(outputFileName, newfile, filename);
		cout << "译码输出完成！" << endl;
		break;
	
	}
}

//3、初始化哈夫曼树并保存到文件中 测试
int main()
{
	string filename = "hfmTree.txt";
	string inputFileName = "ToBeTran.txt";
	string outputFileName = "CodeFile.txt";
	string newfile = "Textfile.txt";
	UI();
	char c;
	cout << "请输入你要选择的功能" << endl;
	cin >> c;
	while (1)
	{
		if (c == 'q'||c == 'Q') {
			return 0;
		}
		system("cls");
		UI();
		menu(c, filename, inputFileName, outputFileName, newfile);
		cout << "请输入你要选择的功能" << endl;
		cin >> c;
		system("pause");
	}

	return 0;
}