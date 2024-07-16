CC = gcc
CFLAGS = -Wall -Werror
SRC_DIR = src
TARGET = wserv

# Lista de objetos
OBJS = main.o \
       cleanup.o \
       getFileName.o \
       getMessage.o \
       parseRequest.o \
       printFile.o \
       printHeader.o \
       recordTotalBytes.o \
       sendMessage.o

# Regla de compilación principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

# Reglas de compilación individuales
main.o: $(SRC_DIR)/main.c $(SRC_DIR)/parseRequest.h $(SRC_DIR)/recordTotalBytes.h
	$(CC) $(CFLAGS) -c $< -o $@

cleanup.o: $(SRC_DIR)/cleanup.c
	$(CC) $(CFLAGS) -c $< -o $@

getFileName.o: $(SRC_DIR)/getFileName.c
	$(CC) $(CFLAGS) -c $< -o $@

getMessage.o: $(SRC_DIR)/getMessage.c
	$(CC) $(CFLAGS) -c $< -o $@

parseRequest.o: $(SRC_DIR)/parseRequest.c $(SRC_DIR)/parseRequest.h
	$(CC) $(CFLAGS) -c $< -o $@

printFile.o: $(SRC_DIR)/printFile.c 
	$(CC) $(CFLAGS) -c $< -o $@

printHeader.o: $(SRC_DIR)/printHeader.c
	$(CC) $(CFLAGS) -c $< -o $@

recordTotalBytes.o: $(SRC_DIR)/recordTotalBytes.c $(SRC_DIR)/recordTotalBytes.h
	$(CC) $(CFLAGS) -c $< -o $@

sendMessage.o: $(SRC_DIR)/sendMessage.c
	$(CC) $(CFLAGS) -c $< -o $@


# Limpiar archivos intermedios y ejecutable
clean:
	rm -f $(OBJS) $(TARGET)

