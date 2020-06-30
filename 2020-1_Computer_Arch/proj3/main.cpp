#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<cstring>
#include<bitset>
#include<cmath>
#define MAX 66000
using namespace std;
int arr[20000];
unsigned int regi[34]={0,};
unsigned int instad[MAX]; 
unsigned int datamem[MAX];
unsigned int HI;
unsigned int LO;



bool checkrange(int n){        // 레지스터 메모리 범위 체크

    if(n>=0x10000000 && n<=0x10010000)return true;
    
    else{
        return false;
    }
    
}

bool checkinst(int n){          // 명령어 메모리 범위 체크
     if(n>=0x00000000 && n<=0x00010000) return true;
     else{
         return false;
     }
}

int main(){
    FILE * fout;
    char filename[200];
    int i=0; int cnt;//  명령어 개수
    int ho; int valinst;
    while(1){
        bool flag=false;
        bool sysflag=false;
        string str;
        printf("mips-sim>");
        cin>>str;
        if (str=="exit"){
            return 0;	
        }
        else if(str=="registers"){
            for (int i = 0; i < 32; i++)
            {
                printf("$%d: 0x%08x\n",i, regi[i]);
            }
            printf("HI: 0x%08x\n", HI);
            printf("LO: 0x%08x\n", LO);
            printf("PC: 0x%08x\n", regi[32]);

        }
        else if(str=="read"){
            scanf("%s",filename); 
            fout=fopen(filename, "rb");
            int ch; i=0;
            while((ch=fgetc(fout))!=EOF){
                arr[i]=ch;
                i++;
            }
        }    
        else if(str=="loadinst"){
            scanf("%s",filename); 
            fout=fopen(filename, "rb");
            int ch; i=0;
            while((ch=fgetc(fout))!=EOF){
                arr[i]=ch;
                i++;
            }
            ho= i/4; // 실제 명령어 개수.
            valinst=0;
            for (int i = 0; i < MAX; i++)
            {
                instad[i]=0xff;
            }
            for (int i = 0; i < ho; i++)
            {
                instad[i]=0+4*i;
            }
            memset(regi, 0, sizeof(regi));
        }else if(str=="run"){
            cin>>cnt; // 실행하고 싶은 명령어 개수

        }else if(str=="loaddata"){
            for (int i = 0; i < MAX; i++)
            {
                datamem[i]=0xff;
            }
            scanf("%s", filename);
            fout=fopen(filename, "rb");
            int ch; int idx2=0;
            while((ch=fgetc(fout))!=EOF){
            datamem[idx2]=ch;
            idx2++;
            }
        }
        if(str=="read" || str=="run"){ 
            string s1="";
            int idx=0;
            //int cur=0; // 현재위치 
            for (int j = 0; j < i; j++)
            {
                //printf("cur: %d\n", j);
                s1+=bitset<8>(arr[j]).to_string();
                if(s1.size()==32){
                    unsigned int address=0;
                    for(int g=31; g>=0; g--){
                        if(s1[g]=='1'){
                            address+=pow(2, 31-g);
                        }
                    }

                    string op=""; string rs=""; string rt=""; string rd=""; string shf=""; string funt="";
                    for (int i = 0; i < s1.size(); i++)
                    {
                        if(i<6){
                            op+=s1[i];
                        }else
                        if(i>=6 && i<11){ 
                            rs+=s1[i];
                        }else if(i>=11 &&i<16){
                            rt+=s1[i];
                        }else if(i>=16 && i<21){
                            rd+=s1[i];
                        }else if(i>=21 && i<26){
                            shf+=s1[i];
                        }else{
                            funt+=s1[i];
                        }
                    }
                    if(op=="000000" && (funt=="100000"|| funt=="100001")){ //add and addu
                        if(str=="read"){printf("inst %d: %08x ",idx, address);} 
                        int rs1=0; 
                        int rt1=0; int rd1=0;

                        for (int i = 4; i >= 0; i--)
                        {   
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                                
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                                
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                                
                            }
                        }
                        if(funt=="100000"){       //add
                            if(str=="read"){printf("add $%d, $%d, $%d\n", rd1, rs1, rt1);}
                            else{
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rd1]=(int)regi[rs1]+(int)regi[rt1];

                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                                
                            }
                        }else{  //addu
                            if(str=="read"){printf("addu $%d, $%d, $%d\n", rd1, rs1, rt1);}
                            else{
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rd1]=regi[rs1]+regi[rt1];


                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }
                        idx++;
                        
                    }else if(op=="100011"){ /////////////////// lw
                       if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        string offset=rd+shf+funt;
                        int rs1=0; int rt1=0; int offset2=0;

                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                        }
                        if(offset[0]=='1'){
                            for (int i = offset.size()-1; i >=0; i--)
                            {
                                if(offset[i]=='1'){
                                    offset2+=pow(2, offset.size()-1-i);
                                }
                            }
                            offset2-=pow(2, offset.size());

                        }else{
                            for (int i = offset.size()-1; i >=0; i--)
                            {
                                if(offset[i]=='1'){
                                    offset2+=pow(2, offset.size()-1-i);
                                }
                            }
                        if(str=="read"){printf("lw $%d, %d($%d)\n", rt1, offset2, rs1);}
                        else{
                            if(!checkrange(offset2+regi[rs1]) || (offset2+regi[rs1])%4!=0){
                                if(!checkrange(offset2+regi[rs1]) && (offset2+regi[rs1])%4==0){
                                    printf("Memory address out of range: 0x%08x\n",offset2+regi[rs1]);
                                }else if((offset2+regi[rs1])%4!=0 && checkrange(offset2+regi[rs1])){
                                    printf("Memory address alignment error: 0x%08x\n",offset2+regi[rs1]); 
                                }else if(!checkrange(offset2+regi[rs1]) && (offset2+regi[rs1])%4!=0){
                                    printf("Memory address out of range: 0x%08x\n",offset2+regi[rs1]);
                                }
                                flag=true;
                                valinst++;
                                regi[32]+=4;
                                break;
                            }else if(!checkinst(regi[32])){
                                flag=true;
                                printf("Memory address out of range: 0x%08x\n", regi[32]);
                                valinst++; 
                                regi[32]+=4;
                                break;
                            }
                                int dataval=0;
                                int j=0;
                                for(int i=offset2+regi[rs1]-0x10000000; i<offset2+regi[rs1]-0x10000000+4; i++){
                                    // cout<<i<<endl;
                                    dataval+=datamem[i]<<(24-8*j);
                                    j++;
                                }
                                // printf("lw address: %08x  val: %08x\n", address, dataval);
                                regi[rt1]=dataval;
                                regi[32]+=4;
                                valinst++;
                                int idx=regi[32]/4;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }    
                            }
                        }
                        idx++;
                    }else if(op=="001000" || op=="001001"){ ////////////// addi, addiu
                        if(str=="read") { printf("inst %d: %08x ",idx, address); }
                        string val=rd+shf+funt;
                        int rs1=0; int rt1=0; int imm=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                        }
                        if(val[0]=='1'){
                            for (int i = val.size()-1; i >= 0; i--)
                            {
                                if(val[i]=='1'){
                                    imm+=pow(2, val.size()-1-i);
                                }
                            }
                            imm= imm-pow(2, val.size());

                        }else{
                            for (int i = val.size()-1; i>=0; i--){
                                if(val[i]=='1'){
                                    imm+=pow(2, val.size()-1-i);
                                }
                            }
                        }
                        if(op=="001000"){  //addi
                            if(str=="read"){printf("addi $%d, $%d, %d\n", rt1, rs1, imm);}
                            else{
                                // printf("addi address: %08x ", address); 
                                // printf("regi%d + imm = %08x + %08x =", rs1, regi[rs1], imm);
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rt1]= (int)regi[rs1]+(int)imm;
                                regi[32]+=4;
                                valinst++;
                                int idx=regi[32]/4;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }else{
                            if(str=="read"){ printf("addiu $%d, $%d, %d\n", rt1, rs1, imm); }
                            else{
                                
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rt1]= (unsigned int)regi[rs1]+(unsigned int)imm;
                                // printf(" %08x\n", regi[rt1]);
                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }
                        idx++;

                    }else if(op=="000101"){                 ///bne
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        string offset=rd+shf+funt;
                        int rs1=0; int rt1=0; int offset2=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                        }
                        if(offset[0]=='1'){
                            for (int i = offset.size()-1; i>=0; i--)
                            {
                                if(offset[i]=='1'){
                                    offset2+=pow(2, offset.size()-1-i);
                                }
                            }
                            offset2-= pow(2, offset.size());
                            
                        }else if(offset[0]=='0'){
                            for (int i = offset.size()-1; i>=0; i--){
                                if(offset[i]=='1'){
                                    offset2+=pow(2, offset.size()-1-i);
                                }
                            }
                        }

                        if(str=="read"){printf("bne $%d, $%d, %d\n", rs1, rt1, offset2);}
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }

                            valinst++;
                            regi[32]+=4;
                            if(valinst==cnt) break;
                            if(regi[rs1]!=regi[rt1]){
                                regi[32]+=offset2*4;
                                j=regi[32]-1;
                                s1="";
                                continue;
                            }    

                        }
                        idx++;
                    }else if(op=="000000"&& funt=="000000"){  ////sll
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rt1=0; int rd1=0; int sa=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                            if(shf[i]=='1'){
                                sa+=pow(2, 4-i);
                            }
                        }
                        if(str=="read"){printf("sll $%d, $%d, %d\n", rd1, rt1, sa);}
                        else{

                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            regi[rd1]=regi[rt1]<<sa;
                            regi[32]+=4;
                            int idx=regi[32]/4;
                            valinst++;
                            if(valinst==cnt) break;
                            if(instad[idx]!=regi[32]){
                                valinst++;
                                break;
                            }
                        }
                        idx++;
                    }else if(op=="000000" && (funt=="001000"|| funt=="001001")){    //jr and jalr
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rd1=0;
                        for (int i = 4; i >=0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                        }
                        if(funt=="001000"){
                            if(str=="read"){printf("jr $%d\n", rs1);}
                            else{
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                valinst++;
                                if(valinst==cnt) break;
                               regi[32]=regi[rs1];
                               j=regi[32]-1;
                               s1="";
                               continue;
                            }
                        }else{
                           if(str=="read"){ printf("jalr $%d\n", rs1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                               valinst++;
                               if(valinst==cnt)break;
                               regi[rd1]=regi[32];
                               regi[32]=regi[rs1];
                               j=regi[32]-1;
                               s1="";
                               continue;
                           }
                        }
                        idx++;

                    }else if(op=="101001"){ // sh
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rt1=0; int offset2=0;
                        string offset=rd+shf+funt;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                        }
                        if(offset[0]=='1'){
                            for (int i = offset.size()-1; i>=0; i--)
                            {
                                if(offset[i]=='1'){
                                    offset2+=pow(2, offset.size()-1-i);
                                }
                            }
                            offset2-= pow(2, offset.size());
                            
                        }else if(offset[0]=='0'){
                            for (int i = offset.size()-1; i>=0; i--){
                                if(offset[i]=='1'){
                                    offset2+=pow(2, offset.size()-1-i);
                                }
                            }
                        }
                        if(str=="read"){printf("sh $%d, %d($%d)\n", rt1, offset2, rs1);}
                        else{
                            if(!checkrange(offset2+regi[rs1]) ||(offset2+regi[rs1])%2!=0){
                                if(!checkrange(offset2+regi[rs1]) &&(offset2+regi[rs1])%2==0){
                                    printf("Memory address out of range: %0x08x\n",offset2+regi[rs1]);
                                }else if(checkrange(offset2+regi[rs1]) && (offset2+regi[rs1])%2!=0){
                                    printf("Memory address alignment error: 0x%08x\n",offset2+regi[rs1]);
                                }else if(!checkrange(offset2+regi[rs1]) && (offset2+regi[rs1])%2!=0){
                                    printf("Memory address out of range: %0x08x\n",offset2+regi[rs1]);
                                }
                                    flag=true;
                                    valinst++;
                                    regi[32]+=4;
                                    break;
                            }else if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }

                            datamem[offset2+regi[rs1]-0x10000000]=(unsigned int)regi[rt1]>>16;
                            regi[32]+=4;
                            int idx=regi[32]/4;
                            valinst++;
                            if(valinst==cnt) break;
                            if(instad[idx]!=regi[32]){
                                valinst++;
                                break;
                            }

                        }
                        idx++;

                    }else if(op=="001111"){  // lui
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        string imm=rd+shf+funt;
                        int rt1=0; int imm2=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                        }
                        // if(imm[0]=='1'){
                        //     for (int i = imm.size()-1; i >=0; i--)
                        //     {
                        //         if(imm[i]=='1'){
                        //             imm2+=pow(2, imm.size()-1-i);
                        //         }
                        //     }
                        //     imm2-= pow(2, imm.size());
                            
                        // }else{
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                        
                        if(str=="read"){printf("lui $%d, %08x\n", rt1, imm2);}
                        else{

                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            
                            regi[rt1]=imm2<<16;
                            // printf("lui address: %08x", address); printf(" register: %d ", rt1); printf("regival: %08x\n", regi[rt1]);
                            regi[32]+=4;
                            int idx=regi[32]/4;
                            valinst++;
                            if(valinst==cnt) break;
                            if(instad[idx]!=regi[32]){
                                valinst++;
                                break;
                            }
                        }
                        idx++;
                    }else if(op=="000011"){  //jal
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        string target=rs+rt+rd+shf+funt; int target2=0;
                        if(target[0]=='1'){
                            for (int i = target.size()-1; i>=0; i--)
                            {   if(target[i]=='1'){
                                    target2+=pow(2, target.size()-1-i);
                                }
                            }
                            target2-=pow(2, target.size());
                            
                        }else{
                            for (int i = target.size()-1; i>=0; i--)
                            {   if(target[i]=='1'){
                                    target2+=pow(2, target.size()-1-i);
                                }
                            }
                        }
                       if(str=="read"){ printf("jal %d\n", target2<<2);}
                       else{

                           if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            valinst++;
                            if(valinst==cnt) break;
                            regi[31]=regi[32]+4; //
                            regi[32]=target2<<2;
                            j=regi[32]-1;
                            //printf("jal address: %08x", address); printf(" register[31]: %d ",regi[31] ); printf("pc: %d\n", regi[32]);
                            s1="";
                            continue;
                       }
                        idx++;
                    }else if(op=="000100"){ //beq
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rt1=0; int offset2=0;
                        string offset=rd+shf+funt;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                        }
                        if(offset[0]=='1'){
                            for (int i = offset.size()-1; i>=0; i--)
                            {   
                                if(offset[i]=='1'){
                                    offset2+=pow(2, offset.size()-1-i);
                                }
                            }
                            offset2-= pow(2, offset.size());
                            
                        }else{
                            for (int i = offset.size()-1; i>=0; i--)
                            {
                                if(offset[i]=='1'){
                                    offset2+=pow(2, offset.size()-1-i);
                                }
                            }
                        }
                        if(str=="read"){printf("beq $%d, $%d, %d\n", rs1, rt1, offset2);}
                        else{

                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            valinst++;
                            regi[32]+=4;
                            if(valinst==cnt) break;
                            if(regi[rs1]==regi[rt1]){
                                regi[32]+=offset2*4;
                                j=regi[32]-1;
                                s1="";
                                continue;
                            }    

                        }
                        idx++;
                    }else if(op=="101011"){  //sw
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rt1=0; int offset2=0;
                        string imm=rd+shf+funt;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                        }
                        if(imm[0]=='1'){
                            for (int i = imm.size()-1; i>=0; i--)
                            {
                                if(imm[i]=='1'){
                                    offset2+=pow(2, imm.size()-1-i);
                                }
                            }
                            offset2-=pow(2, imm.size());
                            
                        }else{
                            for (int i = imm.size()-1; i>=0; i--)
                            {
                                if(imm[i]=='1'){
                                    offset2+=pow(2, imm.size()-1-i);
                                }
                            }
                        }
                       if(str=="read"){ printf("sw $%d, %d($%d)\n", rt1, offset2, rs1);}
                       else{
                           if(!checkrange(offset2+regi[rs1]) || (offset2+regi[rs1])%4!=0){
                               if(!checkrange(offset2+regi[rs1]) && (offset2+regi[rs1])%4==0){
                                    printf("Memory address out of range: 0x%08x\n",offset2+regi[rs1]);
                                }else if((offset2+regi[rs1])%4!=0 && checkrange(offset2+regi[rs1])==true){
                                    printf("Memory address alignment error: 0x%08x\n",offset2+regi[rs1]); 
                                }else if(!checkrange(offset2+regi[rs1]) && (offset2+regi[rs1])%4!=0){
                                    printf("Memory address out of range: 0x%08x\n",offset2+regi[rs1]);
                                }
                               flag=true;
                               regi[32]+=4;
                               valinst++;
                                break;
                            }else if(!checkinst(regi[32])){
                                flag=true;
                                printf("Memory address out of range: 0x%08x\n", regi[32]);
                                valinst++; 
                                regi[32]+=4;
                                break;
                            }
                            // printf("sw address: %08x ", address);
                            // printf("offset : %d, rs: %d rt: %d ", offset2, rs1, rt1);
                            // printf("sw val: %08x\n", regi[rt1]);

                           datamem[offset2+regi[rs1]-0x10000000]=(unsigned int)regi[rt1]>>24;
                           datamem[offset2+1+regi[rs1]-0x10000000]=((unsigned int)regi[rt1]<<8)>>24;
                           datamem[offset2+2+regi[rs1]-0x10000000]=((unsigned int)regi[rt1]<<16)>>24;
                           datamem[offset2+3+regi[rs1]-0x10000000]=((unsigned int)regi[rt1]<<24)>>24;
                        //    for (int i = offset2+regi[rs1]-0x10000000; i < offset2+regi[rs1]-0x10000000+4; i++)
                        //    {
                        //        printf("datamem[%d]: %08x ", i, datamem[i]);
                        //    }
                        //    printf("\n");
                            regi[32]+=4;
                            int idx=regi[32]/4;
                            valinst++;
                            if(valinst==cnt) break;
                            if(instad[idx]!=regi[32]){
                                valinst++;
                                break;
                            }

                       }
                        idx++;
                    }else if(op=="000000" && shf=="00000" &&(funt=="100101" || funt=="100111")){  //or nor
                        if(str=="read") {printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rt1=0; int rd1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                        }
                        if(funt=="100101"){      //or
                           if(str=="read") {printf("or $%d, $%d, $%d\n", rd1, rs1, rt1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                               regi[rd1]=regi[rs1]|regi[rt1];
                            //    printf("or address: %08x ", address);
                            //    printf("regi%d | regi%d = %08x | %08x = %08x\n", rs1, rt1, regi[rs1], regi[rt1], regi[rd1]);
                               regi[32]+=4;
                               int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                           }
                        }
                        else{       //nor
                           if(str=="read") {printf("nor $%d, $%d, $%d\n", rd1, rs1, rt1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                               regi[rd1]=~(regi[rs1]|regi[rt1]);
                               regi[32]+=4;
                               int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                           }
                        }
                        idx++;
                    }else if(op=="000000" && shf=="00000" && funt=="100100"){ //and
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rt1=0; int rd1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                        }
                        if(str=="read"){printf("and $%d, $%d, $%d\n", rd1, rs1, rt1);}
                        else{

                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            
                            regi[rd1]=regi[rs1]&regi[rt1];
                            regi[32]+=4;
                            int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                        }
                        idx++;
                    }else if(op=="000000" && (funt=="011010"|| funt=="011011")){ //div and divu
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rt1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                        }
                        
                        if(funt=="011010"){
                           if(str=="read"){ printf("div $%d, $%d\n",rs1, rt1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                               HI=(signed int)regi[rs1]%(signed int)regi[rt1];
                               LO=(signed int)regi[rs1]/(signed int)regi[rt1];
                               regi[32]+=4;
                               int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                           }
                        }else{
                           if(str=="read"){ printf("divu $%d, $%d\n",rs1, rt1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                               HI=(unsigned int)regi[rs1]%(unsigned int)regi[rt1];
                               LO=(unsigned int)regi[rs1]/(unsigned int)regi[rt1];
                               //printf("Hi lo: %08x %08x\n", HI, LO);
                               regi[32]+=4;
                               int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                           }
                        }
                        idx++;
                    }else if(op=="000000" &&(funt=="010000"|| funt=="010010")){ //mfhi, mflo
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rd1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                        }
                        if(funt=="010000"){
                           if(str=="read"){ printf("mfhi $%d\n",rd1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                               regi[rd1]=HI;
                               regi[32]+=4;
                               int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }

                           }
                        }else{
                           if(str=="read"){ printf("mflo $%d\n",rd1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                               regi[rd1]=LO;
                               regi[32]+=4;
                               int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                           }
                           
                        }
                        idx++;
                    }else if(op=="000000"&&(funt=="010001"||funt=="010011")){ //mthi, mtlo
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rs1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(funt=="010001"){
                           if(str=="read"){ printf("mthi $%d\n",rs1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                HI=regi[rs1];
                                regi[32]+=4;
                               int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                           }
                        }else{
                           if(str=="read"){ printf("mtlo $%d\n",rs1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                               LO=regi[rs1];
                               regi[32]+=4;
                               int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                           }
                        }
                        idx++;
                    }else if((op=="000000" && funt=="011000") ||(op=="000000" &&funt=="011001")){  //mult, multu
                       if(str=="read"){ printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rt1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                        }
                        if(funt=="011000"){
                           if(str=="read"){ printf("mult $%d, $%d\n",rs1, rt1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                               long long int val= (signed long long)(int)regi[rs1]*(signed long long)(int)regi[rt1];
                               HI=(unsigned long long)val>>32;
                               LO=((unsigned long long)val<<32)>>32;                            
                               regi[32]+=4;
                               int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }


                           }
                        }else{
                           if(str=="read"){ printf("multu $%d, $%d\n",rs1, rt1);}
                           else{
                               if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                               unsigned long long val= (unsigned long long)regi[rs1]*(unsigned long long)regi[rt1];
                               HI=(unsigned long long)val>>32;
                               LO=((unsigned long long)val<<32)>>32;                            
                               regi[32]+=4;
                               int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }

                           }
                        }
                        idx++;
                    }else if(op=="000000" && shf=="00000"&& funt=="000100"){ //sllv
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rt1=0; int rd1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                        }
                        if(str=="read"){printf("sllv $%d, $%d, $%d\n",rd1, rt1, rs1);}
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                            regi[rd1]=regi[rt1]<<regi[rs1];
                            regi[32]+=4;
                            int idx=regi[32]/4;
                            valinst++;
                            if(valinst==cnt) break;
                            if(instad[idx]!=regi[32]){
                                valinst++;
                                break;
                            }
                        }
                        idx++;
                    }else if(op=="000000" && shf=="00000"&& (funt=="101010"|| funt=="101011")){ //slt, sltu
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rs1=0; int rt1=0; int rd1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                        }
                        if(funt=="101010"){  //slt
                            if(str=="read"){printf("slt $%d, $%d, $%d\n",rd1, rs1, rt1);}
                            else{
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rd1]=(int)regi[rs1]<(int)regi[rt1];
                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }else{ //sltu
                            if(str=="read"){printf("sltu $%d, $%d, $%d\n",rd1, rs1, rt1);}
                            else{
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rd1]=regi[rs1]<regi[rt1];
                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }
                        idx++;
                    }else if(op=="000000" && rs=="00000" &&funt=="000011"){  // sra
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rd1=0; int shf1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                            if(shf[i]=='1'){
                                shf1+=pow(2, 4-i);
                            }
                        }
                        if(str=="read"){printf("sra $%d, $%d, $%d\n",rd1, rt1, shf1); }
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            regi[rd1]=(int)regi[rt1]>>shf1;
                            regi[32]+=4;
                            int idx=regi[32]/4;
                            valinst++;
                            if(valinst==cnt) break;
                            if(instad[idx]!=regi[32]){
                                valinst++;
                                break;
                            }
                        }
                        idx++;
                    }else if(op=="000000" && shf=="00000" &&funt=="000111"){ // srav
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rs1=0; int rd1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                        }
                         if(str=="read"){printf("srav $%d, $%d, $%d\n",rd1, rt1, rs1); }
                         else{
                             if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            regi[rd1]=(int)regi[rt1]>>regi[rs1];
                            regi[32]+=4;
                            int idx=regi[32]/4;
                            valinst++;
                            if(valinst==cnt) break;
                            if(instad[idx]!=regi[32]){
                                valinst++;
                                break;
                            }
                         }
                        idx++;
                    }else if(op=="000000" && funt=="000010"){ // srl
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rd1=0; int shf1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                            if(shf[i]=='1'){
                                shf1+=pow(2, 4-i);
                            }
                        }
                        if(str=="read"){printf("srl $%d, $%d, $%d\n",rd1, rt1, shf1);}
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            regi[rd1]=regi[rt1]>>shf1;
                            regi[32]+=4;
                            int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                        }
                        idx++;
                        
                    }else if(op=="000000" && funt=="000110" &&shf=="00000"){ // srlv
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rd1=0; int rs1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(str=="read"){printf("srlv $%d, $%d, $%d\n",rd1, rt1, rs1);}
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            regi[rd1]=regi[rt1]>>regi[rs1];
                            regi[32]+=4;
                            int idx=regi[32]/4;
                            valinst++;
                            if(valinst==cnt) break;
                            if(instad[idx]!=regi[32]){
                                valinst++;
                                break;
                            }
                        }
                        idx++;
                    }else if(op=="000000" && shf=="00000" && (funt=="100010" || funt=="100011")){ //sub, subu
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rd1=0; int rs1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(funt=="100010"){  //sub
                            if(str=="read"){printf("sub $%d, $%d, $%d\n",rd1, rs1, rt1); }
                            else{
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rd1]=(int)regi[rs1]-(int)regi[rt1];
                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
         
                        }else{   //subu
                            if(str=="read"){printf("subu $%d, $%d, $%d\n",rd1, rs1, rt1); }
                            else{
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rd1]=(unsigned int)regi[rs1]-(unsigned int)regi[rt1];
                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }
                        idx++;
                    }else if(op=="000000" && rd=="00000"&& rs=="00000"&& rt=="00000"&& shf  =="00000" &&funt=="001100"){ //syscall
                        if(str=="read"){printf("inst %d: %08x syscall\n", idx, address);}
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            valinst++;
                            regi[32]+=4;
                            if(valinst==cnt) break;
                            if(regi[2]==10){
                                printf("EXIT syscall\n");
                                sysflag=true;
                                break;
                            }else if(regi[2]==1){
                                printf("%d", regi[4]);

                            }else if(regi[2]==4){
                                int num=regi[4]-0x10000000;
                                //printf("syscall num: %08x\n", regi[4]);
                                while(1){
                                    int ch=datamem[num];
                                    if(ch==0) {break;}
                                    printf("%c", ch);
                                    num++;
                                }
                            }else{
				printf("Invalid syscall");
				exit(0);


                             }
                        }
                        idx++;
                    }else if(op=="000000" && shf=="00000" && funt=="100110"){ //xor
                        if(str=="read"){ printf("inst %d: %08x ",idx, address); }
                        int rt1=0; int rd1=0; int rs1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(str=="read"){printf("xor $%d, $%d, $%d\n",rd1, rs1, rt1);}
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            regi[rd1]=regi[rs1]^regi[rt1];
                            regi[32]+=4;
                            int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                        } 
                        idx++;
                    }else if(op=="001100"){                                   //andi
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rs1=0; int imm2=0;
                        string imm=rd+shf+funt;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        // if(imm[0]=='1'){
                        //     for (int i = imm.size()-1; i >=0; i--)
                        //     {
                        //         if(imm[i]=='1'){
                        //             imm2+=pow(2, imm.size()-1-i);
                        //         }
                        //     }
                        //     imm2-= pow(2, imm.size());
                            
                        // }else{
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                        //}
                        if(str=="read"){printf("andi $%d, $%d, %d\n",rt1, rs1, imm2); }
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            regi[rt1]= regi[rs1]&imm2;
                            regi[32]+=4;
                            int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                        }
                        idx++;
                    }else if(op=="100000" || op=="100100"){             /////////// lb, lbu
                        if(str=="read"){ printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rs1=0; int imm2=0;
                        string imm=rd+shf+funt;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(imm[0]=='1'){
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                            imm2-= pow(2, imm.size());
                            
                        }else{
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                        }
                        if(op=="100000"){
                            if(str=="read"){ printf("lb $%d, %d($%d)\n",rt1,imm2, rs1);}
                            else{
                                if(!checkrange(imm2+regi[rs1])){
                                    flag=true;
                                    regi[32]+=4;
                                    printf("Memory address out of range: 0x%08x\n",imm2+regi[rs1]);
                                    valinst++;
                                    break;
                                }else if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rt1]=((signed int)datamem[imm2+regi[rs1]-0x10000000]<<24)>>24;
                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }else{
                           if(str=="read"){ printf("lbu $%d, %d($%d)\n",rt1,imm2, rs1);}
                           else{
                               if(!checkrange(imm2+regi[rs1])){
                                   flag=true;
                                   printf("Memory address out of range: 0x%08x\n",imm2+regi[rs1]);
                                   valinst++;
                                    break;
                                }else if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }

                                regi[rt1]=datamem[imm2+regi[rs1]-0x10000000];

                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                           }
                        }
                        idx++;
                    }else if(op=="100001" || op=="100101"){///////////   //////////////// lh, lhu
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rs1=0; int imm2=0;
                        string imm=rd+shf+funt;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(imm[0]=='1'){
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                            imm2-= pow(2, imm.size());
                            
                        }else{
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                        }
                        if(op=="100001"){
                            if(str=="read"){printf("lh $%d, %d($%d)\n",rt1,imm2, rs1);}
                            else{
                                if(!checkrange(imm2+regi[rs1]) || (imm2+regi[rs1])%2!=0){
                                    flag=true;
                                    if(!checkrange(imm2+regi[rs1]) && (imm2+regi[rs1])%2==0){
                                        printf("Memory address out of range: 0x%08x\n",imm2+regi[rs1]);
                                    }else if(checkrange(imm2+regi[rs1]) && (imm2+regi[rs1])%2!=0){
                                        printf("Memory address alignment error: 0x%08x\n",imm2+regi[rs1]);
                                    }else if(!checkrange(imm2+regi[rs1]) && (imm2+regi[rs1])%2!=0){
                                        printf("Memory address out of range: 0x%08x\n",imm2+regi[rs1]);
                                    }
                                    regi[32]+=4;
                                    valinst++;
                                    break;
                                }else if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                int tmp=0;
                                tmp+=datamem[imm2+regi[rs1]-0x10000000]<<8;
                                tmp+=datamem[imm2+regi[rs1]+1-0x10000000];
                                tmp=((signed int)tmp<<16)>>16;
                                // printf("lh: %08x\n", tmp);
                                regi[rt1]=tmp;
                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }else{
                            if(str=="read"){printf("lhu $%d, %d($%d)\n",rt1,imm2, rs1);}
                            else{    
                                if(!checkrange(imm2+regi[rs1]) || (imm2+regi[rs1])%2!=0){
                                    if(!checkrange(imm2+regi[rs1]) && (imm2+regi[rs1])%2==0){
                                        printf("Memory address out of range: 0x%08x\n",imm2+regi[rs1]);
                                    }else if(checkrange(imm2+regi[rs1]) && (imm2+regi[rs1])%2!=0){
                                        printf("Memory address alignment error: 0x%08x\n",imm2+regi[rs1]);
                                    }else if(!checkrange(imm2+regi[rs1]) && (imm2+regi[rs1])%2!=0){
                                        printf("Memory address out of range: 0x%08x\n",imm2+regi[rs1]);
                                    }
                                    flag=true;
                                    regi[32]+=4;
                                    valinst++;
                                    break;
                                }else if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                int tmp=0;
                                tmp+=datamem[imm2+regi[rs1]-0x10000000]<<8;
                                tmp+=datamem[imm2+regi[rs1]-0x10000000+1];
                                tmp=((unsigned int)tmp<<16)>>16;
                                // printf("lhu: %08x\n", tmp);
                                regi[rt1]=tmp;
                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }
                        idx++;
                    }else if(op=="001101"){        ////                         ori
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rs1=0; int imm2=0;
                        string imm=rd+shf+funt;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        // if(imm[0]=='1'){
                        //     for (int i = imm.size()-1; i >=0; i--)
                        //     {
                        //         if(imm[i]=='1'){
                        //             imm2+=pow(2, imm.size()-1-i);
                        //         }
                        //     }
                        //     imm2-= pow(2, imm.size());
                            
                        // }else{
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                        
                        if(str=="read"){printf("ori $%d, $%d, 0x%08x\n",rt1,rs1,imm2);}
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            regi[rt1]=regi[rs1]|imm2;
                            regi[32]+=4;
                            int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                        }
                        idx++;
                    }else if(op=="101000"){ ////////////////////////////////sb
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rs1=0; int imm2=0;
                        string imm=rd+shf+funt;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(imm[0]=='1'){
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                            imm2-= pow(2, imm.size());
                            
                        }else{
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                        }
                        if(str=="read"){printf("sb $%d, %d($%d)\n",rt1,imm2,rs1);}
                        else{
                            if(!checkrange(imm2+regi[rs1])){
                                flag=true;
                                regi[32]+=4;
                                printf("Memory address out of range: 0x%08x\n",imm2+regi[rs1]);
                                valinst++;
                                break;
                            }else if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }

                            datamem[imm2+regi[rs1]-0x10000000]=(unsigned long long)regi[rt1]>>24;

                            regi[32]+=4;
                            int idx=regi[32]/4;
                            valinst++;
                            if(valinst==cnt) break;
                            if(instad[idx]!=regi[32]){
                                valinst++;
                                break;
                            }
                        }
                        idx++;
                    }else if(op=="001010" || op=="001011"){         //////////////slti, sltiu
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rs1=0; int imm2=0;
                        string imm=rd+shf+funt;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(imm[0]=='1'){
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                            imm2-= pow(2, imm.size());
                            
                        }else{
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                        }
                        if(op=="001010"){      //slti
                            if(str=="read"){printf("slti $%d, $%d, %d\n",rt1,rs1, imm2);}
                            else{
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rt1]=((int)regi[rs1])<(int)imm2;
                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }else{     //sltiu
                            if(str=="read"){printf("sltiu $%d, $%d, %d\n",rt1,rs1, imm2);}
                            else{
                                if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                                }
                                regi[rt1]=regi[rs1]<(unsigned int)imm2;
                                regi[32]+=4;
                                int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                            }
                        }
                        idx++;
                    }else if(op=="001110"){ ////////////           ////////////// xori
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        int rt1=0; int rs1=0; int imm2=0;
                        string imm=rd+shf+funt;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
                            }
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        // if(imm[0]=='1'){
                        //     for (int i = imm.size()-1; i >=0; i--)
                        //     {
                        //         if(imm[i]=='1'){
                        //             imm2+=pow(2, imm.size()-1-i);
                        //         }
                        //     }
                        //     imm2-= pow(2, imm.size());
                            
                        // }else{
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                        
                        if(str=="read"){printf("xori $%d, $%d, %d\n",rt1,rs1, imm2);}
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            regi[rt1]=regi[rs1]^imm2;
                            regi[32]+=4;
                            int idx=regi[32]/4;
                                valinst++;
                                if(valinst==cnt) break;
                                if(instad[idx]!=regi[32]){
                                    valinst++;
                                    break;
                                }
                        }
                        idx++;
                    }else if(op=="000010"){                /////////////////////// j
                        if(str=="read"){printf("inst %d: %08x ",idx, address);}
                        string imm=rs+rt+rd+shf+funt; int imm2=0;
                        if(imm[0]=='1'){
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                            imm2-= pow(2, imm.size());
                            
                        }else{
                            for (int i = imm.size()-1; i >=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                        }
                        if(str=="read"){printf("j %d\n",imm2);}
                        else{
                            if(!checkinst(regi[32])){
                                    flag=true;
                                    printf("Memory address out of range: 0x%08x\n", regi[32]);
                                    valinst++; 
                                    regi[32]+=4;
                                    break;
                            }
                            valinst++;
                            if(valinst==cnt) break;
                            regi[32]=(regi[32]&0xf0000000)| (imm2<<2);
                            j=regi[32]-1;
                            s1="";
                            continue;
                        }
                        
                        idx++;
                    }else{
                        if(str=="read")printf("inst %d: %08x unknown instrucion\n", idx, address);
                        idx++;
                    }           
                    s1="";
                }
            }
            if(str=="run"){
                if(cnt>ho){
                    if(!flag && !sysflag){ regi[32]+=4; printf("unknown instruction\n");}
                    printf("Executed %d instructions\n", valinst);
                }else{
                    printf("Executed %d instructions\n", valinst);
                    }
                }
            continue;
        }
        
    }
    return 0;
}
