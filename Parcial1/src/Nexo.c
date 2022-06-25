/*
 * Nexo.c
 *
 *  Created on: 4 jun. 2022
 *      Author: Usuario
 */

#include "Nexo.h"


void printConsultasOptionsMenu ()
{

	printf("\t\tPrograma de Passengers en C:\n\n"
			"\t\t1) ALTA CONSULTA\n\n"
			"\t\t2) MODIFICACION CONSULTA\n\n"
			"\t\t3) BAJA CONSULTA\n\n"
			"\t\t4) DIAGNOSTICAR CONSULTA\n\n"
			"\t\t5) INTERCONSULTA \n\n"
			"\t\t6) LISTAR CONSULTA\n\n"
			"\t\t7) Alta Forzada\n\n"
			"\t\t8) Salir\n"
			""
			"\n\n");
}
/// @brief Pide un numero si es 0 es verdadero si es 1 es falso
///
/// @param mensaje
/// @return
int consultas_confirmDecision (char* mensaje)
{
	int confirmar = -1;// Pointer NULL

	if(mensaje!=NULL)
	{
		confirmar = -3;// Invalid Opcion
		if (!utn_getNumero(&confirmar, mensaje, "\n\tSolo 1 o 0\n", 0, 1, 1)) {

			if (confirmar) {

				confirmar = 0; //Confirmar Decision
			}else{

				confirmar = 1; // Cancel decision
			}
		}
	}
	return confirmar;
}
/// @brief Funcion principal para diagnosticar una consulta
///
/// @param listDiag
/// @param len_Diagnostico
/// @param listMedicos
/// @param len_medicos
/// @return (0) todo bien
/// 		(2) Datos invalidos
///			(-1) NUll pointer or len <0
/// 		(-2) No existe ese id
///
int controller_diagnosticar (Consulta* listConsultas, int len_consultas,
							Diagnostico* listDiag, int len_Diagnostico,
							Medico* listMedicos, int len_medicos,
							Especialidad* listEsp, int len_especialidad,
							Interconsulta* listinter, int len_Interconsulta)
{
	int idMedico, idConsulta, idDiagnostico;
	int index;
	int retorno = -1;//NULL pointer or len <0

	if (	listMedicos!=NULL && len_medicos >0 &&
			listEsp !=NULL && len_especialidad >0 &&
			listConsultas !=NULL && len_consultas >0 &&
			listDiag!=NULL && len_Diagnostico>0 &&
			listinter!=NULL && len_Interconsulta>0) {

		retorno = 2;//Datos invalidos

		printEspecialidades(listEsp, len_especialidad);
		printMedicos(listMedicos, len_medicos);
		if (!consultas_getMedicoFromStdIn(&idMedico)) {

			retorno=printConsulasNoDiagnosticadas(listConsultas, len_consultas, listDiag, len_Diagnostico, listMedicos, len_medicos, listinter, len_Interconsulta);
			if (!retorno && !utn_getNumero(&idConsulta, "\nId Consulta: ", "\n\tError, Consulta invalida\n\n", 1, INT_MAX, 1)) {

				retorno =-2;//No existe el id
				if ((index=consultas_BuscarConsultaPorId(listConsultas, len_consultas, idConsulta))>=0) {

					retorno=6;//Ya esta diagnosticada
					if (listConsultas[index].idDiagnostico==0) {

						retorno=2; //Datos invalidos
						printDiagnosticos(listDiag, len_Diagnostico);
						if (!utn_getNumero(&idDiagnostico,"\nId Diagnostico: ", "\n\tError, Diagnostico invalido\n\n", 1,13,1)) {

							retorno =1; // Cancelar diagnostico
							if (!(consultas_confirmDecision(
									"\n--------------\n"
									"Confirmar\n"
									"---------------\n"
									"Estas seguro que quieres asignarle este Id a la consulta ingresada ?\n"
									"Escribi (1) |Confirmar|  -   Escribi (0)  |Cancelar|\n"
									"Decisicion: "))) {

								listConsultas[index].idDiagnostico = idDiagnostico;
								listConsultas[index].idMedico=idMedico;
								retorno = 0;
							}
						}
					}

				}
			}
		}
	}
	printEstadoDiagnosticarConsultas(retorno);
	return 0;
}
/// @brief Muestra los posibles retornos de la funcion diagnosticar
///
/// @param retorno
void printEstadoInterconsultas (int retorno)
{
	switch (retorno) {
			case 0:
				printf("\n\t!!---------INTERCONSULTA COMPLETADA----------!!\n\n");
				break;
			case 1:
				printf("\n\t\tINTERCONSULTA CANCELADA\n\n");
				break;
			case 2:
				printf("\nIngreso de datos invalidos\n\n");
				break;
			case 3:
				printf("\n\tNo hay mas espacio para añadir otra interconsulta\t\n\n");
				break;
			case 4:
				printf("\n\tPrimero da de alta un consulta para poder asignarle una interconsulta\t\n\n");
				break;
			case 5:
				printf("\n\tNo hay ninguna consulta diagnosticada\n\n");
				break;
			case 6:
				printf("\n\tEl Id de esa consulta no esta diagnosticada\n\n");
				break;
			case -1:
				printf("\n\tError[403] (NULL pointer - len < 0 ) \n\n");
				break;
			case -2:
				printf("\n\t\tNo existe ese id o fue dado antes de baja \n\n");
				break;

		}
}
/// @brief  Funcion principal de pedir los datos de una interconsulta y añadir el id a la lsita de Consultas
///
/// @param listConsultas
/// @param len_consultas
/// @param listInterconsulta
/// @param len_Interconsulta
/// @param listEsp
/// @param len_especialidad
/// @param listSig
/// @param len_sigVitales
/// @param listMedicos
/// @param len_medicos
/// @param listDiag
/// @param len_Diagnostico
/// @param idInterconsulta
/// @return
/// 		(0) todo bien
/// 		(2) Datos invalidos
///			(-1) NUll pointer or len <0
/// 		(-2) No existe ese id
/// 		(3) No hay mas espacio para añadir otra interconsulta
/// 		(4) Sin consultas
int controller_Interconsulta (	Consulta* listConsultas, int len_consultas,
								Interconsulta* listInterconsulta, int len_Interconsulta,
								Especialidad* listEsp, int len_especialidad,
								SignoVital* listSig, int len_sigVitales,
								Medico* listMedicos, int len_medicos,
								Diagnostico* listDiag, int len_Diagnostico , int* idInterconsulta)
{
	int retorno=-1;
	int  idConsulta, idEspecialidad, idSignoVital;
	int index;
	char motivo[50];

	if (	listInterconsulta!=NULL && len_Interconsulta>0 &&
			idInterconsulta!=NULL &&
			listEsp!=NULL && len_especialidad >0 &&
			listSig!=NULL && len_sigVitales >0 &&
			listMedicos!=NULL && len_medicos >0 &&
			listDiag!=NULL && len_Diagnostico>0	) {


		retorno=4; // Sin consultas
		if (!consultas_VereficarEspacio(listConsultas, len_consultas)) {

			retorno=printConsulasDiagnosticadas(listConsultas, len_consultas, listDiag, len_Diagnostico, listMedicos, len_medicos, listInterconsulta, len_Interconsulta);
			if (!retorno) {

				retorno = 2;//Datos invalidos
				if (!utn_getNumero(&idConsulta, "\nId Consulta: ", "\n\tError, Consulta invalida\n\n", 1, INT_MAX, 1)) {

					retorno =-2;//No existe el id
					if ((index=consultas_BuscarConsultaPorId(listConsultas, len_consultas, idConsulta))>=0) {

						retorno=6;//Sin consultas diagnosticadas
						if (listConsultas[index].idDiagnostico>0) {

							retorno=2; //Datos invalidos
							if (!utn_getAlphaNumerico(motivo,"\nMotivo de la interconsulta: ", "\n\tError, motivo invalido\n\n", 1, 45)) {

								printEspecialidades(listEsp, len_especialidad);
								if (!utn_getNumero(&idEspecialidad, "\nId Especialidad: ", "\n\tError, especialidad invalida\n\n", 1, 6, 1)) {

									printSignoVitales(listSig, len_sigVitales);
									if (!utn_getNumero(&idSignoVital, "\nId Signo: ", "\n\tError, signo invalido\n\n", 1, 3, 1)) {

										retorno =1; // Cancelar diagnostico
										if (!(consultas_confirmDecision(
											"\n--------------\n"
											"Confirmar\n"
											"---------------\n"
											"Estas seguro que quieres asignarle este Id a la consulta ingresada ?\n"
											"Escribi (1) |Confirmar|  -   Escribi (0)  |Cancelar|\n"
											"Decisicion: "))) {

											retorno =3; // No hay mas epsacio
											if (interconsulta_BuscarEspacioLibre(listInterconsulta, len_Interconsulta)>=0) {

												listConsultas[index].idInterconsulta = *idInterconsulta;
												retorno = addInterconsulta(listInterconsulta, len_Interconsulta, motivo, idConsulta, idEspecialidad, idSignoVital, idInterconsulta);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	printEstadoInterconsultas(retorno);
	return 0;
}
void printEstadoListar (int retorno)
{
	switch (retorno) {
			case 0:
				printf("\n\t!!---------LISTAR COMPLETADO----------!!\n\n");
				break;
			case 1:
				printf("\n\tNo hay ninguna consulta cargada en el programa, da de alta una primero en  =  | 1) ALTA Consulta | \n\n");
				break;
			case -1:
				printf("\n\tError[403] (NULL pointer - len < 0 ) \n\n");
				break;
			case 2:
				printf("\n\t!!---------SALIR COMPLETADO----------!!\n\n");
				break;


		}
}
void printOpcionListar ()
{
	printf("\n"
			"0) Todas las Interconsultas\n"
			"1) Todos los médicos.\n"
			"2) Todas las consultas.\n"
			"3) Todos los médicos con consultas diagnosticadas.\n"
			"4) Listado de consultas ordenadas por fecha, desde la más reciente hasta la más antigua\n"
			"5) Listado de consultas que ya fueron diagnosticadas.\n"
			"6) Listado de las consultas diagnosticadas con covid-19 desde el inicio de la pandemia hasta la actualidad\n"
			"de una especialidad\n"
			"7) Listado de consultas ordenadas por especialidad alfabéticamente\n"
			"8) Listado de todas las consultas entre el mes de abril y julio para una especialidad determinada.\n"
			"9) Porcentaje de consultas diagnosticadas que atiende cada médico en función del total de diagnósticos\n"
			"10) La enfermedad menos diagnosticada\n"
			"11) La especialidad más estudiada por los médicos.\n"
			"12) Listado de las consultas que tengan una interconsulta con una especialidad indicada y que los signos vitales esten estables\n"
			"13) Mostrar todas las listas de consultas, diagnosticos,medicos,especialidades,interconsultas,signos vitales\n"
			"14) Salir\n\n");
}
int printMedicosConsultasDiagnosticadas (Consulta* listConsultas, int len_consultas,
										 Medico* listMedicos, int len_medicos)
{
	int retorno=-1;
	sAux bufferMedicos[100];

	if (	listConsultas!=NULL && len_consultas >0 &&
			listMedicos!=NULL && len_medicos >0 ) {

		printf("\n"
				"  ------------------------------------------\n"
				" | Id  || Medico        || idEspecialidad   |\n"
				"  ------------------------------------------\n");

		for (int i = 0; i < len_medicos; i++) {
			bufferMedicos[i].id = listMedicos[i].idMedico;
			bufferMedicos[i].acumulador = 0;
		}
		for (int i = 0; i < len_consultas; i++) {
			for (int l = 0; l < len_medicos; l++) {
				if (	listConsultas[i].idMedico == listMedicos[l].idMedico &&
						listMedicos[l].idMedico >0){
					for (int k = 0; k < len_medicos; k++) {
						if (	bufferMedicos[k].id == listMedicos[l].idMedico &&
								bufferMedicos[k].acumulador == 0){

							bufferMedicos[k].acumulador++;
							printMedico((listMedicos+l));
						}
					}
				}
			}
		}
		printf("  ------------------------------------------\n");
		retorno = 0; //OK
	}
	return retorno;
}

/// @brief Clona una nueva lista de consulta
///
/// @param list
/// @return NULL if NULL pointer
/// 		a new copy
Consulta* cloneConsultas (Consulta* list)
{
	Consulta* listClone=NULL;
	if (list!=NULL) {
		listClone=list;
	}
	return listClone;
}
/// @brief Listado de consultas ordenadas por fecha
///
/// @param listConsultas
/// @param len_consultas
/// @return
int sortConsultasPorFecha (Consulta* listConsultas, int len_consultas, int order)
{
	int retorno=-1;
	int i;
	int flagSwap;
	Consulta buffer;

	if( listConsultas!=NULL &&  len_consultas>0 ){
		do{
			flagSwap=0;
			for(i=0; i<len_consultas-1 ; i++){

				if ((listConsultas+i)->isEmpty == VACIO || (listConsultas+i+1)->isEmpty == VACIO)
				{
					continue;
				}
				switch (order) {
					case 1:
						if (	listConsultas[i].fAtencion.anio > listConsultas[i+1].fAtencion.anio ||
								(listConsultas[i].fAtencion.anio == listConsultas[i+1].fAtencion.anio &&
								listConsultas[i].fAtencion.mes > listConsultas[i+1].fAtencion.mes) ||
								(listConsultas[i].fAtencion.mes == listConsultas[i+1].fAtencion.mes &&
								listConsultas[i].fAtencion.dia >= listConsultas[i+1].fAtencion.dia)) {

							flagSwap=1;
							buffer=listConsultas[i];
							listConsultas[i]=listConsultas[i+1];
							listConsultas[i+1]=buffer;
						}
						break;
					case 0:
						if (	listConsultas[i].fAtencion.anio < listConsultas[i+1].fAtencion.anio ||
								(listConsultas[i].fAtencion.anio == listConsultas[i+1].fAtencion.anio &&
								listConsultas[i].fAtencion.mes < listConsultas[i+1].fAtencion.mes) ||
								(listConsultas[i].fAtencion.mes == listConsultas[i+1].fAtencion.mes &&
								listConsultas[i].fAtencion.dia <= listConsultas[i+1].fAtencion.dia)) {

							flagSwap=1;
							buffer=listConsultas[i];
							listConsultas[i]=listConsultas[i+1];
							listConsultas[i+1]=buffer;
						}
						break;
				}
			}
			len_consultas--;
		}while(flagSwap);

		retorno=0;
	}

	return retorno;
}
/// @brief  Imprime las consultas con un iddiagnostico, especialidad y fecha especifica
///
/// @param listConsultas
/// @param len_consultas
/// @param listMedicos
/// @param len_medicos
/// @param listEsp
/// @param len_especialidad
/// @param idDiagnostico
/// @param idEspecialidad
/// @return
int printConsultasByDiagnosticoYEspecialidadYTiempo (Consulta* listConsultas, int len_consultas,
											  Medico* listMedicos, int len_medicos,
											  Especialidad* listEsp, int len_especialidad,
											  int idDiagnostico, int idEspecialidad,
											  int dia, int mes, int anio)
{
	int retorno =-1;
	int flagExitos=1;
	int flagFecha=1;
	if (	listMedicos!=NULL && len_medicos >0 &&
			listEsp!=NULL && len_especialidad >0 &&
			listConsultas!=NULL && len_consultas >0 &&
			idDiagnostico >=0 && idEspecialidad>=0 &&
			dia>0 && mes>0 && anio>0) {

		for (int i = 0; i < len_consultas; i++) {
			if (listConsultas[i].idDiagnostico==idDiagnostico &&
					listConsultas[i].fAtencion.dia >=dia &&
					listConsultas[i].fAtencion.mes >=mes &&
					listConsultas[i].fAtencion.anio >=anio) {
				flagFecha=0;
				for (int j = 0; j < len_medicos; j++) {
					if (listConsultas[i].idMedico == listMedicos[j].idMedico ) {
						for (int l = 0; l < len_especialidad; l++) {
							if (	listEsp[l].idEspecialidad==idEspecialidad &&
									listMedicos[j].idEspecialidad==idEspecialidad) {
								printf("  ----------------------------------------------------------------------------------------------------------------------\n");
								printConsulta(&listConsultas[i]);
								flagExitos=0;
							}
						}
					}
				}
			}
		}
		if (flagFecha) {
			printf("\n\tNo hay ninguna consulta registrada anterior a esa fecha:,(\n\n");
		}
		else{
			if (flagExitos) {
				printf("\n\tNo se encuentra ninguna consulta con esa especialidad con el diagnostico (Covid-19) desde el la pandemia\n\n");
			}
			else{
				printf("  ----------------------------------------------------------------------------------------------------------------------\n");
				retorno=0;
			}
		}
	}
	return retorno;
}
/// @brief BUsca la especialdad que le asignaron a esa consulta y o devuelve por referencia
///
/// @param listConsultas
/// @param len_consultas
/// @param listMedicos
/// @param len_medicos
/// @param listEsp
/// @param len_especialidad
/// @param especialidad
/// @param indice
/// @return
int consultas_buscarEspecialidadConsulta (	Consulta* listConsultas, int len_consultas,
											Medico* listMedicos, int len_medicos,
											Especialidad* listEsp, int len_especialidad, char* especialidad, int indice)
{
	int retorno=-1;

	if( 	listConsultas!=NULL &&  len_consultas>0 &&
				listMedicos!=NULL && len_medicos >0 &&
				listEsp!=NULL && len_consultas >0 &&
				indice >=0){


		for(int i=indice; i<len_consultas-1 ; i++){
			for (int j = 0; j < len_medicos; j++) {
				if (listConsultas[i].idMedico == listMedicos[j].idMedico ) {
					for (int l = 0; l < len_especialidad; l++) {
						if (listMedicos[j].idEspecialidad == listEsp[l].idEspecialidad) {
							strcpy(especialidad,listEsp[l].descripcion);
							return 0;
						}
					}
				}
			}
		}
	}
	return retorno;
}

/// @brief Ordena a los pasajeros dependiendo de la especialidad de la consulta
///
/// @param listConsultas
/// @param len_consultas
/// @param order
/// @param listEsp
/// @param len_especialidad
/// @return
int sortConsultasPorEspecialidad (Consulta* listConsultas, int len_consultas, int order,
								 Medico* listMedicos, int len_medicos,
								 Especialidad* listEsp, int len_especialidad)
{
	int retorno=-1;
	int i;
	int flagSwap;
	int auxcmp;
	char especialidad2[30];
	char especialidad1[30];
	Consulta buffer;

	if( 	listConsultas!=NULL &&  len_consultas>0 &&
			listMedicos!=NULL && len_medicos >0 &&
			listEsp!=NULL && len_consultas >0){

		do{
			flagSwap=0;
			for(i=0; i<len_consultas-1 ; i++){

				consultas_buscarEspecialidadConsulta(listConsultas, len_consultas, listMedicos, len_medicos, listEsp, len_especialidad, especialidad2, i+1);
				consultas_buscarEspecialidadConsulta(listConsultas, len_consultas, listMedicos, len_medicos, listEsp, len_especialidad, especialidad1, i);


				if ((listConsultas+i)->isEmpty == VACIO || (listConsultas+i+1)->isEmpty == VACIO)
				{
					continue;
				}
				auxcmp=stricmp(especialidad1,especialidad2);

				switch (order) {
				case 1:
					if (auxcmp > 0) {
						flagSwap=1;
						buffer=listConsultas[i];
						listConsultas[i]=listConsultas[i+1];
						listConsultas[i+1]=buffer;
					}
					break;
				case 0:
					if (auxcmp < 0	) {
						flagSwap=1;
						buffer=listConsultas[i];
						listConsultas[i]=listConsultas[i+1];
						listConsultas[i+1]=buffer;
					}
					break;
				}
			}
			len_consultas--;
		}while(flagSwap);

		retorno=0;
	}

	return retorno;
}
/// @brief Imprime las consultas entre 2 meses especificos y una especialidad
///
/// @param listConsultas
/// @param len_consultas
/// @param listMedicos
/// @param len_medicos
/// @param listEsp
/// @param len_especialidad
/// @param idEspecialidad
/// @param entre
/// @param hasta
/// @return
int printConsultasEntreMesYEspecialidad (	Consulta* listConsultas, int len_consultas,
											Medico* listMedicos, int len_medicos,
											Especialidad* listEsp, int len_especialidad,
											int idEspecialidad,
											int entre, int hasta)
{
	int retorno =-1;
	int flagExitos=1;
	int flagFecha=1;
	if (	listMedicos!=NULL && len_medicos >0 &&
			listEsp!=NULL && len_especialidad >0 &&
			listConsultas!=NULL && len_consultas >0 &&
			idEspecialidad>=0 &&
			entre>0 &&  hasta>0) {

		for (int i = 0; i < len_consultas; i++) {
			if (listConsultas[i].fAtencion.mes >=entre && listConsultas[i].fAtencion.mes <=hasta) {
				flagFecha=0;
				for (int j = 0; j < len_medicos; j++) {
					if (listConsultas[i].idMedico == listMedicos[j].idMedico ) {
						for (int l = 0; l < len_especialidad; l++) {
							if (	listMedicos[j].idEspecialidad == listEsp[l].idEspecialidad &&
									listMedicos[j].idEspecialidad ==idEspecialidad) {
								printf("  ----------------------------------------------------------------------------------------------------------------------\n");
								printConsulta(&listConsultas[i]);
								printf("  ----------------------------------------------------------------------------------------------------------------------\n");
								flagExitos=0;
							}
						}
					}
				}
			}
		}
		if (flagFecha) {
			printf("\n\tNo hay ninguna consulta registrada en  esa fecha:,(\n\n");
		}
		else{
			if (flagExitos) {
				printf("\n\tNo se encuentra ninguna consulta con esa especialidad \n\n");
			}
		}
		retorno=0;
	}
	return retorno;
}
/// @brief  Imprime los medicos con el porcentaje de consultas que ya diagnosticaron
///
/// @param listConsultas
/// @param len_consultas
/// @param listMedicos
/// @param len_medicos
/// @return
int printPorcentajeConsultasPorMedico (Consulta* listConsultas, int len_consultas,
							Medico* listMedicos, int len_medicos)
{
	int retorno =-1;
	int contadorDiagnosticadas=0;
	sAux bufferContador[100];

	if (	listMedicos!=NULL && len_medicos >0 &&
			listConsultas!=NULL && len_consultas >0 ){

		for (int i = 0; i < len_medicos; i++) {
			bufferContador[i].id= listMedicos[i].idMedico;
			strcpy(bufferContador[i].nombre,listMedicos[i].nombre);
			bufferContador[i].acumulador= 0;
		}

		for (int i = 0; i < len_consultas; i++) {
			if (listConsultas[i].idDiagnostico >0) {
				contadorDiagnosticadas+=10;
				for (int j = 0; j < len_medicos; j++) {
					if (listConsultas[i].idMedico == listMedicos[j].idMedico) {
						bufferContador[j].acumulador+=10;
					}
				}
			}
		}
		printf("\n"
				"  ------------------------------------------\n"
				" | Id  || Medico        || idEspecialidad   |\n"
				"  ------------------------------------------\n");
		for (int i = 0; i < len_medicos; i++) {
			printf(" |%2d)  || %-8s      ||       %-2d%%       |\n",bufferContador[i].id,bufferContador[i].nombre,bufferContador[i].acumulador);
		}
		printf("  ------------------------------------------\n");
		retorno=0;
	}
	return retorno;
}
/// @brief Imprime las enfermedades menos diagnosticas
///
/// @param listConsultas
/// @param len_consultas
/// @param listDiag
/// @param len_Diagnostico
/// @return
int printEnfermedadMenosDiagnosticada (  Consulta* listConsultas, int len_consultas,
										 Diagnostico* listDiag, int len_Diagnostico)
{
	int retorno=-1;
	int flagMenor=1;
	int idEnfermedadMenor;
	int min;
	sAux buffer[50];
	if (listConsultas!=NULL && len_consultas > 0) {

		retorno=0;
		for (int i = 0; i < len_consultas; i++) {
			buffer[i].id=listConsultas[i].idConsulta;
			buffer[i].acumulador=0;
			buffer[i].fk=listConsultas[i].idDiagnostico;
		}
		for (int i = 0; i < len_consultas; i++) {
			for (int j = 0; j < len_Diagnostico; j++) {
				if (listConsultas[i].idDiagnostico == listDiag[j].idDiagnostico) {
					for (int k = 0; k < len_consultas; k++) {
						if (listConsultas[i].idDiagnostico==buffer[k].fk ) {
							buffer[k].acumulador++;
							buffer[k].fk=listConsultas[i].idDiagnostico;
						}
					}
				}
			}
		}
		for (int i = 0; i < len_consultas; i++) {

			if (flagMenor || min >= buffer[i].acumulador) {
				idEnfermedadMenor=buffer[i].fk;
				min=buffer[i].acumulador;
				flagMenor=0;
			}
		}
		printf("\n"
				"  ----------------------------------\n"
				" | Id  || Diagnostico               |\n"
				"  ----------------------------------\n");
		for (int i = 0; i < len_Diagnostico; i++) {
			if (listDiag[i].idDiagnostico == idEnfermedadMenor) {
				printDiagnostico(&listDiag[i]);
			}
		}
		printf("  ----------------------------------\n");

	}
	return retorno;
}
/// @brief Imprime las especialidad mas estudiada por los medicos
///
/// @param listMedicos
/// @param len_medicos
/// @param listEsp
/// @param len_especialidad
/// @return
int printEspecialidadMasEstudiada (Medico* listMedicos, int len_medicos,
								   Especialidad* listEsp, int len_especialidad )
{
	int retorno=-1;
	int flagMayor=1;
	int idEspecialidadMayor;
	int max;
	sAux buffer[50];

	if ( 	listMedicos!=NULL && len_medicos >0 &&
			listEsp!=NULL && len_especialidad >0 ) {

		for (int i = 0; i < len_medicos; i++) {
			buffer[i].id=listMedicos[i].idMedico;
			buffer[i].acumulador=0;
			buffer[i].fk=listMedicos[i].idEspecialidad;
		}
		for (int i = 0; i < len_medicos; i++) {
			for (int j = 0; j < len_especialidad; j++) {
				if (listMedicos[i].idEspecialidad == listEsp[j].idEspecialidad) {
					for (int k = 0; k < len_medicos; k++) {
						if (listMedicos[i].idEspecialidad ==buffer[k].fk){
							buffer[k].acumulador++;
							buffer[k].fk=listMedicos[i].idEspecialidad;
						}
					}
				}
			}
		}
		for (int i = 0; i < len_medicos; i++) {

			if (flagMayor || max <= buffer[i].acumulador) {
				idEspecialidadMayor=buffer[i].fk;
				max =buffer[i].acumulador;
				flagMayor=0;
			}
		}
		printf("\n"
				"  -------------------------\n"
				" | Id  || Especialidad     |\n"
				"  -------------------------\n");
		for (int i = 0; i < len_especialidad; i++) {
			if (listEsp[i].idEspecialidad == idEspecialidadMayor) {
				printEspecialidad(&listEsp[i]);
			}
		}
		printf("  -------------------------\n");
		printMedicos(listMedicos, len_medicos);
		retorno=0;
	}
	return retorno;
}

int printConsultaPorEspecialidadYSignosVitales ( Consulta* listConsultas, int len_consultas,
													  Interconsulta* listInterconsulta, int len_Interconsulta,
													  Especialidad* listEsp, int len_especialidad,
													  SignoVital* listSig, int len_sigVitales,
													  int idEspecialidad, int idSignosVitales)
{
	int retorno=-1;
	int flagEsp=1;
	int flagSig=1;

	if (listConsultas !=NULL && len_Interconsulta > 0 &&
		listInterconsulta!=NULL && len_Interconsulta > 0 &&
		listEsp!=NULL && len_especialidad > 0 &&
		idEspecialidad && idSignosVitales >0 &&
		listSig!=NULL && len_sigVitales > 0 ){

		for (int i = 0; i < len_consultas; i++) {
			if (listConsultas[i].idInterconsulta>0) {
				for (int j = 0; j < len_Interconsulta; j++) {
					if (listConsultas[i].idInterconsulta == listInterconsulta[j].idInterconsulta &&
						listInterconsulta[j].idEspecialidad == idEspecialidad ){
						flagEsp=0;
						if(listInterconsulta[j].idSignosVitales == idSignosVitales){
							flagSig=0;
							printf("  ----------------------------------------------------------------------------------------------------------------------\n");
							printConsulta(&listConsultas[i]);
							printf("  ----------------------------------------------------------------------------------------------------------------------\n");
						}
					}
				}
			}
		}
		if (flagEsp) {
			printf("\n\tNo hay ninguna interconsulta con esa especialidad\n\n");
		}
		else{
			if (flagSig){
				printf("\n\tNo hay ninguna interconsulta con esos signos vitales\n\n");
			}
		}
		retorno=0;
	}
	return retorno;
}
/// @brief Ordena las consultas por Id
///
/// @param lista
/// @param len
/// @return
int sortConsultasById (Consulta* lista,int len)
{
	int retorno=-1;
	int i;
	int contador=0;
	int flagSwap;
	Consulta buffer;

	if( lista!=NULL &&  len>0 ){
		do{
			flagSwap=0;
			for(i=0; i<len-1 ; i++){
				contador++;
				if( lista[i].idConsulta > lista[i+1].idConsulta)
				{
					flagSwap=1;
					buffer=lista[i];
					lista[i]=lista[i+1];
					lista[i+1]=buffer;
				}
			}
			len--;
		}while(flagSwap);

		retorno=contador;
	}

	return retorno;
}
/// @brief FUncion principal de listar  y ordenar todas las entidades del programa
///
/// @param listConsultas
/// @param len_consultas
/// @param listInterconsulta
/// @param len_Interconsulta
/// @param listEsp
/// @param len_especialidad
/// @param listSig
/// @param len_sigVitales
/// @param listMedicos
/// @param len_medicos
/// @param listDiag
/// @param len_Diagnostico
/// @param idInterconsulta
/// @retur (0) Todo bien
///        (1) No hay consultas
///        (2) Salir Completado
///        (-1) NULL pointer or len <0
int controller_Listar (	Consulta* listConsultas, int len_consultas,
						Interconsulta* listInterconsulta, int len_Interconsulta,
						Especialidad* listEsp, int len_especialidad,
						SignoVital* listSig, int len_sigVitales,
						Medico* listMedicos, int len_medicos,
						Diagnostico* listDiag, int len_Diagnostico )
{

	int retorno =-1;
	int opcion,opcion2, opcion3,idEspecialidad;

	Consulta* bufferList = cloneConsultas(listConsultas);

	if (		bufferList!=NULL &&
				listConsultas!=NULL && len_consultas >0 &&
				listInterconsulta!=NULL && len_Interconsulta>0 &&
				listEsp!=NULL && len_especialidad >0 &&
				listSig!=NULL && len_sigVitales >0 &&
				listMedicos!=NULL && len_medicos >0 &&
				listDiag!=NULL && len_Diagnostico>0) {

		retorno=1;
		if (!consultas_VereficarEspacio(listConsultas, len_consultas)) {

			//1 = A-Z - 0 = Z-A
			retorno = 0;
			do {
				printOpcionListar ();

				if (!utn_getNumero(&opcion, "\nOpcion: ", "\n\tError opcion invalida\n", 0, 14, INT_MAX)) {

					switch (opcion) {
						case 0:
							printInterconsultas(listInterconsulta, len_Interconsulta, listEsp, len_especialidad, listSig, len_sigVitales);
							break;
						case 1:
							printMedicos(listMedicos, len_medicos);
							break;
						case 2:
							printConsultas(bufferList, len_consultas, listDiag, len_Diagnostico, listMedicos, len_medicos, listInterconsulta, len_Interconsulta);
							break;
						case 3:
							printEspecialidades(listEsp, len_especialidad);
							printMedicosConsultasDiagnosticadas(bufferList, len_consultas, listMedicos, len_medicos);
							//Medicos con consultas diagnosticadas mostrar especialidades
							break;
						case 4:
							if (!utn_getNumero(&opcion2, "\n\n1) menor a mayor\n0)mayor a menor\nOpcion: ", "\n\tError opcion invalida\n", 0, 1, 0)) {

								sortConsultasPorFecha(bufferList, len_consultas, opcion2);
								printConsultas(bufferList, len_consultas, listDiag, len_Diagnostico, listMedicos, len_medicos, listInterconsulta, len_Interconsulta);
								sortConsultasById(bufferList, len_consultas);
							}
							break;
						case 5:
							printConsulasDiagnosticadas(listConsultas, len_consultas, listDiag, len_Diagnostico, listMedicos, len_medicos, listInterconsulta, len_Interconsulta);
							break;
						case 6:
							printEspecialidades(listEsp, len_especialidad);
							if (!utn_getNumero(&idEspecialidad, "\nIngrese un Id: ", "\n\tError opcion invalida\n", 1, 6, 0)) {
								printMedicos(listMedicos, len_medicos);
								printConsultasByDiagnosticoYEspecialidadYTiempo(bufferList, len_consultas, listMedicos, len_medicos, listEsp, len_especialidad, 2, idEspecialidad,3,3,2020);
							}
							break;
						case 7:
							if (!utn_getNumero(&opcion3, "\n\n1) A - Z\n0)Z - A\nOpcion: ", "\n\tError opcion invalida\n", 0, 1, 0)) {

								sortConsultasPorEspecialidad(bufferList, len_consultas, opcion3, listMedicos, len_medicos, listEsp, len_especialidad);
								printConsultas(bufferList, len_consultas, listDiag, len_Diagnostico, listMedicos, len_medicos, listInterconsulta, len_Interconsulta);
								sortConsultasById(bufferList, len_consultas);
							}
							break;
						case 8:
							printEspecialidades(listEsp, len_especialidad);
							if (!utn_getNumero(&idEspecialidad, "\nIngrese un Id: ", "\n\tError opcion invalida\n", 1, 6, 0)) {
								printMedicos(listMedicos, len_medicos);
								printConsultasEntreMesYEspecialidad(bufferList, len_consultas, listMedicos, len_medicos, listEsp, len_especialidad, idEspecialidad,4 ,7);
							}
							break;
						case 9:
							printPorcentajeConsultasPorMedico(listConsultas, len_consultas, listMedicos, len_medicos);
							break;
						case 10:
							printEnfermedadMenosDiagnosticada(listConsultas, len_consultas, listDiag, len_Diagnostico);
							break;
						case 11:
							printEspecialidadMasEstudiada(listMedicos, len_medicos, listEsp, len_especialidad);
							break;
						case 12:
							printEspecialidades(listEsp, len_especialidad);
							if (!utn_getNumero(&idEspecialidad, "\nOpcion: ", "\n\tError, Opcion invalida\n\n", 1, 6, 0)) {
								printConsultaPorEspecialidadYSignosVitales(listConsultas, len_consultas, listInterconsulta, len_Interconsulta, listEsp, len_especialidad, listSig, len_sigVitales, idEspecialidad, 1);
							}
							break;
						case 13:
							printSignoVitales(listSig, len_sigVitales);
							printInterconsultas(listInterconsulta, len_Interconsulta, listEsp, len_especialidad, listSig, len_sigVitales);
							printDiagnosticos(listDiag, len_Diagnostico);
							printEspecialidades(listEsp, len_especialidad);
							printMedicos(listMedicos, len_medicos);
							printConsultas(listConsultas, len_consultas, listDiag, len_Diagnostico, listMedicos, len_medicos, listInterconsulta, len_Interconsulta);
							break;
						case 14:
							retorno=2;
							break;
					}
				}
			} while (opcion!=14);
		}
	}
	printEstadoListar(retorno);
	return 0;
}
int controller_hardCode (	Consulta* listConsultas, int len_consultas,
							Interconsulta* listInterconsulta, int len_Interconsulta,
							int* nextIdConsulta, int* nextIdinterconsulta)
{
	int retorno =-1;

	if (	listConsultas!=NULL &&
			listConsultas!=NULL && len_consultas >0 &&
			listInterconsulta!=NULL && len_Interconsulta>0 &&
			nextIdConsulta!=NULL && nextIdinterconsulta !=NULL) {

		retorno=1;
		if (!(consultas_confirmDecision(
				"\n--------------\n"
				"Confirmar\n"
				"---------------\n"
				"Estas seguro que quieres cargar datos de prueba?\n se van a sobreescirbir los datos de las consultas anteriormente guardados\n"
				"Escribi (1) |Confirmar|  -   Escribi (0)  |Cancelar|\n"
				"Decisicion: "))) {

			retorno =0;

			HardCodeInterconsultas(listInterconsulta, LEN_Interconsulta,nextIdinterconsulta);

			HardCodeConsultas(listConsultas, LEN_CONSULTA,nextIdConsulta);

		}
	}
	switch (retorno) {
		case 0:
			printf("\n\t...........!HardCode Completado!............\n\n");
			break;
		case -1:
			printf("\n\tNUll pointer or len < 0\n\n");
			break;
		case 1:
			printf("\n\t............!HardCode Cancelado!...............\n\n");
			break;
	}
	return retorno;
}
