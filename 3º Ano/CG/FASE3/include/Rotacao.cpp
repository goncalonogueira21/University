#include "Rotacao.h"

Rotacao :: Rotacao (){
   this->angle= this->x= this->y=this->z=this->tempo=0.0;
}

Rotacao:: Rotacao (float tempo, float angle, float x, float y, float z){
    this->tempo=tempo;
    this->angle=angle;
    this->x = x;
    this->y = y;
    this->z = z;
}

void Rotacao::run() {

    if((int)tempo==0){
        glRotatef(this->angle, this->x, this->y, this->z);
    }
    else{
        float rAux = glutGet(GLUT_ELAPSED_TIME) % ((int) tempo * 1000);
        float r = (rAux*360) / (tempo*1000);
        glRotatef(r,x,y,z);

    }
}