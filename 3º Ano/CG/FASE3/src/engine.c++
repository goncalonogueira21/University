#include "engine.h"

using namespace std;

float alpha = 0;
float beta = 0.5;
float radius = 40;
float xx = 0.0f, yy = 0.0f, zz = 0.0f;
float angle = 0.0f;
float scale =1.0f;
int draw = GL_FILL;
vector<Ponto> vertexes;
vector<Operacao*> ops;
vector<vector<float>> vertVBOs;
int nVBOS = 0;
GLuint *buffers;
int iVBO=0;

void prepareVBOs(){

    buffers = (GLuint*) malloc((sizeof(GLuint))*nVBOS);
    glGenBuffers(nVBOS, buffers);

    for(int i = 0; i < nVBOS; ++i){

        glBindBuffer(GL_ARRAY_BUFFER,buffers[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertVBOs[i].size(), vertVBOs[i].data(), GL_STATIC_DRAW);

    }
}

vector<float> ponto2XYZ(vector<Ponto> p){
    vector<float> xyz;

    for(int i=0; i<p.size();i++){
        xyz.push_back(p[i].getX());
        xyz.push_back(p[i].getY());
        xyz.push_back(p[i].getZ());
    }
    return xyz;
}

void renderScene(void){

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(radius*cos(beta)*sin(alpha),radius*sin(beta),radius*cos(beta)*cos(alpha),
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    //draw instructions

    glPolygonMode(GL_FRONT_AND_BACK,draw);
/*
    glBegin(GL_LINES);
// X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);
// Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
// Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
*/
    glTranslatef(xx, yy, zz);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glScalef(scale,scale,scale);

    // fazer as operações que estão no vetor de operações

    for(int i=0;i<ops.size();i++){
        ops[i]->run();
    }
    iVBO=0;

    glutSwapBuffers();


}
void reshape(int w, int h){
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;
    float ratio = w *1.0 / h;
    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}
void keyboardspecial(int key, int x , int y){
    switch(key){
        case GLUT_KEY_UP:
            zz-=1;
            break;
        case GLUT_KEY_DOWN:
            zz+=1;
            break;
        case GLUT_KEY_LEFT:
            xx-=1;
            break;
        case GLUT_KEY_RIGHT:
            xx+=1;
            break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int a, int b) {
    switch (key) {
        case 'a':
        case 'A':
            alpha -= 0.1;

            break;
        case 'd':
        case 'D':
            alpha += 0.1;
            break;

        case 'w':
        case 'W':
            beta+=0.1;
            if(beta>1.5)beta=1.5;
            break;
        case 's':
        case 'S':
            beta-=0.1;
            if(beta<-1.5)beta=-1.5;
            break;

        case 'p':
        case 'P':
            draw = GL_POINT;
            break;

        case 'l':
        case 'L':
            draw = GL_LINE;
            break;

        case 'f':
        case 'F':
            draw = GL_FILL;
            break;

        case '-':
            scale-=0.1;
            break;

        case '+':
            scale+=0.1;
            break;

    }
    glutPostRedisplay();
}

void mouse (int button, int state, int x, int y){
    if(button==GLUT_LEFT_BUTTON){
        radius+=5.0;
        glutPostRedisplay();
    }
    if(button==GLUT_RIGHT_BUTTON){
        radius-=5.0;
        if(radius<0.0)radius=0.0;
        glutPostRedisplay();
    }

}

//método para ler o ficheiro e preencher vetor

void readFile(string fich){
    string linha;
    string novo;
    string delimiter = ",";
    int pos;
    float xx,yy,zz;
    Ponto p;

    fich = "../models/" + fich;

    ifstream file(fich);

    if(file.is_open()){

        while(getline (file,linha)) {

            pos = linha.find(delimiter);
            novo = linha.substr(0, pos);
            xx = atof(novo.c_str());
            linha.erase(0, pos + delimiter.length());
            p.setX(xx);

            pos = linha.find(delimiter);
            novo = linha.substr(0, pos);
            yy = atof(novo.c_str());
            linha.erase(0, pos + delimiter.length());
            p.setY(yy);

            pos = linha.find(delimiter);
            novo = linha.substr(0, pos);
            zz = atof(novo.c_str());
            linha.erase(0, pos + delimiter.length());
            p.setZ(zz) ;

            vertexes.push_back(p);

        }

        file.close();


    }
    else {

        cout << "ERRO AO LER FICHEIRO" << endl;
    }
}

//método para ler um  xml group

void xmlreadGroup(TiXmlElement *group) {

    float px,py,pz,tlX, tlY, tlZ,timeT, angRo, esX, esY, esZ , roX, roY, roZ, timeR, coR, coG, coB;

    if (strcmp(group->FirstChildElement()->Value(), "group") == 0) {
        group = group->FirstChildElement();
    }

    ops.push_back(new Push());

    for (TiXmlElement *t = group->FirstChildElement(); (strcmp(t->Value(), "models") !=0); t = t->NextSiblingElement()) {

        if (!strcmp(t->Value(), "translate")) {
            const char *a1 = t->Attribute("X");
            const char *a2 = t->Attribute("Y");
            const char *a3 = t->Attribute("Z");
            const char *a4 = t->Attribute("time");

            if (a1) {
                tlX = stof(a1);
            } else tlX = 0;

            if (a2) {
                tlY = stof(a2);
            } else tlY = 0;

            if (a3) {
                tlZ = stof(a3);
            } else tlZ = 0;

            if (a4) {
                timeT = stof(a4);
            } else timeT = 0;

            std::vector<Ponto> pTrans;

            for(TiXmlElement* pt = t->FirstChildElement("point"); pt ; pt = pt->NextSiblingElement("point")){

            const char *a5 = pt->Attribute("X");
            const char *a6 = pt->Attribute("Y");
            const char *a7 = pt->Attribute("Z");

              if (a5) {
                px = stof(a5);
            } else px = 0;

            if (a6) {
                py = stof(a6);
            } else py = 0;

            if (a7) {
                pz = stof(a7);
            } else pz = 0;
            
            

            Ponto ptt = Ponto(px,py,pz);
            cout << "x=" << ptt.getX() << "y=" << ptt.getY() << "z=" << ptt.getZ() << endl;
            pTrans.push_back(ptt);

        }

            ops.push_back(new Translacao(tlX, tlY, tlZ,timeT,pTrans));
        }
        if (!strcmp(t->Value(), "rotate")) {
        	const char *a8=t->Attribute("time");
            const char *a9=t->Attribute("angle");

            if (a8) {
                timeR = stof(a8);
            } else timeR = 0;

            if (a9) {
                angRo = stof(a9);
            } else angRo = 0;

            roX = stof(t->Attribute("X"));
            roY = stof(t->Attribute("Y"));
            roZ = stof(t->Attribute("Z"));

            ops.push_back(new Rotacao(timeR,angRo, roX, roY, roZ));

        }
        if (!strcmp(t->Value(), "scale")) {
            esX = stof(t->Attribute("X"));
            esY = stof(t->Attribute("Y"));
            esZ = stof(t->Attribute("Z"));

            ops.push_back(new Escala(esX, esY, esZ));

        }
        if (!strcmp(t->Value(), "color")) {
            coR = stof(t->Attribute("R"));
            coG = stof(t->Attribute("G"));
            coB = stof(t->Attribute("B"));
            ops.push_back(new Cor(coR, coG, coB));
        }
    }

    for (TiXmlElement *modelo = group->FirstChildElement("models")->FirstChildElement("model"); modelo; modelo = modelo->NextSiblingElement("model")) {

        cout <<"Ficheiro " << modelo->Attribute("file") << " aberto" << endl;
        readFile(modelo->Attribute("file"));// lê as coordenados dos vertices gerados pelo gerador

        ops.push_back(new Desenhar(vertexes.size()));
        vertVBOs.push_back(ponto2XYZ(vertexes));
        nVBOS++;
        vertexes.clear();//limpa o vector dos vertices

    }
    // child parsing
    if(group->FirstChildElement("group")){
        xmlreadGroup(group->FirstChildElement("group"));
    }

    ops.push_back(new Pop());

    //brother parsing
    if(group->NextSiblingElement("group")){
        xmlreadGroup(group->NextSiblingElement("group"));

    }


}


void xmlread(const char* pFilename) {
    string a = "../scenes/";
    string c = a + pFilename;
    pFilename = c.c_str();
    TiXmlDocument doc(pFilename);

    bool loadOkay = doc.LoadFile();
    if (loadOkay){

        TiXmlElement * scene = doc.FirstChildElement("scene");
        TiXmlElement * group = scene-> FirstChildElement("group");

        xmlreadGroup(group);
    }else {
        cout << "Ficheiro XML não foi encontrado" << endl;
    }
}

int main(int argc, char** argv) {


    if (argc > 1){
        xmlread(argv[1]);
    }

//init glut and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG_Project");

// put callback registration here
    glutDisplayFunc( renderScene );
    glutReshapeFunc( reshape );
    glutIdleFunc( renderScene);
    glutSpecialFunc(keyboardspecial);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

#ifndef __APPLE__
    glewInit();
#endif
    glEnableClientState(GL_VERTEX_ARRAY);

// OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    prepareVBOs();

// enter GLUT's main loop
    glutMainLoop();

    return 1;

}