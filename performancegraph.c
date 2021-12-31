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


unsigned int result=0;


double now() 
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

void xorbuf(unsigned int *buffer, int size) 
{
    //unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    //return result;
}

int main(int argc, char*argv[]) 
{ 
    int fd1;
    unsigned int *temp_buf;
    double start, end;
    //char *fname = "hello.txt";
    //char *fname = "ubuntu-21.04-desktop-amd64.iso";
    //char *fname = "dumb.txt";
    char *fname = argv[1];


    unsigned long long block_size = atol(argv[2]);
    
    unsigned long long block_count=0;
    int final_value =0;
    //FILE *fpt;
    //fpt = fopen("Myfast.csv", "w+");

    fd1 = open(fname, O_RDONLY, 0);
    if(fd1<0)
    {
        printf("filename doesn't exit");
    }


   
    temp_buf=(unsigned int *)(malloc(block_size*sizeof(unsigned int)));

    for(int z=0;z<block_size;z++)
            {
                //buf1[z] = 0;
                temp_buf[z] = 0;
            }
    start = now();
    while(read(fd1,temp_buf,block_size)>0)
        {
            xorbuf(temp_buf,block_size);
            memset(temp_buf,0,block_size);
            block_count++;

        }
    end = now();
    printf("XOR value is %08x\n", result);
    double time = end - start;
    printf("Time taken to run %lld is %f\n",block_size,time);
    printf("\n Block count = %lld",block_count);
    printf("\n Speed = %f MiB/s\n",block_count*block_size/(time*1024*1024));
    

close(fd1); 
}
   
  