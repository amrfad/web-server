CC = gcc
CFLAGS = -Wall -Wextra -I./src/core -I./src/handlers -I./src/compression
LDFLAGS = -lz

# Opsi untuk mode debug
DEBUG ?= 0

ifeq ($(DEBUG),1)
    CFLAGS += -g -DDEBUG
endif

# Direktori
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Daftar source files (hanya .c)
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/core/*.c) \
       $(wildcard $(SRC_DIR)/handlers/*.c) \
       $(wildcard $(SRC_DIR)/compression/*.c)

# Konversi path source ke path object
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Nama executable
TARGET = $(BIN_DIR)/nihilon

# Target utama
all: $(TARGET)

# Aturan untuk membuat executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Aturan untuk membuat object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Target untuk membersihkan file hasil kompilasi
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Target debug
debug:
	$(MAKE) DEBUG=1

# Mencegah konflik dengan file bernama 'target'
.PHONY: all clean debug
