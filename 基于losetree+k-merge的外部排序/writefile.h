void writeline(FILE*&fp,int input){
    fprintf(fp,"%d\n",input);
    fflush(fp);
    //printf("w:%d\n",input);
    counts++;
}