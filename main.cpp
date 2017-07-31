#include "mbed.h"

#define RUN_APPLICATION( app )     extern int app_##app(void); return app_##app();

Serial pc(STDIO_UART_TX,STDIO_UART_RX,115200);

int main( void )
{
   /* APPLICATION can be assigned to the folder names under folder "APP" */
   RUN_APPLICATION( mbed_wifi );

	return 0;
}
