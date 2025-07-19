//Zombie Process
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#define BUFFER_SIZE 30
int main(){
        int fd, n;
        char buffer[BUFFER_SIZE];
        fd=open("testFile.txt", O_RDWR);
        printf("File description is %d\n", fd);
        if( !(fd+1)){
                printf("\nFailed to open file.\n");
                exit(1);
        }
        printf("Reading first 10 characters from the file.\n");
        n=read(fd,buffer,10);
        write(1,buffer,n);
        printf("\nSkipping 5 characters from current position in the file:\n");
        lseek(fd,5,SEEK_CUR);
        n=read(fd,buffer,10);
        write(1,buffer,n);
        printf("\nGoing to 5th last character in the file:\n");
        lseek(fd, -5, SEEK_END);
        n=read(fd,buffer,7);
        write(1,buffer,n);
        printf("\nGoing to 3rd character in the file:\n");
        lseek(fd,3,SEEK_SET);
        n=read(fd,buffer,5);
        write(1,buffer,n);
        printf("\n");
        return 0;
}

//Orphan Process
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
        pid_t my_pid, parent_pid, child_pid;
        child_pid = fork();
        if(child_pid < 0){
                printf("\nFork failed. Exiting\n");
                exit(1);
        }
        if(child_pid == 0){
                printf("\n[CHILD] This is the child process.\n");
                my_pid = getpid();
                parent_pid = getppid();
                printf("[CHILD] My pid is %d\n", my_pid);
                printf("[CHILD] My parent's pid is %d\n", parent_pid);
                printf("[CHILD] Sleeping for 10 seconds\n");
                sleep(10);
                printf("\n[CHILD] My parent has ended, so I am an orphan process, adopted my init process.\n");
        }else{
                printf("\n[PARENT] This is the parent process.\n");
                my_pid = getpid();
                parent_pid = getppid();
                printf("[PARENT] My pid is %d\n", my_pid);
                printf("[PARENT] My parent's pid is %d\n", parent_pid);
                printf("[PARENT] Exiting\n");
                exit(0);
        }
        return 0;
}