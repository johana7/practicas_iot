#include "contiki.h" //para crear una aplicacion este encabezado
#include "dev/leds.h"
//hola prueba
#include <stdio.h>
  
PROCESS(hello_world_process, "Hello World");
AUTOSTART_PROCESSES(&hello_world_process);

PROCESS_THREAD(hello_world_process, ev, data)
{
PROCESS_BEGIN();

printf("Hello, World!\n");
leds_on(LEDS_ALL);

PROCESS_END();
}
