#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pss.h"
       
// Defina aca la estructura para guardar nombre y tamanno
Queue *q;

typedef struct {
  char *nom;
  int peso;
} Par;

int cmpPar2(void *ptr, int i, int j) {
  Par **a= ptr;
  int res = (*a[i]).peso - (*a[j]).peso;
  if(res==0){
    return -strcmp((*a[i]).nom,(*a[j]).nom);
  }
  else{
    return res;
  }
}


// Agregue aca las funciones y variables globales adicionales que necesite
void listDir(char *nom) {
  struct stat st_nom;
  int rc;
  rc= stat(nom, &st_nom);

  if (rc!=0) {
    printf("%s no existe\n", nom);
    exit(0);
  }
  //printf("%s\n", nom);
  if (S_ISREG(st_nom.st_mode)) {
    // Es un archivo regular
    // No se hace nada en list-dir.bin
    char *nomarch=malloc(strlen(nom)+1);
    strcpy(nomarch,nom);
    Par *sum = malloc(sizeof(int)+(sizeof(char)*strlen(nom)));
    sum->nom = strdup(nomarch);
    sum->peso = st_nom.st_size;
    put(q,sum);
    free(nomarch);
  }
  else if (S_ISDIR(st_nom.st_mode)) {
    // Es un directorio
    DIR *dir = opendir(nom);
    if (dir == NULL) {
      perror(nom);
      exit(1);
    }
    for (struct dirent *entry = readdir(dir);
         entry != NULL;
         entry = readdir(dir)) {
      if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) {
        continue;
      }
      char *nom_arch= malloc(strlen(nom)+strlen(entry->d_name)+2);
      strcpy(nom_arch, nom);
      strcat(nom_arch, "/");
      strcat(nom_arch, entry->d_name);
      listDir(nom_arch);
      free(nom_arch);
    }
    closedir(dir);
  }
  else {
    // Podria ser un dispositivo, un link simbolico, etc.
    fprintf(stderr, "Archivo %s es de tipo desconocido\n", nom);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  if (argc!=3) {
    fprintf(stderr, "uso: %s <arch|dir>\n", argv[0]);
    exit(1);
  }
  
  int n = atoi(argv[2]);
  q=makeQueue();
  listDir(argv[1]);
  int largo = queueLength(q);
  Par *arr[largo];
  for(int i=0; i< largo;i++){
    arr[i] = get(q);
  }
  destroyQueue(q);

  sortPtrArray(arr,0,largo-1,cmpPar2);

  for (int i= 0; i<largo; i++){
    if(i<n) printf("%s %d\n", (*arr[largo-i-1]).nom, (*arr[largo-i-1]).peso);
    free(arr[largo-1-i]->nom);
    free(arr[largo-i-1]);

  }

  return 0;

}
