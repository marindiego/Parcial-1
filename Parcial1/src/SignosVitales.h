/*
 * SignosVitales.h
 *
 *  Created on: 18 jun. 2022
 *      Author: Usuario
 */

#ifndef SIGNOSVITALES_H_
#define SIGNOSVITALES_H_

#include "utn_funciones.h"
#define LEN_SigVitales 3


typedef struct{

	int idSignosVitales;
	char estado[50];

}SignoVital;


int HardCodeSignosVitales (SignoVital* list, int len);
int printSignoVital (SignoVital* this);
int printSignoVitales (SignoVital* list, int len_SignoVital);

#endif /* SIGNOSVITALES_H_ */
