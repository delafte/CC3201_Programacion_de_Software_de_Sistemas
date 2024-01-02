#include <string.h>
//funcion auxiliar para contar cantidad de palabras
int cantPalabras(char *s){
  char *s1=s;
  int res=0;
  while(*s1){
    while(*s1==' '){
      s1++;
    }
    if(*s1!=0){
      res+=1;
    }
    while(*s1!=' '&& *s1!=0){
      s1++;
    }
  }
  return res;
}
int strCmp(char *s1, char *s2) {
  int c1, c2;
  c1=cantPalabras(s1);
  c2=cantPalabras(s2);
  return c1-c2;
}

void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {
    int t1= strCmp(p[0], p[1]);
    if (t1 <= 0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p = a;
    }
  }
}
