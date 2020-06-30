#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
string arr[205];
int cnt[100][100][100]={0,};
int idx=0;
int solmax=0;
void sol(){

    for (int i = 1; i < idx-1; i++)
    {
        string val= arr[i];
        for(int j=0; j<val.size()-2; j++){
            int a=(val[j]-'0');
            int b=(val[j+1]-'0');
            int c=(val[j+2]-'0');
            cnt[a][b][c]++;
            if(solmax<cnt[a][b][c]) solmax=cnt[a][b][c];
        }
        //memset(cnt, 0, sizeof(cnt));
    }





}
int main(){

    ifstream f("xplanet.inp");
    ofstream w("xplanet.out");
    string s;
    
    while(f){
        getline(f, s);
        arr[idx]=s;
        idx++;
    }
    
    sol();
    
    w<<solmax;

    f.close();
    w.close();

    return 0;

}