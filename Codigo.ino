
#define DOS_SENSORES

double cuadrado(double x) {
  return x * x;
}

// Valores aproximados a la recta de la conductancia
// Conductancia = m * Fuerza + b
#define m1  0.0000025449
#define b1 -0.0000001749

#define m2  0.0000027171
#define b2  0.0000009793

// Producto del voltage inicial con la resistencia
#define Vt_Rf (5 * 51000)

// Area del sensor en metros
#define areaSensor 0.0000713

// Valor máximo una señal analógica
#define MAXANALOG 1023

// Valor maximo del sensor en milivoltios
#define MAXMILIVOLTAGE 5000

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  // Lectura de la entrada de los pines analogicos A0 y A1
  int value1 = analogRead(A0);
  int value2 = analogRead(A1);

  // Se mapea el valor del puerto analogico al valor en milivoltios.
  int V1 = map(value1, 0, MAXANALOG, 0, MAXMILIVOLTAGE);
  int V2 = map(value2, 0, MAXANALOG, 0, MAXMILIVOLTAGE);

  // Calculo de la fuerza en cada sensor
  //
  //      - (Vout + (Vt * Rf) * b)
  // F = ----------------------------
  //           (Vt * Rf) * m   
  //     
 
  double F1 = ( (V1 / 1000.0) - Vt_Rf * b1) / (Vt_Rf * m1);
  double F2 = ( (V2 / 1000.0) - Vt_Rf * b2) / (Vt_Rf * m2);

  // Calculo de la cantidad de Pascales
  double P1 = F1 / areaSensor;
  double P2 = F2 / areaSensor;


#ifdef DOS_SENSORES

  if (value1 > 0 || value2 > 0){
    Serial.print("1,");
    Serial.print(V1);
    Serial.print(",");
    Serial.print(F1);
    Serial.print(",");
    Serial.print(P1);
  
    Serial.print(",2,");
    Serial.print(V2);
    Serial.print(",");
    Serial.print(F2);
    Serial.print(",");
    Serial.println(P2);
  }
  
 #else
 
  if (value1 > 0){
    Serial.print("1,");
    Serial.print(V1);
    Serial.print(",");
    Serial.print(F1);
    Serial.print(",");
    Serial.println(P1);
  }
  
 #endif
  delay(20);
}



