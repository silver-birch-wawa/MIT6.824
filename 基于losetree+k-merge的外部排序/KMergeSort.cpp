#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>
using namespace std;
int k=10;
#define MAXKEY 0xfffffff
#define RUNEND_SYMBOL 0xfffffff // 归并段结束标志
#define w 268435456     // 内存工作区可容纳的记录个数 1GB=1024MB=1024^2KB=1024^3B=1024^3/4 INT=268435456

#include "readfile.h"
#include "losetree.h"
int main(){
        /*读取到文件末端*/
        while(1){
            int t=readline(fp);
            if(t==EOF){
                break;
            }
            printf("%d\n",t);
        }
        fclose(fp);    

        FILE*fp[k];
        int i,j;
        for(i=0;i<k;i++){
            string s=".txt";
            s=to_string(i)+s;
            fp[i]= fopen(s.c_str(), "r+");
        }     
        /*处理代码*/
        
        /*处理结束*/
        for(i=0;i<k;i++){
            fclose(fp[i]);   
        }                                
}