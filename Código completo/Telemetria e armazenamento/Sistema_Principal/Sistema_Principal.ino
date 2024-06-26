/* ================================================================================== */
/* ===== PROGRAMA PRINCIPAL : ATMEGA328P + TELEMETRIA + CARTÃO SD + EXPERIMENTO ===== */
/* ================================================================================== */

/*
    Pinagem:
    - Pino no arduino (Pino no ATMEGA328)
    
    - 11 (17): MOSI (NRF + SD)
    - 12 (18): MISO (NRF + SD)
    - 13 (19): SCK (NRF + SD)
    - 08 (14): CE (NRF)
    - 07 (13): CSN (NRF)
    - 10 (16): CS_PIN (SD)
    - 00 (02): RX (Comunicação serial)
    - 01 (03): TX (Comunicação serial)

    - 05 (11): RX (monitorSerial)
    - 06 (12): TX (monitorSerial)
*/

// Declaração de bibliotecas
#include "libs/NRF24L01_BIBLIOTECA.h"
#include "libs/ARMAZENAMENTO_BIBLIOTECA.h"
#include <SoftwareSerial.h>

#define timeOut 10

SoftwareSerial monitorSerial(5, 6);

void setup()
{
    monitorSerial.begin(9600);
    Serial.begin(9600);

    longRangeSettings();
    setAddress(ADDRESS_0, PIPE_0);
}

void loop() {

    if (monitorSerial.available() > 0) {
        String message = monitorSerial.readStringUntil('\n');
        Serial.println(message);
        
        writeOnSD(message);

        char str[32];
        message.toCharArray(str, 32);

        bool teste = sendMessage(str);
    }
}
