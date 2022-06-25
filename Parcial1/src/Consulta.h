/*
 * Consulta.h
 *
 *  Created on: 27 may. 2022
 *      Author: Usuario
 */

#ifndef CONSULTA_H_
#define CONSULTA_H_

#include "Medico.h"
#include "utn_funciones.h"
#include "interconsulta.h"
#include "Diagnostico.h"

#define LEN_CONSULTA 11
#define LEN_NOMBRE 9

#define CARGADO 1
#define VACIO 0


typedef struct{
	int dia;
	int mes;
	int anio;
}Fecha;

typedef struct{
	int idConsulta;
	char nombre[50];
	Fecha fAtencion;
	int idDiagnostico;
	int idMedico;
	int idInterconsulta;
	int isEmpty;
}Consulta;

int consultas_confirmDecision (char* mensaje);

int HardCodeConsultas (Consulta* list, int len_consultas,int* nextIdConsulta);
int printConsulta (Consulta* this);
int printConsultas (Consulta* listConsultas, int len_consultas,Diagnostico* listDiag, int len_Diagnostico,Medico* listMedicos, int len_medicos,Interconsulta* listinter, int len_Interconsulta);
int printConsulasNoDiagnosticadas (Consulta* listConsultas, int len_consultas,Diagnostico* listDiag, int len_Diagnostico,Medico* listMedicos, int len_medicos,Interconsulta* listinter, int len_Interconsulta);
int printConsulasDiagnosticadas (Consulta* listConsultas, int len_consultas,Diagnostico* listDiag, int len_Diagnostico,Medico* listMedicos, int len_medicos,Interconsulta* listinter, int len_Interconsulta);


int initConsultas(Consulta* listConsultas, int len_consultas);
int consultas_VereficarEspacio (Consulta* listConsultas, int len_consultas);
int consultas_BuscarEspacioLibre (Consulta* listConsultas, int len_consultas);
int consultas_BuscarConsultaPorId (Consulta* listConsultas, int len_consultas, int id);


/*
 * Baja
*/

int removeConsulta (Consulta* listConsultas, int len_consultas, int id);

void printEstadoBajaConsultas (int retorno);

int controller_BajaConsultas (Consulta* listConsultas, int len_consultas, Diagnostico* listDiag, int len_Diagnostico, Medico* listMedicos, int len_medicos,Interconsulta* listinter, int len_Interconsulta);

/*
 * Alta
*/

int consultas_getNameFromStdIn (char* name);
int consultas_getFechaFromStdIn (Fecha* atencion);
int consultas_getMedicoFromStdIn (int* medico);

void printEstadoAltaConsultas (int retorno);

int addConsulta (Consulta* listConsultas, int len_consultas,char* nombre, Fecha atencion, int* nextIdConsulta);
int controller_AltaConsultas (Consulta* listConsultas, int len_consultas,int* nextIdConsulta);

/*
 * Modificacion
*/
int consultas_getNewNombreFromStdin(Consulta* this);
int consultas_getNewFechaFromStdin(Consulta* this);
int consultas_getNewMedicoFromStdin(Consulta* this,Medico* listMedicos, int len_medicos);

void consultas_printOptionsModificar();

int consultas_ediConsulta (Consulta* this,Medico* listMedicos, int len_medicos);

void printEstadoModificacionConsultas (int retorno);
int controller_ModificacionConsultas (Consulta* listConsultas, int len_consultas,Diagnostico* listDiag, int len_Diagnostico,Medico* listMedicos, int len_medicos,Interconsulta* listinter, int len_Interconsulta);

#endif /* CONSULTA_H_ */
