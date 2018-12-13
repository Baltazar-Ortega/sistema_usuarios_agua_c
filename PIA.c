/* PIA 
Desarrollar un programa en C, que maneje un sistema de control de
usuarios del agua potable de una localidad, que permita crear: Altas,
Bajas y Cambios a una estructura de Usuarios y otra de Colonias. La
estructura de usuarios contiene los datos de todos los usuarios de la
localidad, la cual se divide en varias colonias, es por ello que cada
usuario tiene un dato que es la clave de la colonia a la que pertenece. La
estructura de colonias contiene los nombres de todas las colonias de la
localidad. También se manejará una estructura de tarifas, que contendrá
un arreglo de 8 elementos, en el elemento 1 tendrá la tarifa que le
corresponde al usuario tipo 1, en el elemento 2 la tarifa para el usuario
tipo 2, y así sucesivamente.
USUARIOS 				COLONIAS 				TARIFAS
Número					 Clave Colonia			 Tarifa [8]
Tipo Usuario 			Colonia
Nombre
Clave Colonia
Dirección
Consumo
Pago  

Donde:
-Numero.- es el numero de identificacion del usuario.
-Tipo Usuario.- Es el tipo de usuario (1, 2, 3, 4, 5, 6, 7, 8).
-Nombre.- Es el nombre del usuario.
-Clave Colonia.- Es la clave de identificacion de la colonia donde
vive el usuario.
-Colonia.- Es el nombre de la colonia donde vive el usuario.
-Direccion.- Es la direccion del domicilio del usuario.
-Consumo.- Es el consumo en metros cubicos de agua que
consumio el usuario en el periodo correspondiente.
-Pago.- Es el pago realizado por el usuario por el periodo
correspondiente. Si esta en cero, es que no ha pagado.
-Tarifa [8].- es un arreglo que tiene 8 elementos.
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> 
#include<string.h>
#include <time.h>

struct colonias{
	float clv;
	char nomcol[20];
};

struct tarifas {
	float tar[8];
	int pos[8];
};

struct usuario {
	float num;
	float tipo;
	char nom[30];
	float clave;
	char nocol[20];
	char dir[30];
	float cons;
	float pago;
	struct tarifas tari;
};

void altas(int ctr, struct usuario *ap, struct tarifas *pp, struct colonias *op);
void bajas();
void modificacion();
void proceso();
void pagosrealizados();
void pagosnorealizados();
void facturacionlista();
void facturacionindividual(); 
int nrandom();


int main(){
	struct usuario usu[' '];
	struct colonias col[' '];
	struct tarifas tarif;
	int opc, ops = 0, opr, ctr = 0, i, s, ctr2 = 0, cta = 0, ctb = 0, ctc = 0, ctd, opre, u, m, j;
	char aux[' '];
	float import, sobrecon, tot;
	FILE *archivo;
	FILE *archproc;
	printf("\n\n\n\t Sistema de control de usuarios de agua \n\n\n\n\n\n\n\n\n");
	system("pause");
	system("cls");
	printf("\n");
	do{
		for(i= 0;i< 80; i++)
		{
			printf("%c", 95);
		}
		menu:
		printf("\n\n\n\t\t\t\t\t MENU \n");
		for(i= 0;i< 80; i++)
		{
			printf("%c", 95);
		}
		printf("\n\n\t\t\t 1. Altas \n\n\t\t\t 2. Modificacion de datos \n\n\t\t\t 3. Proceso para facturacion \n\n\t\t\t 4. Bajas \n\n\t\t\t 5. Reportes \n\n\t\t\t 6. Salir\n");
		for(i= 0;i< 80; i++)
		{
			printf("%c", 95);
		}
		do
		{
			printf("\n\n\n\t\t Opcion: ");
			fflush(stdin);
			gets(aux);
			opc = atoi(aux);
		}while(opc != 1 && opc != 2 && opc != 3 && opc != 4 && opc != 5 && opc !=6);
		system("cls"); 
		
			switch(opc)
			{
				case 1: archivo = fopen("altas.txt", "r");  //ALTAS
						
						if (archivo == NULL){
							fclose(archivo);
							altas(ctr, &usu[0], &tarif, &col[0]);
							ctr++;
							ctb++;
						}
						else
							if (ctb != 0 && archivo != NULL)
							{
								fclose(archivo);
								for(i= 0;i< 80; i++)
								{
									printf("%c", 95);
								}
									printf("\n");
								printf("\nPara ingresar mas usuarios o colonias debe salir del programa. \n");
								printf("\n");
								system("pause");
								system("cls");
							}
							else
							{
								fclose(archivo);
								ctr++;
								altas(ctr, &usu[0], &tarif, &col[0]);
								ctb++;
							}
					
							for(i= 0;i< 80; i++)
							{
								printf("%c", 95);
							}
							printf("\n");
							do
							{
								printf("\n %cDesea regresar al men%c? [1-Si/2-No]: ", 168, 163);
								fflush(stdin); 
								gets(aux);
								opr = atoi(aux);
							}while(opr != 1 && opr != 2);
							
						system("cls");
						break;
						
				case 2: archivo = fopen("altas.txt", "r");   //MODIFICACIONES
						if (archivo == NULL){
							fclose(archivo);
							printf("\n No ha introducido ningun usuario. \n\n");
							system("pause");
							system("cls");
						}
						else{
							fclose(archivo);
							modificacion(&usu[0], &usu[0], &col[0]);
						}
						for(m= 0;m< 80; m++)
						{
							printf("%c", 95);
						}
						printf("\n");
						do
						{
							printf("\n %cDesea regresar al men%c? [1-Si/2-No]: ", 168, 163);
							fflush(stdin);
							gets(aux);
							opr = atoi(aux);	
						}while(opr != 1 && opr !=2);
						system("cls");
						break;
						
				case 3: cta=0;
						ctd = 0;
						archivo = fopen("altas.txt", "r");   //PROCESOS
						if (archivo == NULL){
							fclose(archivo);
							printf("\n No ha introducido ningun usuario. \n\n");
							system("pause");
							system("cls");
						}
						else
							{
								u = 0;
								//Borro procesos anteriores
								//Pierde su proceso si hace 1.procesos 2.No hace reporte 3 2.vuelve a entrar a procesos
								fclose(archivo);
								archproc = fopen("procesos.txt", "r");
								if (archproc != NULL){  
									u++;
								}
								fclose(archproc);
								if (u > 0)
									remove("procesos.txt");
								//funciones de procesos 
								proceso();
								system("cls");
								for(m= 0;m< 80; m++)
								{
									printf("%c", 95);
								}					
								printf("\n\n Debe realizar facturacion para no perder sus procesos. \n Puede acceder desde Menu->Reportes->Facturacion  \n");
								cta++;
								ctd = 1;
							}
						printf("\n");
						system("pause");  
						system("cls");
						for(m= 0;m< 80; m++)
						{
							printf("%c", 95);
						}
						printf("\n");  
						do
						{
							printf("\n %cDesea regresar al men%c? [1-Si/2-No]: ", 168, 163);
							fflush(stdin);
							gets(aux);
							opr = atoi(aux);
						}while(opr != 1 && opr !=2);
						system("cls");
						break;
						
				case 4: archivo = fopen("altas.txt", "r");    //BAJAS
						if (archivo == NULL){
							fclose(archivo);
							printf("\n No ha introducido ningun usuario. \n\n");
							system("pause");
						}
						else
							if (ctc == 0)
							{
								fclose(archivo);
								bajas(&usu[0], &usu[0], &col[0]);
								ctc++;
							}
							else{
								fclose(archivo);
								for(i= 0;i< 80; i++)
								{
									printf("%c", 95);
								}
								printf("\n");
								printf("\n Para dar de baja otro usuario debes salir del programa \n");
								printf("\n");
								system("pause");
							}
						system("cls");
						do
						{
							for(i= 0;i< 80; i++)
							{
								printf("%c", 95);
							}
							printf("\n");
							printf("\n %cDesea regresar al men%c? [1-Si/2-No]: ", 168, 163);
							fflush(stdin);
							gets(aux);
							opr = atoi(aux);
						}while(opr != 1 && opr!= 2);
						system("cls");		
						break;
						
				case 5: archivo = fopen("altas.txt", "r");   //REPORTES
						if (archivo == NULL){
							fclose(archivo);
							printf("\n No ha introducido ningun usuario. \n\n");
							system("pause");
						}
						else{
							fclose(archivo);
							do
							{
								printf("\n\t\tREPORTES\n");
								for(i= 0;i< 80; i++)
								{
									printf("%c", 95);
								}
								printf("\n");
								printf("\n 1. Pagos realizados \n 2. Pagos no realizados \n 3. Facturacion \n\n");
								for(i= 0;i< 80; i++)
								{
									printf("%c", 95);
								}
								printf("\n");
								printf("\nOpcion: ");
								fflush(stdin);
								gets(aux);
								opre = atoi(aux);
							}while(opre != 1 && opre != 2 && opre != 3);
							system("cls");
							switch(opre){
								case 1: pagosrealizados();
										for(i= 0;i< 80; i++)
										{
											printf("%c", 95);
										}		
										printf("\n");
										printf("\n Reporte de pagos realizados fue creado con exito \n\n");
										system("pause");
										break;
										
								case 2: pagosnorealizados();
										for(i= 0;i< 80; i++)
										{
											printf("%c", 95);
										}
										printf("\n");
										printf("\n Reporte de pagos no realizados fue creado con exito \n\n");
										system("pause");
										break;
										
								case 3: if(cta == 0){
											for(i= 0;i< 80; i++)
											{
												printf("%c", 95);
											}
											printf("\n");
											printf("\n Debe realizar proceso primero \n\n");
											system("pause");	
										}
										else{
											//Realizar facturacion
											facturacionlista();
											facturacionindividual();
											//Hacer el respaldo con el nombre que quiera el usuario
											//Borrar lo que tenia procesos
											for(m= 0;m< 80; m++)
											{
												printf("%c", 95);
											}
											printf("\n");
											printf("\n Facturacion realizada con exito \n\n");
											remove("procesos.txt");
											remove("nprocesos.txt");
											cta = 0;
											system("pause");
										}
										break;
							}
						}
						
						system("cls");
						do
						{
							for(i= 0;i< 80; i++)
							{
								printf("%c", 95);
							}
							printf("\n");
							printf("\n %cDesea regresar al men%c? [1-Si/2-No]: ", 168, 163);
							fflush(stdin);
							gets(aux);
							opr = atoi(aux);
						}while(opr != 1 && opr !=2);
						system("cls");
						break;
						
				case 6: 
						printf("\n\t\tSALIR\n");
						for(i= 0;i< 80; i++)
						{
							printf("%c", 95);
						}
						do
						{
							printf("\n\n %cEst%c seguro de que desea salir? [1-Si/2-No]: ", 168, 160);       //SALIR
							fflush(stdin);
							gets(aux);
							ops = atoi(aux);
						}while(ops != 1 && ops !=2 );
						if (ops == 2)
							opr = 1;
						else
							opr = 2;
						system("cls");
						break;
									
				default: printf("\n\n\tError al introducir opcion, volviendo al menu...\n\n"); 
						system("pause");
						system("cls");
						goto menu;
			}
	} while (ops == 2 || opr == 1);
	
	printf("\n\t\tHa salido del programa...");
	//------
	printf("\n\n\n");
	system("pause");
	return 0;
}


void altas(int ctr, struct usuario *ap, struct tarifas *pp, struct colonias *op)
{
	int i, n=0, opi, opc,m=0, d=0, len,ctri, on, contc=0, contc2=0, e=0, k, var = 0, ocol=0, ag, nuv, nl, j, v, linea, w;
	char aux[' '], aux2[' '], aux3[' '], auxe[' '], auxcol[' '];
	float a,Aux,kaux, numauxe;
	FILE *archivo;
	FILE *archcol;
	FILE *archtar;
	FILE *archn;
	FILE *archncol;
	
	archcol = fopen("colonias.txt", "r");
	if (archcol != NULL){
		ocol = 1;
	}
	fclose(archcol);
	
	if (ctr == 0){ //NO EXISTE NADA
		do{	
		printf("\n\t\tALTAS\n\n");
		printf("\n Establecer las tarifas \n");
		for(i= 0;i< 80; i++)
		{
			printf("%c", 95);
		}
		printf("\n");
		for (i= 0;i< 8;i++){ 
			do
			{
				printf("\n\n Introduzca el valor de la tarifa_%d: ", i+1);
				fflush(stdin);
				gets(aux);
				pp->tar[i] = atof(aux);
			}while(pp->tar[i]<1);
			pp->pos[i] = i+1;
		}
		printf("\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\t\t TARIFAS \n\n");
		for(i= 0;i< 80; i++)
		{
			printf("%c", 95);
		}
		for (i= 0;i< 8;i++){ 
			printf("\n\n Tarifa_%d: %.2f ", i+1, pp->tar[i]);
		}
		printf("\n");
		for(i= 0;i< 80; i++)
		{
			printf("%c", 95);
		}
		printf("\n");
		do
		{
			printf("\n La informacion introducida es correcta [1-Si/2-No]: ");
			fflush(stdin);
			gets(aux);
			opc = atoi(aux);
		}while(opc!=1 && opc!=2);
			system("cls");
		}while(opc==2);
		if (ctr == 0)
		{
			archtar = fopen("tarifas.txt", "wt");
			if(archtar == NULL)
			{
				printf("\nError al crear Archivo Tarifas.\n\n");
			}
			
			for(i= 0; i < 8; i++)
			{
				fprintf(archtar, "%.2f ", pp->tar[i]); 
				fprintf(archtar, "\n");
			}
			fclose(archtar);
		}
		printf("\n\n");
		
		system("cls");
		printf("\n\t\tALTAS\n\n");
		printf("\n DATOS DE COLONIA \n");
		do{
			do{
				for(i= 0;i< 80; i++)
				{
					printf("%c", 95);
				}
				printf("\n");
				do
				{
					printf("\n Introduzca clave de colonia: ");
					fflush(stdin);
					gets(aux);
					op->clv = atof(aux);
					k=op->clv;
					kaux=op->clv - k;
				}while(op->clv<1 || kaux!=0);
				
				do
				{
					printf("\n Introduzca el nombre de la colonia: ");
					fflush(stdin);
					gets(op->nomcol);
					len = strlen(op->nomcol);
					d = 0;
				for(i= 0;i< len;i++){
					if(isdigit(op->nomcol[i])){
						d++;	
						break;
					}
					if (op->nomcol[i] == ' ')
						op->nomcol[i] = '_';
					else 
						continue;
				}
				}while(d > 0);
				for(i= 0;i< 80; i++)
				{
					printf("%c", 95);
				}
				printf("\n");
				do
				{
					printf("\n La informacion introducida es correcta [1-Si/2-No]: ");
					fflush(stdin);
					gets(aux);
					opc = atoi(aux);
				}while(opc != 1 && opc != 2);
				system("cls");
			} while (opc == 2);	
			if (ctr == 0 && var == 0)
			{
					archcol = fopen("colonias.txt", "wt");
					if(archcol == NULL)
					{
						printf("\nError al crear Archivo COLONIAS.\n\n");
					}
					
					fprintf(archcol, "%.2f ", op->clv);
					fprintf(archcol, "%s", op->nomcol); 
					fprintf(archcol, "\n");
					fclose(archcol);
					var = 1;
			}
			else
			{
				archcol = fopen("colonias.txt", "a");
					if(archcol == NULL)
					{
						printf("\nError al abrir Archivo COLONIAS.\n\n");
					}
					fprintf(archcol, "%.2f ", op->clv);
					fprintf(archcol, "%s", op->nomcol); 
					fprintf(archcol, "\n");
					fclose(archcol);
			}
			for(i= 0;i< 80; i++)
			{
				printf("%c", 95);
			}
			printf("\n");
			do{
				printf("\n %cDesea agregar otra colonia? [1-Si/2-No]: ", 168);
				fflush(stdin);//validado hoy
				gets(aux);
				on = atoi(aux);
			} while (on != 1 && on != 2);
			op++;
			contc++;
			system("cls");
		} while (on == 1);
		
		//guardar ncol
		archncol = fopen("ncol.txt", "w");
		fprintf(archncol, "%d", contc);
		fprintf(archncol, "\n");
		fclose(archncol);
		
		system("cls");
		
		//ENTRADA DE USUARIOS PRIMERA INTERACCION------------------------------------
		do{ //control de cantidad de usuarios
			do { //control de informacion correcta
					system("cls");
					printf("\n\n\t Introduzca los datos del nuevo usuario \n\n");
				for(i= 0;i< 80; i++)
				{
					printf("%c", 95);
				}
				printf("\n");
				do{
					printf("\n Numero de usuario: ");
					fflush(stdin);
					gets(aux);
					ap->num = atof(aux);
					k = ap->num;
					kaux = ap->num - k;
				}while(ap->num<1 || kaux!=0);  
							
				do{
					do{
						printf("\n Tipo de usuario [1-8]: ");
						fflush(stdin);
						gets(aux);
						ap->tipo = atof(aux);
						k=ap->tipo;
						kaux=ap->tipo - k;
					}while((ap->tipo!=1 && ap->tipo!=2)&&(ap->tipo!=3 && ap->tipo!=4)&&(ap->tipo!=5 && ap->tipo!=6)&&(ap->tipo!=7 && ap->tipo!=8));  
				}while(kaux!=0);
				do
				{
					printf("\n Nombre: ");
					fflush(stdin);
					gets(ap->nom);
					len = strlen(ap->nom);
					d = 0;
					for(i = 0;i< len;i++){
						if(isdigit(ap->nom[i])){
							d++;	
							break;
					}
					if (ap->nom[i] == ' ')
						ap->nom[i] = '_';
					else 
						continue;
					}
				}while(d > 0);
				
				do{
					do
					{
						v=0;
						printf("\n Clave de colonia: ");
						fflush(stdin);
						gets(aux);
						ap->clave = atof(aux);
						k = ap->clave;
						kaux = ap->clave - k;
					}while(ap->clave<1 || kaux!=0);
					//Buscar si está o no la colonia
					archcol = fopen("colonias.txt", "rt");
					for(j = 0;j< contc;j++){
						fscanf(archcol, "%s", &auxe);
						numauxe = atof(auxe);
						if (numauxe == ap->clave){
							fscanf(archcol, "%s", &auxe);
							v++;
							linea = j + 1;
						}
						else{
							fscanf(archcol, "%s", &auxe);
						}
					}
					fclose(archcol);
					if (v == 0)
						printf("\n Clave no encontrada \n");
				} while (v == 0);
				
				
				do{
					do
					{
						printf("\n Nombre de colonia: ");
						fflush(stdin);
						gets(ap->nocol);
						len = strlen(ap->nocol);
						d = 0;
						for(i = 0;i< len;i++){
						if(isdigit(ap->nocol[i])){
							d++;	
							break;
						}
						if (ap->nocol[i] == ' ')
							ap->nocol[i] = '_';
						else 
							continue;
					}
					}while(d > 0);
					w = 0;
					archcol = fopen("colonias.txt", "rt");
					for (j=0;j<contc;j++){
						fscanf(archcol, "%s", &auxe);
						fscanf(archcol, "%s", &auxe);
						strcpy(auxcol, auxe);
						if ((j+1)==linea && (strcmp(auxcol, ap->nocol)==0))
							w++;
					}
					fclose(archcol);
					if (w == 0)
						printf("\n La clave y el nombre introducido no coinciden \n");
						system("pause");
						system("cls");
				}while(w == 0);
				
				
				printf("\n Direccion: ");
				fflush(stdin);
				gets(ap->dir);
				len = strlen(ap->dir);
				for(i = 0;i< len;i++){
					
					if (ap->dir[i] == ' ')
						ap->dir[i] = '_';
					else 
						continue;
				}
				
				do
				{
					printf("\n Consumo: ");
					fflush(stdin);
					gets(aux);
					ap->cons = atof(aux);
				}while(ap->cons < 1);
				
				do
				{
					printf("\n Pago: ");
					fflush(stdin);
					gets(aux);
					ap->pago = atof(aux);
				}while(ap->pago < 0);
				for(i= 0;i< 80; i++)
				{
					printf("%c", 95);
				}
				do{
					printf("\n\n %cLa informacion introducida es correcta? [1-Si/2-No]: ", 168);
					fflush(stdin);
					gets(aux);
					opc = atoi(aux);
				} while (opc != 1 && opc != 2);
				system("cls");
		} while (opc == 2);
		//impresion en archivo
		
		if (e == 0)
		{
			archivo = fopen("altas.txt", "wt");
			if(archivo == NULL)
			{
				printf("\nError al crear Archivo Altas.\n\n");
			}
			fprintf(archivo, "%.2f ", ap->num); 
			fprintf(archivo, "%.2f ", ap->tipo);
			fprintf(archivo, "%s ", ap->nom);
			fprintf(archivo, "%.2f ", ap->clave);
			fprintf(archivo, "%s ", ap->nocol);
			fprintf(archivo, "%s ", ap->dir);
			fprintf(archivo, "%.2f ", ap->cons);
			fprintf(archivo, "%.2f", ap->pago);
			fprintf(archivo, "\n");
			fclose(archivo);
		}
		else
		{
			archivo = fopen("altas.txt", "at");
			fprintf(archivo, "%.2f ", ap->num); 
			fprintf(archivo, "%.2f ", ap->tipo);
			fprintf(archivo, "%s ", ap->nom);
			fprintf(archivo, "%.2f ", ap->clave);
			fprintf(archivo, "%s ", ap->nocol);
			fprintf(archivo, "%s ", ap->dir);
			fprintf(archivo, "%.2f ", ap->cons);
			fprintf(archivo, "%.2f", ap->pago);
			fprintf(archivo, "\n");
			fclose(archivo);
		}
		for(i= 0;i< 80; i++)
		{
			printf("%c", 95);
		}
		printf("\n");
		do{
			printf("\n\n %cDesea agregar otro usuario? [1-Si/2-No]: ", 168);
			fflush(stdin);
			gets(aux);
			opi = atoi(aux);
		} while (opi != 1 && opi != 2);
		ap++;
		n++;
		e++;
		system("cls");
		} while (opi == 1);
		
		archn = fopen("n.txt", "w");
		fprintf(archn, "%d", n);
		fprintf(archn, "\n");
		fclose(archn);
	} //fin del if de ctr == 0
	
	//SEGUNDA INTERACCION
	//Cuando salio del programa y vuelve a entrar (ya tiene altas y colonias creadas)
	if (ctr != 0 && ocol != 0)
	{
		do{
			do
			{
				printf("\n\t\tAltas\n");
				for(i= 0;i< 80; i++)
				{
					printf("%c", 95);
				}
				printf("\n");
				printf("\n %cQue desea agregar? \n 1. Nuevo usuario \n 2. Nueva colonia \n\n", 168);
				for(i= 0;i< 80; i++)
				{
					printf("%c", 95);
				}
				printf("\n");
				printf("\nOpcion: ");
				fflush(stdin);
				gets(aux);
				ag = atoi(aux);
			}while(ag != 1 && ag != 2);
			system("cls");
			switch(ag)
			{
				case 1: 
						do{ //control de cantidad de usuarios
						do { //control de informacion correcta
								printf("\n\n\t Introduzca los datos del nuevo usuario \n\n");
							for(i= 0;i< 80; i++)
							{
								printf("%c", 95);
							}
							printf("\n");
							do{
								printf("\n Numero de usuario: ");
								fflush(stdin);
								gets(aux);
								ap->num = atof(aux);
								k=  ap->num;
								kaux = ap->num - k;
							}while(ap->num<1 || kaux!=0); 
									
							do{
								do{
									printf("\n Tipo de usuario [1-8]: ");
									fflush(stdin);
									gets(aux);
									ap->tipo = atof(aux);
									k = ap->tipo;
									kaux = ap->tipo - k;
								}while((ap->tipo != 1 && ap->tipo != 2)&&(ap->tipo != 3 && ap->tipo !=4 )&&(ap->tipo !=5 && ap->tipo != 6)&&(ap->tipo !=7 && ap->tipo !=8));  
							}while(kaux != 0);
							do
							{
								printf("\n Nombre: ");
								fflush(stdin);
								gets(ap->nom);
								len = strlen(ap->nom);
								d = 0;
							for(i= 0;i< len;i++){
								if(isdigit(ap->nom[i])){
									d++;	
									break;
								}
								if (ap->nom[i] == ' ')
									ap->nom[i] = '_';
								else 
									continue;
								}
							}while(d > 0);
							
							do{
								do
								{
									v = 0;
									printf("\n Clave de colonia: ");
									fflush(stdin);
									gets(aux);
									ap->clave = atof(aux);
									k = ap->clave;
									kaux = ap->clave - k;
								}while(ap->clave < 1 || kaux != 0);
								//Buscar si está o no la colonia
								archncol = fopen("ncol.txt", "r");
								fscanf(archncol, "%s", &auxe);
								contc = atof(auxe);
								fclose(archncol);
								
								archcol = fopen("colonias.txt", "rt");
								for(j=0;j<contc;j++){
									fscanf(archcol, "%s", &auxe);
									numauxe = atof(auxe);
									if (numauxe == ap->clave){
										fscanf(archcol, "%s", &auxe);
										v++;
										linea = j + 1;
									}
									else{
										fscanf(archcol, "%s", &auxe);
									}
								}
								fclose(archcol);
								if (v == 0)
								{
									for(i= 0;i< 80; i++)
									{
										printf("%c", 95);
									}
									printf("\n");
									printf("\n No hay una colonia con esa clave. ");	
									for(i= 0;i< 80; i++)
									{
										printf("%c", 95);
									}
									printf("\n");
								}
									
							} while (v == 0);
							
							do{
								do
								{
									w = 0;
									printf("\n Nombre de colonia: ");
									fflush(stdin);
									gets(ap->nocol);
									len = strlen(ap->nocol);
									d = 0;
									for(i=0 ;i< len;i++){
										if(isdigit(ap->nocol[i])){
											d++;	
											break;
										}
										if (ap->nocol[i] == ' ')
											ap->nocol[i] = '_';
										else 
											continue;
									}
									}while(d > 0);
									w = 0;
									archncol = fopen("ncol.txt", "r");
									fscanf(archncol, "%s", &auxe);
									contc = atof(auxe);
									fclose(archncol);
									archcol = fopen("colonias.txt", "rt");
									for (j=0;j<contc;j++){
										fscanf(archcol, "%s", &auxe);
										fscanf(archcol, "%s", &auxe);
										strcpy(auxcol, auxe);
										if ((j+1)==linea && (strcmp(auxcol, ap->nocol)==0))
											w++;
									}
									fclose(archcol);
									if (w == 0)
									{
										for(i= 0;i< 80; i++)
										{
											printf("%c", 95);
										}
										printf("\n");
										printf("\n La clave y el nombre introducido no coinciden \n");
										for(i= 0;i< 80; i++)
										{
											printf("%c", 95);
										}
										printf("\n");
									}
										
							}while(w == 0);
							
							do
							{
								printf("\n Direccion: ");
								fflush(stdin);
								gets(ap->dir);
								len = strlen(ap->dir);
								d = 0;
							for(i= 0;i< len;i++){
							if(isdigit(ap->dir[i])){
								d++;	
								break;
							}
							if (ap->dir[i] == ' ')
								ap->dir[i] = '_';
							else 
								continue;
								}
							}while(d > 0);
						
							do
							{
								printf("\n Consumo: ");
								fflush(stdin);
								gets(aux);
								ap->cons = atof(aux);
							}while(ap->cons < 1);
							
							do
							{
								printf("\n Pago: ");
								fflush(stdin);
								gets(aux);
								ap->pago = atof(aux);
							}while(ap->pago < 0);
							for(i= 0;i< 80; i++)
							{
								printf("%c", 95);
							}
							do{
								printf("\n\n %cLa informacion introducida es correcta? [1-Si/2-No]: ", 168);
								fflush(stdin);
								gets(aux);
								opc = atoi(aux);
							} while (opc != 1 && opc != 2);
							system("cls");
						} while (opc == 2);
							//impresion en archivo
							
								archivo = fopen("altas.txt", "at");
								fprintf(archivo, "%.2f ", ap->num); 
								fprintf(archivo, "%.2f ", ap->tipo);
								fprintf(archivo, "%s ", ap->nom);
								fprintf(archivo, "%.2f ", ap->clave);
								fprintf(archivo, "%s ", ap->nocol);
								fprintf(archivo, "%s ", ap->dir);
								fprintf(archivo, "%.2f ", ap->cons);
								fprintf(archivo, "%.2f", ap->pago);
								fprintf(archivo, "\n");
								fclose(archivo);
											
							do{
								for(i= 0;i< 80; i++)
								{
									printf("%c", 95);
								}
								printf("\n");
								printf("\n %cDesea agregar otro usuario? [1-Si/2-No]: ", 168);
								fflush(stdin);
								gets(aux);
								opi = atoi(aux);
							} while (opi != 1 && opi != 2);
							ap++;
							n++;
							system("cls");
							} while (opi == 1);
							archn = fopen("n.txt", "r");
							fscanf(archn, "%s", &aux3); //la guardo en aux 3
							nl = atoi(aux3);
							n = n + nl;
							fclose(archn);
							
							archn = fopen("n.txt", "w");
							fprintf(archn, "%d", n);
							fprintf(archn, "\n");
							fclose(archn);
							break;
							
				case 2: contc=0;
						system("cls");
						printf("\n\t\t\t DATOS DE COLONIA \n\n");
						for(i= 0;i< 80; i++)
						{
						printf("%c", 95);
						}
						printf("\n");
						do{ //Agregar mas colonias
							contc2=0;
							do{ //Informacion correcta
								do{
									do
									{
										v=0;
										printf("\n Introduzca clave de colonia: ");
										fflush(stdin);
										gets(aux);
										op->clv = atof(aux);
										k = op->clv;
										kaux = op->clv - k;
									}while(op->clv<1 || kaux!=0);
									
									archncol = fopen("ncol.txt", "r");
									fscanf(archncol, "%s", &auxe);
									contc = atof(auxe);
									fclose(archncol);
									archcol = fopen("colonias.txt", "rt");
									for(j=0;j<contc;j++){
										fscanf(archcol, "%s", &auxe);
										numauxe = atof(auxe);
										if (numauxe == op->clv){
											fscanf(archcol, "%s", &auxe);
											v++;
										}
										else{
											fscanf(archcol, "%s", &auxe);
										}
									}
									fclose(archcol);
									if (v > 0)
										printf("\n La clave ya existe \n");
								} while (v > 0);
															
									do{
											do{
												w = 0;
												printf("\n Introduzca el nombre de colonia: ");
												fflush(stdin);
												gets(op->nomcol);
												len = strlen(op->nomcol);
												d = 0;
												for(i= 0;i< len;i++){
													if(isdigit(op->nomcol[i])){
														d++;	
														break;
													}
													if (op->nomcol[i] == ' ')
														op->nomcol[i] = '_';
													else 
														continue;
												}
											}while(d>0);
											w = 0;
											archncol = fopen("ncol.txt", "r");
											fscanf(archncol, "%s", &auxe);
											contc = atof(auxe);
											fclose(archncol);
											archcol = fopen("colonias.txt", "rt");
											for (j=0;j<contc;j++){
												fscanf(archcol, "%s", &auxe);
												fscanf(archcol, "%s", &auxe);
												strcpy(auxcol, auxe);
												if(strcmp(auxcol, op->nomcol)==0){
													w++;
												}												
											}
											fclose(archcol);
											if (w > 0)
												printf("\n El nombre ya existe \n");
										}while(w > 0);
									
									for(i= 0;i< 80; i++)
									{
										printf("%c", 95);
									}
									printf("\n");
									do
									{
										printf("\n La informacion introducida es correcta [1-Si/2-No]: ");
										fflush(stdin);
										gets(aux);
										opc = atoi(aux);
									}while(opc != 1 && opc!= 2);
									
									system("cls");
							} while (opc == 2);	
							
							//impresion en archivo colonias
								archcol = fopen("colonias.txt", "a");
								if(archcol == NULL)
								{
									printf("\nError al abrir Archivo COLONIAS.\n\n");					
								}
									fprintf(archcol, "%.2f ", op->clv);
									fprintf(archcol, "%s", op->nomcol); 
									fprintf(archcol, "\n");
									fclose(archcol);
							
							do{
								for(i= 0;i< 80; i++)
								{
									printf("%c", 95);
								}
								printf("\n");
								printf("\n %cDesea agregar otra colonia? [1-Si/2-No]: ", 168);
								fflush(stdin);
								gets(aux);
								on = atoi(aux);
							} while (on != 1 && on != 2);
							
							op++;
							contc2++;
							system("cls");
						} while (on == 1);
						
							archncol = fopen("ncol.txt", "r");
							fscanf(archncol, "%s", &aux3); //la guardo en aux 3
							nl = atoi(aux3);
							contc2 = contc2 + nl;
							fclose(archncol);
							
							archncol = fopen("ncol.txt", "w");
							fprintf(archncol, "%d", contc2);
							fprintf(archncol, "\n");
							fclose(archncol);		
							break;
			} //Fin del switch
			
			do{
				for(i= 0;i< 80; i++)
				{
					printf("%c", 95);
				}
				printf("\n");
				printf("\n %cDesea continuar agregando? [1-Si/2-No]: ", 168);
				fflush(stdin);
				gets(aux);
				nuv = atoi(aux);;
			} while (nuv != 1 && nuv != 2);
			system("cls");
		} while (nuv == 1);
		
	} //Fin del if
}

void modificacion()
{
	int i, linea, ctri = 0, opm = 0, temp = 1, n, opc, s, len, d=0, k, m;
	float num, numaux, nf, nmodi, tm, clvm, conm, pagm, saux;
	char ch, aux[' '], auxnom[' '], auxnomcol[' '], auxdir[' '], anum[' '], atipo[' '], anom[' '], aclave[' '], anocol[' '], adir[' '], 
	acons[' '], apag[' '], aux3[' '], auxm[' '];
	
	FILE *archivo, *archivoaux, *archn;
	
	do{ //modificar a otro usuario
		temp = 1;
		do { //control de numero equivocado
			ctri = 0;
			archn = fopen("n.txt", "r");
			fscanf(archn, "%s", &aux3);
			n = atoi(aux3);
			fclose(archn);
			
			archivo = fopen("altas.txt", "rt");
			printf("\n\t\t\tMODIFICACIONES\n");
			for(m= 0;m< 80; m++)
			{
				printf("%c", 95);
			}
			printf("\n");
			do
			{
				printf("\n Introduzca el numero del usuario que quiere modificar: ");
				fflush(stdin);
				gets(aux);
				num = atof(aux);
			}while(num < 0);
			
				for(i=0;i<n;i++){
					fscanf(archivo, "%s", &aux);
					numaux = atof(aux);
					if (numaux == num){
						nf = numaux;
						printf("\n Numero encontrado \n\n");
						system("pause");
						system("cls");
						ctri++;
						linea = i+1;
						fscanf(archivo, "%s", &atipo);
						fscanf(archivo, "%s", &anom);
						fscanf(archivo, "%s", &aclave);
						fscanf(archivo, "%s", &anocol);
						fscanf(archivo, "%s", &adir);
						fscanf(archivo, "%s", &acons);
						fscanf(archivo, "%s", &apag);
						for(m= 0;m< 80; m++)
						{
							printf("%c", 95);
						}
						printf("\n");
						do
						{
							printf("\n %cQue dato desea modificar? \n\n 1. Numero \n 2. Tipo \n 3. Nombre \n 4. Clave de colonia \n 5. Nombre de colonia", 168);
							printf("\n 6. Direccion \n 7. Consumo \n 8. Pago\n\n"); 
							for(m= 0;m< 80; m++)
							{
								printf("%c", 95);
							}
							printf("\n");
							printf("\nOpcion: ");
							fflush(stdin);
							gets(aux);
							opm = atoi(aux);
						}while(opm != 1 && opm != 2 && opm !=3 && opm != 4 && opm !=5 && opm != 6 && opm != 7 && opm != 8);
						
						switch(opm){
							case 1: system("cls");
									do{
										for(m= 0;m< 80; m++)
										{
											printf("%c", 95);
										}
										printf("\n");
										printf("\n Introduzca el numero de usuario modificado: ");
										fflush(stdin);
										gets(auxm);
										nmodi = atof(auxm);
										s = nmodi;
										saux = nmodi - s;
									} while (nmodi < 1 || saux != 0);
									
									break;
									
							case 2: system("cls");
									do{
										do{
											for(m= 0;m< 80; m++)
											{
												printf("%c", 95);
											}	
											printf("\n");
											printf("\n Introduzca el tipo modificado: ");
											fflush(stdin);
											gets(auxm);
											tm = atof(auxm);
											s = tm;
											saux = tm - s;
										} while ((tm != 1 && tm!=2)&&(tm!=3 && tm!=4)&&(tm!=5 && tm!=6)&&(tm!=7 && tm!=8));
									} while (saux != 0);
									break;
									
							case 3: system("cls");
									do{
										for(m= 0;m< 80; m++)
										{
											printf("%c", 95);
										}
										printf("\n");
										printf("\n Introduzca el nombre modificado: ");
										fflush(stdin);
										gets(auxnom); 
										len = strlen(auxnom);
										d = 0;
										for (k = 0;k< len;k++){
											if (isdigit(auxnom[k])){
												d++;
												break;
											}
											if (auxnom[k] == ' ')
												auxnom[k] = '_';
											else
												continue;
										}
									} while (d > 0);	
									break;
									
							case 4: system("cls");
									do{
										for(m= 0;m< 80; m++)
										{
											printf("%c", 95);
										}
										printf("\n");
										printf("\n Introduzca la clave de colonia modificada: ");
										fflush(stdin);
										gets(auxm);
										clvm = atof(auxm);
										s = clvm;
										saux = clvm - s;
									} while (clvm < 1 || saux != 0);
									
									break;
									
							case 5: system("cls");
									do{
										for(m= 0;m< 80; m++)
										{
											printf("%c", 95);
										}
										printf("\n");
										printf("\n Introduzca el nombre de colonia modificado: ");
										fflush(stdin);
										gets(auxnomcol);
										len = strlen(auxnomcol);
										d = 0;
										for (k=0;k<len;k++){
											if (isdigit(auxnomcol[k])){
												d++;
												break;
											}
											if (auxnomcol[k] == ' ')
												auxnomcol[k] = '_';
											else
												continue;
										}	
									} while (d > 0);		
									break;
									
							case 6: system("cls");
									for(m= 0;m< 80; m++)
									{
										printf("%c", 95);
									}
									printf("\n");
									printf("\n Introduzca la direccion modificada: ");
									fflush(stdin);
									gets(auxdir);
									len = strlen(auxdir);
									d = 0;
									for(k=0;k<len;k++){
										if (auxdir[k] == ' ')
											auxdir[k] = '_';
										else
											continue;
									}
									break;
									
							case 7: system("cls");
									for(m= 0;m< 80; m++)
									{
										printf("%c", 95);
									}
									printf("\n");
									do{
										printf("\n Introduzca el consumo modificado: ");
										fflush(stdin);
										gets(auxm);
										conm = atof(auxm);
									} while (conm < 1);
									break;
									
							case 8: system("cls");
									for(m= 0;m< 80; m++)
									{
										printf("%c", 95);
									}
									printf("\n");
									do{
										printf("\n Introduca el pago modificado: ");
										fflush(stdin);
										gets(auxm);
										pagm = atof(auxm);
									} while (pagm < 0);
									break;
							
						}
					} //FIN del IF
					else{
						fscanf(archivo, "%s", &aux);
						fscanf(archivo, "%s", &aux);
						fscanf(archivo, "%s", &aux);
						fscanf(archivo, "%s", &aux);
						fscanf(archivo, "%s", &aux);
						fscanf(archivo, "%s", &aux);
						fscanf(archivo, "%s", &aux);
					}
			} //FIN DEL FOR-----------
			
			fclose(archivo);
			system("cls");
			if (ctri > 0) //EL numero SI fue encontrado, asi que BORRO su linea
				{
					//PROCESO DE BORRADO
				//-------------------------------------
				printf("\n\n\t Lista de usuarios actuales \n\n");
				archivo = fopen("altas.txt", "r");
				ch = getc(archivo);
				while (ch != EOF)
				{
					printf("%c", ch);
					ch = getc(archivo);
				}
				rewind(archivo);
				archivoaux = fopen("replica.c", "w");
				ch = getc(archivo);
				while (ch != EOF)
				{
					if (temp != linea)
					{
						putc(ch, archivoaux);
					}
					if (ch == '\n')
						temp++;
					ch = getc(archivo);
				}
				fclose(archivo);
				fclose(archivoaux);
				remove("altas.txt");
				rename("replica.c", "altas.txt");
					
			}
			else
			{
				for(m= 0;m< 80; m++)
				{
					printf("%c", 95);
				}					
				printf("\n");
				printf("\n El numero que ingreso no se encuentra en el archivo \n");
				printf("\n");
				system("pause");
				system("cls");
			}
			
		} while (ctri == 0); //el numero no se encontro. 
		
		//--------------------------------------------------------
		//Hacer append
		switch(opm){
			case 1: archivo = fopen("altas.txt", "at");
					fprintf(archivo, "%.2f ", nmodi);  //cambio de numero de usuario
					fprintf(archivo, "%s ", atipo); 
					fprintf(archivo, "%s ", anom);
					fprintf(archivo, "%s ", aclave);
					fprintf(archivo, "%s ", anocol);
					fprintf(archivo, "%s ", adir);
					fprintf(archivo, "%s ", acons);
					fprintf(archivo, "%s", apag);
					fprintf(archivo, "\n");
					fclose(archivo);
					break;
					
			case 2: archivo = fopen("altas.txt", "at");
					fprintf(archivo, "%.2f ", nf);
					fprintf(archivo, "%.2f ", tm); //cambio de tipo de usuario
					fprintf(archivo, "%s ", anom);
					fprintf(archivo, "%s ", aclave);
					fprintf(archivo, "%s ", anocol);
					fprintf(archivo, "%s ", adir);
					fprintf(archivo, "%s ", acons);
					fprintf(archivo, "%s", apag);
					fprintf(archivo, "\n");
					fclose(archivo);
					break;
					
			case 3: archivo = fopen("altas.txt", "at"); 
					fprintf(archivo, "%.2f ", nf);
					fprintf(archivo, "%s ", atipo);
					fprintf(archivo, "%s ", auxnom); //cambio nombre
					fprintf(archivo, "%s ", aclave);
					fprintf(archivo, "%s ", anocol);
					fprintf(archivo, "%s ", adir);
					fprintf(archivo, "%s ", acons);
					fprintf(archivo, "%s", apag);
					fprintf(archivo, "\n");
					fclose(archivo);
					break;
					
			case 4: archivo = fopen("altas.txt", "at");  //cambio de clave de colonia
					fprintf(archivo, "%.2f ", nf);
					fprintf(archivo, "%s ", atipo);
					fprintf(archivo, "%s ", anom);
					fprintf(archivo, "%.2f ", clvm);
					fprintf(archivo, "%s ", anocol);
					fprintf(archivo, "%s ", adir);
					fprintf(archivo, "%s ", acons);
					fprintf(archivo, "%s", apag);
					fprintf(archivo, "\n");
					fclose(archivo);
					break;
					
			case 5: archivo = fopen("altas.txt", "at");  //cambio de nombre de colonia
					fprintf(archivo, "%.2f ", nf);
					fprintf(archivo, "%s ", atipo);
					fprintf(archivo, "%s ", anom);
					fprintf(archivo, "%s ", aclave);
					fprintf(archivo, "%s ", auxnomcol);
					fprintf(archivo, "%s ", adir);
					fprintf(archivo, "%s ", acons);
					fprintf(archivo, "%s", apag);
					fprintf(archivo, "\n");
					fclose(archivo);
					break;
					
			case 6: archivo = fopen("altas.txt", "at");  //cambio de direccion
					fprintf(archivo, "%.2f ", nf);
					fprintf(archivo, "%s ", atipo);
					fprintf(archivo, "%s ", anom);
					fprintf(archivo, "%s ", aclave);
					fprintf(archivo, "%s ", anocol);
					fprintf(archivo, "%s ", auxdir);
					fprintf(archivo, "%s ", acons);
					fprintf(archivo, "%s", apag);
					fprintf(archivo, "\n");
					fclose(archivo);
					break;
					
			case 7: archivo = fopen("altas.txt", "at");  //cambio de consumo
					fprintf(archivo, "%.2f ", nf);
					fprintf(archivo, "%s ", atipo);
					fprintf(archivo, "%s ", anom);
					fprintf(archivo, "%s ", aclave);
					fprintf(archivo, "%s ", anocol);
					fprintf(archivo, "%s ", adir);
					fprintf(archivo, "%.2f ", conm);
					fprintf(archivo, "%s", apag);
					fprintf(archivo, "\n");
					fclose(archivo);
					break;
					
			case 8: archivo = fopen("altas.txt", "at");  //cambio de pago
					fprintf(archivo, "%.2f ", nf);
					fprintf(archivo, "%s ", atipo);
					fprintf(archivo, "%s ", anom);
					fprintf(archivo, "%s ", aclave);
					fprintf(archivo, "%s ", anocol);
					fprintf(archivo, "%s ", adir);
					fprintf(archivo, "%s ", acons);
					fprintf(archivo, "%.2f", pagm);
					fprintf(archivo, "\n");
					fclose(archivo);
					break;
		}
		printf("\n\n\tUSUARIO MODIFICADO CON EXITO\n\n");	
		printf("\n\n\t Lista de usuarios actualizada \n\n");
		archivo = fopen("altas.txt", "r");
		ch = getc(archivo);
		while (ch != EOF)
		{
			printf("%c", ch);
			ch = getc(archivo);
		}
		fclose(archivo);
	
		printf("\n");
		system("pause");
		system("cls");
		for(m= 0;m< 80; m++)
		{
			printf("%c", 95);
		}
		printf("\n");
		do
		{
			printf("\n %cDesea modificar a otro usuario? [1-Si/2-No]: ", 168);
			fflush(stdin);
			gets(aux);
			opc = atoi(aux);	
		}while(opc != 1 && opc != 2);
		system("cls");	
	} while (opc == 1);
}

void proceso()
{
	int opr, ctri=0, n, i, cto=0, cont=0, m;
	float num, numaux, tarifa, consumo, importe, sobrecon, total;
	char aux3[' '], aux[' '], atipo[' '], acons[' '], anom[' '], anomcol[' '], nombre[' '], nomcolonia[' '];
	FILE *archn;
	FILE *archivo;
	FILE *archpro;
	FILE *archnp;
	do{ //Hacer otro proceso
		do{ //control de numero equivocado/no encontrado
			ctri = 0;
			archn = fopen("n.txt", "r");
			fscanf(archn, "%s", &aux3);
			n = atoi(aux3);
			fclose(archn);
			
			archivo = fopen("altas.txt", "rt"); //recuerda cerrar
			printf("\n\t\t\tPROCESOS\n");
			for(m= 0;m< 80; m++)
			{
				printf("%c", 95);
			}					
			printf("\n");
			printf("\n Introduzca el numero del usuario del que se realizara el proceso: ");
			fflush(stdin);
			gets(aux);
			num = atoi(aux);
			for (i= 0;i< n;i++){
				fscanf(archivo, "%s", &aux);
				numaux = atof(aux);
				if (numaux == num){
					printf("\n Numero encontrado \n\n");
					system("pause");
					system("cls");
					ctri++;
					fscanf(archivo, "%s", &atipo); //guardo tipo/tarifa
					fscanf(archivo, "%s", &anom);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &anomcol);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &acons); //guardo consumo
					fscanf(archivo, "%s", &aux);
					strcpy(nombre, anom);
					strcpy(nomcolonia, anomcol);
					tarifa = atof(atipo);
					consumo = atof(acons);
					importe = tarifa * consumo;
					if (consumo > 300){
						//50%
						sobrecon = importe * .50;
						total = importe + sobrecon;
					}
					else
						if(consumo > 200){
							//30%
							sobrecon = importe * .30;
							total = importe + sobrecon;
						}
						else
							if (consumo > 100){
								//20%
								sobrecon = importe * .20;
								total = importe + sobrecon;
							}
							else
								if (consumo > 50){
									//10%	
									sobrecon = importe * .10;
									total = importe + sobrecon;
								}
								else{
									sobrecon = 0;
									total = importe + sobrecon;
								}
								
				} //fin del if de numaux == num
				else{
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
				}
			}
			fclose(archivo);
			
			if (ctri == 0){
				system("cls");
				for(m= 0;m< 80; m++)
				{
					printf("%c", 95);
				}					
				printf("\n");
				printf("\n No existe un usuario con ese numero \n");
				printf("\n");
				system("pause");
				system("cls");
			}
			else{
				for(m= 0;m< 80; m++)
				{
					printf("%c", 95);
				}					
				printf("\n");
				printf("\n\n\t El proceso para %.2f fue realizado con exito \n", num);
				printf("\n Importe: %.2f \n Sobreconsumo: %.2f \n Total: %.2f \n", importe, sobrecon, total);
				printf("\n");
				system("pause");
			}
			
		} while (ctri == 0);
		
		if (cto == 0){
			archpro = fopen("procesos.txt", "wt");
			fprintf(archpro, "%.2f ", num);
			fprintf(archpro, "%s ", nombre); //nombre
			fprintf(archpro, "%s ", nomcolonia); //nombre colonia
			fprintf(archpro, "%.2f ", consumo); //consumo
			fprintf(archpro, "%.2f ", importe);
			fprintf(archpro, "%.2f ", sobrecon);	
			fprintf(archpro, "%.2f", total);
			fprintf(archpro, "\n");
			fclose(archpro);
		}
		else{
			archpro = fopen("procesos.txt", "at");
			fprintf(archpro, "%.2f ", num);
			fprintf(archpro, "%s ", nombre); //nombre
			fprintf(archpro, "%s ", nomcolonia); //nombre colonia
			fprintf(archpro, "%.2f ", consumo); //consumo
			fprintf(archpro, "%.2f ", importe);
			fprintf(archpro, "%.2f ", sobrecon);	
			fprintf(archpro, "%.2f", total);
			fprintf(archpro, "\n");
			fclose(archpro);
		}
		
		cto++;
		system("cls");
		for(m = 0;m< 80; m++)
		{
			printf("%c", 95);
		}
		printf("\n");
		do{
			printf("\n %cDesea realizar otro proceso? [1-Si/2-No]: ", 168);
			fflush(stdin);
			gets(aux);
			opr = atoi(aux);
		} while (opr != 1 && opr != 2);
		cont++;
		system("cls");
	} while(opr == 1);
	
	archnp = fopen("nprocesos.txt", "wt");
	fprintf(archnp, "%d", cont);
	fclose(archnp);	
}

void bajas()
{
	int mod = 0, i, op, opu, opc, m;
	int  linea, ctri=0, opm, temp=1, n, nuev;
	float num, numaux;
	char ch, aux[' '], aux3[' ']; 
	
	FILE *archivo, *archivoaux, *archn;
	
	do{ //Dar de baja a otro usuario
		temp = 1;
		do{ //control de numero equivocado
			ctri = 0;
			archn = fopen("n.txt", "r");
			fscanf(archn, "%s", &aux3);
			n = atoi(aux3);
			fclose(archn);
		
			archivo = fopen("altas.txt", "rt");
			do
			{	
				printf("\n\t\t\tBAJAS\n");
				for(m= 0;m< 80; m++)
				{
					printf("%c", 95);
				}					
				printf("\n");
				printf("\n Introduzca el numero del usuario que quiere dar de baja: ");
				fflush(stdin);
				gets(aux);
				num = atoi(aux);
			}while(num < 0);
			
				for (i= 0;i< n;i++){ 
					fscanf(archivo, "%s", &aux);
					numaux = atof(aux);
					if (numaux == num){
						printf("\n Numero encontrado \n");
						printf("\n");
						system("pause");
						system("cls");
						ctri++;
						linea = i+1;
					}
				else{
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
					fscanf(archivo, "%s", &aux);
				}
			}
			fclose(archivo);	
			if (ctri > 0)
				{
					//PROCESO DE BORRADO
				//-------------------------------------
				printf("\n\n\t Lista de usuarios actuales \n\n");
				archivo = fopen("altas.txt", "r");
				ch = getc(archivo);
				while (ch != EOF)
				{
					printf("%c", ch);
					ch = getc(archivo);
				}
				rewind(archivo);
				archivoaux = fopen("replica.c", "w");
				ch = getc(archivo);
				while (ch != EOF)  
				{
					if (temp != linea)
					{
						putc(ch, archivoaux);
					}
					if (ch == '\n')
						temp++;
					
					ch = getc(archivo);
				}
				fclose(archivo);
				fclose(archivoaux);
				remove("altas.txt");
				rename("replica.c", "altas.txt");
				
				printf("\n\n\tUSUARIO ELIMINADO CON EXITO\n\n");
				archn = fopen("n.txt", "w");
				nuev = n - 1;
				fprintf(archn, "%d", nuev);
				fclose(archn);
				
				
				printf("\n\n\t Lista de usuarios actualizada \n\n");
				archivo = fopen("altas.txt", "r");
				ch = getc(archivo);
				while (ch != EOF)
				{
					printf("%c", ch);
					ch = getc(archivo);
				}
				fclose(archivo);
				printf("\n");
				system("pause");
				//-------------------------------------*/
			}
			else
			{
				for(i= 0;i< 80; i++)
				{
					printf("%c", 95);
				}
				printf("\n");
				printf("\n El numero que ingreso no se encuentra en el archivo \n");
				system("pause");
				system("cls");
			}
				
			
		} while (ctri == 0);
		do
		{	
			system("cls");
			for(i= 0;i< 80; i++)
			{
				printf("%c", 95);
			}
			printf("\n");
			printf("\n %cDesea dar de baja a otro usuario? [1-Si/2-No]: ", 168);
			fflush(stdin);
			gets(aux);
			opc = atoi(aux);
		}while(opc != 1 && opc != 2);
			system("cls");
	}while (opc == 1);
	
}

