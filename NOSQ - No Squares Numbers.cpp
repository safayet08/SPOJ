#include<bits/stdc++.h>
#define MAX 100010
using namespace std;

int arr[MAX][11];

void filter()
{
    //Using sieve technique to filter the square free numbers
    
    int sq = sqrt(MAX);
    arr[0][0] = 1;
    for(int i = 2; i <= sq; i++)
    {
        if(arr[i][10] == 0)
        {
            int k = i*i;
            for(int j = k; j <= 100000; j += k)
                arr[j][10] = 1;
        }
    }
    
  //Now doing the business with the digits
  //Cumulative sum technique is used
    for(int i = 1; i <= 100000; i++)
    {
        if(arr[i][10] == 0)
        {
            int temp = i;
            while(temp != 0)
            {
                arr[i][temp%10] = 1;
                temp /= 10;
            }
            for(int j = 0; j <= 9; j++)
                arr[i][j] += arr[i-1][j];
        }
        else
        {
            for(int j = 0; j <= 9; j++)
                arr[i][j] = arr[i-1][j];
        }
    }
}
int main()
{
    filter();
    int T;
    scanf("%d",&T);
    for(int i=1; i<=T; i++)
    {
        int a,b,d;
        scanf("%d %d %d",&a,&b,&d);
        printf("%d\n",arr[b][d] - arr[a-1][d]);
    }
    return 0;
}
