#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <sstream>
using namespace std;

//class para guardar os parametros de um ponto de controlo
class Point{
public: float x,y,z;
};

class TPoint{
public: float x,y;
};

float PontoFloat[3];

void generateBox(float x, float y, float z, string nome);
void generateBoxDiv(float x, float y, float z,int div, string nome);
string polarToCart(float radius, float alpha, float beta, float pDouble[3]);
void generateSphere(float radius, int slices, int stacks, string nome);
void generatePlane(float x, string nome);
void generateCone(float radius, float height, int slices, int stacks, string nome);
string polarToCartCone(float radius, float height, float alpha, float pDouble[3]);
void generatePatch(string patchfile, int tesselation, string filesave);

int main(int argc, char* argv[]){
    
    string obj = argv[1];
    if(obj.compare("plane")==0){
    	if(argc != 4){
    		cout << "Nº de argumentos errado\n";
    		return 0;
    	}
    	else{
    		generatePlane(stof(argv[2]),argv[3]);
    	}
    }
    else if(obj.compare("box")==0){
    	if(argc != 6 && argc != 7){
    		cout << "Nº de argumentos errado\n";
    		return 0;
    	}
    	else if(argc==6){
    		generateBox(stof(argv[2]),stof(argv[3]),stof(argv[4]),argv[5]);
    	}
    	else{
    		generateBoxDiv(stof(argv[2]),stof(argv[3]),stof(argv[4]),stoi(argv[5]),argv[6]);
    	}
    }
    else if(obj.compare("sphere")==0){
    	if(argc != 6){
    		cout << "Nº de argumentos errado\n";
    		return 0;
    	}
    	else{
    		generateSphere(stof(argv[2]),stoi(argv[3]),stoi(argv[4]),argv[5]);
    	}
    }
    else if(obj.compare("cone")==0){
    	if(argc != 7){
    		cout << "Nº de argumentos errado\n";
    		return 0;
    	}
    	else{
    		generateCone(stof(argv[2]),stof(argv[3]),stoi(argv[4]),stoi(argv[5]),argv[6]);
    	}
    }
    else if(obj.compare("patch")==0){
        if(argc != 5){
            cout << "Nº de argumentos errado\n";
            return 0;
        }
        else{
            generatePatch(argv[2],stof(argv[3]),argv[4]);
        }
    }
    else{
    	cout << "Comando não reconhecido\n";
    }


    return 0;
}


void generatePlane(float x, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);

	file << -x << ", " << 0 << ", " << -x << "\n";
	file << -x << ", " << 0 << ", " << x << "\n";
	file << x << ", " << 0 << ", " << x << "\n";
	file << -x << ", " << 0 << ", " << -x << "\n";
	file << x << ", " << 0 << ", " << x << "\n";
	file << x << ", " << 0 << ", " << -x << "\n";
	file << "--normais--" << "\n";
    file << 0 << ", " << 1 << ", " << 0 << "\n";
    file << 0 << ", " << 1 << ", " << 0 << "\n";
    file << 0 << ", " << 1 << ", " << 0 << "\n";
    file << 0 << ", " << 1 << ", " << 0 << "\n";
    file << 0 << ", " << 1 << ", " << 0 << "\n";
    file << 0 << ", " << 1 << ", " << 0 << "\n";
    file << "--texturas--" << "\n";
    file << 0 << ", " << 0 << "\n";
    file << 0 << ", " << 1 << "\n";
    file << 1 << ", " << 1 << "\n";
    file << 0 << ", " << 0 << "\n";
    file << 1 << ", " << 1 << "\n";
    file << 1 << ", " << 0 << "\n";


	file.close();
}

