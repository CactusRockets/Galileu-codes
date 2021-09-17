#include <SPI.h>
#include <RF24.h>

#define PARACHUTE_TIME 20000

// Pinos CE e CSN
RF24 radio(7, 8);
bool releaseParachute = false;

const byte endereco[][6] = {"1node", "2node"};

void setup() {
  // Inicia a comunicação serial
  Serial.begin(9600);

  // Inicia a comunicação com o modulo
  radio.begin();

  // Define o endereço do receptor (data pipe 0)
  // Define o endereço do transmissor
  radio.openWritingPipe(endereco[1]);
  radio.openReadingPipe(1, endereco[0]);

  // Entra no modo de recebimento
  radio.startListening();
}

void loop() {
  if(radio.available()) {
    char recebido[50];

    // Se recebeu algum pacote, lê o conteudo na variável recebido
    radio.read(&recebido, sizeof(recebido));
    // Imprime o que foi recebido
    Serial.println(recebido);
  }

  if(millis() > PARACHUTE_TIME) {
    releaseParachute = true;

    radio.stopListening();
    radio.write(&releaseParachute, sizeof(releaseParachute));
    radio.startListening();
  }
}
