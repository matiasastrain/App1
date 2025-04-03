#ifndef METRICAN_H
#define METRICAN_H
#include "utilidades.h"





// Métricas con sus respectivas siglas del enunciado
// pms: Pizza más vendida
// pls: Pizza menos vendida
// dms: Fecha con más ventas en términos de dinero (junto a la cantidad de dinero recaudado)
// dls: Fecha con menos ventas en términos de dinero (junto a la cantidad de dinero recaudado)
// dmsp: Fecha con más ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)
// dlsp: Fecha con menos ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)
// apo: Promedio de pizzas por orden
// apd: Promedio de pizzas por día
// ims: Ingrediente más vendido
// hp: Cantidad de pizzas por categoría vendidas


char* pizza_mas_vendida(int*size, Pedido *orders);
char* pizza_menos_vendida(int*size, Pedido *orders);
char* fecha_mas_ventas_dinero(int*size, Pedido *orders);
char* fecha_menos_ventas_dinero(int*size, Pedido *orders);
char* fecha_mas_ventas_pizzas(int*size, Pedido *orders);
char* fecha_menos_ventas_pizzas(int*size, Pedido *orders);
char* promedio_pizzas_orden(int*size, Pedido *orders);
char* promedio_pizzas_dia(int*size, Pedido *orders);
char* ingrediente_mas_vendido(int*size, Pedido *orders);
char* cantidad_pizzas_categoria(int*size, Pedido *orders);

#endif 