void pagosrealizados()
{
	int i, n, m, ctr = 0, ct = 0, noencon = 0, contnr = 0, ncol, j, nr, h, len;
	float pago, auxp, sumtot = 0;
	char nombre[' '], aux[' '], aux2[' '], aux3[' '], anum[' '], atipo[' '], anom[' '], aclave[' '], anocol[' '], adir[' '],
	acons[' '], apag[' '], auxnomc[' '], alnom[' '], alnum[' '], alpag[' '], nomrep[' '], c;
	FILE *archivo; //altas.txt
	FILE *archn; //n.txt
	FILE *archnr; //nr.txt
	FILE *pgraux; //pgrealizadosaux.txt
	FILE *archcol; //colonias.txt
	FILE *archncol; //ncol.txt
	FILE *pgre; //pagosrealizados.txt
	FILE *pgrf; //nombre establecido por el usuario
	
		archn = fopen("n.txt", "r");
		fscanf(archn, "%s", &aux3);
		n = atoi(aux3);
		fclose(archn);
		ctr=0;
		noencon=0;
		ct=0;
		archivo = fopen("altas.txt", "rt");
		for (i=0;i<n;i++){
			if (ctr > 0)
				ct = 1;
			fscanf(archivo, "%s", &anum);
			fscanf(archivo, "%s", &atipo);
			fscanf(archivo, "%s", &anom);
			fscanf(archivo, "%s", &aclave);
			fscanf(archivo, "%s", &anocol);
			fscanf(archivo, "%s", &adir);
			fscanf(archivo, "%s", &acons);
			fscanf(archivo, "%s", &apag);
			pago = atof(apag);
			if (pago > 0 && ctr == 0){
				ctr++;
				noencon++;
				pgraux = fopen("pgrealizadosaux.txt", "wt");
				fprintf(pgraux, "%s ", anum);
				fprintf(pgraux, "%s ", anom);
				fprintf(pgraux, "%s ", anocol);
				fprintf(pgraux, "%s", apag);
				fprintf(pgraux, "\n");
				fclose(pgraux);
				contnr++;
			}
			if (pago > 0 && ct == 1){
				noencon++;
				pgraux = fopen("pgrealizadosaux.txt", "at");
				fprintf(pgraux, "%s ", anum);
				fprintf(pgraux, "%s ", anom);
				fprintf(pgraux, "%s ", anocol);
				fprintf(pgraux, "%s", apag);
				fprintf(pgraux, "\n");
				fclose(pgraux);
				contnr++;
			}
		
		}//FIN DEL CILO FOR
		fclose(archivo);
		if (noencon == 0)
		{
			for(m= 0;m< 80; m++)
			{
				printf("%c", 95);
			}
			printf("\n");
			printf("\n NO hay usuarios con pagos mayores a 0 \n");
			printf("\n");
			system("pause");
			system("cls");
		}
			
		
		if (noencon > 0){
			
			archnr = fopen("archnr.txt", "wt");
			fprintf(archnr, "%d", contnr);
			fclose(archnr);
			
			archncol = fopen("ncol.txt", "rt");
			fscanf(archncol, "%s", &aux);
			ncol = atoi(aux);
			fclose(archncol);
			
			archnr = fopen("archnr.txt", "rt");
			fscanf(archnr, "%s", &aux);
			nr = atoi(aux);
			fclose(archnr);
			
			
			pgre = fopen("pagosrealizados.txt", "wt");
			fprintf(pgre, "\t\t\tREPORTE DE PAGOS REALIZADOS\n\n");
			fprintf(pgre, "NUMERO\t\t  NOMBRE DE USUARIO\t\t COLONIA\t\t PAGO\n\n");
			fclose(pgre);
			
			archcol = fopen("colonias.txt", "rt"); //ordenar por colonias
			for (j=0;j<ncol;j++){
				fscanf(archcol, "%s", &aux);
				fscanf(archcol, "%s", &auxnomc);
				strcpy(nombre, auxnomc);
				pgraux = fopen("pgrealizadosaux.txt", "rt"); //Abro auxiliar
				for (i=0;i<nr;i++){
					fscanf(pgraux, "%s", &alnum);
					fscanf(pgraux, "%s", &alnom);
					fscanf(pgraux, "%s\t", &aux2); //nombre de colonia
					if (strcmp(aux2, nombre)==0){
						fscanf(pgraux, "%s", &alpag);
						auxp = atof(alpag);
						sumtot = sumtot + auxp;
						pgre = fopen("pagosrealizados.txt", "a");
						fprintf(pgre, "%s\t\t  ", alnum);
						len=strlen(alnom);
						for (h=0;h<len;h++){
							if(alnom[h] == '_')
								alnom[h] = ' ';
							else
								continue;
						}
						fprintf(pgre, "%s\t\t\t ", alnom);
						len=strlen(nombre);
						for (h=0;h<len;h++){
							if(nombre[h] == '_')
								nombre[h] = ' ';
							else
								continue;
						}
						fprintf(pgre, "%s\t\t", nombre);
						fprintf(pgre, "%s", alpag);
						fprintf(pgre, "\n");
						fclose(pgre);
					}
					else{
						fscanf(pgraux, "%s", &alpag);
					}
				}
				fclose(pgraux);
			}
			fclose(archcol);
			
			pgre = fopen("pagosrealizados.txt", "at");
			fprintf(pgre, "\n\nTotal de colonias: %d\n\n", ncol);
			fprintf(pgre, "Total general: %.2f\n", sumtot);
			fclose(pgre);
			
			for(m= 0;m< 80; m++)
			{
				printf("%c", 95);
			}
			printf("\n");
			printf("\n Introduzca el nombre con el que se guardara el reporte generado: ");
			fflush(stdin);
			gets(nomrep);
			strcat(nomrep, ".txt"); 
			pgre = fopen("pagosrealizados.txt", "rt");
			pgrf = fopen(nomrep, "w");
			rewind(pgre);
			c = getc(pgre);
			while (c != EOF)
			{
				putc(c, pgrf);
				c = getc(pgre);
			}
			fclose(pgre);
			fclose(pgrf);
			
			remove("archnr.txt");
			remove("pgrealizadosaux.txt");
			remove("pagosrealizados.txt");
		}//FIN DEL IF
}

