#include<stdio.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h> 
#include<string.h>
#include<ctype.h>
#include<unistd.h>


unsigned int xorbuf(unsigned int *buffer, int size) 
{
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

int main(int argc, char*argv[]) 
{ 
    int fd1,fd2;
    char *buf,*buf_read, *temp_buf, *buffer;
    unsigned int *buf1;
    char *ch="11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    char mode;
    if(argc <= 1)
    {
        printf("usage is ./run <filename> -r|w <block_size> <block_count>");
        return -1;
    }

    char *fname = argv[1];
    int total_char=0;
    int read_size = 0;
    int block_size = atoi(argv[3]);
    int block_count = atoi(argv[4]);
    int final_value =0;
    mode = argv[2][1];

    if(mode=='R' || mode=='r')
    {
        int fd1 = open(fname, O_RDONLY, 0);
        int fd2 = open(fname, O_RDONLY, 0);
        if(fd1<0 || fd2<0)
        {
            printf("filename doesn't exit");
        }
        total_char = block_size*block_count;
        buffer = (char *)(malloc(total_char*sizeof(char)));
        read_size = read(fd2, buffer, total_char);
       
        if(read_size != total_char)
        {
            printf("File size is not sufficient");
            strcpy(buffer,"");
            return -1;
        }
        close(fd2);

        buf1 = (unsigned int *)(malloc(total_char*sizeof(unsigned int)));
        temp_buf = (char *)(malloc(block_size*sizeof(char)));
        buf_read = (char *)(malloc(total_char*sizeof(char)));
        for(int i=0;i<block_count;i++)
        {
            int char_read = read(fd1, temp_buf, block_size);
            strncat(buf_read,temp_buf, block_size);
        }
        //printf("The buffer is %s \n", buf_read);
        for(int i=0;i<strlen(buf_read);i++)
        {
            buf1[i]=(int)(buf_read[i]);
        }
        printf("XOR value: %08x\n", xorbuf(buf1,total_char));
    } 
    else if(mode=='W' || mode=='w')
    {
        int fd1 = open(fname, O_RDWR|O_APPEND, 0);
        if(fd1<0)
        {
            //Creation of new file if not existing
            fd1 = creat(fname, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        }
        // If file exists then concatenate the data and write the data into file
        buf = (char *)(malloc(block_size*block_count*sizeof(char)));
        for(int i=0; i<block_count;i++)
        {
            strncat(buf, ch, block_size);
        }
        //printf("%s",buf);
        //printf("%ld",strlen(buf));
        write(fd1, buf, strlen(buf));
    }
    else
    {
        printf("usage is ./run <filename> write only/ read only <block_size> <block_count> \n");
    }
    close(fd1); 

} 
