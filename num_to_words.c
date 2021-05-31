//-----------------------------------------------------------//
//                      LIBRERIAS                            //
//-----------------------------------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//-----------------------------------------------------------//
//                       CONSTANTES                          //
//-----------------------------------------------------------//
int POS = 0;
int CONT = 0;
#define SIZE 1000

//  +-------------------------------------------------------------------------+
//  |                                                                         |
//  |                   FUNCION DE NUMERO A PALABRAS                          |
//  |                                                                         |
//  +-------------------------------------------------------------------------+
void convertir_a_palabras(char* num){
    /**************************************************************************
    Inputs:
      num - número a convertir a texto de tipo chart pointer

    Action:
      Imprime en pantalla la descripción del número ingresado en el parámetro
      'num' en letras
    **************************************************************************/

    // Variable auxiliar para los digitos restantes de números mayores a 4 dígitos
    char* extra = "";

    int len = strlen(num);
    int extra_len = strlen(extra);

    // Caso donde el número sea un parámetro vacio
    if (len == 0) {
        fprintf(stderr, "Número vacio\n");
        return;
    }

    // Caso donde el número es mayor a 9 digitos (num > 999 millones)
    if (len > 9) {
        fprintf(stderr, "Un número mayor de 9 digitos no es permitido\n");
        return;
    }

    // Verifica si 'num' es un número en orden de millones cerrados
    int sumUltimos_6Digitos = -1;
    if (len > 6){
        sumUltimos_6Digitos = 0;
        char* numCopy = num;
        numCopy += (len-6);
        for(int i = 0; i < 6; i++){
            sumUltimos_6Digitos += ((*numCopy - '0')*pow(10, 5 - i));
            ++numCopy;
        }
    }

    char* unidades[] = {"", "un", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve" };
    char* decenas[] = { "", "", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa" };
    char* especiales[] = {"", "diez", "once", "doce", "trece", "catorce", "quince", "dieciséis", "diecisiete", "dieciocho", "diecinueve" };

    // Mantiene iterando hasta que llegue al final de la cadena 'num'
    while (*num != '\0') {

        //-----------------------------------------------------------//
        //                  NUMERO DE 1 DIGITO                       //
        //-----------------------------------------------------------//
        if (len == 1) {

            printf("%s", unidades[*num - '0']); // *num - '0' es equivalente a (int)num

            // La unidad hace parte de un numero mas grande (eg. 6 mil)
            if(extra_len != 0){
                if(*num != '0')
                    printf(" mil ");

                // Actualiza 'num' para analizar el resto del número
                num = extra;
                len = extra_len;
                extra_len = 0;
            }

            // En caso de que el número sea solo una unidad se termina
            else{
                if((*num - '0') == 1)
                    printf(" peso");
                else
                    printf(" pesos");
                return;
            }
        }

        //-----------------------------------------------------------//
        //                 NUMERO DE 2 DIGITOS                       //
        //-----------------------------------------------------------//
        else if(len == 2){
            // Del 10 al 19
            if (*num == '1') {
                int sum = *num - '0' + *(num + 1) - '0';
                printf("%s", especiales[sum]);
            }
            // Del 21 al 29
            else if (*num == '2' && *(num + 1) != '0'){
                printf("%s%s", "veinti", unidades[*(num + 1) - '0']);
            }
            // 20 y del 30 al 99
            else{
                int i = *num - '0';
                printf("%s ", i ? decenas[i] : "");
                ++num;
                if (*num != '0'){
                    if(i == 0){
                        printf("%s", unidades[*num - '0']);
                    }
                    else{
                        printf("y %s", unidades[*num - '0']);
                    }
                }
            }

            // Número de 2 dígitos en el orden de millones (eg. 22 millones)
            if(extra_len == 6){
                printf(" millones ");

                // Actualiza 'num' para analizar el resto del número
                num = extra;
                len = extra_len;
            }

            // Número de 2 dígitos en el orden de miles (eg. 22 mil)
            else if(extra_len != 0){
                printf(" mil ");

                // Actualiza 'num' para analizar el resto del número
                num = extra;
                len = extra_len;
                extra_len = 0;
            }

            // Número de 2 digitos en orden de decenas (eg. 20)
            else{
                 if(sumUltimos_6Digitos != 0)
                    printf(" pesos");

                // numero en orden de millones cerrado
                else
                    printf(" de pesos");
                return;
            }
        }

        //-----------------------------------------------------------//
        //                 NUMERO DE 3 DIGITOS                       //
        //-----------------------------------------------------------//
        else if(len == 3){
            // Caso del 100
            if (*num == '1'){
                // Numero es 100
                if (*num == '1' && *(num + 1) == '0' && *(num + 2) == '0'){
                    printf("%s ", "cien");
                }
                // Numero es >100 y <200
                else{
                    printf("%s ", "ciento");
                }
            }
            // Caso del 500
            else if (*num == '5'){
                printf("%s ", "quinientos");
            }
            // Caso del 700
            else if (*num == '7'){
                printf("%s ", "setecientos");
            }
            // Caso del 900
            else if (*num == '9'){
                printf("%s ", "novecientos");
            }

            // Resto de los casos
            else{

                // Número de 3 dígitos sin iniciar en 0 (eg. skip if -> 023, into if --> 230)
                if(*num != '0')
                    printf("%s%s ", unidades[*num -'0'], "cientos");
            }

            // Se guarda la suma de los dos siguientes digitos
            int digitos = (*(num + 1) - '0')*10 + *(num + 2) - '0';

            // El número no es de 3 digitos cerrados (eg. skip if -> 200, into if -> 236)
            if (digitos != 0){
                --len;
                ++num;
            }

            // Número de 3 dígitos en el orden de millones (eg. 200 millones)
            else if(extra_len == 6){
                printf(" millones ");
                num = extra;
                len = extra_len;
                //extra_len = 0;
            }

            // Número de 3 dígitos en el orden de miles (eg. 200 mil)
            else if(extra_len != 0){
                printf(" mil ");
                num = extra;
                len = extra_len;
                extra_len = 0;
            }

            // Caso específico donde el número es solo parte de centenas y es 100
            else if(*num == '1' && *(num + 1) == '0' && *(num + 2) == '0'){
                printf(" pesos");
                return;
            }

            // Número de 3 digitos en el orden de centenas
            else{
                --len;
                ++num;
            }
        }
        //-----------------------------------------------------------//
        //                 NUMERO DE 4 DIGITOS                       //
        //-----------------------------------------------------------//
        else if(len == 4){
            /*************************************************************
                Solo se analizan de a cuatro dígitos los números en ordenes de
                miles y unidades de millones
            **************************************************************/

            // Caso del 1000
            if (*num == '1'){

                // Si hay extra, el número esta en orden de los millones
                if(extra_len != 0){
                    printf("un millon ");
                }

                // Número esta en orden de los miles
                else{
                    printf("mil ");
                }
            }
            else{
                if(extra_len != 0)
                    printf("%s %s ", unidades[*num -'0'], "millones");

                else
                    printf("%s %s ", unidades[*num -'0'], "mil");
            }

            // Suma los 3 dígitos restantes para analizar
            int digitos = (*(num + 1) - '0')*100 + (*(num + 2) - '0')*10 + *(num + 3) - '0';
            char * str1 = malloc(sizeof(char)*10);
            sprintf(str1,"%d",digitos);

            // Actualiza en 'num' los 3 dígitos restantes para analizar
            num = str1;
            len = strlen(str1);
        }
        //-----------------------------------------------------------//
        //                 NUMERO DE 5 DIGITOS                       //
        //-----------------------------------------------------------//
        else if(len == 5){

            // Se suman los 2 primero dígitos para analizar como decenas
            // en orden de miles
            int digitos = (*num - '0')*10 + *(num + 1) - '0';
            char * str1 = malloc(sizeof(char)*10);
            sprintf(str1,"%d",digitos);

            // Guarda en 'extra' los 3 dígitos restantes para analizar luego de 'num'
            extra = num + 2;
            extra_len = strlen(extra);

            // Analiza los 2 primero dígitos
            num = str1;
            len = 2;
        }
        //-----------------------------------------------------------//
        //                 NUMERO DE 6 DIGITOS                       //
        //-----------------------------------------------------------//
        else if(len == 6){

            // Se suman los 3 primero dígitos para analizar como centenas
            // en orden de miles
            int digitos = (*num - '0')*100 + (*(num + 1) - '0')*10 + *(num + 2) - '0';
            char * str1 = malloc(sizeof(char)*10);
            sprintf(str1,"%d",digitos);

            extra = num + 3;
            extra_len = strlen(extra);

            num = str1;
            len = strlen(str1);
        }
        //-----------------------------------------------------------//
        //                 NUMERO DE 7 DIGITOS                       //
        //-----------------------------------------------------------//
        else if(len == 7){

            // Se suman los 4 primero dígitos para analizar como unidades
            // en orden de millones y centenas en orden de miles
            int digitos = (*num - '0')*1000 + (*(num + 1) - '0')*100 + (*(num + 2) - '0')*10 + *(num + 3) - '0';
            char * str1 = malloc(sizeof(char)*10);
            sprintf(str1,"%d",digitos);

            extra = num + 4;
            extra_len = strlen(extra);

            // Analiza los 4 primero dígitos
            num = str1;
            len = 4;
        }
        //-----------------------------------------------------------//
        //                 NUMERO DE 8 DIGITOS                       //
        //-----------------------------------------------------------//
        else if(len == 8){

            // Se suman los 2 primero dígitos para analizar como decenas
            // en orden de millones
            int digitos = (*num - '0')*10 + *(num + 1) - '0';
            char * str1 = malloc(sizeof(char)*10);
            sprintf(str1,"%d",digitos);

            // Guarda en 'extra' los 6 dígitos restantes para analizar luego de 'num'
            extra = num + 2;
            extra_len = strlen(extra);

            num = str1;
            len = strlen(num);
        }
        //-----------------------------------------------------------//
        //                 NUMERO DE 9 DIGITOS                       //
        //-----------------------------------------------------------//
        else{

            // Se suman los 3 primero dígitos para analizar como centenas
            // en orden de millones
            int digitos = (*num - '0')*100 + (*(num + 1) - '0')*10 + *(num + 2) - '0';
            char * str1 = malloc(sizeof(char)*10);
            sprintf(str1,"%d",digitos);

            extra = num + 3;
            extra_len = strlen(extra);

            num = str1;
            len = strlen(num);
        }
    }
}

//  +-------------------------------------------------------------------------+
//  |                                                                         |
//  |                       FUNCION ENCONTRAR NUMERO                          |
//  |                                                                         |
//  +-------------------------------------------------------------------------+
void buscar_num(int lista[], int num){
    /**************************************************************************
    Inputs:
      num   - número entero a buscar en el array 'lista[]'
      lista - array que contiene número enteros al azar

    Action:
      Busca si 'num' esta en 'lista[]'. En caso afirmativo, guarda en 'POS' la
      posición en la que se ubica por primera vez y en 'CONT' el número de veces
      que aparece en la lista. En caso que no encuentre 'num' en la lista, 'CONT'
      y 'POS' son cero.
    **************************************************************************/

    int i = 0;
    int j = 0;
    for (i = 0; i < SIZE; i++){
        if (lista[i] == num){
            if(j == 0){
                POS = i;
                j = 1;
            }
            CONT++;
        }
    }
}


int main()
{
    // Número a describir en texto
    int num;

    // Arreglo donde se busca el número
    int arreglo[SIZE] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 45, 500, 12, 12, 3, 235, 1, 1000000, 235};

    printf("\n Digite número a buscar: ");
    scanf ("%d", &num);

    // Análisis del número en el arreglo
    buscar_num(arreglo, num);

    printf("\n¿El número %d se encuentra dentro del arreglo? ", num);

    if(CONT != 0){
        printf("Si");
        printf("\nEl número %d se encuentra %d vez/veces dentro del arreglo", num, CONT);
        printf("\nEl número %d se encuentra por primera vez en la posición %d", num, POS);
    }
    else
        printf("No");


    // Convierte decimal a chart pointer
    char * str1 = malloc(sizeof(char)*10);
    sprintf(str1,"%d",num);
    printf("\n\nNúmero en letras:\n");

    // Describe el número en texto
    convertir_a_palabras(str1);

    return 0;
}
