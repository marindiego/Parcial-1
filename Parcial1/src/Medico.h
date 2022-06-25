/*
 * Medico.h
 *
 *  Created on: 27 may. 2022
 *      Author: Usuario
 */

#ifndef MEDICO_H_
#define MEDICO_H_

#define LEN_Medico 9

#include "utn_funciones.h"
#include "ValidacionesGenericos.h"
#include "interconsulta.h"
#include "Diagnostico.h"
#include "Especialidad.h"
#include "SignosVitales.h"

typedef struct{
	int idMedico;
	char nombre[50];
	int idEspecialidad;
}Medico;


/*
 * Hardcode
 */

int HardCodeMedicos (Medico* list, int len);
int printMedico (Medico* this);
int printMedicos (Medico* listMedicos, int len_medicos);




#endif /* MEDICO_H_ */
