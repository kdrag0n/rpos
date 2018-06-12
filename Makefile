CROSS_COMPILE ?= aarch64-linux-gnu-

CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
ASFLAGS = -Iinclude

BUILD_DIR = out
SRC_DIR = src

all: kernel7.img

clean:
	rm -fr $(BUILD_DIR) *.img

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CROSS_COMPILE)gcc $(CFLAGS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	$(CROSS_COMPILE)gcc $(ASFLAGS) -MMD -c $< -o $@

C_FILES = $(wildcard src/*.c)
ASM_FILES = $(wildcard src/*.S)

OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel7.img: $(SRC_DIR)/linkelf.ld $(OBJ_FILES)
	$(CROSS_COMPILE)ld -T src/linker.ld -o $(BUILD_DIR)/kernel7.elf $(OBJ_FILES)
	$(CROSS_COMPILE)objcopy $(BUILD_DIR)/kernel7.elf -O binary kernel7.img
