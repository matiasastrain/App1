#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metrican.h"
#include "utilidades.h"



//___________________________________________________________________________________________________________________________________________________________________________________________
// Cuenta cuántas veces aparece cada pizza_name y guarda el resultado
int contar_pizzas_repetidas(Pedido *orders, int size, char resultados[][75], int *conteos) {
    int distintas = 0;
    for (int i = 0; i < size; i++) {
        int encontrado = 0;
        for (int j = 0; j < distintas; j++) {
            if (strcmp(orders[i].pizza_name, resultados[j]) == 0) {
                conteos[j] += orders[i].quantity;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(resultados[distintas], orders[i].pizza_name);
            conteos[distintas] = orders[i].quantity;
            distintas++;
        }
    }
    return distintas; 
}
//___________________________________________________________________________________________________________________________________________________________________________________________
// Funciones que calculen las métricas solicitadas en el enunciado
//___________________________________________________________________________________________________________________________________________________________________________________________
// pms: Pizza más vendida
char* pizza_mas_vendida(int *size, Pedido *orders) {
    char nombres[100][75];
    int conteos[100] = {0};
    int total = contar_pizzas_repetidas(orders, *size, nombres, conteos);

    int max = 0;
    for (int i = 1; i < total; i++) {
        if (conteos[i] > conteos[max]) max = i;
    }

    char *resultado = malloc(100);
    sprintf(resultado, "%s", nombres[max]);
    return resultado;
}
//___________________________________________________________________________________________________________________________________________________________________________________________
// pls: Pizza menos vendida
char* pizza_menos_vendida(int *size, Pedido *orders) {
    char nombres[100][75];
    int conteos[100] = {0};
    int total = contar_pizzas_repetidas(orders, *size, nombres, conteos);

    int min = 0;
    for (int i = 1; i < total; i++) {
        if (conteos[i] < conteos[min]) min = i;
    }

    char *resultado = malloc(100);
    sprintf(resultado, "%s", nombres[min]);
    return resultado;
}
//___________________________________________________________________________________________________________________________________________________________________________________________
// dms: Fecha con más ventas en términos de dinero (junto a la cantidad de dinero recaudado)
char* fecha_mas_ventas_dinero(int *size, Pedido *orders) {
    char fechas[100][75];
    float totales[100] = {0};
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int encontrado = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                totales[j] += orders[i].total_price;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(fechas[total], orders[i].order_date);
            totales[total] = orders[i].total_price;
            total++;
        }
    }

    int max = 0;
    for (int i = 1; i < total; i++) {
        if (totales[i] > totales[max]) max = i;
    }

    char *resultado = malloc(100);
    sprintf(resultado, "%s: %.2f", fechas[max], totales[max]);
    return resultado;
}
//___________________________________________________________________________________________________________________________________________________________________________________________
// dls: Fecha con menos ventas en términos de dinero (junto a la cantidad de dinero recaudado)
char* fecha_menos_ventas_dinero(int *size, Pedido *orders) {
    char fechas[100][75];
    float totales[100] = {0};
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int encontrado = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                totales[j] += orders[i].total_price;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(fechas[total], orders[i].order_date);
            totales[total] = orders[i].total_price;
            total++;
        }
    }

    int min = 0;
    for (int i = 1; i < total; i++) {
        if (totales[i] < totales[min]) min = i;
    }

    char *resultado = malloc(100);
    sprintf(resultado, "%s: %.2f", fechas[min], totales[min]);
    return resultado;
}
//___________________________________________________________________________________________________________________________________________________________________________________________
// dmsp: Fecha con más ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)
char* fecha_mas_ventas_pizzas(int *size, Pedido *orders) {
    char fechas[100][75];
    int cantidades[100] = {0};
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int encontrado = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                cantidades[j] += orders[i].quantity;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(fechas[total], orders[i].order_date);
            cantidades[total] = orders[i].quantity;
            total++;
        }
    }

    int max = 0;
    for (int i = 1; i < total; i++) {
        if (cantidades[i] > cantidades[max]) max = i;
    }

    char *resultado = malloc(100);
    sprintf(resultado, "%s: %d", fechas[max], cantidades[max]);
    return resultado;
}
//___________________________________________________________________________________________________________________________________________________________________________________________
// dlsp: Fecha con menos ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)
char* fecha_menos_ventas_pizzas(int *size, Pedido *orders) {
    char fechas[100][75];
    int cantidades[100] = {0};
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int encontrado = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                cantidades[j] += orders[i].quantity;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(fechas[total], orders[i].order_date);
            cantidades[total] = orders[i].quantity;
            total++;
        }
    }

    int min = 0;
    for (int i = 1; i < total; i++) {
        if (cantidades[i] < cantidades[min]) min = i;
    }

    char *resultado = malloc(100);
    sprintf(resultado, "%s: %d", fechas[min], cantidades[min]);
    return resultado;
}
//___________________________________________________________________________________________________________________________________________________________________________________________
// apo: Promedio de pizzas por orden
char* promedio_pizzas_orden(int *size, Pedido *orders) {
    int total_pizzas = 0;
    int ordenes[1000] = {0};
    int num_ordenes = 0;

    for (int i = 0; i < *size; i++) {
        int ya_contada = 0;
        for (int j = 0; j < num_ordenes; j++) {
            if (ordenes[j] == orders[i].order_id) {
                ya_contada = 1;
                break;
            }
        }
        if (!ya_contada) {
            ordenes[num_ordenes++] = orders[i].order_id;
        }
        total_pizzas += orders[i].quantity;
    }

    float promedio = (float)total_pizzas / num_ordenes;
    char *resultado = malloc(50);
    sprintf(resultado, "%.2f", promedio);
    return resultado;
}
//___________________________________________________________________________________________________________________________________________________________________________________________
// apd: Promedio de pizzas por día
char* promedio_pizzas_dia(int *size, Pedido *orders) {
    char fechas[100][75];
    int total_pizzas = 0;
    int num_fechas = 0;

    for (int i = 0; i < *size; i++) {
        int ya_contada = 0;
        for (int j = 0; j < num_fechas; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                ya_contada = 1;
                break;
            }
        }
        if (!ya_contada) {
            strcpy(fechas[num_fechas++], orders[i].order_date);
        }
        total_pizzas += orders[i].quantity;
    }

    float promedio = (float)total_pizzas / num_fechas;
    char *resultado = malloc(50);
    sprintf(resultado, "%.2f", promedio);
    return resultado;
}
//___________________________________________________________________________________________________________________________________________________________________________________________
// ims: Ingrediente más vendido
char* ingrediente_mas_vendido(int *size, Pedido *orders) {
    char ingredientes[500][100];
    int conteo[500] = {0};
    int total = 0;

    for (int i = 0; i < *size; i++) {
        char copia[275];
        strcpy(copia, orders[i].pizza_ingredients);
        char *token = strtok(copia, ",\"");
        while (token != NULL) {
            // limpiar espacios
            while (*token == ' ') token++;
            int encontrado = 0;
            for (int j = 0; j < total; j++) {
                if (strcmp(ingredientes[j], token) == 0) {
                    conteo[j] += orders[i].quantity;
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                strcpy(ingredientes[total], token);
                conteo[total] = orders[i].quantity;
                total++;
            }
            token = strtok(NULL, ",\"");
        }
    }

    int max = 0;
    for (int i = 1; i < total; i++) {
        if (conteo[i] > conteo[max]) max = i;
    }

    char *resultado = malloc(100);
    sprintf(resultado, "%s: %d", ingredientes[max], conteo[max]);
    return resultado;
}
//___________________________________________________________________________________________________________________________________________________________________________________________
// hp: Cantidad de pizzas por categoría vendidas
char* cantidad_pizzas_categoria(int *size, Pedido *orders) {
    char categorias[20][50];
    int conteo[20] = {0};
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int encontrado = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(categorias[j], orders[i].pizza_category) == 0) {
                conteo[j] += orders[i].quantity;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(categorias[total], orders[i].pizza_category);
            conteo[total] = orders[i].quantity;
            total++;
        }
    }

    char *resultado = malloc(200);
    resultado[0] = '\0';
    for (int i = 0; i < total; i++) {
        char buffer[50];
        sprintf(buffer, "%s: %d\n", categorias[i], conteo[i]);
        strcat(resultado, buffer);
    }

    return resultado;
}
//___________________________________________________________________________________________________________________________________________________________________________________________
