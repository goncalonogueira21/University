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

void generateBox(float x, float y, float z, string nome);
void generateBoxDiv(float x, float y, float z,int div, string nome);
string polarToCart(float radius, float alpha, float beta);
void generateSphere(float radius, int slices, int stacks, string nome);
void generatePlane(float x, string nome);
void generateCone(float radius, float height, int slices, int stacks, string nome);
string polarToCartCone(float radius,float height, float alpha);
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

	file.close();
}

void generateBox(float x, float y, float z, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);

	float xx=x/2;
	float yy=y/2;
	float zz=z/2;
	// face trás
	file << xx << ", " << yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << -xx << ", " << yy << ", " << -zz << "\n";
	// face cima
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << yy << ", " << -zz << "\n";
	// face frente
	file << -xx << ", " << yy << ", " << zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	// face baixo
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	// face esquerda
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << zz << "\n";
	// direita
	file << xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << -zz << "\n";
	
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
		}
	}

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
		}
	}

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
		}
	}			

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
		}
	}	

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
		}
	}		

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
		}
	}		



	file.close();
}

void generateSphere(float radius, int slices, int stacks, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);
	
	float alpha = 0.0f;
	float beta = M_PI/-2;

	float sliceSize = 2*M_PI/slices;
	float stackSize = M_PI/stacks;

	//inicio da construção
	
	for(int i = 0; i < stacks; ++i){
		for (int j = 0; j < slices; ++j)
		{
			//file << "glColor3f(1.0f, 0.0f, 0.0f);\n";
			file << polarToCart(radius,alpha,beta);
			file << polarToCart(radius,alpha,beta+stackSize);
			file << polarToCart(radius,alpha+sliceSize,beta);
			//file << "glColor3f(0.0f, 0.0f, 1.0f);\n";
			file << polarToCart(radius,alpha,beta+stackSize);
			file << polarToCart(radius,alpha+sliceSize,beta+stackSize);
			file << polarToCart(radius,alpha+sliceSize,beta);
			alpha+=sliceSize;
		}
		beta+=stackSize;
		alpha=0;
	}

	
	file.close();
}

void generateCone(float radius, float height, int slices, int stacks, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);

	float stackSize = height/stacks;
	float sliceSize = 2*M_PI/slices;
	float alpha = 0.0f;
	float r = 0.0f;
	float rUp = 0.0f;
	float yy= height/-2;

	for(int i=0;i<slices;i++){
	    alpha = i*sliceSize;
	    file << polarToCartCone(0,yy,0);
        file << polarToCartCone(radius,yy,alpha+sliceSize);
        file << polarToCartCone(radius,yy,alpha);

	}

	for(int i = 0; i < stacks; i++){


        r=(((float)stacks-i)/stacks)*radius;
        rUp=(((float)stacks-(i+1))/stacks)*radius;
        for(int j = 0; j < slices; j++){

            alpha=j*sliceSize;

            file << polarToCartCone(rUp,yy+stackSize*(i+1),alpha);
            file << polarToCartCone(r,yy+stackSize*i,alpha);
            file << polarToCartCone(r,yy+stackSize*i,alpha+sliceSize);
            file << polarToCartCone(rUp,yy+stackSize*(i+1),alpha);
            file << polarToCartCone(r,yy+stackSize*i,alpha+sliceSize);
            file << polarToCartCone(rUp,yy+stackSize*(i+1),alpha+sliceSize);


		}
	}


	file.close();
}

string polarToCart(float radius, float alpha, float beta){
	float x = radius*cos(beta)*sin(alpha);
	float y = radius*sin(beta);
	float z = radius*cos(beta)*cos(alpha);
	return to_string(x) + ", " + to_string(y) + ", " + to_string(z) + "\n";
	//return "glVertex3f(" + to_string(x) + "f, " + to_string(y) + "f, " + to_string(z) + "f);\n";
}

string polarToCartCone(float radius,float height, float alpha){
	float x = radius*sin(alpha);
	float y = height;
	float z = radius*cos(alpha);
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