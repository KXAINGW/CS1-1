#include <iostream>
using namespace std;

void recDivisionNlogonia( int N, int M, int numQueriesRemaining );

int main()
{
	int K, N, M;
	cin >> K;
	while( K > 0 )
	{
		cin >> N >> M;
		recDivisionNlogonia( N, M, K );
		cin >> K;
	}

	system( "pause" );
}

void recDivisionNlogonia( int N, int M, int numQueriesRemaining )
{
	


	int x, y;
	cin >> x >> y;

	if (x == N || y == M)
		cout << "divisa" << endl;
	else if (x > N && y > M)
		cout << "NE" << endl;
	else if (x<N && y>M)
		cout << "NO" << endl;
	else if (x < N && y < M)
		cout << "SO" << endl;
	else
		cout << "SE" << endl;

	if (--numQueriesRemaining)
		return recDivisionNlogonia(N, M, numQueriesRemaining);

}