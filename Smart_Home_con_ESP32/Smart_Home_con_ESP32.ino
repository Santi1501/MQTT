#include <WiFi.h>
#include <PubSubClient.h>

#define Boton_living 27
#define Boton_cocina 26
#define Boton_dormitorio 25
#define Boton_bathroom 33

WiFiClient espClient;
// Creamos un cliente de MQTT con la conexión a internet via wifi
PubSubClient client(espClient);

bool estadoLiving = HIGH, estadoCocina = HIGH, estadoBathroom = HIGH, estadoDormitorio = HIGH;
int xd = 0;

void setup() {

  pinMode(Boton_living, INPUT_PULLUP);
  pinMode(Boton_cocina, INPUT_PULLUP);
  pinMode(Boton_dormitorio, INPUT_PULLUP);
  pinMode(Boton_bathroom, INPUT_PULLUP);

  Serial.begin(115200);

  // Conectarse a una red por nombre + contraseña
  WiFi.begin("iPhone de Morci", "morcilover123");

  while (WiFi.status() != WL_CONNECTED){
    
    Serial.printf("\nConectando Wi-Fi");
    delay(500);

  }

  if (WiFi.status() == WL_CONNECTED){
    
    Serial.printf("\nWi-Fi conectado");

  }

  // Realizamos la conexión con el servidor
  client.setServer("broker.hivemq.com", 1883);
  client.connect("laurogod"); // devuelve un booleano indicando si se conecto correctamente
  client.connected(); // devuelve un booleano que nos permite chequear si la conexión fue exitosa
}

void loop() {
  xd++;

  if(xd == 3500000) {
    estadoLiving = HIGH;
    estadoCocina = HIGH; 
    estadoBathroom = HIGH;
    estadoDormitorio = HIGH;
    xd = 0;
  }

  if(digitalRead(Boton_living) == LOW && estadoLiving == HIGH) {
    client.publish("casa/luz/belau/living", "ON");
    Serial.println("Luz living.");
    estadoLiving = LOW;
    }

  if(digitalRead(Boton_cocina) == LOW && estadoCocina == HIGH){
    client.publish("casa/luz/belau/cocina", "ON");
    Serial.println("Luz cocina.");
    estadoCocina = LOW;
  }

  if(digitalRead(Boton_dormitorio) == LOW && estadoDormitorio == HIGH) {
    client.publish("casa/luz/belau/dormitorio", "ON");
    Serial.println("Luz dormitorio.");
    estadoDormitorio = LOW;
  }

  if(digitalRead(Boton_bathroom) == LOW && estadoBathroom == HIGH){
    client.publish("casa/luz/belau/bathroom", "ON");
    Serial.println("Luz bathroom.");
    estadoBathroom = LOW;
  }

  /*if(){
    client.publish("casa/luz/todas", "ON");
  }*/
}