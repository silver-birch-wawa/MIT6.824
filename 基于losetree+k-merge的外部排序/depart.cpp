#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<string>
#include<vector>
#include<queue>
using namespace std;

// 把宏定义统一写到一块更方便
#include "defination.h"

int counts=0;
// 统计写进去的数字个数，避免读取的初始文件数据在计算中缺失没有写进各个段文件中

#include "generatefile.h"
// 生成初始文件
#include "readfile.h"
#include "writefile.h"

#include "txtSize.h"
// 败者树
#include "losetree.h"

/*
本程序负责生成一组(0,1000]的随机整数并写入txt文件中，并通过置换排序算法生成多个子文件，
生成的文件中数据已经按从小到大顺序排好序
*/
int main(){
    // generatefile(1,w); 生成1个含w个数字的文件
    FILE*fp=fopen("y.txt", "r+");
    // 4GB的没办法读直接返回-1
    int i,j;
    /*处理代码*/
    losetree ls(k);
    // 初始化
    ls.build(fp);
    /*初始化结束*/
    // 初始化段号
    int pre_scope=1;
    while(ls.get_block(fp,pre_scope++)){
        printf("ok\n"); 
        //少打点省内存
    }
    printf("\nfilenum:%d\n",pre_scope-1);
    printf("counts:%d",counts);
    fclose(fp);
}
