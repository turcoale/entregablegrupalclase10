/*=============================================================================
Ejercicio Entregable 10
Autores:
        Gessi Paniagua
        Guillermo López
        Amid Ale
Implementación de MEF en un ascensor
 =============================================================================*/
 

/*==================[inclusions]=============================================*/

#include "program.h"   // <= Own header
#include "sapi.h"      // <= sAPI library

/*==================[macros and definitions]=================================*/
typedef enum {EN_ESPERA,MODO_CONFIGURACION,BAJANDO,LEER_PISO,SUBIENDO,
ABRIENDO_PUERTA,PUERTA_ABIERTA,ALARMA_PUERTA_ABIERTA,CERRANDO_PUERTA,PUERTA_CERRADA} estadoMEF;

#define PISO_INVALIDO (-100)
#define TIEMPO_MAX_ALARMA (30)
#define TIEMPO_MAX_ABIERTA (10)
/*==================[internal data declaration]==============================*/
estadoMEF estadoActual;
bool configurar= false;
int nuevo_piso=PISO_INVALIDO;
int pisoActual=0;
bool sensor_puerta= false;
int tiempoAlarma =0;
int tiempoAbierta=0;


/*==================[internal functions declaration]=========================*/
void inicializarMEF(void);
void actualizarMEF(void);


/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[main function]==========================================*/

// MAIN FUNCTION, ENTRY PINT TO THE PROGRAM AFTER POR OR RESET.
int main( void ){

   // ---------- SETUP ----------------------------------------
   // Initialize an configurate the board
   boardConfig();

   // ---------- REPEAT FOR EVER ------------------------------
   while( TRUE )
   {
      // If TEC1 is pressed, turn on the LEDB
      gpioWrite( LEDB, !(gpioRead(TEC1)) );

      // If TEC2 is pressed, turn on the LED1
      gpioWrite( LED1, !(gpioRead(TEC2)) );

      // If TEC3 is pressed, turn on the LED2
      gpioWrite( LED2, !(gpioRead(TEC3)) );

      // If TEC4 is pressed, turn on the LED3
      gpioWrite( LED3, !(gpioRead(TEC4)) );
   }

   // IT SHOULD NEVER COME HERE, because this program runs directly on a
   // microcontroller and is not called by any Operating System, as in
   // case of a PC program.
   return 0;
}

/*==================[internal functions definition]==========================*/
void inicializarMEF(void)
{
	estadoActual = EN_ESPERA;
	nuevo_piso=PISO_INVALIDO;
	pisoActual=0;
}


void actualizarMEF(void)
{	
	switch(estadoActual){
		case EN_ESPERA:
			if(configurar== true){
				estadoActual=MODO_CONFIGURACION;
			}
			if(nuevo_piso!= PISO_INVALIDO){
				estadoActual=LEER_PISO;
			}
			
			break;
		case MODO_CONFIGURACION:
			if(configurar==false){
				estadoActual= EN_ESPERA;
			}			
			break;
		case BAJANDO:
			//ENCENDER MOTOR PARA BAJAR
			
			if(pisoActual==nuevo_piso){
				estadoActual= ABRIENDO_PUERTA;
				pisoActual=nuevo_piso;
				nuevo_piso=PISO_INVALIDO;
			}
			

			break;
		case LEER_PISO:
			// leer piso desde teclado
			if(nuevo_piso > pisoActual){
				estadoActual=SUBIENDO;
			}
			if(nuevo_piso < pisoActual){
				estadoActual=BAJANDO;
			}			
			break;	
		case SUBIENDO:
			// ENCENDER MOTOR PARA SUBIR
			if(pisoActual== nuevo_piso){
				estadoActual=ABRIENDO_PUERTA;
				pisoActual=nuevo_piso;
				nuevo_piso=PISO_INVALIDO;
			}
			break;
		case ABRIENDO_PUERTA:
			// ABRIR PUERTA
			if(sensor_puerta == true){
				estadoActual=PUERTA_ABIERTA;	
			}
			
			break;
		case PUERTA_ABIERTA:
			if(tiempoAlarma >=TIEMPO_MAX_ALARMA){
				estadoActual=ALARMA_PUERTA_ABIERTA;
			}
			if(tiempoAbierta >= TIEMPO_MAX_ABIERTA){
				estadoActual= CERRANDO_PUERTA;
			}
			
			
			break;
		case ALARMA_PUERTA_ABIERTA:
			if(tiempoAlarma == 0){
				estadoActual= PUERTA_ABIERTA;
			}
			
			break;
		case CERRANDO_PUERTA:
			if(sensor_puerta == true){
				estadoActual= ABRIENDO_PUERTA;
			}
			else{
				estadoActual= PUERTA_CERRADA;
			}
			break;
		case PUERTA_CERRADA:
			if(nuevo_piso > pisoActual){
				estadoActual=SUBIENDO;
			}
			if(nuevo_piso < pisoActual){
				estadoActual=BAJANDO;
			}
			break;
		default:
		
			inicializarMEF();
		          break;
	}
}



/*==================[external functions definition]==========================*/

/*==================[end of file]============================================*/
