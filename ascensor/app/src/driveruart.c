/*=============================================================================
Ejercicio Entregable 10
Autores:
        Gessi Paniagua    gessi.paniagua@gmail.com
        Guillermo López   lopezg.ing@gmail.com
        Amid Ale          amidale@gmail.com
Implementación de MEF en un ascensor
MODULO driverio Manejo de entradas y salidas
 =============================================================================*/

#include "driveruart.h"

void entrarModoMenu(void)
    {
      uartConfig(UART_USB,115200); 
      mostrarMenu();
      leerEntradaUsuario();
    } 	

void mostrarMenu(void)
    {
      uint8_t menu[] = "Bienvenido al modo Configuración\r\nIngrese su opción:\r\n  1_ CONFIGURAR VELOCIDAD ENTRE PISO\r\n  2_ CONFIGURAR VELOCIDAD DE APERTURA/CIERRE DE PUERTA\r\n  3_ CONFIGURAR CANTIDAD DE PISOS (1 - 20)\r\n  4_ CONFIGURAR CANTIDAD DE SUBSUELOS (0 - 5)\r\n  5_ SALIR\r\n\r\n\r\n";
    
      uartWriteString(UART_USB,menu);
    }
    
void leerEntradaUsuario()
    {
      nuevodato = uartReadByte(UART_USB, dato);  
      while(!nuevodato);
      if (nuevodato){ 
      switch (dato)
            {
             case '1':
         	      
             break;
             
             case '2': 
               
 	   break;
             
             case '3':
               
	   break;
           
             case '4':   
               	     	
	   break;
           
             case '5':
                uartWriteString(UART_USB,"Configurado Hasta Luego!!!!\r\n");
     	   break;
     	  
     	   default :
     	      uartWriteString(UART_USB,"Opción invalida!!!");
     	      leerEntradaUsuario();
     	      
     	      
            }	}
    }