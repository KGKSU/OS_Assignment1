#include "header.h"

int main(int argc, char** argv){
    int fileDesc = shm_open("/table", O_CREAT | O_EXCL | O_RDWR, 00700);
    ftruncate(fileDesc, sizeof(struct sharedMemory));
    struct sharedMemory* sharedMemoryPointer = mmap (NULL, sizeof(struct sharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, fileDesc, 0);
    sem_init(&sharedMemoryPointer->flag, 1, 1);
    memset(sharedMemoryPointer->table, 0, sizeof(sharedMemoryPointer->table));

    while(1){
        sem_wait(&sharedMemoryPointer->flag);
        for(int i = 0; i < 2; i++){
            if(sharedMemoryPointer->table[i] == 0){
                sharedMemoryPointer->table[i] = 1;
                printf("Producer has produced.\n");
                break;
            }
        }
        sem_post(&sharedMemoryPointer->flag);
    }
}