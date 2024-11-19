#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>



typedef struct {
    int id;
    char *temas;
}Datos;

void suscribirse(char *pipe) {

    int id = getpid();
    int fd = open(pipe, O_WRONLY);
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
        char tema = getchar();
        getchar();
        printf("\nTema selecionado: %c\n",tema);
        temas[i] = tema;
        i++;
        if(i<5){
            printf("\nDesea continuar? \n1 --> Yes\n2 --> No\n");
            scanf("%d", &cont); 
            getchar();
        }
        else{
            cont=0;
        }
    }
    char tem[i+1];

    /*
    for (int j =0;j<i+1;j++){
        tem[j]=temas[j];
        printf("\n%c",tem[j]);
    }
    */
    Datos datos;
    datos.id=id;
    printf("\n%d",datos.id);
    datos.temas=temas;

    /*
    for(int j = 0; j<i+1; j++){
        printf("\n%c",datos.temas[j]);
    }
    */

    write(fd, &datos, sizeof(datos));
    close(fd);
}

void recibirNoticias(const char *pipe) {
    while (1){
        int fd = open(pipe, O_RDONLY);
        if(fd == -1){
            perror("Error al abrir el FIFO");
            return;
        }

        char *noticia;
        read(fd,noticia,sizeof(noticia));

        printf("\nNoticia recibida: \n%s",noticia);
    }
    
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <nombre_pipe>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (mkfifo(argv[2], 0666) == -1) {
        perror("Error al crear el FIFO");
        return EXIT_FAILURE;
    }
    char *pipe = argv[2];
    printf("%s",pipe);
    suscribirse(pipe);
    recibirNoticias(pipe);

    return 0;
}