/*
 * Especialidad.c
 *
 *  Created on: 18 jun. 2022
 *      Author: Usuario
 */


#include "Especialidad.h"

/// @brief hardcode lista de especialidades
///
/// @param list
/// @param len
/// @return
int HardCodeEspecialidades (Especialidad* list, int len)
{
	int hardcode = -1, i;

	if (list !=NULL && len > 0) {

		Especialidad buffer[10]=
					{{1,"Cardiologa"},
					{2,"Nefrologia"},
					{3,"Oncologo"},
					{4,"Psiquiatra"},
					{5,"Neurologia"},
					{6,"Medico General"},
					{7,"Endocrinologo"}};
		for (i = 0; i < len; i++) {
			*(list+i)=*(buffer+i);
		}
	}
	return hardcode;
}
/// @brief Muestra una especialidad
///
/// @param list
/// @return
int printEspecialidad (Especialidad* this)
{
	int retorno =-1;
	if (this!=NULL   ) {

		printf(" |%2d)  || %-14s   |    \n",this->idEspecialidad,this->descripcion);
		retorno=0;
	}
	return retorno;
}
/// @brief Muestra a varias especialidades
///
/// @param list
/// @param len_especialidad
/// @return
int printEspecialidades (Especialidad* list, int len_especialidad)
{
	int retorno =-1;
	if (list!=NULL && len_especialidad>0) {

		printf("\n"
				"  -------------------------\n"
				" | Id  || Especialidad     |\n"
				"  -------------------------\n");
		for (int i = 0; i < len_especialidad; i++) {

			printEspecialidad ((list+i));
		}
		printf("  -------------------------\n");
		retorno=0;
	}
	return retorno;
}
