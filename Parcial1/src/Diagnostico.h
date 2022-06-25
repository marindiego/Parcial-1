/*
 * Diagnostico.h
 *
 *  Created on: 18 jun. 2022
 *      Author: Usuario
 */

#ifndef DIAGNOSTICO_H_
#define DIAGNOSTICO_H_

#include "utn_funciones.h"
#include "Medico.h"
#include "interconsulta.h"


#define LEN_DIAGNOSTICO 16

typedef struct{
	int idDiagnostico;
	char descripcion[25];
}Diagnostico;

int HardCodeDiagnosticos (Diagnostico* list, int len);
int printDiagnostico (Diagnostico* this);
int printDiagnosticos (Diagnostico* list, int len_Diagnostico);

void printEstadoDiagnosticarConsultas (int retorno);


#endif /* DIAGNOSTICO_H_ */
