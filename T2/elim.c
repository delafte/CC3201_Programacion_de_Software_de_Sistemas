#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elim.h"
void eliminar(char *str, char *pat) {
  int lenpat = strlen(pat),cnt=0;
  char* ptr1 = str;
  char* ptr2 = pat;
  while(*ptr1!=0){
    if(*ptr2 == 0){
      ptr2 -= lenpat;
      cnt=0;
    }
    if(*ptr1 == *ptr2){
      ptr1+=1;
      ptr2+=1;
      cnt+=1;
    }
    else{
      ptr1-=cnt;
      ptr2-=cnt;
      cnt = 0;
      *str = *ptr1;
      ptr1+=1;
      str+=1;
    }
  }
  if(cnt!=0 && cnt!=lenpat){
    ptr1-=cnt;
    *str='\0';
    strcat(str,ptr1);
  }
  else{
    *str = '\0';
  }
}

char *eliminados(char *str, char *pat) {
  int len = strlen(str),lenpat = strlen(pat), ap=0,cnt=0,devolver=0;
  char *ptr1 = str;
  char *ptr2 = pat;
  while(*ptr1!=0){
    if(*ptr2 == 0){
      ptr2 -= lenpat;
      ap+=1;
      cnt=0;
    }
    if(*ptr1==*ptr2){
      ptr2+=1;cnt+=1;
    }
    else if(cnt!=0){
      ptr2-=cnt;
      cnt = 0;
    }
    ptr1+=1;
  }
  if(*ptr2==0){
    ap+=1;
  } 
  int lenstr2 = len-(ap*lenpat);
  char* str2 = malloc(lenstr2+1);
  ptr1-=len;
  if(cnt!=0){
    ptr2 -=cnt;
    cnt=0;
  }
  while(*ptr1!=0){
    if(*ptr2 == 0){
      ptr2 -= lenpat;
      cnt=0;
    }
    if(*ptr1 == *ptr2){
      ptr1+=1;
      ptr2+=1;
      cnt+=1;
    }
    else{
      ptr1-=cnt;
      ptr2-=cnt;
      cnt = 0;
      *str2 = *ptr1;
      ptr1+=1;
      str2+=1;devolver+=1;
    }
  }
  if(cnt!=0 && cnt!=lenpat){
    ptr1-=cnt;
    *str2='\0';
    strcat(str2,ptr1);
  }
  else{
    *str2 = '\0';
  }
  str2-=devolver;
  return str2;
}
