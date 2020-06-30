#include<iostream>
#include<fstream>
#include<cmath>
#include<algorithm>
#include<climits>
#include<vector>
using namespace std;
int val;
unsigned long long minval=LLONG_MAX;
void getmin(int cnt, unsigned long long num){
    if(val==cnt) {
        minval=min(minval, num);
        return;
    }
    
    if((num-1)/3!=0 && (num-1)%3==0 && (num-1)/3!=1){
        getmin(cnt+1, num*2);
        getmin(cnt+1, (num-1)/3);
        
    }
    else{
        getmin(cnt+1, num*2);
    }
    

        
}

int main(int argc, const char* argv[]){

    ifstream inp; inp.open("3n1.inp");
    ofstream out("3n1.out");

    inp>>val;

    unsigned long long maxval=pow(2, val);
    
    getmin(0, 1);

    // for (int i = 0; i < val; i++)
    // {
        
    // }
    
    //cout<<minval<<" "<<maxval<<endl;

    out<<minval;
    out<<" ";
    out<<maxval;
    inp.close();
    out.close();
    return 0;
}