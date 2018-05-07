#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "grafo.h"

struct vertice {
    int id;
    char nome[20];
    float latitude, longitude;
};

struct grafo {
    Vertice *vertice;
    int numVertices;
    int **matAdjacencia;
};

Grafo* cria_grafo(int tam) {
    if(tam <= 0) printf("Erro, o grafo deve ter pelo menos um vertice.\n");
    else {
        int i;
        Grafo *g = (Grafo*) malloc(sizeof(Grafo));
        if(g != NULL) {
            g->vertice = (Vertice*) malloc(tam * sizeof(Vertice));
            if(g->vertice != NULL) {
                char strings[tam][50];
                FILE *f = fopen("nos.txt", "r+");
                if(f == NULL) {
                    printf("Erro ao abrir o arquivo nos.txt.\n");
                } else {
                    for(i = 0; i < tam; i++) {
                        fgets(strings[i], 50, f);
                    }
                    fclose(f);
                    for(i = 0; i < tam; i++) {
                        g->vertice[i].id = atoi(strtok(strings[i], ";"));
                        strcpy(g->vertice[i].nome, strtok(NULL, ";"));
                        g->vertice[i].latitude = atof(strtok(NULL, ";"));
                        g->vertice[i].longitude = atof(strtok(NULL, ";"));
                    }
                }
                g->matAdjacencia = (int**) malloc(tam * sizeof(int*));
                if(g->matAdjacencia != NULL) {
                    for(i = 0; i < tam; i++) {
                        g->matAdjacencia[i] = (int*) malloc(tam * sizeof(int));
                        if(g->matAdjacencia[i] != NULL) {
                            for(int j = 0; j < tam; j++) {
                                g->matAdjacencia[i][j] = 0;
                            }
                        }
                        else {
                            printf("Nao foi possivel alocar espaco na posicao %d, cancelando a alocacao das outras posicoes.\n", i);
                        }
                    }
                } else {
                    printf("Nao foi possivel alocar espaco para o vetor de ponteiros da matriz de adjacencia.\n");
                }
            } else {
                printf("Nao foi possivel alocar espaco para o vetor de vertices.\n");
            }
            g->numVertices = tam;
        } else {
            printf("Nao foi possivel alocar espaco para o grafo.\n");
        }
        return g;
    }
    return NULL;
}

void imprimeVertices(Grafo *g) {
    for(int i = 0; i < numVertices(g); i++)
        printf("id: %d\nnome: %s\nlatitude: %f\nlongitude: %f\n", g->vertice[i].id, g->vertice[i].nome, g->vertice[i].latitude, g->vertice[i].longitude);
}

int numVertices(Grafo *g) {
    //retorna -1 se for um grafo inválido
    if(g == NULL) {
        printf("Grafo invalido.\n");
        return -1;
    }
    return g->numVertices;
}

int insereAresta(Grafo *g, int v1, int v2, int peso) {
    if (g == NULL) {
        printf("Grafo invalido.\n");
        return -1;
    } else {
        printf("Tentando inserir uma aresta de peso %d entre os vertices %d e %d.\n", peso, v1, v2);
        g->matAdjacencia[v1][v2] = peso;
        return 1;
    }
}

int leArestas(Grafo *g) {
    int nlinhas = countlines("arestas.txt");
    char strings[nlinhas][20];
    FILE *f = fopen("arestas.txt", "r+");
    if(f == NULL)
        printf("Erro ao abrir o arquivo arestas.txt.\n");
    else {
        for(int i = 0; i <= nlinhas; i++) {
            fgets(strings[i], 20, f);
        }
        fclose(f);
        for(int i = 0; i < nlinhas; i++) {
            int v1 = atoi(strtok(strings[i], ";"));
            int v2 = atoi(strtok(NULL, ";"));
            int peso = atoi(strtok(NULL, ";"));
            insereAresta(g, v1, v2, peso);
        }
    }
    return 1;
}

void imprimeMatAdj(Grafo *g) {
    for(int i = 0; i < numVertices(g); i++) {
        for (int j = 0; j < numVertices(g); j++) {
            printf("%5d ", g->matAdjacencia[i][j]);
        }
        putchar('\n');
    }
}

int countlines(char *file) {
    int lines = 0;
    FILE *f = fopen(file, "r+");
    if(f == NULL)
        printf("Erro ao abrir o arquivo %s.\n", file);
    else {
        char ch;
        while(!feof(f)) {
            ch = fgetc(f);
            if(ch == '\n') {
                lines++;
            }
        }
        fclose(f);
    }
    return lines;
}
