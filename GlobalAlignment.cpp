#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include<string>
using std::string;

//scoring function
struct scoring{
	int match;
	int mismatch;
	int gap_penalty;
}g;
string s, t;						//接收使用者輸入的序列
char align_s[51], align_t[51];		//存放配對後的序列

void similarity(int**);				//初始存取分數的陣列
int max( int, int, int );			//分數取最大值
int p( int, int );					//選擇match或mismatch的分數
int align(int, int, int, int**);	//執行alignment

int main()
{
	string temp;					//暫存使用者輸入的序列
	int len = 0;					//序列執行alignment後的長度
	
	g.gap_penalty = -2;				//global alignment 的 scoring function
	g.mismatch = -1;
	g.match = 1;

	s.push_back('-');				//因第一個字元不會使用到，為執行alignment方便
	t.push_back('-');				//，將第一個單位隨意安插一字元

									//使用者輸入序列
	cout << "Input sequence s:\n";     
	cin >> temp;
	s += temp;
	cout << "Input t:\n";
	cin >> temp;
	t += temp;

	int **F = new int *[s.length()];
	for( int k = 0 ; k < s.length() ; k++ )
		F[k] = new int [t.length()];
	
	//執行similarity
	similarity(F);
	//執行alignment
	len = align( s.length()-1, t.length()-1, len, F );

	//輸出結果
	cout << "\n\n\ns:";
	for( int i = 1 ; i <= len ; i++ )
		cout << align_s[i] << " "; 
	cout << endl << "t:";
	for( int i = 1 ; i <= len ; i++ )	
		cout << align_t[i] << " ";

	cout << endl;

	return 0;
}

int align( int i, int j, int len, int **F )
{
	if( i == 0 && j == 0 )
		len = 0;
	else if( i > 0 && F[i][j] == F[i-1][j] + g.gap_penalty )
	{
		len = align(i-1, j, len, F);
		len++;
		align_s[len] = s[i];
		align_t[len] = '-';
	}
	else if( i > 0 && j > 0 && F[i][j] == F[i-1][j-1]+p( i, j ))
	{
		len = align( i-1, j-1, len, F );
		len++;
		align_s[len] = s[i];
        align_t[len] = t[j];
	}
	else if( j > 0 && F[i][j] == F[i][j-1]+g.gap_penalty )
	{
		len = align( i, j-1, len, F );
		len++;
		align_s[len] = '-';
        align_t[len] = t[j];
	}
	return len;
}

void similarity( int **F )
{
	for( int i = 0 ; i < s.length()-1 ; i++ )
		F[i][0] = i*g.gap_penalty;
	for( int i = 0 ; i < t.length()-1 ; i++ )
		F[0][i] = i*g.gap_penalty;

	for( int i = 1 ; i < s.length() ; i++ )
		for( int j = 1 ; j < t.length() ; j++ )
			F[i][j] = max( F[i-1][j] + g.gap_penalty, F[i-1][j-1] + p(i,j), F[i][j-1] + g.gap_penalty);
}

int max( int a, int b, int c )
{
	int temp = a;

	if( b > temp )
		temp = b;
	if( c > temp )
		temp = c;

	return temp;
}

int p( int i, int j )
{
	if( s[i] == t[j] )
		return g.match;
	else
		return g.mismatch;
}