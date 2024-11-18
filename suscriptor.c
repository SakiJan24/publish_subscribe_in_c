#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


typedef struct {
    int id;
    char *temas;
}Datos;


void suscribirse(char *pipe) {

    int id = getpid();
    int fd = open(pipe, O_RDONLY);
    if(fd == -1){
        perror("Error al abrir el FIFO");
        return;
    }
    int cont = 1;
    int i = 0;
    char temas[5];
    while(cont == 1){
        printf("\nIngrese el tema al que desea suscribirse");
        printf("\n1) A\n2) E\n3) C\n4) P\n5) S\n");
        char tema;
        scanf(" %c",tema);
        temas[i] = tema;
        i++;
        if(i<5){
          printf("\nDesea continuar? \n1 --> Yes\n2 --> No\n");
        scanf("%d", &cont);  
        }
        else{
            cont=0;
        }
    }

    Datos datos;
    datos.id=id;
    datos.temas=temas;
    printf("\n%s",temas);
    printf("\n\n%s",datos.temas[0]);
    write(fd, &datos, sizeof(datos));

}

/*
void recibirNoticias(const char *pipeName) {

}
*/
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <nombre_pipe>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *pipe = argv[2];
    printf("%s",pipe);
    suscribirse(*argv);

    return 0;
}

//gcc .\suscriptor.c -o .\suscriptor
//.\suscriptor -s pipeSSC