void generateBox(float x, float y, float z, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);

	float xx=x/2;
	float yy=y/2;
	float zz=z/2;


	vector<Point> normal;
	vector<TPoint> textures;

	// face trás
	file << xx << ", " << yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << -xx << ", " << yy << ", " << -zz << "\n";
    Point p;
    TPoint t;
    p.x=0; p.y=0; p.z=-1;
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    t.x=0.75; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=0.75; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=1; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.75; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=1; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=1; t.y=(2.0f/3.0f);
    textures.push_back(t);
	
	// face cima
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << yy << ", " << -zz << "\n";
    p.x=0; p.y=1; p.z=0;
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    t.x=0.25; t.y=1;
    textures.push_back(t);
    t.x=0.25; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=0.5; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=0.25; t.y=1;
    textures.push_back(t);
    t.x=0.5; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=0.5; t.y=1;
    textures.push_back(t);
	// face frente
	file << -xx << ", " << yy << ", " << zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
    p.x=0; p.y=0; p.z=1;
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    t.x=0.25; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=0.25; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.5; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.25; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=0.5; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.5; t.y=(2.0f/3.0f);
    textures.push_back(t);
	// face baixo
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
    p.x=0; p.y=-1; p.z=0;
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    t.x=0.25; t.y=0;
    textures.push_back(t);
    t.x=0.5; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.25; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.25; t.y=0;
    textures.push_back(t);
    t.x=0.5; t.y=0;
    textures.push_back(t);
    t.x=0.5; t.y=(1.0f/3.0f);
    textures.push_back(t);
	// face esquerda
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << zz << "\n";
    p.x=-1; p.y=0; p.z=0;
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    t.x=0; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=0; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.25; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=0.25; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.25; t.y=(2.0f/3.0f);
    textures.push_back(t);
	// direita
	file << xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << -zz << "\n";
    p.x=1; p.y=0; p.z=0;
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    normal.push_back(p);
    t.x=0.5; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=0.5; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.75; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.5; t.y=(2.0f/3.0f);
    textures.push_back(t);
    t.x=0.75; t.y=(1.0f/3.0f);
    textures.push_back(t);
    t.x=0.75; t.y=(2.0f/3.0f);
    textures.push_back(t);

    file << "--normais--" << "\n";


    for(int i=0;i<normal.size();i++){
        file << normal[i].x << ", " << normal[i].y << ", " << normal[i].z << "\n";
    }
	
	file << "--texturas--" << "\n";

	for(int i=0;i<textures.size();i++){
        file << textures[i].x << ", " << textures[i].y << "\n";
    }


	file.close();
}

