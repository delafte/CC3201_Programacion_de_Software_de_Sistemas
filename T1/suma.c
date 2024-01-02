#include <stdio.h>
#include "suma.h"
typedef unsigned long long Bcd;
Bcd sumaBcd(Bcd x, Bcd y){
  Bcd mask = ~((Bcd)(-1) << 4);//definimos mascara
  Bcd resultado = 0;//variables necesarias
  int resto = 0;
  int mover = 0;
  for(int i = 0; i < 16; i++){//ciclo para ir sumando por partes los numeros
    Bcd result = (x&mask)+(y&mask)+resto;//usamos operadores de bits y sumas
    if(result > 9){
      result = result-10;
      resto = 1;
    }
    else{
      resto = 0;
    }
    if(mover > 56 && resto == 1){//si se supera limite de shifts y aun queda por sumar mas digitos a la izq->desborde
      return 0xffffffffffffffff;
    }
    resultado += result << mover;
    x = x >> 4;
    y = y >> 4;
    mover += 4;
  }
  if (resto == 1){//si al terminar de sumar nos queda aun un uno por sumar:
    mover +=4;
    resultado += 1 << mover;
  }
  return resultado;//retornamos resultado final
}