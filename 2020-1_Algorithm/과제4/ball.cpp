#include<iostream>
#include<fstream>
using namespace std;

int pipenum;
int labelnum;
int pipe[200010];
int result[100005];

int main(int argc, const char* argv[]){

    ifstream input("ball2.inp");
    ofstream out("ball.out");
    
    int i=0;
    while(!input.eof()){
        input>>pipe[i];
        i++;
    }

    pipenum=pipe[0];
    labelnum=pipe[pipenum+1];
    
    for (int i = 2; i <= pipenum; i++)
    {
        pipe[i]+=pipe[i-1];
    }
    int idx=0;
    int left, right, mid;
   

    for (int i = pipenum+2; i < pipenum+2+labelnum; i++)
    {
         left=1;
         right=pipenum;
        while(1){
            mid=(left+right)/2;
            if(pipe[mid]==pipe[i]){
                //cout<<mid<<endl;
                out<<mid<<"\n";
                
                break;
            }else if(mid==1 && left==1 && pipe[i]<pipe[mid]){
                //cout<<left<<endl;
                out<<left<<"\n";
                break;
            }else if(pipe[i]<pipe[mid] && pipe[i]<pipe[mid-1]){
                right=mid-1;
                if(right<=left){
                    //cout<<left<<endl;
                    out<<left<<"\n";
                    break;
                }
            }else if(pipe[i]<pipe[mid] && pipe[i]>pipe[mid-1]){
                //cout<<mid<<endl;
                out<<mid<<"\n";
                break;
            }else if(pipe[i]<pipe[mid] && pipe[i]==pipe[mid-1]){
                //cout<<mid-1<<endl;
                out<<mid-1<<"\n";
                break;
            }
            else if(pipe[i]>pipe[mid]){
                left=mid+1;
                if(right<=left){
                    //cout<<left<<endl;
                    out<<left<<"\n";
                    break;
                }
            }
        }
        
    }
    
    // for (int i = 0; i < idx; i++)
    // {
    //     cout<<result[i]<<endl;
    // }
    
    

    return 0;
}