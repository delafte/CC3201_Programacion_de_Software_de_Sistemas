#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

int main(int argc, char *argv[]) {
  if(argc != 4){//revisamos que la cantidad de argumentos entregados es correcta
    fprintf(stderr, "Uso: ./definir <diccionario> <llave> <definicion>\n");
    exit(1);
  }
  //variables iniciales
  char *nomArch = argv[1];
  char *llave = argv[2];
  int tamllave = strlen(llave);

  FILE *f=fopen(nomArch, "r+");
  if(f == NULL){
      perror(nomArch);
      exit(2);
    }
  int ancho = 81;
  char buff[ancho+1];
  //Para calcular tamano del archivo en bytes
  fseek(f,0,SEEK_END);
  int tamArch =ftell(f);
  int cantLineas= tamArch/ancho;
  
  int a = hash_string(llave)%cantLineas, i=cantLineas;

  while(i>0){
    fseek(f, a*ancho, SEEK_SET);
    fread(buff, tamllave, 1,f);

    //para casos en que ya este la palabra en el diccionario
    int ver_si_esta= strncmp(buff, llave, tamllave);
    if (ver_si_esta == 0){
      fprintf(stderr,"La llave %s ya se encuentra en el diccionario\n",llave);
      exit(3);
    }
    
    //si el primer caracter es espacio, entonces encontramos un espacio para anotar definicion
    if(buff[0]==' '){
      fseek(f, a*ancho, SEEK_SET);
      fwrite(llave, tamllave,1,f);
      fwrite(":", 1, 1, f);
      fwrite(argv[3], strlen(argv[3]),1,f);
      break;
    }
    i--;
    if(++a>cantLineas){
      a=0;
    }
  }  
  fclose(f);
  if(i==0){
    fprintf(stderr,"%s: el diccionario esta lleno\n", nomArch);
    exit(1);
  }
}