#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "CONECTA+";
const char* password = "senai512";

const char* mqtt_server = "192.168.0.113";
const int mqtt_port = 3026;

const char* mqtt_topic = "/grupo02/led";

const int LED_PIN = 5;
WiFiClient espClient;

PubSubClient client(espClient);

void setup_wifi() {
  Serial.println();
  Serial.print("Conectando ao Wi-Fi");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    Serial.print(".");
  }

  Serial.println("WiFi conectado!");

  Serial.print("IP do ESP32: ");

  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte*, payload, unsigned int length) {

  Serial.print("Mensagem recebida no tópico: ");

  Serial.println(topic);

  String mensagem = "";

  for (unsigned int i = 0; i < length, i++) {
    mensagem += (char)payload[i];
  }

  Serial.print("Mensagem:");
  Serial.println(mensagem);

  mensagem.trim();

  if (mensagem == "true") {
    digitalWrite(LED_PIN, HIGH);

    Serial.println("LED Ligado");
  }

  else if (mensagem == "false") {
    digitalWrite(LED_PIN, LOW)

      Serial.println("LED Desligado")
  } else {
    Serial.println("Valor desconhecido.");
  }
}

void reconnect() {
  while (!cliente.connected()) {
    Serial.print("Conetando ao MQTT...");

    String clientId = "ESP32-LED-";
    ClientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!");

      if (client.subscribe(mqtt_topic)) {
        Serial.print("Inscrito no tópico : ")

          Serial.println(mqtt_topic);
      } else {
        Serial.println("Falha ao assinar o tópico!")
      }
    } else {
      Serial.print("falhou. Código: ")
        Serial.println(client.state());
      Serial.println("Tentando novamente em 5 segundos...")

        delay(5000)
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, LOW);

  digitalWrite(LED_PIN, LOW);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);

  client.setCallback(callback);
}

void loop {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}