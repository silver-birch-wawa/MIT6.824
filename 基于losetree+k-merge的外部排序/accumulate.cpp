#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<string>
#include<vector>
#include <io.h>
#include <queue>
#include<iostream>
using namespace std;

// 把宏定义统一写到一块更方便
#include "defination.h"

int counts=0;

#define MAXNUM 0xfffff
#include "txtSize.h"
#include "getFileName.h"
#include "generatefile.h"
#include "readfile.h"
#include "writefile.h"
#include "losetree.h"
// 先一次性读取所有文件的size，生成
// 1.怎么选择k个段号.txt？--> 利用堆排序动态提取最小的k个合并然后生成新的段插入堆中
// 2.如果文件数小于k怎么办？--> 对空余的抽中了就insert MAXNUM
// 3.如果文件数大于k怎么办？--> 反正之前insert的都丢掉了，接着来一轮直到losetree insert的时候返回的l[key[0]].value==MAXNUM
// 4.边读边写入losetree，直到MAXNUM宣布新段生成结束，重置所有值为0继续
int main(){
    priority_queue<fileinfo,vector<fileinfo>,cmp>filesinfo;
    getAllFileNames(filesinfo,string("./txt"));
    int i,j;
    losetree l(k);
    // 因为文件消息不太占内存可以进行堆排序
    int res=l.kmerge(filesinfo);
    cout<<"res in file:"<<res<<endl;
    FILE*resfile=fopen(("./txt/"+to_string(res)).c_str(),"r+");
    while(1){
        int t=readline(resfile);
        if(t==EOF){
            break;
        }
        cout<<"res:"<<t<<endl;
    }
    fclose(resfile);
}