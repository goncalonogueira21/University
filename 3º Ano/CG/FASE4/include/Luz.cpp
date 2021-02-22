#include "Luz.h"
#include <GL/glew.h>

void Luz::run() {

    float pos[4] = {x,y,z,0.0};

    float difLight[4] = {ambtR, ambtG, ambtB, 0.0};

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, difLight);

}