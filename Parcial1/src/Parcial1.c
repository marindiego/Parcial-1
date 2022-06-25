/*
 ============================================================================
 Name        : Parcial1.c
 Author      : DIego
 Version     :
 Copyright   : Your copyright notice
 Description : Se necesita administrar las consultas de un sanatorio privado, y para ello se deber� realizar un programa de acuerdo
a lo siguiente:
 ============================================================================
 */

#include "Nexo.h"

int main(void) {

	setbuf(stdout,NULL);

	int opcion;
	int nextIdConsulta=1;
	int nextIdinterconsulta=1;

	Diagnostico listDiagnosticos[LEN_DIAGNOSTICO];
	Medico listMedicos[LEN_Medico];
	Especialidad listEspecialidades[LEN_Especialidades];
	SignoVital listSigVitales[LEN_SigVitales];
	Interconsulta listInterConsulta[LEN_Interconsulta];
	Consulta listConsultas[LEN_CONSULTA];

	//Inicializa Entidades
	initConsultas(listConsultas, LEN_CONSULTA);
	initInterconsultas(listInterConsulta, LEN_Interconsulta);

	//hardCode entidades secundarias
	HardCodeDiagnosticos(listDiagnosticos, LEN_DIAGNOSTICO);
	HardCodeMedicos(listMedicos, LEN_Medico);
	HardCodeSignosVitales(listSigVitales, LEN_SigVitales);
	HardCodeEspecialidades(listEspecialidades, LEN_Especialidades);

	listInterConsulta[0].idInterconsulta=0;
	strcpy(listInterConsulta[0].motivo,"No es necesario una interconsulta");
	listInterConsulta[0].idEspecialidad=0;
	listInterConsulta[0].idSignosVitales=0;
	listInterConsulta[0].isEmpty =CARGADO;



	printf( "Nombre: DIEGO MARIN 1(c)      								 \n"
			"Trabajo Practico 1er Parcial	 							 \n"
			"Descripcion: A.B.M - ( Consultas medicas para un sanatorio )\n"
			"1er Cuatrimestre                    \n"
			""
			"\nEnjoy :,)\n\n");

	do {
		printConsultasOptionsMenu();

		if (!utn_getNumero(&opcion, "Opcion: ","\n\tError opcion invalida\n", 1, 7, INT_MAX)) {

			switch (opcion) {
				case 1:
					controller_AltaConsultas(listConsultas, LEN_CONSULTA,  &nextIdConsulta);
					break;
				case 2:
					controller_ModificacionConsultas(listConsultas, LEN_CONSULTA, listDiagnosticos, LEN_DIAGNOSTICO, listMedicos, LEN_Medico, listInterConsulta, LEN_Interconsulta);
					break;
				case 3:
					controller_BajaConsultas(listConsultas, LEN_CONSULTA,listDiagnosticos,LEN_DIAGNOSTICO,listMedicos,LEN_Medico,listInterConsulta,LEN_Interconsulta);
					break;
				case 4:
					controller_diagnosticar(listConsultas, LEN_CONSULTA, listDiagnosticos,LEN_DIAGNOSTICO, listMedicos, LEN_Medico, listEspecialidades, LEN_Especialidades, listInterConsulta, LEN_Interconsulta);
					break;
				case 5:
					controller_Interconsulta(listConsultas, LEN_CONSULTA, listInterConsulta, LEN_Interconsulta, listEspecialidades, LEN_Especialidades, listSigVitales, LEN_SigVitales, listMedicos, LEN_Medico, listDiagnosticos, LEN_DIAGNOSTICO, &nextIdinterconsulta);
					break;
				case 6:
					//Listar
					controller_Listar(listConsultas,LEN_CONSULTA, listInterConsulta, LEN_Interconsulta, listEspecialidades, LEN_Especialidades, listSigVitales, LEN_SigVitales, listMedicos, LEN_Medico, listDiagnosticos, LEN_DIAGNOSTICO );
					break;
				case 7:
					//Hardcodear
					controller_hardCode(listConsultas, LEN_CONSULTA, listInterConsulta, LEN_Interconsulta, &nextIdConsulta, &nextIdinterconsulta);
					break;
				case 8:
					printf("\nSalir Completdo!!!!\n\n");
					break;
			}
		}
	} while (opcion!=8);

	return EXIT_SUCCESS;
}
