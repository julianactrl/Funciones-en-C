#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, const char * argv[] )
{
    if ( argc > 1 ) {
        int server_socket, client_socket, longitud_cliente, puerto;

        puerto = atoi( argv[1] );

        struct sockaddr_in server;
        struct sockaddr_in client;

        //Variables del server
        server.sin_family = AF_INET; //Protocolo TCP/IP
        server.sin_port = htons( puerto ); //Puerto
        server.sin_addr.s_addr = INADDR_ANY; //Firewall (todos se puede conectar)
        bzero( &(server.sin_zero), 8); // 8 posiciones llenas con zeros

        //Crear socket del servidor modo escucha
        // Familia de protocolo, 
        if ( ( server_socket = socket( AF_INET, SOCK_STREAM, 0) )== -1) {
            printf( "No e abrir el socket\n");
            return -1;
        }

        //Conectar socket a un puerto
        //Guardar config en server
        if ( bind( server_socket, (struct sockaddr *) &server, sizeof( struct sockaddr)) == -1 ) {
            printf( "No pude abrir el puerto %s\n", argv[1] );
            return -2;
        }

        //Poner el socket en modo escucha definiendo lim de cola
        if( listen( server_socket, 5) == -1) {
            printf( "No pude ponerme en modo escucha\n");
            return -3;
        }
        longitud_cliente = sizeof( struct sockaddr_in );
        printf( "Esperando clientes...\n");

        //Intentar recibir el primer cliente
        if ( ( client_socket = accept( server_socket, (struct sockaddr *) &client, &longitud_cliente )) == -1 ) {
            printf( "No pudimos aceptar una conexion\n");
            return -4;
        }

        char str[INET_ADDRSTRLEN];
        //Primera conexion a str
        inet_ntop( AF_INET, &(client.sin_addr), str, INET_ADDRSTRLEN );
        printf( "Se conecto un cliente desde la ip %s:%d. Lo saludo\n", str, client.sin_port);
        
        //Mandando mensaje a la conexion
        send( client_socket, "Bienvenido a mi servidor.\n", 26, 0);
        printf( "Saludo enviado!\n");

        //cerrar por completo
        shutdown( client_socket, 2);
        shutdown( server_socket, 2);
    } 
    //El usuario no ingreso el puerto por la linea de comandos
    else {
        printf( "Por favor, indique el puerto\n");
        return -5;
    }
}