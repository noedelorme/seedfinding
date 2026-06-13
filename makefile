CC = gcc

CUBIOMES_DIR = cubiomes
CUBIOMES_BUILD = $(CUBIOMES_DIR)/build
CUBIOMES_LIB = $(CUBIOMES_BUILD)/libcubiomes_static.a

SRC_DIR = src
BUILD_DIR = build

CFLAGS = -I$(CUBIOMES_DIR)
LDFLAGS = $(CUBIOMES_LIB) -lm

.PHONY: all run clean

all:
	cmake -S $(CUBIOMES_DIR) -B $(CUBIOMES_BUILD)
	cmake --build $(CUBIOMES_BUILD)

run:
	@if [ -z "$(TARGET)" ]; then echo "Usage: make run TARGET=nom"; exit 1; fi
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/$(TARGET).c $(LDFLAGS) -o $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(CUBIOMES_BUILD)
