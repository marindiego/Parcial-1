/*
 * Consulta.c
 *
 *  Created on: 27 may. 2022
 *      Author: Usuario
 */

#include "Consulta.h"

/// @brief Carga 10 consultas en el vector de consultas
///
/// @param list
/// @param len_consultas
/// @return
int HardCodeConsultas (Consulta* list, int len_consultas,int* nextIdConsulta)
{
	int retorno = -1;
	if (list!=NULL && len_consultas>0) {

		Consulta buffer[15]=
					{{1,"Veronica",{5,6,2022},2,4,3,CARGADO},
					{2,"Juan",{10,7,2022},0,0,0,CARGADO},
					{3,"Ramon",{15,2,2021},11,5,0,CARGADO},
					{4,"Lautaro",{23,10,2022},1,7,0,CARGADO},
					{5,"Rodrigo",{17,6,2021},6,4,9,CARGADO},
					{6,"Carla",{4,10,2020},13,3,0,CARGADO},
					{7,"Andres",{22,7,2022},14,7,0,CARGADO},
					{8,"David",{27,9,2022},15,7,11,CARGADO},
					{9,"Javier",{4,8,2019},7,6,0,CARGADO},
					{10,"Juan",{5,9,2020},8,8,0,CARGADO},
					{11,"Paolo",{20,8,2021},9,1,10,CARGADO}};

		for (int i = 0; i < len_consultas; i++) {
			*(list+i)=*(buffer+i);

			if (list[i].idConsulta >= *nextIdConsulta) {

				*nextIdConsulta = list[i].idConsulta;
				(*nextIdConsulta)++;
			}
		}
		retorno = 0;
	}
	return retorno;
}
int printConsulta (Consulta* this)
{
	int retorno =-1;
	if (this!=NULL && this->isEmpty == CARGADO) {

		printf(" | %3d     ||   %-8s    ||  %-2d   ||   %-2d  ||  %-4d    ||       %3d        ||       %2d         ||        %2d          |\n",this->idConsulta,this->nombre,this->fAtencion.dia,this->fAtencion.mes,this->fAtencion.anio,this->idDiagnostico,this->idMedico,this->idInterconsulta);
		retorno=0;
	}
	return retorno;
}
/// @brief Busca el index de una consulta por el id y la retorna
///
/// @param listConsultas
/// @param len_consultas
/// @return (-1) No existe esa consulta
/// 		(0) index elemento
int consultas_BuscarConsultaPorId (Consulta* listConsultas, int len_consultas, int id)
{
	int index=-1;
	int i;
	if (listConsultas!=NULL && len_consultas>0 && id>0)
	{
		for (i = 0; i < len_consultas; i++)
		{
			if ( listConsultas[i].idConsulta == id &&
					listConsultas[i].isEmpty== CARGADO )
			{
				index = i;
				break;
			}
		}
	}
	return index;
}
/// @brief Para indicar que todas las posiciones del array están vacías,
/// esta función pone la bandera (isempty) en TRUE en todas
/// posición del array
///
/// @param listConsultas
/// @param len_consultas
/// @return (-1) NUll pointer
///
int initConsultas(Consulta* listConsultas, int len_consultas)
{
	int retorno=-1;
	int i;

	if(listConsultas!=NULL && len_consultas>0){
		retorno=0;
		for (i = 0; i < len_consultas; i++)
		{
			(listConsultas+i)->isEmpty=VACIO;
		}
	}
	return retorno;
}
/// @brief Si hay por lo menos una consulta en el array devuelve TRUE
///
/// @param listConsultas
/// @param len_consultas
/// @return (-1) Non hay espacio
///         (0) hay espacio
int consultas_VereficarEspacio (Consulta* listConsultas, int len_consultas)
{
	int i;
	int respuesta=-1; // Pointer NULL or len < 0 or there is not space
	if (listConsultas!=NULL && len_consultas>0  ) {
		for (i = 0; i < len_consultas; i++) {
			if((listConsultas+i)->isEmpty!= VACIO){
				respuesta=0; //There are space in the array
				break;
			}
		}
	}
	return respuesta;
}
/// @brief Retorna un indice que este disponible
///
/// @param listConsultas
/// @param len_consultas
/// @return (-1) No hay espacio
/// 		index si hay espacio
int consultas_BuscarEspacioLibre (Consulta* listConsultas, int len_consultas)
{
	int index=-1;
	int i;

	if(listConsultas!=NULL && len_consultas>0){
		for (i = 0; i < len_consultas; i++) {
			if (listConsultas[i].isEmpty== VACIO) {
				index = i;
				break;
			}
		}
	}
	return index;
}