void generateBoxDiv(float x, float y, float z, int div, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);

	float xx = x/-2;
	float yy = y/-2;
	float zz = z/-2;
	float incX = x/div;
	float incY = y/div;
	float incZ = z/div;
	float textX = 0.25 / div;
	float textY = (1.0f/3.0f)/div;
	vector<Point> normais;
	vector<TPoint> texturas;
	float xfrente = 0.25;
	float yfrente = (1.0f/3.0f);

	//frente
	for (int i = 0; i < div; ++i){
		
		for (int j = 0; j < div; ++j)
		{
			
			file << xx+incX*j << ", " << yy+incY*(i+1) << ", " << -zz << "\n";
			file << xx+incX*(j) << ", " << yy+incY*(i) << ", " << -zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i) << ", " << -zz << "\n";
			file << xx+incX*j << ", " << yy+incY*(i+1) << ", " << -zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i) << ", " << -zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i+1) << ", " << -zz << "\n";
			Point p;
			p.x=0; p.y=0; p.z=1;
			normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            TPoint t;
            t.x=xfrente; t.y=yfrente+textY;
            texturas.push_back(t);
            t.x=xfrente; t.y=yfrente;
            texturas.push_back(t);
            t.x=xfrente+textX; t.y=yfrente;
            texturas.push_back(t);
            t.x=xfrente; t.y=yfrente+textY;
            texturas.push_back(t);
            t.x=xfrente+textX; t.y=yfrente;
            texturas.push_back(t);
            t.x=xfrente+textX; t.y=yfrente+textY;
            texturas.push_back(t);

            xfrente+=textX;

		}
		yfrente+=textY;
	}

	float xtras=0.75;
	float ytras=(1.0f/3.0f);
	//trás
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
			file << xx+incX*j << ", " << yy+incY*(i+1) << ", " << zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i) << ", " << zz << "\n";
			file << xx+incX*(j) << ", " << yy+incY*(i) << ", " << zz << "\n";
			file << xx+incX*j << ", " << yy+incY*(i+1) << ", " << zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i+1) << ", " << zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i) << ", " << zz << "\n";
            Point p;
            p.x=0; p.y=0; p.z=-1;
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            TPoint t;
            t.x=xtras+textX; t.y=ytras+textY;
            texturas.push_back(t);
            t.x=xtras; t.y=ytras;
            texturas.push_back(t);
            t.x=xtras+textX; t.y=ytras;
            texturas.push_back(t);
            t.x=xtras+textX; t.y=ytras+textY;
            texturas.push_back(t);
            t.x=xtras; t.y=ytras+textY;
            texturas.push_back(t);
            t.x=xtras; t.y=ytras;
            texturas.push_back(t);

            xtras+=textX;
		}
		ytras+=textY;
	}

	float xesquerda = 0;
	float yesquerda = (1.0f/3.0f);

	//esquerda
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
			file << xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*j << "\n";
			file << xx << ", " << yy+incY*(i) << ", " << zz+incZ*j << "\n";
			file << xx << ", " << yy+incY*(i) << ", " << zz+incZ*(j+1) << "\n";
			file << xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*j << "\n";
			file << xx << ", " << yy+incY*(i) << ", " << zz+incZ*(j+1) << "\n";
			file << xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*(j+1) << "\n";
            Point p;
            p.x=-1; p.y=0; p.z=0;
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            TPoint t;
            t.x=xesquerda; t.y=yesquerda+textY;
            texturas.push_back(t);
            t.x=xesquerda; t.y=yesquerda;
            texturas.push_back(t);
            t.x=xesquerda+textX; t.y=yesquerda;
            texturas.push_back(t);
            t.x=xesquerda; t.y=yesquerda+textY;
            texturas.push_back(t);
            t.x=xesquerda+textX; t.y=yesquerda;
            texturas.push_back(t);
            t.x=xesquerda+textX; t.y=yesquerda+textY;
            texturas.push_back(t);

            xesquerda+=textX;
		}
		yesquerda+=textY;
	}			

	float xdireita=0.5;
	float ydireita=(1.0f/3.0f);

	//direita
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
		file << -xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*j << "\n";
		file << -xx << ", " << yy+incY*(i) << ", " << zz+incZ*(j+1) << "\n";
		file << -xx << ", " << yy+incY*(i) << ", " << zz+incZ*j << "\n";
		file << -xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*j << "\n";
		file << -xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*(j+1) << "\n";
		file << -xx << ", " << yy+incY*(i) << ", " << zz+incZ*(j+1) << "\n";
		Point p;
		p.x=1; p.y=0; p.z=0;
		normais.push_back(p);
		normais.push_back(p);
		normais.push_back(p);
		normais.push_back(p);
		normais.push_back(p);
		normais.push_back(p);
		TPoint t;
        t.x=xdireita+textX; t.y=ydireita+textY;
        texturas.push_back(t);
        t.x=xdireita; t.y=ydireita;
        texturas.push_back(t);
        t.x=xdireita+textX; t.y=ydireita;
        texturas.push_back(t);
        t.x=xdireita+textX; t.y=ydireita+textY;
        texturas.push_back(t);
        t.x=xdireita; t.y=ydireita+textY;
        texturas.push_back(t);
        t.x=xdireita; t.y=ydireita;
        texturas.push_back(t);

        xdireita+=textX;
		}
		ydireita+=textY;
	}	

	float xcima=0.25;
	float ycima=(2.0f/3.0f);
	//cima
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
			file << xx+incX*(j+1) << ", " << -yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*j << ", " << -yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*(j) << ", " << -yy << ", " << zz+incZ*(i+1) << "\n";
			file << xx+incX*(j+1) << ", " << -yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*j << ", " << -yy << ", " << zz+incZ*(i+1) << "\n";
			file << xx+incX*(j+1) << ", " << -yy << ", " << zz+incZ*(i+1) << "\n";
            Point p;
            p.x=0; p.y=1; p.z=0;
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            TPoint t;
            t.x=xcima+textX; t.y=ycima+textY;
            texturas.push_back(t);
            t.x=xcima; t.y=ycima+textY;
            texturas.push_back(t);
            t.x=xcima; t.y=ycima;
            texturas.push_back(t);
            t.x=xcima+textX; t.y=ycima+textY;
            texturas.push_back(t);
            t.x=xcima; t.y=ycima;
            texturas.push_back(t);
            t.x=xcima+textX; t.y=ycima;
            texturas.push_back(t);

            xcima+=textX;
		}
		ycima+=textY;
	}		

	float xbaixo=0.25;
	float ybaixo=0;
	//baixo
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
			file << xx+incX*(j+1) << ", " << yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*(j) << ", " << yy << ", " << zz+incZ*(i+1) << "\n";
			file << xx+incX*j << ", " << yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*(j+1) << ", " << yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*(j+1) << ", " << yy << ", " << zz+incZ*(i+1) << "\n";
			file << xx+incX*j << ", " << yy << ", " << zz+incZ*(i+1) << "\n";
            Point p;
            p.x=0; p.y=-1; p.z=0;
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            normais.push_back(p);
            TPoint t;
            t.x=xbaixo+textX; t.y=ybaixo;
            texturas.push_back(t);
            t.x=xbaixo; t.y=ybaixo+textY;
            texturas.push_back(t);
            t.x=xbaixo; t.y=ybaixo;
            texturas.push_back(t);
            t.x=xbaixo+textX; t.y=ybaixo;
            texturas.push_back(t);
            t.x=xbaixo+textX; t.y=ybaixo+textY;
            texturas.push_back(t);
            t.x=xbaixo; t.y=ybaixo+textY;
            texturas.push_back(t);

            xbaixo+=textX;
		}
		ybaixo+=textY;
	}
	        file << "--normais--" << "\n";
	for(int i=0;i<normais.size();i++){
	    file << normais[i].x << ", " << normais[i].y << ", " << normais[i].z << "\n";
	}

            file << "--texturas--" << "\n";
	for(int i=0;i<texturas.size();i++){
	    file << texturas[i].x << ", " << texturas[i].y << "\n";
	}

	file.close();
}

