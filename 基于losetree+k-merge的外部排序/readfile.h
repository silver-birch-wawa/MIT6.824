int readline(FILE*fp){
       int buff;
       if (fscanf(fp, "%d", &buff) > 0){
              // 判断是否读到文件终止符了
              //printf("in:%d\n",buff);
              return buff;
       }
       else{
              return EOF;
       }
}