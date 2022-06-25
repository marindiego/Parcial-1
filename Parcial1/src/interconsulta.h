/*
 * interconsulta.h
 *
 *  Created on: 18 jun. 2022
 *      Author: Usuario
 */

#ifndef INTERCONSULTA_H_
#define INTERCONSULTA_H_


#define LEN_Interconsulta 14

#define CARGADO 1
#define VACIO 0

#include "utn_funciones.h"
#include "Especialidad.h"
#include "SignosVitales.h"


typedef struct{
	int idInterconsulta;
	char motivo[50];
	int idEspecialidad;
	int idSignosVitales;
	int isEmpty;
}Interconsulta;

int initInterconsultas(Interconsulta* list, int len);
int HardCodeInterconsultas (Interconsulta* list, int len_Interconsulta, int* idInterconsulta);
int printInterconsulta (Interconsulta* this);
int printInterconsultas (Interconsulta* list, int len_Interconsulta,Especialidad* listEsp, int len_especialidad, SignoVital* listSig, int len_sigVitales);

int interconsulta_BuscarEspacioLibre (Interconsulta* list, int len_Interconsulta);
int addInterconsulta (Interconsulta* list, int len_Interconsulta,char* motivo, int idConsulta, int idEspecialidad, int idSignoVital, int* nextId);



#endif /* INTERCONSULTA_H_ */
