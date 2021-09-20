#include "contiki.h" //vamos a tener dos nodos distintos, uno para enviar datos cada intervalo de tiempo y otro recibiendo los datos
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"

#include <string.h> //para utilizar una funcion para copiar lo que hay en una variable a una variable dentro de una direccion

#include "sys/log.h" //para bitacoras dentro de contiki 
#define LOG_MODULE "Broadcast Sending App" //declaramos unas constantes, nombre del modulo 
#define LOG_LEVEL LOG_LEVEL_INFO //bitacora para depuracion de la aplicacion. 

#define SEND_INTERVAL (8 * CLOCK_SECOND) // indicar cada cuando voy a enviar la informacion(8 segundos, clock_second=1,000 milisegundos)

PROCESS(broadcast_sender, "Broadcast Sender Example");
AUTOSTART_PROCESSES(&broadcast_sender);//es para decir a contiki cual es el proceso que se va a iniciaqlizar ya que se puede tener mas de un proceso

PROCESS_THREAD(broadcast_sender, ev data)//hacemos hilo process_thread de broadcast_sender,eventos y datos de entrada 
{
    static struct etimer periodic_timer;//declarar temporizador de eventos
    static unsigned counter =0;// declarar una variable de contador, con este para cada que yo este mandando un paquete le sumo 1 al contador para saber el lapzo de tiempo que trasncurrio

    PROCESS_BEGIN(); // inicar el proceso
    
    nullnet_buf = (uint8_t *) &counter;//variables que necesitan un nell para que todo lo que se aguarde en la variable counter (buffer del nullnet) todo lo que copie en esa variable ,automaticamente el nullnet va a enviar esa informacion a travez del medio fisico o red inalambrica, como todo buffer debe saber su tamaño se debe declarar como variable estatixa sin signo y se saca el tamaño para poder reservar el espacio en el buffer dentro del nullnet 
    nullnet_len = sizeof(counter);

    etimer_set(&periodic_timer, SEND_INTERVAL);//inicializar el timer periodico, y en SEND_INTERVAL va a enviar cada 8 segundos es decir cada que lo cumpla  
    while (1) {
            PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

            LOG_INFO("Sending %u\n", counter)//CON EL LOG_INFO ESTARA MOSTRANDO INFORMACION EN PANTALLA CUANDO HAYA DEFINIDO UN NIVEL DE LOG
            memcpy(nullnet_buf, &counter, sizeof(counter));
            nullnet_len = sizeof(counter);

            NETSTACK_NETWORK.output(NULL);
            counter++;

            etimer_reset(&periodic_timer);
    }
    PROCESS_END();
}