#include "engine.h"

using namespace std;


float lx = 5.0f, ly = 5.0f, lz = 5.0f; //coordenadas lookAt
float xx = 0.0f, yy = 0.0f, zz = 0.0f; // coordenadas da camara
float angle = 0.0f;
float scale =1.0f;
int draw = GL_FILL;
vector<Point> vertexes;


void renderScene(void){

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(lx,ly,lz, //todo: alterar aqui
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    //draw instructions

    glPolygonMode(GL_FRONT_AND_BACK,draw);

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

    glTranslatef(xx, yy, zz);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glScalef(scale,scale,scale);
    glBegin(GL_TRIANGLES);

    int i = 0;

    for(; i< vertexes.size(); i+=3) {

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(vertexes[i].x, vertexes[i].y, vertexes[i].z);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(vertexes[i+1].x, vertexes[i+1].y, vertexes[i+1].z);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(vertexes[i+2].x, vertexes[i+2].y, vertexes[i+2].z);

    }

    glEnd();
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
            angle -= 10;

            break;
        case 'd':
        case 'D':
            angle += 10;
            break;

        case 'w':
        case 'W':
            yy+=1;

            break;
        case 's':
        case 'S':
            yy-=1;
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


//método para ler o ficheiro e preencher vetor

void readFile(string fich){
    string linha;
    string novo;
    string delimiter = ",";
    int pos;
    float xx,yy,zz;
    Point p ;

    fich = "../models/" + fich;

    ifstream file(fich);

    if(file.is_open()){

        while(getline (file,linha)) {

            pos = linha.find(delimiter);
            novo = linha.substr(0, pos);
            xx = atof(novo.c_str());
            linha.erase(0, pos + delimiter.length());
            p.x = xx;

            pos = linha.find(delimiter);
            novo = linha.substr(0, pos);
            yy = atof(novo.c_str());
            linha.erase(0, pos + delimiter.length());
            p.y = yy;

            pos = linha.find(delimiter);
            novo = linha.substr(0, pos);
            zz = atof(novo.c_str());
            linha.erase(0, pos + delimiter.length());
            p.z = zz;

            vertexes.push_back(p);

        }

        file.close();


    }
    else {

        cout << "ERRO AO LER FICHEIRO" << endl;
    }
}

//método para ler ficheiro xml



//método para ler ficheiro xml

void xmlread(const char* pFilename){

    string a = "../scenes/";
    string c = a + pFilename;

    pFilename = c.c_str();

    TiXmlDocument doc(pFilename);

    bool loadOkay = doc.LoadFile();
    if (loadOkay)
    {
        TiXmlElement *root;
        root = doc.FirstChildElement();
        for(TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {

            string modelo = elem->Attribute("file");
            cout  << modelo << "lido com sucesso" << endl;
            readFile(modelo);
        }
    }
    else
    {
        printf("ERRO A LER XML\"%s\"\n", pFilename);
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
// OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main loop
    glutMainLoop();

    return 1;

}
