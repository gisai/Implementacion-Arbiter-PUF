#include <math.h>
#define n 10 //cantidad de numeros por muestra
#define r1 7 //primer lag de x
#define s1 1 //segundo lag de x
#define r2 5 //primer lag de y
#define s2 2//segundo lag de y
#define r3 4//primer lag de z
#define s3 1//segundo lag de z
#define N 3 //tamaño de la palabra
#define m 8 //modulo (2^N)
#define d 2 //cantidad de desplazamientos

int X[n] = {1,0,3,5,7,4,5,0,1,6};
int Y[n] = {2,4,1,5,6,3,2,1,7,5};
int Z[n] = {0,2,1,3,6,7,4,5,3,7};
int w; //salida del algoritmo
int xp;//X'n
int yp;//Y'n
int zp;//Z'n
int xs;//Xn
int ys;//Yn
int zs;//Zn

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xp = ((X[(n-1)-r1]+X[(n-1)-s1]) % m) >> d;
  yp = ((Y[(n-1)-r2]+X[(n-1)-s2]) % m) >> d;
  zp = ((Z[(n-1)-r3]+X[(n-1)-s3]) % m) >> d;

  xs = ((X[(n-1)-r1]+X[(n-1)-s1]) % m) ^ zp;
  ys = ((Y[(n-1)-r2]+Y[(n-1)-s2]) % m) ^ xp;
  zs = ((Z[(n-1)-r3]+Z[(n-1)-s3]) % m) ^ yp;

  w = xs ^ zs;
  //printf("X: %d \n",xs);
  //printf("Y: %d \n",ys);
  //printf("Z: %d \n",zs);
  Serial.print("W:");
  Serial.println(w);
  //Desplazar los 3 arrays y añadir el ultimo 
  //valor calculado
  for(int i = (n-1); i >= 0;i--){
    X[i]=X[i-1];
    Y[i]=Y[i-1];
    Z[i]=Z[i-1];
  }
  X[0]=xs;
  Y[0]=ys;
  Z[0]=zs;
}
