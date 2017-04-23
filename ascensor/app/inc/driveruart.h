/*=============================================================================
Ejercicio Entregable 10
Autores:
        Gessi Paniagua    gessi.paniagua@gmail.com
        Guillermo López   lopezg.ing@gmail.com
        Amid Ale          amidale@gmail.com
Implementación de MEF en un ascensor
MODULO driveruart Manejo de puerto Serial
 =============================================================================*/

#ifndef DRIVERUART_H
#define DRIVERUART_H

#include "sapi.h"

void entrarModoMenu(void);
void mostrarMenu(void);
void leerEntradaUsuario(void);

static bool_t nuevodato = 0;
static uint8_t dato;



#endif
