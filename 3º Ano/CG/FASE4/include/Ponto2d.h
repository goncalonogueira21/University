#ifndef TRABALHO_PONTO2D_H
#define TRABALHO_PONTO2D_H



class Ponto2d {
    float u;
    float v;

public:
    Ponto2d();
    Ponto2d(float a, float b);
    float getU() { return this->u; }
    float getV() { return this->v; }
    void setU( float b) { this->u = b; }
    void setV( float b) { this->v = b; }


};


#endif //TRABALHO_PONTO2D_H
