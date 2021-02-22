#include <Luz.h>
#include "engine.h"

using namespace std;

float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

float posX=0.0f, posY = 0.0f, posZ = 0.0f;

int alpha = 0, beta = 45, r = 50;
float scale =1.0f;
float angle = 0.0f;

int draw = GL_FILL;
vector<Ponto> vertexes;
vector<Operacao*> ops;
vector<vector<float>> vertVBOs;
vector<vector<float>> texVBOs;
vector<vector<float>> normVBOs;
vector<string> texFiles;

int nVBOVert = 0;
int nVBOTex = 0;
int nVBONorm = 0;

GLuint *buffersVerts;
GLuint *buffersTextsCoords;
GLuint *buffersNorms;
GLuint *buffersTexID;

vector<Ponto> normal;
vector<Ponto2d> texturas;

void prepareVBOs(){
    //vertices
    buffersVerts = (GLuint*) malloc((sizeof(GLuint))*nVBOVert);
    //normais
    buffersNorms = (GLuint*) malloc((sizeof(GLuint))*nVBONorm);
    //textures
    buffersTextsCoords  = (GLuint*) malloc((sizeof(GLuint))*nVBOTex);

    //vbos dos vertices
    glGenBuffers(nVBOVert, buffersVerts);
    for(int i = 0; i < nVBOVert; ++i){

        glBindBuffer(GL_ARRAY_BUFFER,buffersVerts[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertVBOs[i].size(), vertVBOs[i].data(), GL_STATIC_DRAW);

    }

    //vbos das normais
    glGenBuffers(nVBONorm, buffersNorms);
    for(int i = 0; i < nVBONorm; ++i){

        glBindBuffer(GL_ARRAY_BUFFER,buffersNorms[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normVBOs[i].size(), normVBOs[i].data(), GL_STATIC_DRAW);

    }

    //vbos das texturas

    glGenBuffers(nVBOTex, buffersTextsCoords);
    for(int i = 0; i < nVBOTex; ++i){

        glBindBuffer(GL_ARRAY_BUFFER,buffersTextsCoords[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texVBOs[i].size(), texVBOs[i].data(), GL_STATIC_DRAW);

    }

}

int loadTex(std::string s) {

    unsigned int t,tw,th;
    unsigned char *texData;
    unsigned int texID;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1,&t);
    ilBindImage(t);
    ilLoadImage((ILstring)s.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    std::cout << s << std::endl;
    std::cout << tw << "Withd" << std::endl;
    std::cout << th << std::endl;
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1,&texID);

    glBindTexture(GL_TEXTURE_2D,texID);
    glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;

}

void loadTextures(){

    buffersTexID  = (GLuint*) malloc((sizeof(GLuint))*nVBOTex);

    for(int i = 0; i < nVBOTex; ++i){

        buffersTexID [i] = loadTex(texFiles[i]);

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

vector<float> ponto2DtoUV(vector<Ponto2d> p){
    vector<float> uv;

    for(int i=0; i<p.size();i++){
        uv.push_back(p[i].getU());
        uv.push_back(p[i].getV());
    }
    return uv;
}

void renderScene(void){

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camX,camY,camZ,
              0,0,0,
              0.0f,1.0f,0.0f);

    //draw instructions
    glTranslatef(posX, posY, posZ);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glScalef(scale,scale,scale);
    glPolygonMode(GL_FRONT_AND_BACK,draw);

    glEnable(GL_LIGHTING);


    // fazer as operações que estão no vetor de operações

    for(int i=0;i<ops.size();i++){
        ops[i]->run();
    }

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
            posZ-=1;
            break;
        case GLUT_KEY_DOWN:
            posZ+=1;
            break;
        case GLUT_KEY_LEFT:
            posX-=1;
            break;
        case GLUT_KEY_RIGHT:
            posX+=1;
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

void processMouseButtons(int button, int state, int xx, int yy) {

    if (state == GLUT_DOWN)  {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP) {
        if (tracking == 1) {
            alpha += (xx - startX);
            beta += (yy - startY);
        }
        else if (tracking == 2) {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }
}


void processMouseMotion(int xx, int yy) {

    int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {


        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }
    else if (tracking == 2) {

        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
    camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}




//método para ler o ficheiro e preencher vetor

void readFile(string fich){
    string linha;
    string novo;
    string delimiter = ",";
    int pos;
    float xx,yy,zz;
    Ponto p;
    Ponto2d pT;
    fich = "../models/" + fich;

    ifstream file(fich);

    if(file.is_open()){

        while(getline (file,linha) && (linha.compare("--texturas--")) != 0 && (linha.compare("--normais--")) != 0) {

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

        if ((linha.compare("--normais--")) == 0) {
            while (getline(file, linha) && (linha.compare("--texturas--")) != 0) {
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
                p.setZ(zz);

                normal.push_back(p);
            }
        }

        if ((linha.compare("--texturas--")) == 0) {
            while (getline(file, linha)) {
                pos = linha.find(delimiter);
                novo = linha.substr(0, pos);
                xx = atof(novo.c_str());
                linha.erase(0, pos + delimiter.length());
                pT.setU(xx);

                pos = linha.find(delimiter);
                novo = linha.substr(0, pos);
                yy = atof(novo.c_str());
                linha.erase(0, pos + delimiter.length());
                pT.setV(yy);



                texturas.push_back(pT);
            }
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
           // cout << "x=" << ptt.getX() << "y=" << ptt.getY() << "z=" << ptt.getZ() << endl;
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
        if (modelo->Attribute("textura")) cout <<"Textura encontrada " << modelo->Attribute("textura") << endl; //readFile(modelo->Attribute("textura"));
        //adicionado o nome do ficheiro ao vetor de texturas
        texFiles.push_back(modelo->Attribute("textura"));
        cout << "hello" << endl;
        //caso sem normais nem texturas
        if((normal.size()==0) && (texturas.size()==0)){
            ops.push_back(new Desenhar(vertexes.size(),nVBOVert++,-1,-1));
        }
        //caso sem texturas mas com normais
        else if((normal.size()>0) && (texturas.size() ==0)){
            ops.push_back(new Desenhar(vertexes.size(),nVBOVert++,-1,nVBONorm++));
        }
        //caso com texturas mas sem normais
        else if((normal.size()==0) && (texturas.size() >0)){
            ops.push_back(new Desenhar(vertexes.size(),nVBOVert++,nVBOTex++,-1));
        } //caso com texturas e normais
        else{
            ops.push_back(new Desenhar(vertexes.size(),nVBOVert++,nVBOTex++, nVBONorm++));
        }
        vertVBOs.push_back(ponto2XYZ(vertexes));
        normVBOs.push_back(ponto2XYZ(normal));
        texVBOs.push_back(ponto2DtoUV(texturas));
        cout << vertVBOs[0].size() << endl;
        cout << texVBOs[0].size() << endl;
        cout <<normVBOs[0].size() << endl;
        //nVBOVert++;
        vertexes.clear();//limpa o vector dos vertices
        normal.clear(); //limpa o vector das normais
        texturas.clear();//limpa o vector das texturas

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
float readFloat(std::string str)
{
    float ret = 0.0f;
    std::stringstream ss(str);

    ss >> ret;

    return ret;
}

std::string toLower(const char* str)
{
    std::string aux(str);

    std::transform(aux.begin(), aux.end(), aux.begin(), ::tolower);

    return aux;
}

void xmlreadLight(TiXmlElement* light)
{
    Ponto pos(0.0f, 0.0f, 1.0f);      // Posição da luz
    Ponto diff(1.0f, 1.0f, 1.0f);     // Cor difusa da luz
    Ponto spec(1.0f, 1.0f, 1.0f);     // Cor especular da luz
    Ponto ambt(0.0f, 0.0f, 0.0f);     // Cor ambiente da luz
    Ponto spotDir(0.0f, 0.0f, -1.0f); // Direção da spot light



    bool isPoint = false;
    bool isDirectional = false;
    bool isSpot = false;




    for (TiXmlAttribute* a = light->FirstAttribute(); a ; a = a->Next()) {



        if (!strcmp(a->Name(), "posX")) {
            pos.setX(readFloat(a->Value()));

        }
        else if (!strcmp(a->Name(), "posY")) {
            pos.setY(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "posZ")) {
            pos.setZ(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "diffR")) {
            diff.setX(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "diffG")) {
            diff.setY(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "diffB")) {
            diff.setZ(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "specR")) {
            spec.setX(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "specG")) {
            spec.setY(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "specB")) {
            spec.setZ(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "ambtR")) {
            ambt.setX(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "ambtG")) {
            ambt.setY(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "ambtB")) {
            ambt.setZ(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "spotDirX")) {
            spotDir.setX(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "spotDirY")) {
            spotDir.setY(readFloat(a->Value()));
        }
        else if (!strcmp(a->Name(), "spotDirZ")) {
            spotDir.setZ(readFloat(a->Value()));
        }

        else if (!strcmp(a->Name(), "type")) {


            if (!strcmp(a->Value(),"POINT")) {
                isPoint = true;


            }
            else if (!strcmp(a->Value(), "DIRECTIONAL")){
                isDirectional = true;

            }
            else if (!strcmp(a->Value(), "SPOT")) {
                isSpot = true;

            }

        }

    }


    if (isPoint) {

        ops.push_back(new Luz(pos.getX(),pos.getY(),pos.getZ(),ambt.getX(), ambt.getY(), ambt.getZ()));


    }
    else if (isDirectional) {


    }
    else if (isSpot) {



    }

}

void parseLights(TiXmlElement* lights)
{

    for (TiXmlElement* light = lights->FirstChildElement(); light ;light = light->NextSiblingElement()) {

        std::string lightName(toLower(light->Value()));

        if (lightName == "light") {

            xmlreadLight(light);

        }
        else {

            cout << "problema no xml com as luzes" << endl;
        }
    }
}


void xmlread(const char* pFilename) {
    string a = "../scenes/";
    string c = a + pFilename;
    pFilename = c.c_str();
    TiXmlDocument doc(pFilename);
    string tipoluz;
	float isPoint = 0;
	float luzX, luzY, luzZ;

    bool loadOkay = doc.LoadFile();
    if (loadOkay){

        TiXmlElement * scene = doc.FirstChildElement("scene");
        TiXmlElement * group = scene-> FirstChildElement("group");
        TiXmlElement * luzes = scene-> FirstChildElement("lights");
        parseLights(luzes);
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
    glutInitWindowSize(1500,800);
    glutCreateWindow("CG_Project");

// put callback registration here
    glutDisplayFunc( renderScene );
    glutReshapeFunc( reshape );
    glutIdleFunc( renderScene);
    glutSpecialFunc(keyboardspecial);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);


#ifndef __APPLE__
    glewInit();
#endif

// OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    //glClearColor(0, 0, 0, 0);
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    //glEnable(GL_TEXTURE_2D);

    prepareVBOs();
    loadTextures();

// enter GLUT's main loop
    glutMainLoop();

    return 1;

}