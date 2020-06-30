#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

int dp[3010]={};
int num[3010]={};
int numsize;



int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int max=-12345678;
    ifstream readFile("monosequence.inp");
    ofstream OutFile("monosequence.out");
    int idx=0;
    
        while(!readFile.eof()){
            
            readFile>>num[idx];
            idx++;
            
        }
    
    numsize=num[0];
    
    for(int i=1; i<=numsize; i++){
        int min=0; 
        for(int j=0; j<i; j++){
            if(num[i]>=num[j]){
                if(min < dp[j]){
                    min=dp[j];
                }
            }
        }

        dp[i]=min+1;
        if (max < dp[i])
            max = dp[i];

    }

    

    OutFile<<max;

    readFile.close();
    OutFile.close();

    return 0;
}