int printConsultas (Consulta* listConsultas, int len_consultas,
				   Diagnostico* listDiag, int len_Diagnostico,
				   Medico* listMedicos, int len_medicos,
				   Interconsulta* listinter, int len_Interconsulta)
{
	int retorno =-1;

	if (	listConsultas!=NULL && len_consultas> 0 &&
			listDiag!=NULL && len_Diagnostico> 0 &&
			listMedicos!=NULL && len_medicos >0 &&
			listinter!=NULL && len_Interconsulta>0) {

		//Cover
		printf("\n"
				"  ----------------------------------------------------------------------------------------------------------------------\n"
				" |   Id    ||   Nombre      ||  Dia  ||  Mes  ||  Anio    ||   idDiagnostico  ||     idMedico     ||  idInterconsulta   | \n"
				"  ----------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < len_consultas; i++) {
			if (listConsultas[i].isEmpty == CARGADO) {
				for (int k = 0; k < len_Diagnostico; k++) {
					if (listConsultas[i].idDiagnostico == listDiag[k].idDiagnostico) {
						for (int l = 0; l < len_medicos; l++) {
							if (listConsultas[i].idMedico == listMedicos[l].idMedico) {
								for (int m = 0; m < len_Interconsulta; m++) {
									if (listConsultas[i].idInterconsulta == listinter[m].idInterconsulta) {
										printConsulta(&listConsultas[i]);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
		printf("  ----------------------------------------------------------------------------------------------------------------------\n");
		retorno =0;
	}
	return retorno;
}
/// @brief  Imprime consultas No diagnosticasdas
///
/// @param listConsultas
/// @param len_consultas
/// @param listDiag
/// @param len_Diagnostico
/// @param listMedicos
/// @param len_medicos
/// @param listinter
/// @param len_Interconsulta
/// @return (-1) NULL pointer
/// 		(0) Todo bien
///         (3) Todas las  consultas estan diagnosticadas
int printConsulasNoDiagnosticadas ( Consulta* listConsultas, int len_consultas,
									Diagnostico* listDiag, int len_Diagnostico,
									Medico* listMedicos, int len_medicos,
									Interconsulta* listinter, int len_Interconsulta)
{
	int retorno =-1;
	int flag=1;
	if (	listConsultas!=NULL && len_consultas> 0 &&
			listDiag!=NULL && len_Diagnostico> 0 &&
			listMedicos!=NULL && len_medicos >0 &&
			listinter!=NULL && len_Interconsulta>0) {

		for (int i = 0; i < len_consultas; i++) {
			if (listConsultas[i].isEmpty == CARGADO && listConsultas[i].idDiagnostico==0) {
				flag=0;
				for (int k = 0; k < len_Diagnostico; k++) {
					if (listConsultas[i].idDiagnostico == listDiag[k].idDiagnostico) {
						for (int l = 0; l < len_medicos; l++) {
							if (listConsultas[i].idMedico == listMedicos[l].idMedico) {
								for (int m = 0; m < len_Interconsulta; m++) {
									if (listConsultas[i].idInterconsulta == listinter[m].idInterconsulta) {
										printf("  ----------------------------------------------------------------------------------------------------------------------\n");
										printConsulta((listConsultas+i));
										break;
									}
								}
							}
						}
					}
				}
			}
		}

		if (!flag) {

			printf("  ----------------------------------------------------------------------------------------------------------------------\n");
			retorno =0;
		}
		else{

			retorno=3;
		}
	}
	return retorno;
}
/// @brief Imprime las consultas diagnosticadas y si no hay retorna 5
///
/// @param listConsultas
/// @param len_consultas
/// @param listDiag
/// @param len_Diagnostico
/// @param listMedicos
/// @param len_medicos
/// @param listinter
/// @param len_Interconsulta
/// @return
int printConsulasDiagnosticadas ( Consulta* listConsultas, int len_consultas,
									Diagnostico* listDiag, int len_Diagnostico,
									Medico* listMedicos, int len_medicos,
									Interconsulta* listinter, int len_Interconsulta)
{
	int retorno =-1;
	int flag=1;
	if (	listConsultas!=NULL && len_consultas> 0 &&
			listDiag!=NULL && len_Diagnostico> 0 &&
			listMedicos!=NULL && len_medicos >0 &&
			listinter!=NULL && len_Interconsulta>0) {

		//Cover

		for (int i = 0; i < len_consultas; i++) {
			if (listConsultas[i].isEmpty == CARGADO && listConsultas[i].idDiagnostico>0) {
				flag=0;
				for (int k = 0; k < len_Diagnostico; k++) {
					if (listConsultas[i].idDiagnostico == listDiag[k].idDiagnostico) {
						for (int l = 0; l < len_medicos; l++) {
							if (listConsultas[i].idMedico == listMedicos[l].idMedico) {
								for (int m = 0; m < len_Interconsulta; m++) {
									if (listConsultas[i].idInterconsulta == listinter[m].idInterconsulta) {
										printf("  ----------------------------------------------------------------------------------------------------------------------\n");
										printConsulta((listConsultas+i));
										break;
									}
								}
							}
						}
					}
				}
			}
		}
		if (!flag) {

			printf("  ----------------------------------------------------------------------------------------------------------------------\n");
			retorno =0;
		}
		else{
			retorno=5;
		}
	}
	return retorno;
}
/// @brief Eliminar una consulta por su Id (poner la bandera isEmpty en 0)
///
/// @param listConsultas
/// @param len_consultas
/// @param id
/// @return (0) todo bien
/// 	   (-1) NUll pointer o len < 0
int removeConsulta (Consulta* listConsultas, int len_consultas, int id)
{
	int retorno=-1;
	int index;

	if (listConsultas!=NULL && len_consultas>0 && id>0) {

		if( (index= consultas_BuscarConsultaPorId(listConsultas, len_consultas, id)) >= 0 )
		{
			listConsultas[index].isEmpty=VACIO; //Change Flag FALSE
			retorno=0;
		}
	}
	return retorno;
}
/// @brief Imprime los posibles retornos de la funcion baja controller
///
/// @param retorno nada
void printEstadoBajaConsultas (int retorno)
{
	switch (retorno) {
		case 0:
			printf("\n\t!!---------BAJA COMPLETADA----------!!\n\n");
			break;
		case 1:
			printf("\n\t\tBAJA CANCELADA\n\n");
			break;
		case 2:
			printf("\n\tIngreso de datos invalidos\n\n");
			break;
		case 3:
			printf("\n\tNo hay ninguna consulta cargada en el sistema para dar de baja\n\n");
			break;
		case -1:
			printf("\n\tError[405](NULL pointer - len < 0 ) \n\n");
			break;
		case -2:
			printf("\n\t\tNo existe ese id o fue dado antes de baja \n\n");
			break;
	}
}
/// @brief Funcion encargada de toda la logica para dar una baja
///
/// @param listConsultas
/// @param len_consultas
/// @param listDiag
/// @param len_Diagnostico
/// @param listMedicos
/// @param len_medicos
/// @param listinter
/// @param len_Interconsulta
/// @return (-1) NUll pointer or len < 0
///         (2) Datos invalidos
/// 		(-2) No existe el id
/// 		(1) Baja cancelada
/// 		(0) Baja exitosa
int controller_BajaConsultas (Consulta* listConsultas, int len_consultas,
							 Diagnostico* listDiag, int len_Diagnostico,
							 Medico* listMedicos, int len_medicos,
							 Interconsulta* listinter, int len_Interconsulta)
{
	int retorno = -1; //NULL pointer or len <0
	int idBaja;

	if (listConsultas!=NULL && len_consultas > 0 &&
			listDiag!=NULL && len_Diagnostico> 0 &&
			listMedicos!=NULL && len_medicos >0 &&
			listinter!=NULL && len_Interconsulta>0 ) {

		retorno = 3; // no hay consultas
		if (!consultas_VereficarEspacio(listConsultas, len_consultas)) {
			retorno=2;// NO es un numero;

			printConsultas(listConsultas, len_consultas, listDiag, len_Diagnostico, listMedicos, len_medicos, listinter, len_Interconsulta);
			if (!utn_getNumero(&idBaja, "Id Baja: ", "\n\tError, No es un id\n\n", 0, INT_MAX,1)) {

				retorno = -2;//No existe el id
				if (consultas_BuscarConsultaPorId(listConsultas, len_consultas, idBaja)>=0) {

					retorno = 1;//Remove cancelled
					if (!(consultas_confirmDecision(
								"\n--------------\n"
								"Confirmar\n"
								"---------------\n"
								"Estas seguro que quieres eliminar este id de la base de datos del sistema?\n"
								"Escribi (1) |Confirmar Baja|  -   Escribi (0)  |Cancelar Baja|\n"
								"Decisicion: "))) {

						retorno=removeConsulta(listConsultas, len_consultas, idBaja); // Todo bien
					}
				}
			}
		}
	}
	printEstadoBajaConsultas(retorno);
	return 0;
}
/// @brief Pide un nombre
///
/// @param name
/// @return (-1) Nombre invalido
///         (0) Todo bien
int consultas_getNameFromStdIn (char* name)
{
	int retorno = -1; // Error getting a name
	char buffer[20];

	if (name != NULL  )
	{
		if (!utn_getCharNombre(buffer, "\nNombre: ", "\n\tError, nombre invalido\n\n", 1, LEN_NOMBRE)) {

			if (PrimerasLetrasMayuscula(buffer))
			{
				strcpy(name,buffer);
				retorno = 0; //ok
			}
		}

	}
	return retorno;
}
/// @brief Pide una fecha
///
/// @param name
/// @return retorno (-1) Fecha invalido
///         		(0) Todo bien
int consultas_getFechaFromStdIn (Fecha* atencion)
{
	int retorno = -1; // Error getting a price
	Fecha buffer;


	if (	!utn_getNumero(&buffer.dia, "Dia: ", "\n\tError, Dia invalido \n\n", 1, 31, 1) &&
			!utn_getNumero(&buffer.mes, "Mes: ","\n\tError, Mes invalido \n\n" , 1, 12, 1) &&
			!utn_getNumero(&buffer.anio, "Año: ", "\n\tError, Año invalido \n\n", 2000, 9999, 1)) {

		atencion->dia= buffer.dia;
		atencion->mes=buffer.mes;
		atencion->anio=buffer.anio;
		retorno =0;
	}
	return retorno;
}
/// @brief Pide un medico como entero
///
/// @param medico
/// @return (-1) Fecha invalido
///         (0) Todo bien
int consultas_getMedicoFromStdIn (int* medico)
{
	int retorno =-1;
	int buffer;

	if (!utn_getNumero(&buffer, "Id medico: ", "\n\tError, Medico invalido\n\n", 1, 8, 1)) {

		*medico=buffer;
		retorno=0;
	}
	return retorno;
}
/// @brief Imprime los posibles retornos de la funcion alta controller
///
/// @param retorno
void printEstadoAltaConsultas (int retorno)
{
	switch (retorno) {
		case 0:
			printf("\n\t!!---------ALTA COMPLETADA----------!!\n\n");
			break;
		case 1:
			printf("\n\t\tALTA CANCELADA\n\n");
			break;
		case 2:
			printf("\nIngreso de datos invalidos\n\n");
			break;
		case -1:
			printf("\n\tError[403] No hay espacio para dar de alta una consulta en el sistema or (NULL pointer - len < 0 ) \n\n");
			break;

	}
}
/// @brief añadir en una lista existente de consultas los valores recibidos como parámetros
/// en la primera posición vacía
///
/// @param listConsultas
/// @param len_consultas
/// @param nombre
/// @param atencion
/// @param medico
/// @param nextIdConsulta
/// @return (-1)NULL pointer len <0 no hay espacio
///         (0) todo bien
int addConsulta (Consulta* listConsultas, int len_consultas,char* nombre, Fecha atencion, int* nextIdConsulta)
{
	int retorno=-1;
	int index;

	if (listConsultas!=NULL && len_consultas > 0 && nombre!=NULL ) {

		index=consultas_BuscarEspacioLibre(listConsultas, len_consultas);
		if (index>=0) {

			listConsultas[index].idConsulta=*nextIdConsulta;
			strcpy(listConsultas[index].nombre,nombre);
			listConsultas[index].fAtencion.dia=atencion.dia;
			listConsultas[index].fAtencion.mes=atencion.mes;
			listConsultas[index].fAtencion.anio=atencion.anio;
			listConsultas[index].idDiagnostico = 0;
			listConsultas[index].idMedico=0;
			listConsultas[index].idInterconsulta=0;
			listConsultas[index].isEmpty=CARGADO;
			(*nextIdConsulta)++;

			retorno=0;
		}
	}
	return retorno;
}
/// @brief Funcion principal de dar de alta una consulta
///
/// @param listConsultas
/// @param len_consultas
/// @param listDiag
/// @param len_Diagnostico
/// @param listMedicos
/// @param len_medicos
/// @param listinter
/// @param len_Interconsulta
/// @return (-1) NUll pointer or len < 0
///         (2) Datos invalidos
/// 		(1) Alta cancelada
int controller_AltaConsultas (Consulta* listConsultas, int len_consultas,int* nextIdConsulta)
{
	int retorno = -1;//NULL pointer or len <0
	char nombre[50];
	Fecha atencion;

	if (		listConsultas!=NULL && len_consultas > 0 &&
				consultas_BuscarEspacioLibre(listConsultas, len_consultas)>=0) {

		retorno = 2;//Datos invalidos
		if (	!consultas_getNameFromStdIn(nombre) &&
				!consultas_getFechaFromStdIn(&atencion)) {

			retorno =1;//Alta cancelada
			if (!(consultas_confirmDecision(
					"\n--------------\n"
					"Confirmar\n"
					"---------------\n"
					"Estas seguro que quieres agregrar los datos de un nueva consulta al sistema?\n"
					"Escribi (1) |Confirmar|  -   Escribi (0)  |Cancelar|\n"
					"Decisicion: "))) {

				retorno = addConsulta(listConsultas, len_consultas, nombre, atencion, nextIdConsulta);
			}
		}
	}
	printEstadoAltaConsultas(retorno);
	return 0;
}
/// @brief  pide nuevo nombre y lo guarda al puntero elemento de la entidad
///
/// @param this
/// @return (-1) this es NULL pointer
///         (0) todo bien
/// 		(2) Datos invalidos
///         (1) Modificacion cancelada
int consultas_getNewNombreFromStdin(Consulta* this)
{
	int retorno = -1;
	char buffer[50];

	if (this!=NULL ) {

		retorno = 2; //Invalid Opcion
		if (!consultas_getNameFromStdIn(buffer)) {

			retorno = 1;// retorno cancelled
			if (!consultas_confirmDecision(
					"\n--------------\n"
					"Confirmar\n"
					"---------------\n"
					"Estas seguro que quieres cambiar?\n"
					"Escribi (1) |Confirmar|  -   Escribi (0)  |Cancelar|\n"
					"Decisicion: "))
			{
				PrimerasLetrasMayuscula(buffer);
				strcpy(this->nombre,buffer);
				retorno = 0; //ok
			}
		}
	}
	return retorno;
}
/// @brief   pide nueva fecha  y lo guarda al puntero elemento de la entidad
///
/// @param this
/// @return  (-1) this es NULL pointer
///         (0) todo bien
/// 		(2) Datos invalidos
///         (1) Modificacion cancelada
int consultas_getNewFechaFromStdin(Consulta* this)
{
	int retorno = -1;
	Fecha buffer;

	if (this!=NULL ) {

		retorno = 2;
		if (!consultas_getFechaFromStdIn(&buffer)) {

			retorno =1;
			if (!(consultas_confirmDecision(
					"\n--------------\n"
					"Confirmar\n"
					"---------------\n"
					"Estas seguro que quieres cambiar?\n"
					"Escribi (1) |Confirmar|  -   Escribi (0)  |Cancelar|\n"
					"Decisicion: "))) {

				this->fAtencion.dia= buffer.dia;
				this->fAtencion.mes=buffer.mes;
				this->fAtencion.anio=buffer.anio;
				retorno =0;
			}
		}
	}
	return retorno;
}
/// @brief pide nuevo medico  y lo guarda al puntero elemento de la entidad
///
/// @param this
/// @return  (-1) this es NULL pointer
///         (0) todo bien
/// 		(2) Datos invalidos
///         (1) Modificacion cancelada
int consultas_getNewMedicoFromStdin(Consulta* this,Medico* listMedicos, int len_medicos)
{
	int retorno = -1;
	int buffer;

	if (this!=NULL && listMedicos!=NULL && LEN_Medico >0 ) {
		printMedicos(listMedicos, len_medicos);

		retorno = 2; //Invalid Opcion
		if (!consultas_getMedicoFromStdIn(&buffer)) {

			retorno = 1;// retorno cancelled
			if (!consultas_confirmDecision(
					"\n--------------\n"
					"Confirmar\n"
					"---------------\n"
					"Estas seguro que quieres cambiar?\n"
					"Escribi (1) |Confirmar|  -   Escribi (0)  |Cancelar|\n"
					"Decisicion: "))
			{
				this->idMedico=buffer;
				retorno = 0; //ok
			}
		}
	}
	return retorno;
}
void consultas_printOptionsModificar()
{
	printf("\n"
			"1) Nombre\n"
			"2) Fecha\n"
			"3) Medico\n"
			"4) Salir\n");
}
/// @brief Edita el campo de una consulta a placer
///
/// @param this
/// @return (-1) Modifcacion cancelada
///         (0) Modifcacion exitosa
/// 		(2) Datos invalidos
int consultas_ediConsulta (Consulta* this,Medico* listMedicos, int len_medicos)
{
	int retorno = -1;
	int opcion;

	if (this!=NULL && listMedicos!=NULL && LEN_Medico >0 ) {

		do{
			printf("\n"
					"  ----------------------------------------------------------------------------------------------------------------------\n"
					" |   Id    ||   Nombre      ||  Dia  ||  Mes  ||  Anio    ||   idDiagnostico  ||     idMedico     ||  idInterconsulta   | \n"
					"  ----------------------------------------------------------------------------------------------------------------------\n");
			printConsulta(this);
			printf("  ----------------------------------------------------------------------------------------------------------------------\n");

			consultas_printOptionsModificar();

			if (!utn_getNumero(&opcion, "Opcion: ", "\n\tError, numero invalido\n\n", 1, 10, 0)) {

				switch (opcion) {
					case 1:
						retorno = consultas_getNewNombreFromStdin(this);
						break;
					case 2:
						retorno = consultas_getNewFechaFromStdin(this);
						break;
					case 3:
						retorno = consultas_getNewMedicoFromStdin(this,listMedicos,len_medicos);
						break;
				}
			}
		}while(opcion!=4);
	}
	return retorno;
}


void printEstadoModificacionConsultas (int retorno)
{
	switch (retorno) {
			case 0:
				printf("\n\t!!---------MODIFICACION COMPLETADA----------!!\n\n");
				break;
			case 1:
				printf("\n\t\tMODIFICACION CANCELADA\n\n");
				break;
			case 2:
				printf("\n\tIngreso de datos invalidos\n\n");
				break;
			case 3:
				printf("\n\tNo hay consultas para modificar  en el sistema\n\n");
				break;
			case -1:
				printf("\n\tError[403](NULL pointer - len < 0 ) \n\n");
				break;
			case -2:
				printf("\n\tNo existe ese id o fue dado de baja antes\n\n");
				break;

		}
}
/// @brief Funcion principal de la modificacion de un pasajero
///
/// @param listConsultas
/// @param len_consultas
/// @param listDiag
/// @param len_Diagnostico
/// @param listMedicos
/// @param len_medicos
/// @param listinter
/// @param len_Interconsulta
/// @return (-1) NUll pointer or len < 0
///         (2) Datos invalidos
/// 		(-2) No existe el id
/// 		(1) modificacion cancelada
/// 		(0) modificacion exitosa
int controller_ModificacionConsultas (Consulta* listConsultas, int len_consultas,
									  Diagnostico* listDiag, int len_Diagnostico,
									  Medico* listMedicos, int len_medicos,
									  Interconsulta* listinter, int len_Interconsulta)
{
	int retorno =-1;
	int id;
	int index;

	if (		listConsultas!=NULL && len_consultas > 0 &&
				listMedicos!=NULL && len_medicos >0 )
	{
		retorno=3;
		if (!consultas_VereficarEspacio(listConsultas, len_consultas)) {

			printConsultas(listConsultas, len_consultas, listDiag, len_Diagnostico, listMedicos, len_medicos, listinter, len_Interconsulta);

			retorno=2;//Datos invalidos
			if (!utn_getNumero(&id, "\nId Modificar: ", "\n\tError opcion invalida\n\n", 0, INT_MAX, 1)) {

				retorno = -2;//No existe el id
				if ((index=consultas_BuscarConsultaPorId(listConsultas, len_consultas, id))>=0) {

					retorno = consultas_ediConsulta((listConsultas+index),listMedicos,len_medicos);
				}
			}
		}
	}
	printEstadoModificacionConsultas(retorno);
	return 0;
}
