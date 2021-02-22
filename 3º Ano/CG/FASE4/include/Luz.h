
#ifndef TRABALHO_LUZ_H
#define TRABALHO_LUZ_H
#include "Operacao.h"


class Luz: public Operacao {

        float x;
        float y;
        float z;

        float ambtR;
        float ambtG;
        float ambtB;

    public:
        Luz(float x, float y, float z,float ambtR, float ambtG, float ambtB){
            this->x=x;
            this->y= y;
            this->z= z;
            this->ambtR=ambtR;
            this->ambtG= ambtG;
            this->ambtB= ambtB;
        };

        void run();


};

#endif