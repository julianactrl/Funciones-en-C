#include <stdio.h>
#include <string.h>

int main()
{
	char * name = "Juliana";
	char * otherName = "Micaela";

	printf( "Los nombres son  %s\n", strcmp( name, otherName) == 0 ? "iguales" : "distintos" );

	return 0;
}
