//#define n 8 //longitud de la palabra de entrada (challenge)

int challenges1[200];
int challenges2[200];
int challenges3[200]; 
int funcionaTodas[50]; 

int fin = 0;

int l = 0;
int m = 0;
int n = 0;
int o = 0;

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
if(fin != 1){
  
 for (int i = 0; i <= 255; i++) { // Recorrer todos los números de 0 a 255
    int X[8]; // Array de 8 posiciones para almacenar el número binario
    
    int OKprim = 0; 
    int OKseg = 0;
    int OKterc = 0;
    int todas = 0;  
    
    int aux = i;   
    Serial.println(i);
    
    // Convertir el número a su representación binaria de 8 bits
    for (int j = 7; j >= 0; j--) {
      X[j] = aux & 1; // Obtener el bit correspondiente
      aux >>= 1; // Desplazar el número hacia la derecha
    }

   digitalWrite(A3,X[0]); //entrada de los challenges en la PUF
   digitalWrite(10,X[1]); 
   digitalWrite(2,X[2]);
   digitalWrite(3,X[3]);
   digitalWrite(4,X[4]);
   digitalWrite(5,X[5]);
   digitalWrite(6,X[6]);
   digitalWrite(7,X[7]);
   
   for (int k = 0; k <= 2500; k++) {
   if(digitalRead(11)==1){
      OKprim=1;
   } 
   if(digitalRead(12)==1){
      OKseg=1;
   }
   if(digitalRead(13)==1){
      OKterc=1;
   }
   }   
   

   if(OKprim == 1){
     challenges1[l]=i;
     Serial.print("Funciona en primera: "); 
     Serial.println(i); 
     l++;
   }
   if(OKseg == 1){
     challenges2[m]=i;     
     Serial.print("Funciona en segunda: "); 
     Serial.println(i);    
     m++;      
    }  
   if(OKterc == 1){
     challenges3[n]=i;
     Serial.print("Funciona en tercera: "); 
     Serial.println(i);  
     n++;
   }
   if((OKprim && OKseg && OKterc) == 1){
     funcionaTodas[o]=i;
     Serial.println();
     Serial.println();
     Serial.println();
     Serial.println("############################################################################################");
     Serial.println();
     Serial.print("Funciona en todas: "); 
     Serial.println(i); 
     Serial.println();
     Serial.println("############################################################################################");   
     Serial.println();
     Serial.println();
     Serial.println();  
     o++;    
   }   

   // Imprimir el número binario en el monitor serie
   for (int j = 0; j < 8; j++) {
     Serial.print(X[j]);
    }
   Serial.println(); 
   Serial.println("------------------------------------------------------");
  
   if(i == 255){
     fin = 1;
    }
  
  }
  
//imprimir los challenges que funcionaron en cada par de filas de la PUF
  Serial.println("PUF1:");
  for(int p; p <= 200; p++){
    Serial.print(challenges1[p]);
    Serial.print(", ");  
  }
  
  Serial.println();
  Serial.println("PUF2:");
  for(int p = 0; p <= 199; p++){
    Serial.print(challenges2[p]);
    Serial.print(", ");  
  }

  Serial.println();
  Serial.println("PUF3:");
  for(int p = 0; p <= 199; p++){
    Serial.print(challenges3[p]);
    Serial.print(", ");  
  } 

  Serial.println();
  Serial.println("TODAS:");
  for(int p = 0; p <= 49; p++){
    Serial.print(funcionaTodas[p]);
    Serial.print(", ");  
  }
}   
}
