#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main()
{
    //FILE *f = fopen("nos.txt", "r+");
    //char strings[26][50];
    //for(int i = 0; i < 26; i++) {
        //fgets(strings[i], sizeof(strings[i]), f);
    //}
    //fclose(f);
    //for(int i = 0; i < 26; i++) {
        //printf("%s", strings[i]);
    //}
    Grafo *g = cria_grafo(26);
    leArestas(g);
    imprimeMatAdj(g);
    //imprimeVertices(g);
    //printf("%d", countlines("arestas.txt"));
    return 0;
}
