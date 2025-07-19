//Parent
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>

int main(int argc, char *argv[]){
        int i;
        pid_t pid;
        int k,n1,n2,n3;
        const int SIZE=4096;
        int shmid;
        void *ptr;
        shmid = shmget((key_t)1122, 4096, 0666 | IPC_CREAT);
        ptr = shmat(shmid, NULL, 0666);
        if(argc == 2){
                sscanf(argv[1], "%d", &i);
                if(i<1){
                        printf("Error input: %d\n", i);
                        return 0;
                }
        }else if(argc > 1){
                printf("Too many arguments\n");
                return 1;
        }else{
                printf("Invalid input format\n");
                return 1;
        }
        pid = fork();
        if(pid == 0){
                execlp("./fib","fib", argv[1], NULL);
        }else if(pid > 0){
                wait(NULL);
                printf("\nPARENT: child completed\n");
                printf("Parent printing\n");
                printf("%s", (char*)ptr);
                printf("\n");
                shmdt(ptr);
        }
        return 0;
}

//child
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<stdlib.h>

int main(int arg, char *argv[]){
        int k=2, n1,n2,n3;
        void *ptr;
        int shmid = shmget((key_t)1122, 4096, 0666);
        ptr = shmat(shmid, NULL , 0666);
        int i= atoi(argv[1]);
        n1 = 0;
        n2 = 1;
        sprintf(ptr, "%d ", n1);
        ptr += strlen(ptr);
        sprintf(ptr, "%d ", n2);
        ptr += strlen(ptr);
        while(k != i){
                n3 = n2+n1;
                sprintf(ptr, "%d ", n3);
                n1 = n2;
                n2 = n3;
                ptr += strlen(ptr);
                k++;
        }
        ptr += strlen(ptr);
        shmctl(shmid, IPC_RMID, NULL);
        return 0;
}