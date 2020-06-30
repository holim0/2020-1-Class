#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
long long map[105][105];
long long dp[105][105];
bool check[105][105]={false,};
int m, n;
int dx[]={0, -1, 1};
int dy[]={1, 1, 1};
long long summax=0;
bool mrange(int x, int y){

    if(x<0 || y<0 || x>=m || y>=n) return false;
    
    else return true;

}

int main(int argc, const char* argv[]){

    ifstream inp("mouse.inp");
    ofstream out("mouse.out");
    int idx=0;
    while(!inp.eof()){
        if(idx==0) {
            inp>>m;idx++;
        }
        if(idx==1){
            inp>>n; idx++;
        }
        else{
            for(int i=0; i<m; i++){
                for (int j = 0; j < n; j++)
                {
                    inp>>map[i][j];
                }
            }
        }
    }

    
    for (int i = 0; i < m; i++) // 초기화 
    {
        dp[i][0]=map[i][0];
    }

    
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if(j>=0 && i-1>=0 && j<m && i-1<n){
                dp[j][i]= max(dp[j][i], dp[j][i-1]+map[j][i]);
            }
            if(j+1>=0 && i-1>=0 && j+1<m && i-1<n){
                dp[j][i]= max(dp[j][i], dp[j+1][i-1]+map[j][i]);
            }
            if(j-1>=0 && i-1>=0 && j-1<m && i-1<n){
                dp[j][i]= max(dp[j][i], dp[j-1][i-1]+map[j][i]);
            }
        }
    }
    
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }

    for (int i = 0; i < m; i++)
    {
        summax=max(summax, dp[i][n-1]);
    }
    
    

    out<<summax;

    inp.close();
    out.close();


    return 0;
}