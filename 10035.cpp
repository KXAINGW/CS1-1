#include<iostream>
using namespace std;
int main()
{
	char num1[11], num2[11];
	while (cin >> num1 >> num2, (strlen(num1)!=1||num1[0] != '0') || (strlen(num2)!=1||num2[0] != '0'))
	{
		int i = 0, j = 0, k =0, times = 0;
		int sum[12] = {};
		int num1Len = strlen(num1);
		int num2Len = strlen(num2);
		//¶¶§Ç¬O¤Ïªº
		//12345
		//0,1,2,3,4
		while (i < num1Len && j < num2Len)
		{
			sum[k] += (num1[num1Len-i-1]-'0') + (num2[num2Len-j-1]-'0');
			k++,i++, j++;
		}
		while (i < num1Len)
		{
			sum[k] += num1[num1Len-i-1] - '0';
			k++, i++;
		}
		while (j < num2Len)
		{
			sum[k] += num2[num2Len-j-1] - '0';
			k++, j++;
		}


		for (int i = 0; i <k; i++)
		{
			if (sum[i] > 9)
			{
				sum[i] -= 10;
				sum[i + 1] ++;
				times += 1;
			}
			//cout << sum[i];
		}
		//cout << endl;
		if(times>1)
			cout<<times<< " carry operations." << endl;
		else if(times ==1)
			cout<<times<< " carry operation." << endl;
		else
			cout << "No carry operation." << endl;
	}
	return 0;
}

/*#include<iostream>
#include<string.h>
using namespace std;
int addfun(int sum[], int add[],int,int);
int main()
{
    char num1[10], num2[10];
    int index, sumlen,addlen;
    while (cin >> num1 >> num2)
    {
    	int sum[11] = {};
    	int add[10] = {};
    	if (num1[0] == 48 && num2[0] == 48 && num1[1] == 0 && num2[1] == 0)
    	    break;
    	sumlen = strlen(num1);
    	for (int i = sumlen; i > 0; i--)
    	    sum[sumlen - i] = num1[i-1]-'0';
    	addlen = strlen(num2);
    	for (int i = addlen; i > 0; i--)
    	    add[addlen - i] = num2[i-1] - '0';
    	index = addfun(sum, add,sumlen,addlen);
    	if (index != 0 && index!=1)
    	    cout << index << " carry operations."<<endl;
    	else if(index ==1)
    	    cout<< index << " carry operation." << endl;
    	else
    	    cout << "No carry operation." << endl;	
    }
    return 0;
}

int addfun(int sum[], int add[], int sumlen, int addlen)
{
    int index = 0;
    if (sumlen >= addlen)
    {
        for (int i = 0; i < sumlen; i++)
    	    sum[i] += add[i];
    	for (int i = 0; i < sumlen; i++)
    	{
    	    if (sum[i] > 9)
    	    {
                sum[i + 1] += 1;
                sum[i] -= 1;
                index++;
    	    }
    	}
    }
    else
    {
    	for (int i = 0; i < addlen; i++)
    	    sum[i] += add[i];
    	for (int i = 0; i < addlen; i++)
    	{
    	    if (sum[i] > 9)
    	    {
    		    sum[i + 1] += 1;
    		    sum[i] -= 1;
    		    index++;
    	    }
    	}
    }
    return index;
}*/