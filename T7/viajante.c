#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "viajante.h"

int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double viajante_par(int z[], int n, double **m, int nperm, int p) {
  // Complete esta funcion
  // Puede invocar a su version secuencial: viajante
  // Use la funcion leer para que el padre reciba la ruta del hijo.
  // Use fork() para crear p nuevos procesos.  El padre solo obtiene los
  // resultados de los procesos hijos a traves de pipes, entierra a los
  // los hijos y calcula el resultado final.
  // Despues de invocar fork() agregue: srandom(getUSecsOfDay()*getpid());
  // Esto es para que cada proceso genere secuencias de numeros aleatorios
  // diferentes.
  int pids[p];
  int fds[p][2];

  for (int i= 0; i<p; i++) {
    pipe(fds[i]);
    pids[i] = fork();
    srandom(getUSecsOfDay()*getpid());

    if (pids[i] == 0){ //hijo i-esimo
      close(fds[i][0]);
      double res = viajante(z,n,m,nperm/p);
      write(fds[i][1], &res, sizeof(double));
      for(int j=0; j<n+1;j++){
        write(fds[i][1], &z[j], sizeof(int));
      }
      exit(1);
    }
    else{
      close(fds[i][1]);
    }
  }
  double res=0;
  for(int i = 0; i<p; i++){
    double res_hijo;
    int z2[n+1];

    leer(fds[i][0], &res_hijo, sizeof(double));
    for(int j =0; j<n+1; j++){
      leer(fds[i][0], &z2[j], sizeof(int));
    }
    if(i == 0){
      res = res_hijo;
    }
    else if(res_hijo < res){
      res = res_hijo;
      for (int j=0; j<n+1; j++) {
        z[j] = z2[j];
      }
    }
    close(fds[i][0]);
    waitpid(pids[i], NULL, 0);
  }
  return res;
} 
