// 生成随机数，一行一个数
int generate_num(){
    int a;
    a = rand();
    return a;
}
// 根据k值生成对应数量的文件,根据weight设置k个文件之和的大小，每个文件大小均匀
void generatefile(int k,int weight){
    int i,j;
    srand((unsigned)time(NULL));
    for(i=0;i<k;i++){
        FILE *fp = NULL;
        string s=".txt";
        s=to_string(i)+s;
        fp = fopen(s.c_str(), "w+");
        for(j=0;j<w/k;j++){
                fprintf(fp, "%d\n",generate_num()%1000+1);
        }
        fclose(fp);
    } 
}