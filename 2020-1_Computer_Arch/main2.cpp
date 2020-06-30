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

int main(){
    FILE * fout;
    char filename[200];
    while(1){
        string str;
        printf("mips-sim>");
        cin>>str;
        if(str=="registers"){
            for (int i = 0; i < 32; i++)
            {
                printf("$%d: 0x%08x\n",i, regi[i]);
            }
            printf("PC: 0x%08x\n", regi[32]);

        }
        else if(str=="read" || str=="loadinst"){
            scanf("%s",filename); 
            fout=fopen(filename, "rb");
            int ch;
            int i=0;
            int cnt;
            while((ch=fgetc(fout))!=EOF){
                arr[i]=ch;
                i++;
            }

            int ho= i/4; // 실제 명령어 개수.
            int valinst=0;
            if(str=="loadinst"){
                memset(instad, 0xffffffff, sizeof(instad));
                for (int i = 0; i < ho; i++)
                {
                     instad[i]=0+4*i;
                }
                memset(regi, 0, sizeof(regi));
                
                string s; printf("mips-sim>");
                cin>>s;  
                if(s=="exit"){fclose(fout); return 0;}
                else if(s=="run"){
                    cin>>cnt; // 실행하고 싶은 명령어 개수
                }
            }

            string s1="";
            int idx=0;
            for (int j = 0; j < i; j++)
            {
                s1+=bitset<8>(arr[j]).to_string();
                if(s1.size()==32){
                    unsigned long long address=0;
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
                                int val=regi[rs1]+regi[rt1];
                                regi[rd1]=val;
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
                                int val=regi[rs1]+regi[rt1];
                                regi[rd1]=val;
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
                        }

                        if(str=="read"){printf("lw $%d, %d($%d)\n", rt1, offset2, rs1);}
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
                                unsigned int val= regi[rs1]+(unsigned)imm;
                                regi[rt1]=val;
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
                            if(str=="read"){ printf("addiu $%d, $%d, %d\n", rt1, rs1, imm); }
                            else{
                                unsigned int val= regi[rs1]+(unsigned)imm;
                                regi[rt1]=val;
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
                        int rs1=0;
                        for (int i = 4; i >=0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(funt=="001000"){
                            if(str=="read"){printf("jr $%d\n", rs1);}
                        }else{
                           if(str=="read"){ printf("jalr $%d\n", rs1);}
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
                        
                        if(str=="read"){printf("lui $%d, %d\n", rt1, imm2);}
                        else{
                            regi[rt1]=imm2<<16;
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
                       if(str=="read"){ printf("jal %d\n", target2);}
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
                               regi[rd1]=regi[rs1]|regi[rt1];
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
                        }else{
                           if(str=="read"){ printf("divu $%d, $%d\n",rs1, rt1);}
                        }
                        idx++;
                    }else if(funt=="010000"|| funt=="010010"){ //mfhi, mflo
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
                        }else{
                           if(str=="read"){ printf("mflo $%d\n",rd1);}
                        }
                        idx++;
                    }else if(funt=="010001"||funt=="010011"){ //mthi, mtlo
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
                        }else{
                           if(str=="read"){ printf("mtlo $%d\n",rs1);}
                        }
                        idx++;
                    }else if(funt=="011000"||funt=="011001"){  //mult, multu
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
                        }else{
                           if(str=="read"){ printf("multu $%d, $%d\n",rs1, rt1);}
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
                                regi[rd1]=(signed)regi[rs1]<(signed)regi[rt1];
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
                            int val=(signed)regi[rt1]>>shf1;
                            regi[rd1]=(unsigned) val;
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
                            int val=(signed)regi[rt1]>>regi[rs1];
                            regi[rd1]=(unsigned) val;
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
                                regi[rd1]=regi[rs1]-regi[rt1];
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
                                regi[rd1]=regi[rs1]-regi[rt1];
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
                        idx++;
                    }else if(op=="000000" && shf=="00000" && funt=="100110"){ //xor
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
                        if(str=="read"){printf("xor $%d, $%d, $%d\n",rd1, rs1, rt1);}
                        else{
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
                        if(op=="100000"){
                            if(str=="read"){printf("lb $%d, %d($%d)\n",rt1,imm2, rs1);}
                        }else{
                           if(str=="read"){ printf("lbu $%d, %d($%d)\n",rt1,imm2, rs1);}
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
                        }else{
                            if(str=="read"){printf("lhu $%d, %d($%d)\n",rt1,imm2, rs1);}
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
                                regi[rt1]=signed(regi[rs1])<imm2;
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
                                regi[rt1]=regi[rs1]<(unsigned)imm2;
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
                    }else if(op=="000010"){                           /////////////////////// j
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
                        idx++;
                    }else{
                        if(str=="read")printf("inst %d: %08x unknown instrucion\n", idx, address);
                        idx++;
                    }           
                    s1="";
                }
            }
            if(str=="loadinst"){
                if(cnt>ho){
                    regi[32]+=4;
                    printf("unknown instruction\n");
                    printf("Executed %d instructions\n", valinst);
                }else{
                    printf("Executed %d instructions\n", valinst);
                    }
                }
            continue;
        } 
        else if(str=="exit"){
            fclose(fout);
            return 0;
        }  
    }
    return 0;
}