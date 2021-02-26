#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/copia.h"

#define MAX_SIZE 100

//funcao que verifica a existencia de um produto numa lista
int existeP(char *c,char **codigos){
int flag=-1;
int res=0;

for(int i=0;codigos[i];i++){
     if((flag=strcmp(c,codigos[i]))==0) res=1;

}

return res;

}
//funcao auxiliar que retira o primeiro caracter de uma string
void switchs(char s[],char h[]){
 char *ss=NULL;
ss=s;
int i; 

for(i=0;s[i];i++){
h[i]=s[i+1];
}
h[i]='\0';

s=ss;


}

// funcao responsavel por dividir uma linha de venda num array de strings
char** split(char *p){
char **ret=malloc(64*sizeof(char*));
char** aux=ret;
int i=0;
int init_size = strlen(p);
  char str[init_size];
strcpy(str,p);
  char *ptr = strtok(str," ");

  while (ptr != NULL)
  {      
    
ret[i]=strdup(ptr);
    ptr = strtok(NULL, " ");
i++;
  }
return aux-1;
}



// funcao que verifica a existencia de uma string num array de strings
int verificaCod(char **c,char *v){
 int i=0;

   for (i=0;c[i]!=0;i++){
    
        if (strcmp(c[i],v)) return 1;


	}

	return 0;
}



// funcao  que verifica existencia de um codigo numa lista
int verificaCP(char *cv,char **cp){
    int i;
    
    int flag=1;
    char ** aux = cp;
    for(i=0;cp[i];i++){
      flag=strcmp(cp[i],cv);
            if(flag==0) break;

    }
    cp=aux;
    return flag;
}


char * str_slice(char str[], int slice_from, int slice_to){

    // if a string is empty, returns nothing
    if (str[0] == '\0')
        return NULL;

    char *buffer;
    size_t str_len, buffer_len;

    // for negative indexes "slice_from" must be less "slice_to"
    if (slice_to < 0 && slice_from < slice_to) {
        str_len = strlen(str);

        // if "slice_to" goes beyond permissible limits
        if (abs(slice_to) > str_len - 1)
            return NULL;

        // if "slice_from" goes beyond permissible limits
        if (abs(slice_from) > str_len)
            slice_from = (-1) * str_len;

        buffer_len = slice_to - slice_from;
        str += (str_len + slice_from);

    // for positive indexes "slice_from" must be more "slice_to"
    } else if (slice_from >= 0 && slice_to > slice_from) {
        str_len = strlen(str);

        // if "slice_from" goes beyond permissible limits
        if (slice_from > str_len - 1)
            return NULL;

        buffer_len = slice_to - slice_from;
        str += slice_from;

    // otherwise, returns NULL
    } else
        return NULL;

    buffer = calloc(buffer_len, sizeof(char));
    strncpy(buffer, str, buffer_len);
    return buffer;
}


















