#ifndef COPIA
#define COPIA










int existeP(char *c,char **codigos);

void switchs(char s[],char h[]);

int verificaCod(char **c,char *v);

char**  cop(FILE* fp);

char** retCP(char **v);
int verificaCP(char *cv,char **cp);

char ** retCC(char **v);
char ** guardaE(char ** v,char **p);

char** split(char *p);

char* str_slice(char str[], int slice_from, int slice_to);


#endif