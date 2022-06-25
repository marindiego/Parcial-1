/*
 * SignosVitales.c
 *
 *  Created on: 18 jun. 2022
 *      Author: Usuario
 */

#include "SignosVitales.h"

/// @brief hardcode lista de SignosVitales
///
/// @param list
/// @param len
/// @return
int HardCodeSignosVitales (SignoVital* list, int len)
{
	int hardcode = -1, i;

	if (list !=NULL && len > 0) {

		SignoVital buffer[5]=
					{{1,"Estables"},
					{2,"Regulares"},
					{3,"Bajos"}};
		for (i = 0; i < len; i++) {
			*(list+i)=*(buffer+i);
		}
	}
	return hardcode;
}
/// @brief Muestra un pasajero
///
/// @param list
/// @return
int printSignoVital (SignoVital* this)
{
	int retorno =-1;
	if (this!=NULL   ) {

		printf(" |%2d)  || %-9s      |\n", this->idSignosVitales,this->estado);
		retorno=0;
	}
	return retorno;
}
/// @brief Muestra a varios pasajeros
///
/// @param list
/// @param len_SignoVital
/// @return
int printSignoVitales (SignoVital* list, int len_SignoVital)
{
	int retorno =-1;
	if (list!=NULL && len_SignoVital>0) {

		printf("\n"
				"  -----------------------\n"
				" | Id  || SignoVital     |\n"
				"  -----------------------\n");
		for (int i = 0; i < len_SignoVital; i++) {

			if (list[i].idSignosVitales>0 && list[i].idSignosVitales<=3) {

				printSignoVital ((list+i));
			}
		}
		printf("  -----------------------\n");
		retorno=0;
	}
	return retorno;
}
