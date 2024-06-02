#ifndef MAP_H_INCLUDE
#define MAP_H_INCLUDE

#include "status.h"
#include "List.h"

#define MAX_LENGTH 1024
static char* mapFileName = "FRANCE.MAP";
typedef struct City {
    char* name;
    int lang;
    int lat;
    int g;
    int h;
    List* neighbour;
    struct City* backptr;
}City;

typedef struct Neighbour {
    char* name;
    int distance;
}Neighbour;

List* parseMapFile( char* );
City* findCity( List* , char* );
status findPath( List*, char*, char* );
City* createCity( );
Neighbour* createNeighbour( );
void destroyCities( List* );
void destroyCity( City** );
void destroyNeighbour( Neighbour** );

#endif