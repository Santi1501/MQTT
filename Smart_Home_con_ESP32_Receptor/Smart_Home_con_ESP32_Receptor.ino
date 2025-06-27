#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);
bool living = false, cocina = false, dormitorio = false, baño = false, todas = false;

#define LIVING_PIN     13
#define COCINA_PIN     14
#define DORMITORIO_PIN 26
#define BAO_PIN       33

void callback(char* topic, byte* payload, unsigned int length) {
  String topic1 = String(topic);
  Serial.println("xd");
  
  if (topic1 == "casa/luz/belau/living" && todas == false) { // LIVING
    if (living == false)
    {
      Serial.println("Luz del living encendida.");
      digitalWrite(LIVING_PIN, HIGH);
      living = true;
    }
    else {
      Serial.println("Luz del living apagada.");
      digitalWrite(LIVING_PIN, LOW);
      living = false;
    }
  } 

  else if (topic1 == "casa/luz/belau/cocina" && todas == false) { // COCINA
    if (cocina == false)
    {
      Serial.println("Luz de la cocina encendida.");
      digitalWrite(COCINA_PIN, HIGH);
      cocina = true;
    }
    else {
      Serial.println("Luz de la cocina apagada.");
      digitalWrite(COCINA_PIN, LOW);
      cocina = false;
    }
  } 

  else if (topic1 == "casa/luz/belau/dormitorio" && todas == false) { // DORMITORIO
    if (dormitorio == false)
    {
      Serial.println("Luz del dormitorio encendida.");
      digitalWrite(DORMITORIO_PIN, HIGH);
      dormitorio = true;
    }
    else {
      Serial.println("Luz del dormitorio apagada.");
      digitalWrite(DORMITORIO_PIN, LOW);
      dormitorio = false;
    }
  } 

  else if (topic1 == "casa/luz/belau/bathroom" && todas == false) { // BAÑO
    if (baño == false)
    {
      Serial.println("Luz del baño encendida.");
      digitalWrite(BAO_PIN, HIGH);
      baño = true;
    }
    else {
      Serial.println("Luz del baño apagada.");
      digitalWrite(BAO_PIN, LOW);
      baño = false;
    }
  }

  else if (topic1 == "casa/luz/belau/todas") {
    if (todas == false)
    {
      Serial.println("Luz todas encendidas.");
      digitalWrite(BAO_PIN, HIGH);
      digitalWrite(DORMITORIO_PIN, HIGH);
      digitalWrite(COCINA_PIN, HIGH);
      digitalWrite(LIVING_PIN, HIGH);
      todas = true;
    }
    else {
      Serial.println("Luz del todas apagada.");
      digitalWrite(BAO_PIN, LOW);
      digitalWrite(DORMITORIO_PIN, LOW);
      digitalWrite(COCINA_PIN, LOW);
      digitalWrite(LIVING_PIN, LOW);
      todas = false;
    }

    living = false;
    cocina = false;
    dormitorio = false;
    baño = false;
  }

  Serial.println("-------------------------------------------");
}


void setup() {
  Serial.begin(115200);

  // Conectarse a una red por nombre + contraseña
  WiFi.begin("iPhone de Morci","morcilover123");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando WiFi...");
  }

  Serial.println("WiFi conectado con exito!");

  client.setCallback(callback);
  client.setServer("broker.hivemq.com", 1883);
  client.connect("belmonte"); // devuelve un booleano indicando si se conecto correctamente

  if (!client.connected()) {
    Serial.println("MQTT no conectado, reintentando...");
    client.connect("belmonte");
  } else {
    Serial.println("MQTT conectado.");
  }

  client.subscribe("casa/luz/belau/+"); // seguir patron del topico a escuchar
  Serial.println("-------------------------------------------");

  pinMode(LIVING_PIN, OUTPUT);
  pinMode(COCINA_PIN, OUTPUT);
  pinMode(DORMITORIO_PIN, OUTPUT);
  pinMode(BAO_PIN, OUTPUT);
}

void loop() {
  client.loop();
}