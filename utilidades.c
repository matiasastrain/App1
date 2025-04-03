#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilidades.h"

#define MAX_LINE 1024
#define MAX_FIELDS 12

//MOdificar el código ya que lo saqué de internet

// Parseo manual de línea de CSV respetando comillas dobles
int parse_csv_line(char *line, char **fields, int max_fields) {
    int field_count = 0;
    char *ptr = line;
    int in_quotes = 0;

    fields[field_count++] = ptr;

    while (*ptr) {
        if (*ptr == '"') {
            in_quotes = !in_quotes;
        } else if (*ptr == ',' && !in_quotes) {
            *ptr = '\0';
            if (field_count < max_fields) {
                fields[field_count++] = ptr + 1;
            }
        }
        ptr++;
    }

    return field_count;
}

int read_csv(const char *filename, Pedido *orders) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error al abrir el archivo %s\n", filename);
        return -1;
    }

    char line[MAX_LINE];
    int count = 0;

    fgets(line, MAX_LINE, fp); // Saltar encabezado

    while (fgets(line, MAX_LINE, fp)) {
        char *fields[MAX_FIELDS];
        int field_count = parse_csv_line(line, fields, MAX_FIELDS);
        if (field_count < 12) continue;

        orders[count].pizza_id = atoi(fields[0]);
        orders[count].order_id = atoi(fields[1]);
        strcpy(orders[count].pizza_name_id, fields[2]);
        orders[count].quantity = atoi(fields[3]);
        strcpy(orders[count].order_date, fields[4]);
        strcpy(orders[count].order_time, fields[5]);
        orders[count].unit_price = atof(fields[6]);
        orders[count].total_price = atof(fields[7]);
        strcpy(orders[count].pizza_size, fields[8]);
        strcpy(orders[count].pizza_category, fields[9]);
        strcpy(orders[count].pizza_ingredients, fields[10]);
        strcpy(orders[count].pizza_name, fields[11]);

        count++;
    }

    fclose(fp);
    return count;
}

void print_orders(Pedido *orders, int count) {
    for (int i = 0; i < count; i++) {
        printf("Pizza ID: %d\n", orders[i].pizza_id);
        printf("Order ID: %d\n", orders[i].order_id);
        printf("Pizza Name ID: %s\n", orders[i].pizza_name_id);
        printf("Quantity: %d\n", orders[i].quantity);
        printf("Order Date: %s\n", orders[i].order_date);
        printf("Order Time: %s\n", orders[i].order_time);
        printf("Unit Price: %.2f\n", orders[i].unit_price);
        printf("Total Price: %.2f\n", orders[i].total_price);
        printf("Pizza Size: %s\n", orders[i].pizza_size);
        printf("Pizza Category: %s\n", orders[i].pizza_category);
        printf("Pizza Ingredients: %s\n", orders[i].pizza_ingredients);
        printf("Pizza Name: %s\n\n", orders[i].pizza_name);
    }
}