void pagosnorealizados()
{
	int i, n, ctr=0, ct=0, noencon=0, contnr=0, ncol, j, nr, m, len, h;
	float pago, auxp, sumtot=0;
	char nombre[' '], aux[' '], aux2[' '], aux3[' '], anum[' '], atipo[' '], anom[' '], aclave[' '], anocol[' '], adir[' '],
	acons[' '], apag[' '], auxnomc[' '], alnom[' '], alnum[' '], alpag[' '], nomrep[' '], c;
	FILE *archivo; //altas.txt
	FILE *archn; //n.txt
	FILE *archnr; //nnor.txt
	FILE *pgraux; //pgnorealizadosaux.txt
	FILE *archcol; //colonias.txt
	FILE *archncol; //ncol.txt
	FILE *pgre; //pagosnorealizados.txt
	FILE *pgrf; //nombre establecido por el usuario

		archn = fopen("n.txt", "r");
		fscanf(archn, "%s", &aux3);
		n = atoi(aux3);
		fclose(archn);
		ctr=0;
		noencon=0;
		ct=0;
		archivo = fopen("altas.txt", "rt");
		for (i=0;i<n;i++){
			if (ctr > 0)
				ct = 1;
			fscanf(archivo, "%s", &anum);
			fscanf(archivo, "%s", &atipo);
			fscanf(archivo, "%s", &anom);
			fscanf(archivo, "%s", &aclave);
			fscanf(archivo, "%s", &anocol);
			fscanf(archivo, "%s", &adir);
			fscanf(archivo, "%s", &acons);
			fscanf(archivo, "%s", &apag);
			pago = atof(apag);
			if (pago == 0 && ctr == 0){
				ctr++;
				noencon++;
				pgraux = fopen("pgnorealizadosaux.txt", "wt");
				fprintf(pgraux, "%s ", anum);
				fprintf(pgraux, "%s ", anom);
				fprintf(pgraux, "%s ", anocol);
				fprintf(pgraux, "%s", apag);
				fprintf(pgraux, "\n");
				fclose(pgraux);
				contnr++;
			}
			if (pago == 0 && ct == 1){
				noencon++;
				pgraux = fopen("pgnorealizadosaux.txt", "at");
				fprintf(pgraux, "%s ", anum);
				fprintf(pgraux, "%s ", anom);
				fprintf(pgraux, "%s ", anocol);
				fprintf(pgraux, "%s", apag);
				fprintf(pgraux, "\n");
				fclose(pgraux);
				contnr++;
			}
		
		}//FIN DEL CILO FOR
		fclose(archivo);
		if (noencon == 0)
		{
			for(m= 0;m< 80; m++)
			{
				printf("%c", 95);
			}
			printf("\n");
			printf("\n NO hay usuarios pago igual a 0 \n");
			printf("\n");
			system("pause");
			system("cls");
		}
			
		if (noencon > 0){
			
			archnr = fopen("nnor.txt", "wt");
			fprintf(archnr, "%d", contnr);
			fclose(archnr);
			
			archncol = fopen("ncol.txt", "rt");
			fscanf(archncol, "%s", &aux);
			ncol = atoi(aux);
			fclose(archncol);
			
			archnr = fopen("nnor.txt", "rt");
			fscanf(archnr, "%s", &aux);
			nr = atoi(aux);
			fclose(archnr);
			
			
			pgre = fopen("pagosnorealizados.txt", "wt");
			fprintf(pgre, "\t\t\tREPORTE DE PAGOS NO REALIZADOS\n\n");
			fprintf(pgre, "NUMERO\t\t  NOMBRE DE USUARIO\t\t COLONIA\t\t PAGO\n\n");
			fclose(pgre); 
			
			archcol = fopen("colonias.txt", "rt");
			for (j=0;j<ncol;j++){
				fscanf(archcol, "%s", &aux);
				fscanf(archcol, "%s", &auxnomc);
				strcpy(nombre, auxnomc);
				pgraux = fopen("pgnorealizadosaux.txt", "rt"); //Abro auxiliar
				for (i=0;i<nr;i++){
					fscanf(pgraux, "%s", &alnum);
					fscanf(pgraux, "%s", &alnom);
					fscanf(pgraux, "%s", &aux2); //nombre de colonia
					if (strcmp(aux2, nombre)==0){
						fscanf(pgraux, "%s", &alpag);
						auxp = atof(alpag);
						sumtot = sumtot + auxp;
						pgre = fopen("pagosnorealizados.txt", "a");
						fprintf(pgre, "%s\t\t  ", alnum);
						len=strlen(alnom);
						for (h=0;h<len;h++){
							if(alnom[h] == '_')
								alnom[h] = ' ';
							else
								continue;
						}
						fprintf(pgre, "%s\t\t\t ", alnom);
						len=strlen(nombre);
						for (h=0;h<len;h++){
							if(nombre[h] == '_')
								nombre[h] = ' ';
							else
								continue;
						}
						fprintf(pgre, "%s\t\t ", nombre);
						fprintf(pgre, "%s", alpag);
						fprintf(pgre, "\n");
						fclose(pgre);
					}
					else{
						fscanf(pgraux, "%s", &alpag);
					}
				} 
				fclose(pgraux);
			}
			fclose(archcol);
			
			pgre = fopen("pagosnorealizados.txt", "at");
			fprintf(pgre, "\n\nTotal de colonias: %d\n\n", ncol);
			fprintf(pgre, "Total general: %.2f\n", sumtot);
			fclose(pgre);
			
			for(m= 0;m< 80; m++)
			{
				printf("%c", 95);
			}
			printf("\n");
			printf("\n Introduzca el nombre con el que se guardara el reporte generado: ");
			fflush(stdin);
			gets(nomrep);
			strcat(nomrep, ".txt"); //VALIDAR que no exista ya un archivo con ese nombre
			pgre = fopen("pagosnorealizados.txt", "rt");
			pgrf = fopen(nomrep, "w");
			rewind(pgre);
			c = getc(pgre);
			while (c != EOF)
			{
				putc(c, pgrf);
				c = getc(pgre);
			}
			fclose(pgre);
			fclose(pgrf);
			
			remove("nnor.txt");
			remove("pgnorealizadosaux.txt");
			remove("pagosnorealizados.txt");
			system("cls");
		}//FIN DEL IF		
}

