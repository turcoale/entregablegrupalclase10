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
typedef enum {EN_ESPERA1,DIGITO_1,DIGITO_2,GUARDANDO_PISO} estadoMEF1;

#define PISO_INVALIDO (-100)
#define TIEMPO_MAX_ALARMA (30)
#define TIEMPO_MAX_ABIERTA (10)
/*==================[internal data declaration]==============================*/
estadoMEF estadoActual;
estadoMEF1 estadoActual1;
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
return;
}
/* MAQUINA DE ESTADO DE LOS PISOS*/ 
void guardarPiso(char piso ){


}
char leertecla(void){

/* usar la sapi para leer el tecledo matricial aca */
return(0);
}


void inicializarMEF1(void)
{
	estadoActual1 = EN_ESPERA1;



}
void actualizarMEF1(void)
{
	char tecla = leertecla();
	char digito1=0;
	char digito2=0;
	
	switch(estadoActual1){
		case EN_ESPERA1:
			if((tecla <= 9) && (tecla >= 0)){
				estadoActual1=DIGITO_1;
				digito1=tecla;
				
			}
			
			break;
		case DIGITO_1:
			if((tecla <= 9) && (tecla >= 0)){
				estadoActual1=DIGITO_2;
				digito2=tecla;
				
			}
			if(tecla == 'B'){
				estadoActual1=EN_ESPERA1;			

			}
			if(tecla == 'A'){
				estadoActual1=GUARDANDO_PISO;
			}			
			break;
		case DIGITO_2:
			if(tecla == 'B'){
				estadoActual1=EN_ESPERA1;
				
			}
			if(tecla == 'A'){
				estadoActual1=GUARDANDO_PISO;
			}			
			break;
		case GUARDANDO_PISO:
			 guardarPiso( (digito1*10)+digito2);
			 estadoActual1=EN_ESPERA1;
					
			break;	
		default:
		
			inicializarMEF1();
		}
   return ;
}

/*==================[main function]==========================================*/

// MAIN FUNCTION, ENTRY PINT TO THE PROGRAM AFTER POR OR RESET.
int main( void ){

   // ---------- SETUP ----------------------------------------
   // Initialize an configurate the board
   boardConfig();

   // ---------- REPEAT FOR EVER ------------------------------
   while( TRUE ){
	actualizarMEF();
	actualizarMEF1();
	}

 

}


/*==================[external functions definition]==========================*/

/*==================[end of file]============================================*/
