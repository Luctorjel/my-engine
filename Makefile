# Nome do executável final
TARGET = meu_jogo

# Compilador e flags
CC = gcc
CFLAGS = -Wall -std=c99 -O2

# Configurações para o modo Só CPU (Software Renderer da Raylib)
CFLAGS += -DGRAPHICS_API_OPENGL_SOFTWARE

# Bibliotecas necessárias no Linux para abrir a janela (GLFW) e o renderizador de CPU
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Arquivos fonte (compila todos os arquivos .c no diretório atual)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Linkagem do binário
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# Compilação dos arquivos de código
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos temporários
clean:
	rm -f $(OBJS) $(TARGET)
