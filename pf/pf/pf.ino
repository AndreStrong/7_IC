#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN 9

DHT dht(DHTPIN, DHTTYPE);
//se define el pin de entrada spuerta
const int sPuerta = 8;
// se definen los pines 6 y 7 como salidas para el motor
const int motorA = 6;
const int motorB = 7;
//se define el pin 5 como salida de un led de alarma
const int ledAlarma = 5;
void setup() {
  // put your setup code here, to run once:

  //se inicia el puerto serie
  Serial.begin(9600);
  //se inicializa la biblioteca del sensor de temperatura y humedad
  dht.begin();
  //se establece el pin digital 8 como el sPuerta
  pinMode(sPuerta, INPUT); 
  //se establecen los pines 6 y 7 como salida para el motor
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT); 
  //se establece el pin 5 como salida del LED
  pinMode(ledAlarma, OUTPUT); 
  
  
}

void loop() {
  delay(2000);
  
  //lectura de sensor de temperatura y humedad
  float humedity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if(isnan(humedity) || isnan(temperature)){
    Serial.println("ERROR: Asegurese de conectar correctamente los sensores de TEMPERATURA y PUERTA");  
    return;
  }
  //lectura de spuerta
  int puerta = digitalRead(sPuerta);
  //salidas a monitor serie
  Serial.print("Humedad: ");
  Serial.print(humedity);
  Serial.print(" %");
  Serial.print(" Temperatura: ");
  Serial.print(temperature);
  Serial.print(" °C");
  Serial.print(" Puerta: ");
  Serial.print(puerta);
  

  //encender ventilador sin alarma 
  if((temperature >= 20) && (temperature <= 30) && (puerta == 1))
  {
      //Actuadores
      digitalWrite(ledAlarma, LOW);
      digitalWrite(motorA, HIGH);
      digitalWrite(motorB, LOW);
      //imprimir
      Serial.print(" Ventilador: ON");
      Serial.println("");
    
  }else if((temperature > 30) && (puerta == 1)){
      //Actuadores
      digitalWrite(ledAlarma, HIGH);
      digitalWrite(motorA, HIGH);
      digitalWrite(motorB, LOW);
      //imprimir
      Serial.print(" Ventilador: ON (!)");
      Serial.println("");
  }else{
      //Actuadores
      digitalWrite(ledAlarma, LOW);
      digitalWrite(motorA, LOW);
      digitalWrite(motorB, LOW);
      //imprimir
      Serial.print(" Ventilador: OFF");
      Serial.println("");
    }

}
