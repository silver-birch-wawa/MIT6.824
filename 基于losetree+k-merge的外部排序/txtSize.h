// 获取文件大小
#include <sys/stat.h>
int txt_file_size(const char* filename)
{
    struct stat statbuf;
    stat(filename,&statbuf);
    int size=statbuf.st_size;
 
    return size;
}
int get_size_by_int(int t){
    string folder="./txt/";
    string name = string(folder + to_string(t));
    return txt_file_size(name.c_str());   
}
void printsize(const char* filename){
    //cout<<filename<<":"<<txt_file_size(filename)<<endl;
}