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

    typedef struct {
        char *nombre;
        char *descripcion;
        char *(*funcion)(int *, Pedido *);
    } Metrica;
    
    Metrica metricas_disponibles[] = {
        {"pms",  "Pizza mas vendida", pizza_mas_vendida},
        {"pls",  "Pizza menos vendida", pizza_menos_vendida},
        {"dms",  "Fecha mas ventas dinero", fecha_mas_ventas_dinero},
        {"dls",  "Fecha menos ventas dinero", fecha_menos_ventas_dinero},
        {"dmsp", "Fecha mas ventas pizzas", fecha_mas_ventas_pizzas},
        {"dlsp", "Fecha menos ventas pizzas", fecha_menos_ventas_pizzas},
        {"apo",  "Promedio pizzas orden", promedio_pizzas_orden},
        {"apd",  "Promedio pizzas dia", promedio_pizzas_dia},
        {"ims",  "Ingrediente mas vendido", ingrediente_mas_vendido},
        {"hp",   "Cantidad pizzas categoria", cantidad_pizzas_categoria}
    };
    
    int total_metricas = sizeof(metricas_disponibles) / sizeof(Metrica);

    // Procesar cada métrica indicada por línea de comandos
    for (int i = 2; i < argc; i++) {
        bool encontrada = false;

        for (int j = 0; j < total_metricas; j++) {
            if (strcmp(argv[i], metricas_disponibles[j].nombre) == 0) {
                char *resultado = metricas_disponibles[j].funcion(&cantidad_pedidos, pedidos);
                printf("%s: %s\n", metricas_disponibles[j].descripcion, resultado);

                // IMPORTANTE: Usar free(resultado) únicamente si la función asignó memoria dinámica (malloc/calloc/realloc)

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