void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

void cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void generateSphere(float radius, int slices, int stacks, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);
	
	float alpha = 0.0f;
	float beta = M_PI/-2;

	float sliceSize = 2*M_PI/slices;
	float stackSize = M_PI/stacks;

    //text
    float U = 0;
    float V=0;
    float incU = 1.0f / slices;
    float incV = 1.0f / stacks;

    vector<Point> normais;
    vector<TPoint> texturas;
    float p1[3],p2[3],p3[3];
    float res[3];
    Point p;
    TPoint t;

    float texV=1/(float) slices;
    float texH=1/ (float) stacks;
	//inicio da construção
	
	for(int i = 0; i < stacks; ++i){
		for (int j = 0; j < slices; ++j)
		{
			//file << "glColor3f(1.0f, 0.0f, 0.0f);\n";
			file << polarToCart(radius, alpha, beta, p1);
            file << polarToCart(radius, alpha, beta + stackSize, p2);
            file << polarToCart(radius, alpha + sliceSize, beta, p3);
            //normais
            normalize(p1);
            normalize(p2);
            normalize(p3);
            p.x=p1[0];
            p.y=p1[1];
            p.z=p1[2];
            normais.push_back(p);
            p.x=p2[0];
            p.y=p2[1];
            p.z=p2[2];
            normais.push_back(p);
            p.x=p3[0];
            p.y=p3[1];
            p.z=p3[2];
            normais.push_back(p);

            //calcular normal
            //float v1[3]={p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2]};
            //float v2[3]={p3[0]-p1[0],p3[1]-p1[1],p3[2]-p1[2]};

            //cross(v1,v2,res);

            //normalize(res);

            //p.x=res[0];
            //p.y=res[1];
            //p.z=res[2];

            //normais.push_back(p);

            t.x= U; t.y= V;
            texturas.push_back(t);
            t.x= U; t.y= V+incV;
            texturas.push_back(t);
            t.x=U+incU; t.y= V;
            texturas.push_back(t);

			//file << "glColor3f(0.0f, 0.0f, 1.0f);\n";
			file << polarToCart(radius, alpha, beta + stackSize, p1);
			file << polarToCart(radius, alpha + sliceSize, beta + stackSize, p2);
			file << polarToCart(radius, alpha + sliceSize, beta, p3);

            normalize(p1);
            normalize(p2);
            normalize(p3);
            p.x=p1[0];
            p.y=p1[1];
            p.z=p1[2];
            normais.push_back(p);
            p.x=p2[0];
            p.y=p2[1];
            p.z=p2[2];
            normais.push_back(p);
            p.x=p3[0];
            p.y=p3[1];
            p.z=p3[2];
            normais.push_back(p);

            //float v3[3]={p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2]};
            //float v4[3]={p3[0]-p1[0],p3[1]-p1[1],p3[2]-p1[2]};

            //cross(v3,v4,res);

            //normalize(res);

            //p.x=res[0];
            //p.y=res[1];
            //p.z=res[2];

            //normais.push_back(p);

            t.x= U; t.y= V+incV;
            texturas.push_back(t);
            t.x= U+incU; t.y= V+incV;
            texturas.push_back(t);
            t.x=U+incU; t.y= V;
            texturas.push_back(t);

			alpha+=sliceSize;
			U+=incU;
		}
		beta+=stackSize;
		V+=incV;
		alpha=0;
		U=0.0f;
	}

	file << "--normais--" << "\n";

	for(int i=0; i<normais.size(); i++){
	    file << normais[i].x << ", " << normais[i].y << ", " << normais[i].z << "\n";
	}

	file << "--texturas--" << "\n";

	for(int i=0; i<texturas.size();i++){
	    file << texturas[i].x << ", " << texturas[i].y << "\n";
	}

	file.close();
}

