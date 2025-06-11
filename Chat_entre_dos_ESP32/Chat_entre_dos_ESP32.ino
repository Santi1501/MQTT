#include <WiFi.h>
#include <PubSubClient.h>

// Callback (una función con una firma particular) que respondera ante un nuevo mensaje recibido
void callback(char* topic, byte* payload, unsigned int length) {
  // Iteramos el payload
  for (int i = 0; i < length; i++) {
    
    char letra = (char)payload[i];
    Serial.print(letra);
  }
}

void setup() {

  // Conectarse a una red por nombre + contraseña
  WiFi.begin(iphone de Morci, morcilover123);

  if (WiFi.status() != WL_CONNECTED){
    // aun no esta conectado
  }
  // ok

  // Configuramos el cliente con el callback correcto
  client.setCallback(callback);

  WiFiClient espClient;
  // Creamos un cliente de MQTT con la conexión a internet via wifi
  PubSubClient client(espClient);

  // Realizamos la conexión con el servidor
  client.setServer(broker.hivemq.com, 1883);
  client.connect("laurogod") // devuelve un booleano indicando si se conecto correctamente
  client.connected(); // devuelve un booleano que nos permite chequear si la conexión fue exitosa
  client.subscribe("huergo/sistemas-embebidos/laurora"); // seguir patron del topico a escuchar
}

void loop() {
  
  // Leer del monitor serial el mensaje a enviar
  if (Serial.available()) {
    
    String msg = Serial.readStringUntil('\n');
    // Enviar un mensaje a un chat
    client.publish("huergo/sistemas-embebidos/laurora" , msg.c_str() ); // convertir el mensaje mediante .c_str()

  }
  // En caso de encontrar un nuevo mensaje en el topico al que estamos subscritos, ejecutará el callback que ya seteamos
  client.loop();
}