/*
 * interconsulta.c
 *
 *  Created on: 18 jun. 2022
 *      Author: Usuario
 */

#include "interconsulta.h"


/// @brief Para indicar que todas las posiciones del array están vacías,
/// esta función pone la bandera (isempty) en TRUE en todas
/// posición del array
///
/// @param listConsultas
/// @param len_consultas
/// @return (-1) NUll pointer
///
int initInterconsultas(Interconsulta* list, int len)
{
	int retorno=-1;
	int i;

	if(list!=NULL && len>0){
		retorno=0;
		for (i = 0; i < len; i++)
		{
			(list+i)->isEmpty=VACIO;
		}
	}
	return retorno;
}
/// @brief hardcode lista de Interconsultas
///
/// @param list
/// @param len
/// @return
int HardCodeInterconsultas (Interconsulta* list, int len_Interconsulta, int* idInterconsulta)
{
	int hardcode = -1, i;

	if (list !=NULL && len_Interconsulta > 0) {

		Interconsulta buffer[20]=
					{{0,"No es necesario una interconsulta",0,0,CARGADO},
					{1,"Enfermedad infecciosa",6,1,CARGADO},
					{2,"Tos seca,Perdida del gusto",6,3,CARGADO},
					{3,"Presion en el pecho, opresion, dolor",1,1,CARGADO},
					{4,"Pensamientos distorsionados y negativos",5,1,CARGADO},
					{5,"Alucinaciones,Delirios",5,2,CARGADO},
					{6,"Alcoholismo o consumo de drogas",4,3,CARGADO},
					{7,"Sudores nocturnos,fiebres inexplicables",4,2,CARGADO},
					{8,"Miedo irracional y constante hacia los animales",4,1,CARGADO},
					{9,"Convulsiones,Confusion temporal",5,2,CARGADO},
					{10,"Temblores,Rigidez muscular,Cambios en el habla",5,3,CARGADO},
					{11,"Fatiga, debilidad,Perdida de apetito",1,2,CARGADO},
					{12,"Aumento del apetito,aumento de la sed,fatiga.",6,2,CARGADO},
					{13,"Dolor de cabeza fuerte,Sangrado nasal.",1,2,CARGADO}};

		for (i = 0; i < len_Interconsulta; i++) {
			*(list+i)=*(buffer+i);
			if (list[i].idInterconsulta >= *idInterconsulta) {

				*idInterconsulta = list[i].idInterconsulta;
				(*idInterconsulta)++;
			}
		}
	}
	return hardcode;
}
/// @brief Muestra un Interconsulta
///
/// @param list
/// @return
int printInterconsulta (Interconsulta* this)
{
	int retorno =-1;
	if (this!=NULL && this->isEmpty == CARGADO ) {

		printf(" |%3d)  || %-47s      	||       %-5d      ||       %-3d         |\n",this->idInterconsulta,this->motivo,this->idEspecialidad,this->idSignosVitales);
		retorno=0;
	}
	return retorno;
}
/// @brief Muestra a varias Interconsultas
///
/// @param list
/// @param len_Interconsulta
/// @param listEsp
/// @param len_especialidad
/// @param listSig
/// @param len_sigVitales
/// @return (0) todo bien - (-1) todo mal
int printInterconsultas (Interconsulta* list, int len_Interconsulta,Especialidad* listEsp, int len_especialidad, SignoVital* listSig, int len_sigVitales)
{
	int retorno =-1;
	if (list!=NULL && len_Interconsulta>0 && listEsp!=NULL && len_especialidad >0 && listSig!=NULL && len_sigVitales >0 ) {

		printf("\n"
				"  ---------------------------------------------------------------------------------------------------------------\n"
				" | Id  || 			 Motivo                                 ||  IdEspecialista  || IdSignosVitales   |\n"
				"  ---------------------------------------------------------------------------------------------------------------\n");
		printInterconsulta(&list[0]);
		for (int i = 1; i < len_Interconsulta; i++) {
			for (int k = 0; k < len_especialidad; k++) {
				if (list[i].idEspecialidad == listEsp[k].idEspecialidad) {
					for (int l = 0; l <len_sigVitales; l++) {
						if (list[i].idSignosVitales == listSig[l].idSignosVitales) {
							printInterconsulta ((list+i));
						}
					}
				}
			}
		}
		printf("  ---------------------------------------------------------------------------------------------------------------\n");
		retorno=0;
	}
	return retorno;
}
/// @brief Retorna un indice que este disponible
///
/// @param listConsultas
/// @param len_consultas
/// @return (-1) No hay espacio
/// 		index si hay espacio
int interconsulta_BuscarEspacioLibre (Interconsulta* list, int len_Interconsulta)
{
	int index=-1;
	int i;

	if(list!=NULL && len_Interconsulta>0){
		for (i = 0; i < len_Interconsulta; i++) {
			if (list[i].isEmpty== VACIO) {
				index = i;
				break;
			}
		}
	}
	return index;
}
/// @brief Añade un elemento en el primer indice que encuentra disponible
///
/// @param motivo
/// @param idConsulta
/// @param idEspecialidad
/// @param idSignoVital
/// @return (-1) todo mal
///         (0) todo bien
int addInterconsulta (Interconsulta* list, int len_Interconsulta,char* motivo, int idConsulta, int idEspecialidad, int idSignoVital, int* nextId)
{
	int retorno=-1;
	int index;
	if (motivo!=NULL && idConsulta > 0 && idEspecialidad> 0 && idSignoVital> 0 && nextId !=NULL) {

		index = interconsulta_BuscarEspacioLibre(list, len_Interconsulta);
		if (index >=0) {

			list[index].idInterconsulta=*nextId;
			strcpy(list[index].motivo,motivo);
			list[index].idEspecialidad= idEspecialidad;
			list[index].idSignosVitales = idSignoVital;
			list[index].isEmpty = CARGADO;
			retorno =0;
			(*nextId)++;
		}
	}

	return retorno;
}