void generateCone(float radius, float height, int slices, int stacks, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);

	float stackSize = height/stacks;
	float sliceSize = 2*M_PI/slices;
	float tetaNext;
	float alpha = 0.0f;
	float r = 0.0f;
	float rUp = 0.0f;
	float yy= height/-2;
	vector<Point> normais;
	vector<TPoint> texturas;
	float p1[3];
	float p2[3];
	float p3[3];
    float res[3];
    Point p;
    TPoint t;

    //base
	for(int i=0;i<slices;i++){
	    alpha = i*sliceSize;

	    file << polarToCartCone(0, yy, 0, p1);
        file << polarToCartCone(radius, yy, alpha + sliceSize, p2);
        file << polarToCartCone(radius, yy, alpha, p3);
        p.x=0; p.y=-1;p.z=0;
        normais.push_back(p);
        normais.push_back(p);
        normais.push_back(p);

        t.x=0.25f; t.y=0.5f;
        texturas.push_back(t);
        t.x=(0.25f+cos(alpha+sliceSize)/4.0f); t.y=(0.5f + sin(alpha+sliceSize) / 2.0f);
        texturas.push_back(t);
        t.x=(0.25f + cos(alpha) / 4.0f); t.y=(0.5f + sin(alpha) / 2.0f);
        texturas.push_back(t);




	}

	for(int i = 0; i < stacks; i++){


        r=(((float)stacks-i)/stacks)*radius;
        rUp=(((float)stacks-(i+1))/stacks)*radius;
        for(int j = 0; j < slices; j++){

            alpha=j*sliceSize;

            file << polarToCartCone(rUp, yy + stackSize * (i + 1), alpha, p1);
            file << polarToCartCone(r, yy + stackSize * i, alpha, p2);
            file << polarToCartCone(r, yy + stackSize * i, alpha + sliceSize, p3);

            float v1[3]={p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2]};
            float v2[3]={p3[0]-p1[0],p3[1]-p1[1],p3[2]-p1[2]};

            cross(v1,v2,res);

            normalize(res);

            p.x=res[0];
            p.y=res[1];
            p.z=res[2];

            normais.push_back(p);

            file << polarToCartCone(rUp, yy + stackSize * (i + 1), alpha, p1);
            file << polarToCartCone(r, yy + stackSize * i, alpha + sliceSize, p2);
            file << polarToCartCone(rUp, yy + stackSize * (i + 1), alpha + sliceSize, p3);

            float v3[3]={p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2]};
            float v4[3]={p3[0]-p1[0],p3[1]-p1[1],p3[2]-p1[2]};
            cross(v3,v4,res);

            normalize(res);

            p.x=res[0];
            p.y=res[1];
            p.z=res[2];

            normais.push_back(p);

            float res = (float) (stacks-i) / stacks;
            float resplus = (float) (stacks-(i+1)) / stacks;

            t.x=(0.75f + 0.25f * cos(alpha) * resplus); t.y=(0.5f + 0.5f * sin(alpha) * resplus);
            texturas.push_back(t);
            t.x=(0.75f + 0.25f * cos(alpha) * res); t.y=(0.5f + 0.5f * sin(alpha) * res);
            texturas.push_back(t);
            t.x=(0.75f + 0.25f * cos(alpha + sliceSize) * res); t.y=(0.5f + 0.5f * sin(alpha + sliceSize) * res);
            texturas.push_back(t);
            t.x=(0.75f + 0.25f * cos(alpha) * resplus); t.y=(0.5f + 0.5f * sin(alpha) * resplus);
            texturas.push_back(t);
            t.x=(0.75f + 0.25f * cos(alpha + sliceSize) * res); t.y=(0.5f + 0.5f * sin(alpha + sliceSize) * res);
            texturas.push_back(t);
            t.x=(0.75f + 0.25f * cos(alpha + sliceSize) * resplus); t.y=(0.5f + 0.5f * sin(alpha + sliceSize) * resplus);
            texturas.push_back(t);


		}
	}

    file << "--normais--" << "\n";

    for(int i=0; i<normais.size(); i++){
        file << normais[i].x << ", " << normais[i].y << ", " << normais[i].z << "\n";
    }

    file << "--texturas--" << "\n";

    for(int i=0; i<texturas.size();i++){
        file << texturas[i].x << ", " << texturas[i].y << "\n";
    }

	file.close();
}

