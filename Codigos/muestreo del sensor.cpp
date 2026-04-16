/* CALCULO DE PERIODO - PROYECTO PENDULO
   Este codigo detecta el punto de retorno para medir el tiempo T
*/

unsigned long tiempoAnterior = 0;
float periodo = 0;
int umbralDistancia = 100; // Ajusta segun la distancia de tu pendulo

void calcularPeriodo(int distanciaActual) {
  /* Si la distancia es menor al umbral, asumimos que 
     la masa paso por el centro 
  */
  if (distanciaActual < umbralDistancia) {
    unsigned long tiempoAhora = millis();
    periodo = (tiempoAhora - tiempoAnterior) / 1000.0; // Convertir a segundos
    tiempoAnterior = tiempoAhora;
    
    Serial.print("Periodo detectado: ");
    Serial.println(periodo);
  }
}
