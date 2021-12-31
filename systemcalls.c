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
    int fd1,fd2;
    char temp_buf[10000];
    double start, end, start_l, end_l, start_w, end_w,start_o, end_o;
    if(argc <= 1)
    {
        printf("usage is ./measurement <filename>  <block_size>");
        return -1;
    }
    //FILE *fpt;
    //fpt = fopen("MyFile.csv", "w+");
    char *fname = argv[1];
    //int total_char=0;
    int block_size = 1;
    //int block_count = atoi(argv[3]);
    int i=0;

 
    fd1 = open(fname, O_RDWR, 0);
    if(fd1<0)
        {
            printf("filename doesn't exit");
        }

    //Time calculation for read operation
    {
    start = now();
    for(int y=0; y<(1024*1024);y++)
        {
            read(fd1,temp_buf,block_size);
            //printf("\n%d th read",y);     
        }
      end = now();
    double time = end - start;
    double perf = 1/ time;
    double perf_B = perf*1024*1024;
    printf("\n\nfile size %d",1024*1024);
    printf("\nread: time taken %f",time);
    printf("\nread: performance at %d= %f MiB/s",block_size,perf);
    printf("\nread: performance at %d= %f B/s",block_size,perf_B);
    }

    //time calculation for lseek operation
    {
    start_l = now();
    for(int y=0; y<(1024*1024);y++)
        {
            lseek (fd1, 0, SEEK_CUR);
            //printf("\n%d th lseek",y);     
        }
    end_l = now();
    double time = end_l - start_l;
    double perf = 1/ time;
    double perf_B = perf*1024*1024;
    printf("\n\nfile size %d",1024*1024);
    printf("\nlseek: time taken %f",time);
    printf("\nlseek: performance at %d= %f MiB/s",block_size,perf);
    printf("\nlseek: performance at %d= %f B/s",block_size,perf_B);
    }

  
    //Time calculation for write operation
    fd2 = open("hello.txt", O_RDWR, 0);
    {
    start_w = now();
    for(int y=0; y<(1024*1024);y++)
        {
            write(fd2,"1", 1);
            //printf("\n%d th read",y);     
        }
    end_w = now();
    double time = end_w - start_w;
    double perf = 1/ time;
    double perf_B = perf*1024*1024;
    printf("\n\nfile size %d",1024*1024);
    printf("\nwrite: time taken %f",time);
    printf("\nwrite: performance at %d= %f MiB/s",block_size,perf);
    printf("\nwrite: performance at %d= %f B/s",block_size,perf_B);
    }  

    // Time calculation for open operation
    {
    start_o = now();
    for(int y=0; y<(1024*1024);y++)
        {
            fd2 = open("hello.txt", O_RDWR, 0);
            //printf("\n%d th read",y);     
        }
    end_o = now();
    double time = end_o - start_o;
    double perf = 1/ time;
    double perf_B = perf*1024*1024;
    printf("\n\nfile size %d",1024*1024);
    printf("\nopen: time taken %f",time);
    printf("\nopen: performance at %d= %f MiB/s",block_size,perf);
    printf("\nopen: performance at %d= %f B/s",block_size,perf_B);
    } 
    close(fd2); 
} 