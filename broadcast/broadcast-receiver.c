#include "contiki.h"//es el que va a recibir la informacion, 
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"

#include <string.h> //para utilizar una funcion para copiar lo que hay en una variable a una variable dentro de una direccion

#include "sys/log.h" //para bitacoras dentro de contiki 
#define LOG_MODULE "Broadcast Receiver App" //declaramos unas constantes, nombre del modulo 
#define LOG_LEVEL LOG_LEVEL_INFO //para que imprima toda la informacion 
 
#define WAIT_INTERVAL (8 * CLOCK_SECOND)

PROCESS(broadcast_receiver, "Broadcast Received Example");
AUTOSTART_PROCESSES(&broadcast_receiver);

void input_callback(const void *data, uint16_t len,
    const linkaddr_t * source, const linkaddr_t *destination)//definicir una funcion para llamarla cada que reciba un paquete 
{
    if (len == sizeof(unsigned)){
        unsigned counter;
        memcpy(&counter, data, sizeof(counter));

        LOG_INFO("Received %u from ",(counter));
        LOG_INFO_LLADDR(source);
        LOG_INFO_("\n");
    }
}    