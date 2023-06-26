#include <math.h>
#define n 10 //cantidad de numeros por muestra
#define r1 6 //primer lag de x
#define s1 1 //segundo lag de x
#define r2 5 //primer lag de y
#define s2 2//segundo lag de y
#define r3 9//primer lag de z
#define s3 4//segundo lag de z
#define N 10 //tamaño de la palabra
#define m 1024 //modulo (2^N)
#define d 2 //cantidad de desplazamientos

int C[8] = {1,1,0,0,1,1,0,1}; //Challenge de entrada para las tres PUFs

int X[n];
int Y[n] = {2,4,1,5,6,3,2,1,7,5};
int Z[n];

int w; //salida del algoritmo
int xp;//X'n
int yp;//Y'n
int zp;//Z'n
int xs;//Xn
int ys;//Yn
int zs;//Zn

int SemillasCargadas = 0;

int mod2amod10(int V[], int tam){ // función para convertir los vectores con el valor binario en un número decimal, se pasa por parámetro el vector con el número binario y el tamaño de este
  int aux =0;  
  int potencia = 1;

  for(int j = 0; j < tam; j++){ //se suman todos los bits multiplicados por 2 elevado a su posición en la cadena de bits
   aux = aux + (V[j]*potencia); 
   potencia = 2 * potencia;    
  } 

  return aux;
}

void crearSemilla(int S[n], int pin){
  
  for(int i = 0; i < n; i++){          //en este bucle se genera el vector semilla para un PLFG con la salida de la PUF que se indique por parámetro 
    int k[N];

    while(digitalRead(pin) == 0){}    
    
    for(int j = 0; j < N; j++){
      k[j] = digitalRead(pin);
      delay(50);
    }   
    
    delay(1000);
    
    int aux = mod2amod10(k, N);
    
    S[i]=aux;
  }
}

void setup() {
 Serial.begin(9600);

 pinMode(A3, OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
   
 pinMode(11, INPUT);
 pinMode(12, INPUT);   
 pinMode(13, INPUT);
}

void loop() { 
    
if(SemillasCargadas == 0){    
  int xk[N]; //vectores auxiliares para guardar las salidas de las 3 PUFs  
  int yk[N];
  int zk[N]; 

  digitalWrite(A3,C[0]);
  digitalWrite(10,C[1]); 
  digitalWrite(2,C[2]);
  digitalWrite(3,C[3]);
  digitalWrite(4,C[4]);
  digitalWrite(5,C[5]);
  digitalWrite(6,C[6]);
  digitalWrite(7,C[7]);
  

  Serial.println();
  crearSemilla(X, 11);  
  Serial.println("Generado X");  
  //crearSemilla(Y, 12);
  //Serial.println("Generado Y");  
  crearSemilla(Z, 13);   
  Serial.println("Generado Z"); 
  
  SemillasCargadas = 1;  
  
  Serial.println();
  Serial.print("X: ");
  for (int j = 0; j < n; j++) {
     Serial.print(X[j]);
     Serial.print(", ");
  }
  Serial.println();
  Serial.print("Y: ");
  for (int j = 0; j < n; j++) {
     Serial.print(Y[j]);
     Serial.print(", ");
  }
  Serial.println();
  Serial.print("Z: ");
  for (int j = 0; j < n; j++) {
     Serial.print(Z[j]);
     Serial.print(", ");
  }
  Serial.println();  
}
  xp = ((X[(n-1)-r1]+X[(n-1)-s1]) % m) >> d;
  yp = ((Y[(n-1)-r2]+X[(n-1)-s2]) % m) >> d;
  zp = ((Z[(n-1)-r3]+X[(n-1)-s3]) % m) >> d;

  xs = ((X[(n-1)-r1]+X[(n-1)-s1]) % m) ^ zp;
  ys = ((Y[(n-1)-r2]+Y[(n-1)-s2]) % m) ^ xp;
  zs = ((Z[(n-1)-r3]+Z[(n-1)-s3]) % m) ^ yp;

  w = xs ^ zs;
  
    
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