void facturacionlista()
{
	FILE *ap;
	FILE *ap1;
	FILE *ap2;
	FILE *archnp;
	FILE *archproc;
	FILE *archncol;
	FILE *pgre;
	FILE *pgrf;
	time_t t;
	struct tm *tm;
	char aux[' '], anum[' '], anom[' '], anomcol[' '], acons[' '], aimp[' '],
	ascon[' '], atot[' '], coln[' '], nomrep[' '], c, fecha[100];
	int np, i, ctr=0, fol=0, cp, m;
	float totaux, tot=0;
	
	ap1 = fopen("faclista.txt", "wt");
	if(ap1 == NULL)
	{
		printf("\nHubo problemas para crear el archivo de texto.");
	}
	
	fprintf(ap1, "\t\t\tREPORTE DE FACTURACION\n\n");
	fprintf(ap1, "NUMERO\t\tNOMBRE DE USUARIO\t\tCOLONIA\t\tCONSUMO\t\tIMPORTE\t\tSOBRECONSUMO\t\tTOTAL\n\n");
	
	archnp = fopen("nprocesos.txt", "rt");
	fscanf(archnp, "%s", &aux);
	np = atoi(aux);
	fclose(archnp);

	archproc = fopen("procesos.txt", "rt");
	for (i=0;i<np;i++){
		fscanf(archproc, "%s", &anum);
		fscanf(archproc, "%s", &anom);
		fscanf(archproc, "%s", &anomcol);
		fscanf(archproc, "%s", &acons);
		fscanf(archproc, "%s", &aimp);
		fscanf(archproc, "%s", &ascon);
		fscanf(archproc, "%s", &atot);
		totaux = atof(atot);
		tot = tot + totaux;
		fprintf(ap1, "%s\t\t%s\t\t\t%s\t\t%s\t\t%s\t\t%s\t\t\t%s\n\n\n", anum, anom, anomcol, acons, aimp, ascon, atot);
	}
	
	fclose(archproc);
	
	archncol = fopen("ncol.txt", "rt");
	fscanf(archncol, "%s", &coln);
	fclose(archncol);
	
	fprintf(ap1, "\n\n Total de colonias: %s\n\n", coln);
	fprintf(ap1, "Total general: %.2f\n", tot);
	fclose(ap1);
	for(m= 0;m< 80; m++)
	{
	printf("%c", 95);
	}
	printf("\n");

	ap1 = fopen("faclista.txt", "r");
	ap2 = fopen("faclista.xls", "w");
	if (ap2 == NULL){
		printf("\nHubo problemas para crear el archivo excel.");
	}
	rewind(ap1);
	while (c != EOF)
	{
		putc(c, ap2);
		c = getc(ap1);
	}
	fclose(ap1);
	fclose(ap2);
	system("cls");
	for(m= 0;m< 80; m++)
	{
		printf("%c", 95);
	}
	printf("\n");
	printf("\n Introduzca el nombre con el que se guardara el reporte de lista de facturacion generado: ");
	fflush(stdin);
	gets(nomrep);
	strcat(nomrep, ".txt"); 
	pgre = fopen("faclista.txt", "rt");
	pgrf = fopen(nomrep, "w");
	rewind(pgre);
	c = getc(pgre);
	while (c != EOF)
	{
		putc(c, pgrf);
		c = getc(pgre);
	}
	fclose(pgre);
	fclose(pgrf);	
	remove("faclista.txt");
	printf("\n\n Se creara su respectiva copia en excel...\n\n");
	system("pause");
	printf("\n");
	printf("\n El reporte se ha guardado con exito \n\n");
	system("pause");
	system("cls");
}

