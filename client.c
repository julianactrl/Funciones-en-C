#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main( int argc, const char * argv[] )
{
    //Direccion ip del server, puerto
    if ( argc > 2 ) {
        const char *ip;
        int client_socket, numbytes, puerto;
        char buff[100];

        ip = argv[1];
        puerto = atoi( argv[2]);

        //Server al que nos queremos conectar
        struct sockaddr_in server;

        // Convertir argumento a dirección ip
        if ( inet_pton( AF_INET, argv[1], &server.sin_addr) <= 0 ) {
            printf( "La ip %s no es valida\n", ip);
            return -1;
        }

        printf( "Abriendo el socket\n");

        //Abrir el socket del cliente
        if ( ( client_socket = socket( AF_INET, SOCK_STREAM, 0 )) == -1 ) {
            printf( "No pude abrir el socket\n" );
            return -2;
        }
        // A que server nos vamos a conectar?
        server.sin_family = AF_INET;
        server.sin_port = htons( puerto ); //Convertir a estructura
        bzero( &(server.sin_zero), 8);
        //Intentar la conexion
        printf( "Conectando a %s:%d", ip, puerto );

        if ( connect( client_socket, (struct sockaddr *) &server, sizeof( struct sockaddr)) == -1) {
            printf( "No pude contarme al servidor\n");
            return -3;
        }

        printf( "Recibiendo...\n");

        if (( numbytes = recv( client_socket, buff, 100, 0)) == -1) {
            printf( "Error en la lectura\n");

            return -4;
        }
        buff[numbytes] = '\0';

        printf( "El servidor envio el mensaje '%s'\n", buff);

        shutdown( client_socket, 2);

    } else {
        printf( "Por favor, indique ip del servidor y el puerto\n");
        return -5;
    }
               return 0;
}
