#include "./header.h"

int main(int argc, char** argv){
    int fileDesc = shm_open("/table", O_RDWR, 00700);
    struct sharedMemory* sharedMemoryPointer = mmap (NULL, sizeof(struct sharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, fileDesc, 0);

    while(1){
        sem_wait(&sharedMemoryPointer->flag);
        for(int i = 0; i < 2; i++){
            if(sharedMemoryPointer->table[i] == 1){
                sharedMemoryPointer->table[i] = 0;
                printf("Consumer has consumed.\n");
                break;
            }
        }
        sleep(1);
        sem_post(&sharedMemoryPointer->flag);
    }
}
