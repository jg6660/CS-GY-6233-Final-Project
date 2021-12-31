#include<stdio.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h> 
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/time.h>
#include<math.h>


double now() 
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main(int argc, char*argv[]) 
{ 
    int fd1;
    int block_count=1;
    char *temp_buf;
    double start, end;
    if(argc <= 1)
    {
        printf("usage is ./measurement <filename>  <block_size>");
        return -1;
    }

    char *fname = argv[1];
    int block_size = atoi(argv[2]);
    start = now();
    temp_buf = (char *)(malloc(block_size*block_count*sizeof(char)));
    fd1 = open(fname, O_RDWR, 0);
    if(fd1<0)
        {
            printf("filename doesn't exit");
        }
    for(int i=0;i<block_count;i++)
     {
            read(fd1, temp_buf, block_size);
     }
    end = now();
    if(end-start >=5)
    {
        printf("file size = %d",block_count*block_size);
        exit(0);
    }
    while((end - start)<=5 )
    {
        block_count*=2;
        temp_buf = (char *)(malloc(block_size*block_count*sizeof(char)));
        fd1 = open(fname, O_RDWR|O_APPEND, 0);
        start = now();
        for(int i=0;i<block_count;i++)
        {
            read(fd1, temp_buf, block_size);
        }
        end = now();
        //printf("\ntime taken is %f",end-start);
    }
    double timec  = end-start;

    double file_size = (double)block_count*block_size/(1024*1024);
    printf("\n File size:  %f MB\n", file_size);
    
    //printf("\n Performance: %f MiB/s\n",file_size/timec);
    close(fd1); 
} 