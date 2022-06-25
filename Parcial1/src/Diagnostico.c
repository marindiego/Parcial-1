/*
 * Diagnostico.c
 *
 *  Created on: 18 jun. 2022
 *      Author: Usuario
 */


#include "Diagnostico.h"

/// @brief hardcode lista de Diagnosticos
///
/// @param list
/// @param len
/// @return
int HardCodeDiagnosticos (Diagnostico* list, int len)
{
	int hardcode = -1, i;

	if (list !=NULL && len > 0) {

		Diagnostico buffer[20]=
					{{0,"Sin diagnostico"},
					{1,"Gripe A"},
					{2,"Covid-19"},
					{3,"Pre infarto"},
					{4,"Fobias"},
					{5,"Ezquisofrenia"},
					{6,"Tumor"},
					{7,"Cancer"},
					{8,"Hipertiroidismo"},
					{9,"Epilepsia"},
					{10,"Parkinson"},
					{11,"Insuficiencia cardíaca"},
					{12,"Enfermedad neurológica"},
					{13,"Hipertensión  arterial"},
					{14,"Diabetes"},
					{15,"Anemia"}};

		for (i = 0; i < len; i++) {
			*(list+i)=*(buffer+i);
		}
	}
	return hardcode;
}
/// @brief Muestra un diagnostico
///
/// @param list
/// @return
int printDiagnostico (Diagnostico* this)
{
	int retorno =-1;
	if (this!=NULL ) {

		printf(" |%2d)  || %-22s    | \n",this->idDiagnostico,this->descripcion);
		retorno=0;
	}
	return retorno;
}
/// @brief Muestra a varios diagnostico
///
/// @param list
/// @param len_Diagnostico
/// @return
int printDiagnosticos (Diagnostico* list, int len_Diagnostico)
{
	int retorno =-1;
	if (list!=NULL && len_Diagnostico>0) {

		printf("\n"
				"  ----------------------------------\n"
				" | Id  || Diagnostico               |\n"
				"  ----------------------------------\n");
		for (int i = 0; i < len_Diagnostico; i++) {

			printDiagnostico ((list+i));
		}
		printf("  ----------------------------------\n");
		retorno=0;
	}
	return retorno;
}
/// @brief Muestra los posibles retornos de la funcion diagnosticar
///
/// @param retorno
void printEstadoDiagnosticarConsultas (int retorno)
{
	switch (retorno) {
			case 0:
				printf("\n\t!!---------DIAGNOSTICAR COMPLETADA----------!!\n\n");
				break;
			case 1:
				printf("\n\t\tDIAGNOSTICAR CANCELADA\n\n");
				break;
			case 2:
				printf("\nIngreso de datos invalidos\n\n");
				break;
			case 3:
				printf("\n\tNo hay ninguna consulta disponible\n\n");
				break;
			case 6:
				printf("\n\tEsa consulta tiene un diagnostico, eliga otra\n\n");
				break;
			case -1:
				printf("\n\tError[403]  (NULL pointer - len < 0 ) \n\n");
				break;
			case -2:
				printf("\n\t\tNo existe ese id o fue dado antes de baja \n\n");
				break;

		}
}





