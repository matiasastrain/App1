#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include "utilidades.h"
#include "metrican.h"

#define MAX_PEDIDOS 10000

// Tipo para punteros a funciones de métricas
typedef char* (*funcion_metrica)(int*, Pedido*);

// Asociación entre nombre de métrica y función correspondiente
typedef struct {
    char nombre[6];  // 5 caracteres + '\0'
    funcion_metrica funcion;
} Metrica;

int main(int argc, char *argv[]) {
    // Si llegan menos de 3 argumentos, establecemos valores por defecto
    // (Esto es opcional; puedes simplemente hacer un "usage" y salir)
    if (argc < 3) {
        fprintf(stderr, "Advertencia: DATOS MANUALMENTE MAL IMPORTADOS EN EL EJECUTABLE. Se usarán valores por defecto.\n");
        argv[1] = "ventas.csv";
        argv[2] = "pms";
        argc = 3;
    }

    Pedido pedidos[MAX_PEDIDOS];
    int cantidad_pedidos = read_csv(argv[1], pedidos);
    if (cantidad_pedidos < 0) {
        fprintf(stderr, "Error al leer el archivo: %s\n", argv[1]);
        return 1;
    }

    // Lista de métricas disponibles (cadenas cortas)
    Metrica metricas_disponibles[] = {
        {"pms",  pizza_mas_vendida},
        {"pls",  pizza_menos_vendida},
        {"dms",  fecha_mas_ventas_dinero},
        {"dls",  fecha_menos_ventas_dinero},
        {"dmsp", fecha_mas_ventas_pizzas},
        {"dlsp", fecha_menos_ventas_pizzas},
        {"apo",  promedio_pizzas_orden},
        {"apd",  promedio_pizzas_dia},
        {"ims",  ingrediente_mas_vendido},
        {"hp",   cantidad_pizzas_categoria}
    };
    int total_metricas = sizeof(metricas_disponibles) / sizeof(Metrica);

    // Procesar cada métrica indicada por línea de comandos
    for (int i = 2; i < argc; i++) {
        bool encontrada = false;

        for (int j = 0; j < total_metricas; j++) {
            if (strcmp(argv[i], metricas_disponibles[j].nombre) == 0) {
                char *resultado = metricas_disponibles[j].funcion(&cantidad_pedidos, pedidos);
                printf("%s: %s\n", argv[i], resultado);

                // Ojo: solo liberar si la función aloca memoria con malloc
                free(resultado);
                encontrada = true;
                break;
            }
        }
        if (!encontrada) {
            fprintf(stderr, "Métrica desconocida: %s\n", argv[i]);
        }
    }

    return 0;
}
