#include <iostream>
#include <algorithm>
using namespace std;

int recMaxSpeed( int numRemaining );

int main()
{
	int T;
	cin >> T;
	for( int i = 1; i <= T; i++ )
	{
		int N;
		cin >> N;
		cout << "Case " << i << ": " << recMaxSpeed( N ) << endl;
	}

	system( "pause" );
}

int recMaxSpeed( int numRemaining )
{
	int speed;
	cin >> speed;

	if (numRemaining > 1)
	{
		int num = recMaxSpeed(--numRemaining);
		/*return num > speed ? num : speed;*/
		if (num > speed)
			return num;
		else
			return speed;
	}
		
	else 
		return speed;

}