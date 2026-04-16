/* PROGRAMA DE PRUEBA: SENSOR DE HERRADURA
  Este código mide el tiempo entre cortes del haz infrarrojo.
*/

const int sensorPin = 18;
volatile unsigned long tiempoCorte = 0;
volatile bool detectado = false;

// Función que se activa al detectar el paso del péndulo
void IRAM_ATTR detectarPaso() {
  tiempoCorte = micros();
  detectado = true;
}

void setup() {
  Serial.begin(115200);
  
  /* Configuración del hardware */
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), detectarPaso, FALLING);
  
  Serial.println("Iniciando pruebas...");
}

void loop() {
  /* Si el sensor detectó un corte, muestra el tiempo en pantalla */
  if (detectado) {
    Serial.print("Tiempo en microsegundos: ");
    Serial.println(tiempoCorte);
    
    detectado = false; // Reinicia la detección
  }
}
