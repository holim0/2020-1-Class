#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<bitset>
#include<cmath>
using namespace std;
int arr[20000];

int main(){
    
    FILE * fout;
    char filename[200];
    while(1){
        string str;
        printf("\nmips-sim>");
        cin>>str;
        if(str=="read"){
            scanf("%s",filename); 
            fout=fopen(filename, "rb");
            int ch;
            int i=0;
            while((ch=fgetc(fout))!=EOF){
                arr[i]=ch;
                i++;
            }
            
            string s1="";
            int idx=0;
            for (int j = 0; j < i; j++)
            {
                s1+=bitset<8>(arr[j]).to_string();
                if(s1.size()==32){
                    long long address=0;
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
                        printf("inst %d: %08x ",idx, address); 
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
                        if(funt=="100000"){
                            printf("add $%d, $%d, $%d\n", rd1, rs1, rt1);
                        }else{
                            printf("addu $%d, $%d, $%d\n", rd1, rs1, rt1);
                        }
                        idx++;
                        
                    }else if(op=="100011"){ /////////////////// lw
                        printf("inst %d: %08x ",idx, address);
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

                        printf("lw $%d, %d($%d)\n", rt1, offset2, rs1);
                        idx++;

                    }else if(op=="001000" || op=="001001"){ ////////////// addi, addiu
                        printf("inst %d: %08x ",idx, address);
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
                        if(op=="001000"){
                            printf("addi $%d, $%d, %d\n", rt1, rs1, imm);
                        }else{
                            printf("addiu $%d, $%d, %d\n", rt1, rs1, imm);
                        }
                        idx++;

                    }else if(op=="000101"){                 ///bne
                        printf("inst %d: %08x ",idx, address);
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

                        printf("bne $%d, $%d, %d\n", rs1, rt1, offset2);
                        idx++;
                    }else if(op=="000000"&& funt=="000000"){  ////sll
                        printf("inst %d: %08x ",idx, address);
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
                        printf("sll $%d, $%d, %d\n", rd1, rt1, sa);
                        idx++;
                    }else if(op=="000000" && (funt=="001000"|| funt=="001001")){    //jr and jalr
                        printf("inst %d: %08x ",idx, address);
                        int rs1=0;
                        for (int i = 4; i >=0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(funt=="001000"){
                            printf("jr $%d\n", rs1);
                        }else{
                            printf("jalr $%d\n", rs1);
                        }
                        idx++;

                    }else if(op=="101001"){ // sh
                        printf("inst %d: %08x ",idx, address);
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
                        printf("sh $%d, %d($%d)\n", rt1, offset2, rs1);
                        idx++;

                    }else if(op=="001111"){  // lui
                        printf("inst %d: %08x ",idx, address);
                        string imm=rd+shf+funt;
                        int rt1=0; int imm2=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rt[i]=='1'){
                                rt1+=pow(2, 4-i);
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
                        printf("lui $%d, %d\n", rt1, imm2);
                        idx++;
                    }else if(op=="000011"){  //jal
                        printf("inst %d: %08x ",idx, address);
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
                        printf("jal %d\n", target2);
                        idx++;

                    }else if(op=="000100"){ //beq
                        printf("inst %d: %08x ",idx, address);
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
                        printf("beq $%d, $%d, %d\n", rs1, rt1, offset2);
                        idx++;

                    }else if(op=="001001"){  //addiu
                        printf("inst %d: %08x ",idx, address);
                        int rs1=0; int rt1=0; int imm2=0;
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
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                            imm2-=pow(2, imm.size());
                            
                        }else{
                            for (int i = imm.size()-1; i>=0; i--)
                            {
                                if(imm[i]=='1'){
                                    imm2+=pow(2, imm.size()-1-i);
                                }
                            }
                        }
                        printf("addiu $%d, $%d, %d\n", rt1, rs1, imm2);
                        idx++;
                    }else if(op=="101011"){  //sw
                        printf("inst %d: %08x ",idx, address);
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
                        printf("sw $%d, %d($%d)\n", rt1, offset2, rs1);
                        idx++;
                    }else if(op=="000000" && shf=="00000" &&(funt=="100101" || funt=="100111")){  //or nor
                        printf("inst %d: %08x ",idx, address);
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
                        if(funt=="100101"){
                            printf("or $%d, $%d, $%d\n", rd1, rs1, rt1);
                        }
                        else{
                            printf("nor $%d, $%d, $%d\n", rd1, rs1, rt1);
                        }
                        idx++;
                    }else if(op=="000000" && shf=="00000" && funt=="100100"){ //and
                        printf("inst %d: %08x ",idx, address);
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
                        printf("and $%d, $%d, $%d\n", rd1, rs1, rt1);
                        idx++;
                    }else if(op=="000000" && (funt=="011010"|| funt=="011011")){ //div and divu
                        printf("inst %d: %08x ",idx, address);
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
                            printf("div $%d, $%d\n",rs1, rt1);
                        }else{
                            printf("divu $%d, $%d\n",rs1, rt1);
                        }
                        idx++;
                    }else if(funt=="010000"|| funt=="010010"){ //mfhi, mflo
                        printf("inst %d: %08x ",idx, address);
                        int rd1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rd[i]=='1'){
                                rd1+=pow(2, 4-i);
                            }
                        }

                        if(funt=="010000"){
                            printf("mfhi $%d\n",rd1);
                        }else{
                            printf("mflo $%d\n",rd1);
                        }
                        idx++;
                    }else if(funt=="010001"||funt=="010011"){ //mthi, mtlo
                        printf("inst %d: %08x ",idx, address);
                        int rs1=0;
                        for (int i = 4; i >= 0; i--)
                        {
                            if(rs[i]=='1'){
                                rs1+=pow(2, 4-i);
                            }
                        }
                        if(funt=="010001"){
                            printf("mthi $%d\n",rs1);
                        }else{
                            printf("mtlo $%d\n",rs1);
                        }
                        idx++;
                    }else if(funt=="011000"||funt=="011001"){  //mult, multu
                        printf("inst %d: %08x ",idx, address);
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
                            printf("mult $%d, $%d\n",rs1, rt1);
                        }else{
                            printf("multu $%d, $%d\n",rs1, rt1);
                        }
                        idx++;
                    }else if(op=="000000" && shf=="00000"&& funt=="000100"){ //sllv
                        printf("inst %d: %08x ",idx, address);
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
                        printf("sllv $%d, $%d, $%d\n",rd1, rt1, rs1);
                        idx++;
                    }else if(op=="000000" && shf=="00000"&& (funt=="101010"|| funt=="101011")){ //slt, sltu
                        printf("inst %d: %08x ",idx, address);
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
                        if(funt=="101010"){
                            printf("slt $%d, $%d, $%d\n",rd1, rs1, rt1);
                        }else{
                           printf("sltu $%d, $%d, $%d\n",rd1, rs1, rt1); 
                        }
                        idx++;
                    }else if(op=="000000" && rs=="00000" &&funt=="000011"){  // sra
                        printf("inst %d: %08x ",idx, address);
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
                        printf("sra $%d, $%d, $%d\n",rd1, rt1, shf1); 
                        idx++;
                    }else if(op=="000000" && shf=="00000" &&funt=="000111"){ // srav
                        printf("inst %d: %08x ",idx, address);
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
                        printf("srav $%d, $%d, $%d\n",rd1, rt1, rs1); 
                        idx++;
                    }else if(op=="000000" && funt=="000010"){ // srl
                        printf("inst %d: %08x ",idx, address);
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
                        printf("srl $%d, $%d, $%d\n",rd1, rt1, shf1); 
                        idx++;
                        
                    }else if(op=="000000" && funt=="000110" &&shf=="00000"){ // srlv
                        printf("inst %d: %08x ",idx, address);
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
                        printf("srlv $%d, $%d, $%d\n",rd1, rt1, rs1); 
                        idx++;
                    }else if(op=="000000" && shf=="00000" && (funt=="100010" || funt=="100011")){ //sub, subu
                        printf("inst %d: %08x ",idx, address);
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
                        if(funt=="100010"){
                            printf("sub $%d, $%d, $%d\n",rd1, rs1, rt1); 
                        }else{
                            printf("subu $%d, $%d, $%d\n",rd1, rs1, rt1); 
                        }
                        idx++;
                    }else if(op=="000000" && rd=="00000"&& rs=="00000"&& rt=="00000"&& shf  =="00000" &&funt=="001100"){ //syscall
                        printf("inst %d: %08x syscall\n", idx, address);
                        idx++;
                    }else if(op=="000000" && shf=="00000" && funt=="100110"){ //xor
                        printf("inst %d: %08x ",idx, address);
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
                        printf("xor $%d, $%d, $%d\n",rd1, rs1, rt1); 
                        idx++;
                    }else if(op=="001100"){                                   //andi
                        printf("inst %d: %08x ",idx, address);
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
                        printf("andi $%d, $%d, %d\n",rt1, rs1, imm2); 
                        idx++;
                    }else if(op=="100000" || op=="100100"){             /////////// lb, lbu
                        printf("inst %d: %08x ",idx, address);
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
                            printf("lb $%d, %d($%d)\n",rt1,imm2, rs1);
                        }else{
                            printf("lbu $%d, %d($%d)\n",rt1,imm2, rs1);
                        }
                        idx++;
                    }else if(op=="100001" || op=="100101"){///////////                        //////////////// lh, lhu
                        printf("inst %d: %08x ",idx, address);
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
                            printf("lh $%d, %d($%d)\n",rt1,imm2, rs1);
                        }else{
                            printf("lhu $%d, %d($%d)\n",rt1,imm2, rs1);
                        }
                        idx++;
                    }else if(op=="001101"){        ////                                      ori
                        printf("inst %d: %08x ",idx, address);
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
                        printf("ori $%d, $%d, %d\n",rt1,rs1,imm2);
                        idx++;
                    }else if(op=="101000"){ ////////////////////////////////sb
                        printf("inst %d: %08x ",idx, address);
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
                        printf("sb $%d, %d($%d)\n",rt1,imm2,rs1);
                        idx++;
                    }else if(op=="001010" || op=="001011"){         //////////////slti, sltiu
                        printf("inst %d: %08x ",idx, address);
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
                        if(op=="001010"){
                            printf("slti $%d, $%d, %d\n",rt1,rs1, imm2);
                        }else{
                            printf("sltiu $%d, $%d, %d\n",rt1,rs1, imm2);
                        }
                        idx++;
                    }else if(op=="001110"){ ////////////           ////////////// xori
                        printf("inst %d: %08x ",idx, address);
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
                        printf("xori $%d, $%d, %d\n",rt1,rs1, imm2);
                        idx++;
                    }else if(op=="000010"){                           /////////////////////// j
                        printf("inst %d: %08x ",idx, address);
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
                        printf("j %d\n",imm2);
                        idx++;
                    }else{
                        if(printf("inst %d: unknown instrucion\n", idx);
                        idx++;
                    }           
                    s1="";
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