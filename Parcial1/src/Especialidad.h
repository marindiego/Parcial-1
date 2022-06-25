/*
 * Especialidad.h
 *
 *  Created on: 18 jun. 2022
 *      Author: Usuario
 */

#ifndef ESPECIALIDAD_H_
#define ESPECIALIDAD_H_


#define LEN_Especialidades 7


#include "utn_funciones.h"

typedef struct{
	int idEspecialidad;
	char descripcion[50];
}Especialidad;



int HardCodeEspecialidades (Especialidad* list, int len);
int printEspecialidad (Especialidad* this);
int printEspecialidades (Especialidad* list, int len_especialidad);

#endif /* ESPECIALIDAD_H_ */
