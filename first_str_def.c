#include <stdio.h>

int main()

{ 
	char * name = "Juliana";

	printf( "Nombre = %s, (%p)\n", name, name );

	for ( int i = 0; i < 7; i++ ) {
		printf( "name[%d] (%p) = %c\n", i, name + i, name[i] );
	}

	return 0;
}

