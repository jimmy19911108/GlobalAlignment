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
string s, t;						//�����ϥΪ̿�J���ǦC
char align_s[51], align_t[51];		//�s��t��᪺�ǦC

void similarity(int**);				//��l�s�����ƪ��}�C
int max( int, int, int );			//���ƨ��̤j��
int p( int, int );					//���match��mismatch������
int align(int, int, int, int**);	//����alignment

int main()
{
	string temp;					//�Ȧs�ϥΪ̿�J���ǦC
	int len = 0;					//�ǦC����alignment�᪺����
	
	g.gap_penalty = -2;				//global alignment �� scoring function
	g.mismatch = -1;
	g.match = 1;

	s.push_back('-');				//�]�Ĥ@�Ӧr�����|�ϥΨ�A������alignment��K
	t.push_back('-');				//�A�N�Ĥ@�ӳ���H�N�w���@�r��

									//�ϥΪ̿�J�ǦC
	cout << "Input sequence s:\n";     
	cin >> temp;
	s += temp;
	cout << "Input t:\n";
	cin >> temp;
	t += temp;

	int **F = new int *[s.length()];
	for( int k = 0 ; k < s.length() ; k++ )
		F[k] = new int [t.length()];
	
	//����similarity
	similarity(F);
	//����alignment
	len = align( s.length()-1, t.length()-1, len, F );

	//��X���G
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