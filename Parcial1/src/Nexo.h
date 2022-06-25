/*
 * Nexo.h
 *
 *  Created on: 4 jun. 2022
 *      Author: Usuario
 */

#ifndef NEXO_H_
#define NEXO_H_

#include "interconsulta.h"
#include "Consulta.h"
#include "Medico.h"
#include "Diagnostico.h"
#include "Especialidad.h"
#include "SignosVitales.h"
#include "utn_funciones.h"

typedef struct{
	int id;
	char nombre[50];
	int acumulador;
	int fk;
}sAux;


void printConsultasOptionsMenu ();


int controller_diagnosticar (Consulta* listConsultas, int len_consultas,Diagnostico* listDiag, int len_Diagnostico,Medico* listMedicos, int len_medicos,Especialidad* listEsp, int len_especialidad,Interconsulta* listinter, int len_Interconsulta);

void printEstadoInterconsultas (int retorno);

int controller_Interconsulta (Consulta* listConsultas, int len_consultas,Interconsulta* list, int len_Interconsulta,Especialidad* listEsp, int len_especialidad, SignoVital* listSig, int len_sigVitales,Medico* listMedicos, int len_medicos,	Diagnostico* listDiag, int len_Diagnostico,int* idInterconsulta);



void printEstadoListar (int retorno);
void printOpcionListar ();
int printMedicosConsultasDiagnosticadas (Consulta* listConsultas, int len_consultas,Medico* listMedicos, int len_medicos);

Consulta* cloneConsultas (Consulta* list);

int sortConsultasPorFecha (Consulta* listConsultas, int len_consultas, int order);
int printConsultasByDiagnosticoYEspecialidadYTiempo (Consulta* listConsultas, int len_consultas, Medico* listMedicos, int len_medicos,	 Especialidad* listEsp, int len_especialidad,  int idDiagnostico, int idEspecialidad,int dia, int mes, int anio);
int consultas_buscarEspecialidadConsulta (	Consulta* listConsultas, int len_consultas,Medico* listMedicos, int len_medicos,Especialidad* listEsp, int len_especialidad, char* especialidad, int indice);

int sortConsultasPorEspecialidad (Consulta* listConsultas, int len_consultas, int order,Medico* listMedicos, int len_medicos,Especialidad* listEsp, int len_especialidad);

int printConsultasEntreMesYEspecialidad (Consulta* listConsultas, int len_consultas,Medico* listMedicos, int len_medicos,Especialidad* listEsp, int len_especialidad,int idEspecialidad,int entre, int hasta);

int printConsultaPorEspecialidadYSignosVitales ( Consulta* listConsultas, int len_consultas,Interconsulta* listInterconsulta, int len_Interconsulta,Especialidad* listEsp, int len_especialidad,SignoVital* listSig, int len_sigVitales,int idEspecialidad, int idSignosVitales);

int sortConsultasById (Consulta* lista,int len);

int controller_Listar (	Consulta* listConsultas, int len_consultas,Interconsulta* listInterconsulta, int len_Interconsulta,Especialidad* listEsp, int len_especialidad,SignoVital* listSig, int len_sigVitales,Medico* listMedicos, int len_medicos,Diagnostico* listDiag, int len_Diagnostico);

int controller_hardCode (	Consulta* listConsultas, int len_consultas,Interconsulta* listInterconsulta, int len_Interconsulta,	int* nextIdConsulta, int* nextIdinterconsulta );
#endif /* NEXO_H_ */
