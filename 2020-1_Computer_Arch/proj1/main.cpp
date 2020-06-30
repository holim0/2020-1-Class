#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;
ifstream openfile;

int missTime=0; 
int WriteTime=0;

struct data
{
    int valid=0;
    int dirty=0;
    int tag=-10;
};

struct data2{
    int valid[2]={0,};
    int LRU=0;
    int dirty[2]={0,};
    int tag[2]={-10, -10};
};

struct data cache0[1024];
struct data2 cache1[512];

void type0(){


     while(!openfile.eof()){
            string val;
            getline(openfile, val);
            string num;
            if(val[3]=='x'){
                for(int i=4; i<=11; i++){
                    num+=val[i];
                }
            }else{
                for(int i=2; i<=9; i++){
                    num+=val[i];
                }
            }
            unsigned int newNum;
            stringstream convert(num);
            convert>>hex>>newNum;
            int tag=newNum>>14;
            int index=(newNum<<18)>>22;
            int offset=(newNum<<28)>>30;
            if(val[0]=='L'){
                //cout<<"L: "<<tag<<" "<<index<<" "<<offset<<endl;
                if(cache0[index].valid==0){
                    missTime++;
                    cache0[index].valid=1;
                    cache0[index].tag=tag;
                }else if(cache0[index].valid==1 && cache0[index].tag!=tag){
                    missTime++;
                    cache0[index].tag=tag;
                }else if(cache0[index].valid==1 && cache0[index].tag==tag){
                    continue;
                }

            }else if(val[0]=='S'){
                //cout<<"S: "<<tag<<" "<<index<<" "<<offset<<endl;
                if(cache0[index].valid==0){
                    missTime++;
                    WriteTime++;
                }else if(cache0[index].valid==1 && cache0[index].tag!=tag){
                    missTime++; WriteTime++;
                }else if(cache0[index].valid==1 && cache0[index].tag==tag){
                    WriteTime++;
                }

            }
            

        }

    cout<<missTime<<" "<<WriteTime<<endl;

}



