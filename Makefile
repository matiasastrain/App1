# Nombre del ejecutable
TARGET = App1

# Archivos fuente
SRCS = main.c metrican.c utilidades.c

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Regla principal
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Regla para ejecutar el programa con argumentos
run: $(TARGET)
	./$(TARGET) ventas.csv pms

# Regla para limpiar archivos compilados
clean:
	rm -f $(TARGET)
