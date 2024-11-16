#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>


#define MAX_BUFFER_SIZE 1024
#define MAX_SUBSCRIPTORES 100
#define MAX_TOPICS 5


typedef struct {
    pid_t pid;
    char topics[MAX_TOPICS];
    int numTopics;
    char pipeName[30];
} Suscriptor;

Suscriptor suscriptores[MAX_SUBSCRIPTORES];
int numSuscriptores = 0;
int running = 1; // Variable para controlar la ejecución del sistema


pthread_mutex_t lock;

void finalizarSistema(int sig) {


}


void *gestionarSuscripciones(void *arg) {

}

void *gestionarPublicadores(void* arg) {

    
}


int main(int argc, char *agv[]){

    return 0;
}