string polarToCart(float radius, float alpha, float beta,float p[3]){
	float x = radius*cos(beta)*sin(alpha);
	p[0]=x;
	float y = radius*sin(beta);
	p[1]=y;
	float z = radius*cos(beta)*cos(alpha);
	p[2]=z;
	return to_string(x) + ", " + to_string(y) + ", " + to_string(z) + "\n";
	//return "glVertex3f(" + to_string(x) + "f, " + to_string(y) + "f, " + to_string(z) + "f);\n";
}

string polarToCartCone(float radius,float height, float alpha, float p[3]){
	float x = radius*sin(alpha);
	p[0]=x;
	float y = height;
	p[1]=y;
	float z = radius*cos(alpha);
	p[2]=z;
	return to_string(x) + ", " + to_string(y) + ", " + to_string(z)+"\n";
}

void generatePatch(string patchfile, int tesselation, string filesave){

    string path = "../models/" + patchfile + ".patch";

    ifstream f(path);

    int patches=0;
    int vertices=0;
    vector<vector<int>> indicesPatch;
    vector<Point> PControlo;

    if(f.is_open()){
        //ler patch
        string line;
        if(getline(f,line)) sscanf(line.c_str(),"%d\n",&patches);
        for(int i=0; i<patches ;i++){
            vector<int> aux;
            if(getline(f,line)){

                stringstream str_strm;
                str_strm << line;

                string temp;
                int found;
                while (!str_strm.eof()) {

                    str_strm >> temp;

                    if (stringstream(temp) >> found)
                        aux.push_back(found);

                    temp = "";
                }

            }

            indicesPatch.push_back(aux);
        }

        if(getline(f,line)) sscanf(line.c_str(),"%d\n",&vertices);
        for(int i=0; i<vertices ;i++){
            float x=0,y=0,z=0;
            if(getline(f,line)) sscanf(line.c_str(),"%f, %f, %f\n",&x,&y,&z);

            Point p;
            p.x = x; p.y = y; p.z = z;

            PControlo.push_back(p);
        }

        f.close();
    }
    else {
        printf("Ficheiro nao encontrado");
        exit(0);
    }

    //desenhar patch
    double t;
    int index, indices[4];
    double q[4][tesselation][3],r[tesselation][tesselation][3],tess = 1/((double)tesselation-1);

    fstream g;
    string path1 = "../models/" + filesave + ".3d";
    g.open(path1,std::ios::out);

    if(g.is_open()){   //numero de pontos
        for(int n=0; n<patches; n++){
            //recolher os vértices do array com os pontos de controlo para o x y e z
            double p[16][3];
            for(int m=0; m<16; m++){
                p[m][0] = PControlo[indicesPatch[n][m]].x;
                p[m][1] = PControlo[indicesPatch[n][m]].y;
                p[m][2] = PControlo[indicesPatch[n][m]].z;
            }
            int j=0,k=0;
            //desenhar as 4 curvas
            for(int i=0; i<15; i+=4){
                indices[0] = i;
                indices[1] = i+1;
                indices[2] = i+2;
                indices[3] = i+3;
                //calcular a curva
                for(int a=0; a<tesselation-1; a++){
                    t = a*tess;
                    index = floor(t);
                    t = t - index;
                    q[j][k][0] = (-p[indices[0]][0] +3*p[indices[1]][0] -3*p[indices[2]][0] +p[indices[3]][0])*t*t*t + (3*p[indices[0]][0] -6*p[indices[1]][0] +3*p[indices[2]][0])*t*t + (-3*p[indices[0]][0] +3*p[indices[1]][0])*t + p[indices[0]][0];
                    q[j][k][1] = (-p[indices[0]][1] +3*p[indices[1]][1] -3*p[indices[2]][1] +p[indices[3]][1])*t*t*t + (3*p[indices[0]][1] -6*p[indices[1]][1] +3*p[indices[2]][1])*t*t + (-3*p[indices[0]][1] +3*p[indices[1]][1])*t + p[indices[0]][1];
                    q[j][k][2] = (-p[indices[0]][2] +3*p[indices[1]][2] -3*p[indices[2]][2] +p[indices[3]][2])*t*t*t + (3*p[indices[0]][2] -6*p[indices[1]][2] +3*p[indices[2]][2])*t*t + (-3*p[indices[0]][2] +3*p[indices[1]][2])*t + p[indices[0]][2];
                    k++;
                }

                t = 1;

                q[j][k][0] = (-p[indices[0]][0] +3*p[indices[1]][0] -3*p[indices[2]][0] +p[indices[3]][0])*t*t*t + (3*p[indices[0]][0] -6*p[indices[1]][0] +3*p[indices[2]][0])*t*t + (-3*p[indices[0]][0] +3*p[indices[1]][0])*t + p[indices[0]][0];
                q[j][k][1] = (-p[indices[0]][1] +3*p[indices[1]][1] -3*p[indices[2]][1] +p[indices[3]][1])*t*t*t + (3*p[indices[0]][1] -6*p[indices[1]][1] +3*p[indices[2]][1])*t*t + (-3*p[indices[0]][1] +3*p[indices[1]][1])*t + p[indices[0]][1];
                q[j][k][2] = (-p[indices[0]][2] +3*p[indices[1]][2] -3*p[indices[2]][2] +p[indices[3]][2])*t*t*t + (3*p[indices[0]][2] -6*p[indices[1]][2] +3*p[indices[2]][2])*t*t + (-3*p[indices[0]][2] +3*p[indices[1]][2])*t + p[indices[0]][2];

                j++;
                k=0;
            }

            for(int j=0; j<tesselation; j++){
                for(int a=0; a<tesselation-1; a++){
                    t = a*tess;;
                    index = floor(t);
                    t = t - index;

                    r[j][k][0] = (-q[0][j][0] +3*q[1][j][0] -3*q[2][j][0] +q[3][j][0])*t*t*t + (3*q[0][j][0] -6*q[1][j][0] +3*q[2][j][0])*t*t + (-3*q[0][j][0] +3*q[1][j][0])*t + q[0][j][0];
                    r[j][k][1] = (-q[0][j][1] +3*q[1][j][1] -3*q[2][j][1] +q[3][j][1])*t*t*t + (3*q[0][j][1] -6*q[1][j][1] +3*q[2][j][1])*t*t + (-3*q[0][j][1] +3*q[1][j][1])*t + q[0][j][1];
                    r[j][k][2] = (-q[0][j][2] +3*q[1][j][2] -3*q[2][j][2] +q[3][j][2])*t*t*t + (3*q[0][j][2] -6*q[1][j][2] +3*q[2][j][2])*t*t + (-3*q[0][j][2] +3*q[1][j][2])*t + q[0][j][2];


                    k++;
                }

                t = 1;

                r[j][k][0] = (-q[0][j][0] +3*q[1][j][0] -3*q[2][j][0] +q[3][j][0])*t*t*t + (3*q[0][j][0] -6*q[1][j][0] +3*q[2][j][0])*t*t + (-3*q[0][j][0] +3*q[1][j][0])*t + q[0][j][0];
                r[j][k][0] = (-q[0][j][1] +3*q[1][j][1] -3*q[2][j][1] +q[3][j][1])*t*t*t + (3*q[0][j][1] -6*q[1][j][1] +3*q[2][j][1])*t*t + (-3*q[0][j][1] +3*q[1][j][1])*t + q[0][j][1];
                r[j][k][0] = (-q[0][j][2] +3*q[1][j][2] -3*q[2][j][2] +q[3][j][2])*t*t*t + (3*q[0][j][2] -6*q[1][j][2] +3*q[2][j][2])*t*t + (-3*q[0][j][2] +3*q[1][j][2])*t + q[0][j][2];

                k=0;
            }

            for(int i=0; i<tesselation-1; i++)
                for(int j=0; j<tesselation-1; j++){
                    g << r[i][j][0];   g << ", "; g << r[i][j][1];   g << ", "; g << r[i][j][2];   g << '\n';
                    g << r[i+1][j][0]; g << ", "; g << r[i+1][j][1]; g << ", "; g <<r[i+1][j][2];  g << '\n';
                    g << r[i][j+1][0]; g << ", "; g << r[i][j+1][1]; g << ", "; g << r[i][j+1][2]; g << '\n';

                    g << r[i+1][j][0];   g << ", "; g << r[i+1][j][1];   g << ", "; g << r[i+1][j][2];   g << '\n';
                    g << r[i+1][j+1][0]; g << ", "; g << r[i+1][j+1][1]; g << ", "; g << r[i+1][j+1][2]; g << '\n';
                    g << r[i][j+1][0];   g << ", "; g << r[i][j+1][1];   g << ", "; g << r[i][j+1][2];   g << '\n';
                }
        }
        g.close();
    }
    else { printf("Nao e possivel abrir o ficheiro\n"); exit(0);

    }


}