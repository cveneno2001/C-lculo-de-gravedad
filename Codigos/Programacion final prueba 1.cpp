/* VERSION: ANALISIS ESTADISTICO
   Calcula g y el error experimental entre muestras
*/

const int sensorPin = 18;
const float L = 0.50; // Longitud en metros
const int MUESTRAS_MAX = 10;

volatile unsigned long tInicio = 0;
volatile int cruces = 0;
float tiempos[MUESTRAS_MAX];
int conteo = 0;

void IRAM_ATTR detectar() {
  unsigned long ahora = micros();
  cruces++;
  if (cruces == 1) tInicio = ahora;
  else if (cruces == 3) {
    if (conteo < MUESTRAS_MAX) {
      tiempos[conteo] = (ahora - tInicio) / 1000000.0;
      conteo++;
    }
    cruces = 0;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(18, detectar, FALLING);
}

void loop() {
  if (conteo >= MUESTRAS_MAX) {
    float suma = 0;
    for(int i=0; i<MUESTRAS_MAX; i++) suma += tiempos[i];
    float T_prom = suma / MUESTRAS_MAX;
    float g = (39.478 * L) / (T_prom * T_prom);
    
    Serial.print("Gravedad Promedio: ");
    Serial.println(g);
    conteo = 0; // Reiniciar ciclo
  }
}
