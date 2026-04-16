/* CALCULO FINAL DE GRAVEDAD
   Este codigo promedia 10 lecturas y calcula el valor de g
*/

const int sensorPin = 18;
const float PI_CUADRADO = 9.8696;
const float LONGITUD_HILO = 0.50; // CAMBIA ESTO: Longitud L en metros

volatile unsigned long t1 = 0;
volatile unsigned long t2 = 0;
volatile int cortes = 0;
volatile bool muestraLista = false;

float sumaPeriodos = 0;
int lecturasHechas = 0;
const int TOTAL_MUESTRAS = 10;

void IRAM_ATTR detectarPaso() {
  unsigned long ahora = micros();
  if (ahora - t1 > 100000) { 
    cortes++;
    if (cortes == 1) t1 = ahora;
    else if (cortes == 3) {
      t2 = ahora;
      muestraLista = true;
      cortes = 0;
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), detectarPaso, FALLING);
  Serial.println("Iniciando experimento: Realiza 10 oscilaciones...");
}

void loop() {
  if (muestraLista) {
    float T = (t2 - t1) / 1000000.0;
    sumaPeriodos += T;
    lecturasHechas++;
    
    Serial.print("Muestra ");
    Serial.print(lecturasHechas);
    Serial.print(": T = ");
    Serial.println(T, 4);

    if (lecturasHechas >= TOTAL_MUESTRAS) {
      float promedioT = sumaPeriodos / TOTAL_MUESTRAS;
      /* Formula: g = (4 * PI^2 * L) / T^2 */
      float g = (4.0 * PI_CUADRADO * LONGITUD_HILO) / (promedioT * promedioT);
      
      Serial.println("---------------------------");
      Serial.print("RESULTADO FINAL g: ");
      Serial.print(g, 2); 
      Serial.println(" m/s^2");
      Serial.println("---------------------------");
      
      lecturasHechas = 0;
      sumaPeriodos = 0;
    }
    muestraLista = false;
  }
}
