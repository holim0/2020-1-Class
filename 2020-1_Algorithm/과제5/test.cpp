#include<iostream>
#include<fstream>
using namespace std;


int main(){

    ofstream out("result.inp");

    for(int i=1; i<=3000; i++){
        out<<200<<" ";
    }

    return 0;

}