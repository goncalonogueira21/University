#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <vector>

#endif

#ifndef TRABALHO_TRANSLACAO_H
#define TRABALHO_TRANSLACAO_H

#include "Operacao.h"
#include "Ponto.h"

class Translacao: public Operacao{
    float x, y, z;
    float tempo;
    std::vector<Ponto> trans;
    std::vector<Ponto> pontosCatmull;
    float cima[3]{};

public:
    Translacao();
    Translacao(float x, float y, float z, float t, std::vector<Ponto> trans);
    float getX() {return this->x;}
    float getY() {return this->y;}
    float getZ() {return this->z;}
    float getTempo(){return this->tempo;}
    float* getCima(){return this->cima;}
    std::vector<Ponto> getTrans(){return this->trans;}
    std::vector<Ponto> getPontosCatmull(){return this->pontosCatmull;}
    void setX(float x){this->x=x;}
    void setY(float y){this->y=y;}
    void setZ(float z){this->z=z;}
    void setTempo(float x){ this->tempo = x;}
    void setTrans(std::vector<Ponto> t){ this->trans = t;}
    void setPontosCatmull(std::vector<Ponto> pC){ this->pontosCatmull = pC;}
    static void multMatrixVector(float* m, float* v, float* res);
    void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv);
    void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv);
    std::vector<Ponto> geraPontosCurva();
    void run();
};


#endif //TRABALHO_TRANSLACAO_H
