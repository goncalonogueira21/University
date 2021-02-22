#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <IL/il.h>

#include <sstream>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "tinyxml.cpp"
#include "tinyxml.h"
#include "tinyxmlerror.cpp"
#include "tinyxmlparser.cpp"
#include "tinystr.cpp"
#include "tinystr.h"
#include "Operacao.h"
#include "Translacao.h"
#include "Rotacao.h"
#include "Escala.h"
#include "Cor.h"
#include "Push.h"
#include "Pop.h"
#include "Desenhar.h"

extern GLuint *buffersVerts;
extern GLuint *buffersTextsCoords;
extern GLuint *buffersNorms;
extern GLuint *buffersTexID;