void type1(){

    int cnt=0;
    while(!openfile.eof()){
            string val;
            getline(openfile, val);
            string num;
            
            if(val[3]=='x'){
                for(int i=4; i<=11; i++){
                    num+=val[i];
                }
            }else{
                for(int i=2; i<=9; i++){
                    num+=val[i];
                }
            } 
            unsigned int newNum;
            stringstream convert(num);
            convert>>hex>>newNum;
            int tag=newNum>>15;
            int offsetidx=(newNum<<17)>>23;
            int offset=(newNum<<26)>>29;
            
            
            
            if(val[0]=='L'){
                //cout<<"L: "<<tag<<" "<<offsetidx<<" "<<offset<<" ";
                //cout<<cache1[offsetidx].valid[0]<<" "<<cache1[offsetidx].tag[0]<<endl;
                if(cache1[offsetidx].LRU==0 && cache1[offsetidx].valid[0]==0){ /// 둘 다 빈 경우.
                    //cout<<"miss"<<endl;
                    //cout<<1<<endl;
                    missTime++;
                    cache1[offsetidx].valid[0]=1;
                    cache1[offsetidx].tag[0]=tag;
                    cache1[offsetidx].LRU=1;

                }else if(cache1[offsetidx].LRU==1 && cache1[offsetidx].valid[1]==0 && cache1[offsetidx].tag[0]!=tag){
                       missTime++; 
                       //cout<<"miss"<<endl;
                       //cout<<2<<endl;
                       //cout<<cnt<<": "<<missTime<<endl; 
                       //cnt++;
                       cache1[offsetidx].LRU=0;
                       cache1[offsetidx].valid[1]=1;
                       cache1[offsetidx].tag[1]=tag;
                       // 첫번째 있고 두 번째 빈 경우

                }else if(cache1[offsetidx].LRU==1 && cache1[offsetidx].valid[1]==1&&cache1[offsetidx].tag[1]!=tag &&cache1[offsetidx].tag[0]!=tag){
                    missTime++;
                    //cout<<"miss"<<endl;
                    if(cache1[offsetidx].dirty[1]==1){
                        WriteTime++;
                        //cout<<"Write-back"<<endl;
                        cache1[offsetidx].dirty[1]=0;
                    }
                    // cout<<3<<endl;
                    // cout<<cnt<<": "<<missTime<<endl; 
                    // cnt++;
                    cache1[offsetidx].LRU=0;
                    cache1[offsetidx].tag[1]=tag;
                    // 두번째 가르키는데 존재하고 태그가 다른 경우.
                }else if(cache1[offsetidx].LRU==0 &&cache1[offsetidx].tag[0]!=tag &&cache1[offsetidx].tag[1]!=tag ){
                    missTime++;
                    //cout<<"miss"<<endl;
                    if(cache1[offsetidx].dirty[0]==1){
                        WriteTime++;
                        //cout<<"Write-back"<<endl;
                        cache1[offsetidx].dirty[0]=0;
                    }
                    // cout<<4<<endl;
                    // cout<<cnt<<": "<<missTime<<endl; 
                    // cnt++;
                    cache1[offsetidx].LRU=1;
                    cache1[offsetidx].tag[0]=tag;
                    //첫번째 가르키는데 존재하고 태그가 다른 경우.
                }
                else if((cache1[offsetidx].valid[0]==1 && cache1[offsetidx].tag[0]==tag) || (cache1[offsetidx].valid[1]==1 && cache1[offsetidx].tag[1]==tag)){
                    //cout<<"inside hit"<<endl;
                    //cout<<"hit"<<endl;
                    if(cache1[offsetidx].valid[0]==1 && cache1[offsetidx].tag[0]==tag){
                        if(cache1[offsetidx].LRU==0){
                            cache1[offsetidx].LRU=1;
                        }

                     }else if(cache1[offsetidx].valid[1]==1 && cache1[offsetidx].tag[1]==tag){
                        if(cache1[offsetidx].LRU==1){
                            cache1[offsetidx].LRU=0;
                        }
                     }
                    continue;       // set 안에 있는경우. hit.
                }



            }else if(val[0]=='S'){
                //cout<<"S: "<<tag<<" "<<offsetidx<<" "<<offset<<" ";
                
                if(cache1[offsetidx].LRU==0 && cache1[offsetidx].valid[0]==0){  // 아무것도 없을때
                    missTime++;
                    //cout<<"miss"<<endl;
                    cache1[offsetidx].valid[0]=1;
                    cache1[offsetidx].tag[0]=tag;
                    cache1[offsetidx].LRU=1;
                    cache1[offsetidx].dirty[0]=1;

                }else if(cache1[offsetidx].LRU==1 &&cache1[offsetidx].valid[1]==0 &&cache1[offsetidx].tag[0]!=tag){
                    missTime++;
                    //cout<<"miss"<<endl;
                    cache1[offsetidx].valid[1]=1;
                    cache1[offsetidx].tag[1]=tag;
                    cache1[offsetidx].LRU=0;
                    cache1[offsetidx].dirty[1]=1;
                    //첫번째꺼랑 다르고 두번째꺼 비워져 있을때

                }else if(cache1[offsetidx].LRU==0 && cache1[offsetidx].valid[0]==1 && cache1[offsetidx].tag[0]!=tag &&cache1[offsetidx].tag[1]!=tag){
                    missTime++;
                    //cout<<"miss"<<endl;
                    if(cache1[offsetidx].dirty[0]==1){
                        //cout<<"Write-back"<<endl;
                        WriteTime++;
                    }else{
                        cache1[offsetidx].dirty[0]=1;
                    }
                    
                    cache1[offsetidx].tag[0]=tag;
                    cache1[offsetidx].LRU=1;

                    
                    //첫번째 가르키고 값이 다를떄
                }else if(cache1[offsetidx].LRU==1 && cache1[offsetidx].valid[1]==1 &&cache1[offsetidx].tag[1]!=tag &&cache1[offsetidx].tag[0]!=tag){
                    missTime++;
                    //cout<<"miss"<<endl;
                    if(cache1[offsetidx].dirty[1]==1){
                        WriteTime++;
                        //cout<<"Write-back"<<endl;
                    }else{
                        cache1[offsetidx].dirty[1]=1;
                    }

                    
                    cache1[offsetidx].tag[1]=tag;
                    cache1[offsetidx].LRU=0;

                
                    //두번째 가르키고 값이 다를때 

                }else if((cache1[offsetidx].valid[0]==1 && cache1[offsetidx].tag[0]==tag) || (cache1[offsetidx].valid[1]==1 && cache1[offsetidx].tag[1]==tag)){
                    //cout<<"hit"<<endl;
                     if(cache1[offsetidx].valid[0]==1 && cache1[offsetidx].tag[0]==tag){
                        cache1[offsetidx].dirty[0]=1;
                        if(cache1[offsetidx].LRU==0){
                            cache1[offsetidx].LRU=1;
                        }

                     }else if(cache1[offsetidx].valid[1]==1 && cache1[offsetidx].tag[1]==tag){
                        cache1[offsetidx].dirty[1]=1;
                        if(cache1[offsetidx].LRU==1){
                            cache1[offsetidx].LRU=0;
                        }
                     }

                    
                    continue;  
                    
                    ///hit 인 경우
                
                }


            }


        }

        cout<<missTime<<" "<<WriteTime<<endl;

}

int main(int argc, char *argv[]){
    string cacheType, filename;
   
       //cin>>cacheType>>filename;

	cacheType=argv[1];
	filename=argv[2];
        string s="./trace"+filename+".txt";
        
        openfile.open(s.c_str());
        
        if(cacheType=="0"){
            type0();
        }
        else{
            type1();
        }
        

    return 0;
}