void facturacionindividual()
{
	FILE *archnp; // "nprocesos.txt" la n de procesos
	FILE *naltas; //n.txt
	FILE *ap; //facindividual.txt
	FILE *ap1; //facindividual.xls  
	FILE *archaltas; //altas.txt
	FILE *archproc; //procesos.txt
	FILE *archtaf; //tarifas.txt
	FILE *pgre;
	FILE *pgrf;
	time_t t;
	struct tm *tm;
	int i, j, m, k, kc, np, n, tipo, fol=0, cp, h, len;
	char auxnp[' '], auxn[' '], apnum[' '], apnom[' '], apnomcol[' '], apcons[' '],
	apimp[' '], apsobre[' '], aptot[' '], aux[' '], auxnum[' '], atipo[' '], adir[' '],
	auxtar[' '], auxe[' '], fecha[100], nomrep[' '], c;
	float pnum, numaux, vtar;
	
	ap = fopen("facindividual.txt", "wt");
	
	archnp = fopen("nprocesos.txt", "rt");
	fscanf(archnp, "%s", &auxnp);
	np = atoi(auxnp);
	fclose(archnp);
	
	naltas = fopen("n.txt", "rt");
	fscanf(naltas, "%s", &auxn);
	n = atoi(auxn);
	fclose(naltas);
	
	archproc = fopen("procesos.txt", "rt");
	for (i=0;i<np;i++){
		fscanf(archproc, "%s", &apnum);
		fscanf(archproc, "%s", &apnom);
		fscanf(archproc, "%s", &apnomcol);
		fscanf(archproc, "%s", &apcons);
		fscanf(archproc, "%s", &apimp);
		fscanf(archproc, "%s", &apsobre);
		fscanf(archproc, "%s", &aptot);
		pnum = atof(apnum); //NUMERO DE PROCESO
		archaltas = fopen("altas.txt", "rt");
		for (j=0;j<n;j++)
		{ //BUSCO EL NUMERO en altas 
			fscanf(archaltas, "%s", &auxnum);
			numaux = atof(auxnum);
			if (pnum == numaux){
				fscanf(archaltas, "%s", &atipo);
				fscanf(archaltas, "%s", &aux); //nombre
				fscanf(archaltas, "%s", &aux); //clv colonia
				fscanf(archaltas, "%s", &aux); //colonia
				fscanf(archaltas, "%s", &adir); //direccion!!
				fscanf(archaltas, "%s", &aux); //consumo
				fscanf(archaltas, "%s", &aux); //pago
				
				tipo = atoi(atipo);
				//sacar el valor de la tarifa
				archtaf = fopen("tarifas.txt", "rt");
				for (k=0;k<8;k++){
					fscanf(archtaf, "%s", &auxtar);
					kc = k+1;
					if (tipo == kc);
						vtar = atof(auxtar);
				}
				fclose(archtaf);
				fol++;
				//impresion de factura individual
				
					for(m= 0;m< 80; m++)
					{
						fprintf(ap, "%c", 95);
					}
					len=strlen(apnom);
					for (h=0;h<len;h++){
						if(apnom[h] == '_')
							apnom[h] = ' ';
						else
							continue;
					}
					len=strlen(adir);
					for (h=0;h<len;h++){
						if(adir[h] == '_')
							adir[h] = ' ';
						else
							continue;
					}
					len=strlen(apnomcol);
					for (h=0;h<len;h++){
						if(apnomcol[h] == '_')
							apnomcol[h] = ' ';
						else
							continue;
					}
					printf("\n");
					fprintf(ap,"\n\nCOMPAÑIA DE AGUA POTABLE ACME\t\t\tFACTURA");
					fprintf(ap, "\nAv. Matamoros 2004\t\t\t\tFolio: %d", fol);
					fprintf(ap, "\nFraccionamiento Colinas del Valle\nMonterrey, NL.");
					fprintf(ap, "\nRFC: PAA 141120 S4");
					t = time(0);
			  		tm = localtime(&t);
			  		strftime(fecha, 100, "%d/%m/%Y", tm);
					fprintf(ap, "\nMonterrey, NL. a %s", fecha); 
					cp = nrandom();
					fprintf(ap, "\n\nNumero: %s\nUsuario: %s\nDireccion: %s\nColonia: %s\nC.P: %d\n", apnum, apnom, adir, apnomcol, cp);
					fprintf(ap, "Tipo de Usuario: %s\nConsumo:  %s\nTarifa: %.2f\t\t\t\t\tImporte: %s", atipo, apcons, vtar, apimp);
					fprintf(ap, "\n\t\t\t\t\t\tSobreconsumo: %s\n\t\t\t\t\t\tTotal a pagar: %s", apsobre, aptot);
					fprintf(ap, "\nPaguese antes de: 22/may/18");
					fprintf(ap, "\n\n\n");
			} //FIN DEL IF
			else{
				fscanf(archaltas, "%s", &auxe);
				fscanf(archaltas, "%s", &auxe);
				fscanf(archaltas, "%s", &auxe);
				fscanf(archaltas, "%s", &auxe);
				fscanf(archaltas, "%s", &auxe);
				fscanf(archaltas, "%s", &auxe);
				fscanf(archaltas, "%s", &auxe);
			}
		} //Fin del for de altas
		fclose(archaltas);
	}
	fclose(archproc);
	fclose(ap);
	
	ap = fopen("facindividual.txt", "r");
	ap1 = fopen("facindividual.xls", "w");
	if(ap1 == NULL)
	{
		printf("\nHubo problemas para crear el archivo en excel.");
	}
	rewind(ap);
	c = getc(ap);
	while (c != EOF)
	{		
		putc(c, ap1);
		c = getc(ap);
	}
	fclose (ap);
	fclose(ap1);
	system("cls");
	for(m= 0;m< 80; m++)
	{
		printf("%c", 95);
	}
			printf("\n");
	printf("\n Introduzca el nombre con el que se guardara el reporte de facturas individuales generado: ");
	fflush(stdin);
	gets(nomrep);
	strcat(nomrep, ".txt"); 
	pgre = fopen("facindividual.txt", "rt");
	pgrf = fopen(nomrep, "w");
	rewind(pgre);
	c = getc(pgre);
	while (c != EOF)
	{
		putc(c, pgrf);
		c = getc(pgre);
	}
	fclose(pgre);
	fclose(pgrf);	
	remove("facindividual.txt");
	
	printf("\n\nSe creara su respectiva copia en excel...\n\n");
	system("pause");
	printf("\n El reporte se ha guardado con exito \n\n");
	system("pause");
	
}

int nrandom()
{
	int num;
	
	num = 10000 + rand() %((99999 + 1) - 10000);
	
	return num;
}


