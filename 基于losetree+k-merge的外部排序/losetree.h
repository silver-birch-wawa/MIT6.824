class losetree{
    public:
        // 叶节点
        int *key;
        // 非叶节点
        typedef struct{
            int value;
            // 存放具体数值
            int scope;
            // 属于哪个块
        }leaf;
        leaf*l;
        // 二叉败者树的非叶节点，负责索引到对应叶节点，大小为k
        losetree(int k){
            l=new leaf[k];
            key=new int(k);
            int i;
            for(i=k-1;i>=0;i--){
                key[i]=0;
                l[i].scope=0;
                l[i].value=0;
            }   
            //memset(&l,0,k*sizeof(leaf));
            //memset(&key,0,k*sizeof(int));
        }
        // 用于置换-选择排序(分段)的初始化,必须从后往前推，因为要保证0这个点最后被覆盖
        void build(FILE*fp){
            // 初始化叶节点
            int i;
            // memset(key,0,k*sizeof(int));
            // 读取k个数字填充败者树         
            for(i=k-1;i>=0;i--){
                l[i].scope=1;
                insert(readline(fp),i);
            }
        }
        void insert(int input,int position){
            // position 在叶节点上的位置(为了方便，我们允许它的值大于k，
            // 从而实现leaf还有losertree两个不同类型数据的操作共享)
            // now从叶节点循着父节点(now/2)往上冒泡
            int now=k+position;
            // 比较胜者点之前的value与当前插入的值,从而决定是否对scope进行修改
            if(input>=l[key[0]].value){
                l[position].scope;
            }
            else{
                l[position].scope+=1;
            }
            // 用输入对胜者点进行替换(需要放在scope修改之后，因为key[0]在大部分操作中=position，要不然永远相等了)
            l[position].value=input;

            // position存放胜出值对应的leaf点位置,now则是树非叶节点的位置
            while(now!=0){
                // 考虑我(position)失败的情况，即父节点段号更小或者段号相等但是值更小，将胜者position用父节点指向的节点位置覆盖
                if(l[key[(now/2)]].scope<l[position].scope||(l[key[(now/2)]].scope==l[position].scope&&l[key[(now/2)]].value<l[position].value)){
                    int temp=key[now/2];
                    key[now/2]=position;
                    position=temp;
                }
                // 考虑我胜利的情况,啥都不用做
                else{

                }
                now/=2;
            }
            key[0]=position;
        }
        int get_block(FILE* fp,int pre_scope){
            FILE* out=NULL;
            if(l[key[0]].value==MAXNUM){
                return 0;
            }
            else{
                string folder="./txt/";
                string filename=(folder+to_string(pre_scope));
                //printf("%s\n",filename.c_str());
                out=fopen(filename.c_str(),"w+");
                // 每次都要先摘掉tree头部的min值然后再insert知道下个段的min值替代了tree的头
                writeline(out,l[key[0]].value);              
            }
            int i;
            while(1){
                // 不断从文件读取数据输入败者树，
                // 如果段号更新则输出前一个段号的所有数据
                int input=readline(fp);
                //printf("input:%d\n",input);
                // 发现读到初始文件句尾了
                if(input==EOF){           
                    // 填充MAXNUM把里面残余的数据挤出来         
                    // 先修改scope,反正读到MAXNUM就退出
                    l[key[0]].scope=MAXNUM;
                    insert(MAXNUM,key[0]);          
                }
                else{       
                    // 正常插入
                    insert(input,key[0]);                    
                }
                // scope更新说明已经刷新到下一个段了
                if(l[key[0]].scope>pre_scope){
                    if(l[key[0]].value==MAXNUM){
                        fclose(out);
                        // 返回0表示已经读完最后一个段了
                        return 0;
                    }
                    pre_scope=l[key[0]].scope;
                    break;
                }
                writeline(out,l[key[0]].value);
            }
            fclose(out);
            // 返回1表示还有别的段没读完
            return 1;
        }
        // 简化版的无最佳归并树BMT的k路归并排序 返回最终的resfile名字
        int kmerge(priority_queue<fileinfo,vector<fileinfo>,cmp>&q){
            // 每次轮回前检查以下待排序的文件数量filenum有没有>=k个，不足的就记录下来用MAXNUM灌水，
            // 写入的文件名=filenum+1
            // 如果发现输出了MAXNUM说明结束了，返回
            // 如果没有输出MAXNUM则接着读，如果有个别分支读不出来数据但是又没读到MAXNUM就用MAXNUM替代-1然后就不用管了
            // fclose()
            int i,j;
            int resfile=-1;
            int end=q.size();
            string folder="./txt/";
            for(i=1;;i++){
                //int size=q.size();
                if(q.size()==1){
                    break;
                }
                FILE*out=fopen((folder+to_string(end+i)).c_str(),"w+");
                //FILE*leafs=(FILE*)malloc(k*sizeof(FILE*));
                FILE*leafs[k];
                int blank=0;
                if(q.size()>=k){
                    j=k;
                    while(j){
                        leafs[j-1]=fopen((folder+to_string(q.top().scope)).c_str(),"r+");
                        j--;
                        q.pop();
                    }        
                    // build
                    for(j=k-1;j>=0;j--){
                        l[j].scope=1;
                        insert(readline(leafs[j]),j);
                    }
                    // circle read
                    while(l[key[0]].value!=MAXNUM){
                        writeline(out,l[key[0]].value);
                        int newinput=readline(leafs[key[0]]);
                        if(newinput==EOF){
                            // 如果其中一个段读到底了就用MAXNUM封一下
                            insert(MAXNUM,key[0]);
                        }
                        else{
                            insert(newinput,key[0]);
                        }
                    }       
                    for(j=0;j<k;j++){
                        fclose(leafs[j]);
                    }
                }
                else{
                    j=q.size();
                    blank=k-q.size();
                    while(j){
                        leafs[j-1]=fopen((folder+to_string(q.top().scope)).c_str(),"r+");
                        j--;    
                        q.pop();                    
                    }
                    //build
                    for(j=k-1;j>=k-blank;j--){
                        l[j].scope=1;
                        insert(MAXNUM,j);                        
                    }
                    for(j=k-blank-1;j>=0;j--){
                        l[j].scope=1;
                        insert(readline(leafs[j]),j);
                    }
                    // circle read
                    while(l[key[0]].value!=MAXNUM){
                        writeline(out,l[key[0]].value);
                        int newinput=readline(leafs[key[0]]);
                        if(newinput==EOF){
                            // 如果其中一个段读到底了就用MAXNUM封一下
                            insert(MAXNUM,key[0]);
                        }
                        else{
                            insert(newinput,key[0]);
                        }
                    }
                    for(j=0;j<q.size();j++){
                        fclose(leafs[j]);
                    }
                }
                //delete[]leafs;
                fclose(out);                
                // out 写完记得加到priority_queue的队列里面去
                fileinfo f;
                f.scope=end+i;
                f.size=get_size_by_int(f.scope);
                q.push(f);
                // 每次losetree用完都要重新置为0
                for(j=k-1;j>=0;j--){
                    key[j]=0;
                    l[j].scope=0;
                    //l[j].value=0;
                }                   
            }
            return q.top().scope;
        }
};