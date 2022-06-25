/*
 * Medico.c
 *
 *  Created on: 27 may. 2022
 *      Author: Usuario
 */

#include "Medico.h"

/// @brief Carga 5 medicos en el vector de medicos
///
/// @param list
/// @param len
/// @return int Return (-1) if Error [Invalid length or NULL pointer] or (0) if ok
int HardCodeMedicos (Medico* list, int len)
{
	int hardcode = -1, i;

	if (list !=NULL && len > 0) {

		Medico buffer[10]=
				{{1,"Pedro",5},
				{2,"German",4},
				{3,"Marina",1},
				{4,"Gianni",3},
				{5,"Carlos",1},
				{6,"Lionel",3},
				{7,"Neymar",6},
				{8,"Diego",7},
				{0,"",0}};

		for (i = 0; i < len; i++) {
			*(list+i)=*(buffer+i);
		}
		hardcode = 0;
	}

	return hardcode;
}
/// @brief Imprime un medico
///
/// @param listMedicos
/// @return
int printMedico (Medico* this)
{
	int retorno = -1;
	if (this!=NULL ) {
		printf(" |%2d)  || %-8s      ||       %-2d         |\n",this->idMedico,this->nombre,this->idEspecialidad);
		retorno = 0;
	}

	return retorno ;
}
/// @brief Medicos disponibles en la lista
///
/// @param listMedicos
int printMedicos (Medico* listMedicos, int len_medicos)
{
	int retorno = -1; // len < 0 or pointer NULL

	if (listMedicos !=NULL && len_medicos >= 0 ) {

		printf("\n"
				"  ------------------------------------------\n"
				" | Id  || Medico        || idEspecialidad   |\n"
				"  ------------------------------------------\n");

		for (int i = 0; i < len_medicos; i++) {
			if (listMedicos[i].idMedico>0) {
				printMedico((listMedicos+i));
			}
		}
		printf("  ------------------------------------------\n");
		retorno = 0; //OK
	}
	return retorno;
}
