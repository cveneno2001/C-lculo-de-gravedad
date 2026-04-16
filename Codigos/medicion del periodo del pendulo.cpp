/* MEDICION AUTOMATICA DE PERIODO
   Este codigo calcula el tiempo de una oscilacion completa (T)
*/

const int sensorPin = 18;
volatile unsigned long tiempoCorte1 = 0;
volatile unsigned long tiempoCorte2 = 0;
volatile int contadorCortes = 0;
volatile bool periodoListo = false;
float periodoFinal = 0;

void IRAM_ATTR detectarPaso() {
  unsigned long tiempoAhora = micros();
  
  /* Filtro simple para evitar rebotes de señal (debouncing) */
  if (tiempoAhora - tiempoCorte1 > 100000) { 
    contadorCortes++;
    
    if (contadorCortes == 1) {
      tiempoCorte1 = tiempoAhora; // Inicio de la oscilacion
    } 
    else if (contadorCortes == 3) {
      tiempoCorte2 = tiempoAhora; // Fin de la oscilacion (paso 1 -> 2 -> 3)
      periodoListo = true;
      contadorCortes = 0; // Reiniciamos para la siguiente medida
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), detectarPaso, FALLING);
  Serial.println("Esperando oscilacion del pendulo...");
}

void loop() {
  if (periodoListo) {
    /* Calculo del periodo en segundos */
    periodoFinal = (tiempoCorte2 - tiempoCorte1) / 1000000.0;
    
    Serial.print("Periodo detectado (T): ");
    Serial.print(periodoFinal, 4);
    Serial.println(" segundos");
    
    periodoListo = false;
  }
}
