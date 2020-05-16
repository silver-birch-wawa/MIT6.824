#define MAXNUM 0xfffff
#define w 1073741824
// 1GB=1024*1024*1024=1073741824 w的值基本上不影响内存
int k=7;
// 500MB情况下 最高支持142路归并排序(暂时不清楚为什么,理论应该不止这个数)

// 文件信息
typedef struct{
    int scope;
    int size;
}fileinfo;

// 文件大小堆排序
struct cmp{
	bool operator()(fileinfo&a, fileinfo&b){
		if(a.size == b.size)return a.size>b.size;
		return a.size>b.size;
	}
};