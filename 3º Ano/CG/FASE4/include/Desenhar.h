#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "Ponto.h"
#include "Ponto2d.h"
#include "Operacao.h"

#ifndef TRABALHO_DESENHAR_H
#define TRABALHO_DESENHAR_H


class Desenhar: public Operacao{

    int vertexes;
    int nVBOVert;
    int nVBOText;
    int nVBONorm;

public:
    Desenhar(int vertexes, int nVBOVert, int nVBOText, int nVBONorm){
        this->vertexes=vertexes;
        this->nVBOVert= nVBOVert;
        this->nVBOText= nVBOText;
        this->nVBONorm=nVBONorm;
    };

    void run();

};


#endif //TRABALHO_DESENHAR_H
