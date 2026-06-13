CC = gcc

CUBIOMES_DIR = cubiomes
BUILD_DIR = build
SRC_DIR = src

CUBIOMES_LIB = $(CUBIOMES_DIR)/build/libcubiomes_static.a

CFLAGS = -I$(CUBIOMES_DIR)
LDFLAGS = $(CUBIOMES_LIB) -lm

SOURCES := $(wildcard $(SRC_DIR)/*.c)
TARGETS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SOURCES))

.PHONY: all cubiomes run clean

all: cubiomes $(TARGETS)

cubiomes:
	cmake -S $(CUBIOMES_DIR) -B $(CUBIOMES_DIR)/build
	cmake --build $(CUBIOMES_DIR)/build

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%: $(SRC_DIR)/%.c $(CUBIOMES_LIB) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

run:
	@if [ -z "$(TARGET)" ]; then echo "Usage: make run TARGET=nom_du_programme"; exit 1; fi
	./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(CUBIOMES_DIR)/build
