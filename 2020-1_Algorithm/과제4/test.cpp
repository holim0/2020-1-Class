#include<iostream>
#include<cstdlib>
#include<fstream>
using namespace std;

int main(){

    ofstream out("mouse2.inp");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j< 5; j++)
        {
            int num=rand()%100;
            out<<num<<" ";
        }
        out<<"\n";
    }
    


    return 0;
}