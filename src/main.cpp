#include <WiFi.h>
#include <PubSubClient.h>

// =========================
// Wi-Fi
// =========================
const char* ssid = "CONECTA+";
const char* password = "senai512";

// =========================
// MQTT
// =========================
const char* mqtt_server = "192.168.0.109";
const int mqtt_port = 3026;

const char* mqtt_topic = "/GRUPO02/LucasZ/led";

// =========================
// LED
// =========================
const int LED_PIN = 5;

// =========================
// Objetos
// =========================
WiFiClient espClient;
PubSubClient client(espClient);

// =========================
// Variáveis de Controle
// =========================
bool iniciarPiscada = false;
int contadorPiscadas = 0;
unsigned long tempoAnterior = 0;
const unsigned long intervalo = 200;
bool estadoLED = LOW;


// =========================
// Conectar ao Wi-Fi
// =========================
void setup_wifi() {
  Serial.println();
  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());
}


// =========================
// Receber mensagem MQTT
// =========================
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  String mensagem = "";
  for (unsigned int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }

  mensagem.trim();
  mensagem.toLowerCase(); // Aceita maiúsculas e minúsculas

  Serial.print("Mensagem: ");
  Serial.println(mensagem);

  // 1. LIGAR FIXO
  if (mensagem == "on" || mensagem == "1") {
    iniciarPiscada = false;
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED LIGADO FIXO");

  } 
  // 2. DESLIGAR
  else if (mensagem == "off" || mensagem == "0" || mensagem == "false") {
    iniciarPiscada = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED DESLIGADO");

  } 
  // 3. PISCAR 10 VEZES
  else if (mensagem == "piscar" || mensagem == "true") {
    Serial.println("Comando RECEBIDO: Iniciando 10 piscadas..");
    iniciarPiscada = true;
    contadorPiscadas = 0;
    tempoAnterior = millis();
    estadoLED = HIGH;
    digitalWrite(LED_PIN, estadoLED);

  } 
  else {
    Serial.println("Valor desconhecido. Use: on, off, piscar, true ou false.");
  }
}


// =========================
// Conectar ao MQTT
// =========================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");

    String clientId = "ESP32-LED-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println(" conectado!");

      if (client.subscribe(mqtt_topic)) {
        Serial.print("Inscrito no tópico: ");
        Serial.println(mqtt_topic);
      } else {
        Serial.println("Falha ao assinar o tópico!");
      }

    } else {
      Serial.print(" falhou. Código: ");
      Serial.println(client.state());
      Serial.println("Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}


// =========================
// SETUP
// =========================
void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}


// =========================
// LOOP
// =========================
void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  // Executa o modo piscar apenas quando acionado
  if (iniciarPiscada) {
    unsigned long tempoAtual = millis();

    if (tempoAtual - tempoAnterior >= intervalo) {
      tempoAnterior = tempoAtual;

      estadoLED = !estadoLED;
      digitalWrite(LED_PIN, estadoLED);

      contadorPiscadas++;

      if (contadorPiscadas >= 20) {
        iniciarPiscada = false;
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED terminou as 10 piscadas");
      }
    }
  }
}