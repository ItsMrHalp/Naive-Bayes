CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -Wno-missing-braces -Wshadow -Wconversion -Wfloat-equal -std=c17 -g
LDFLAGS = 

# Папки
SRCDIR  = src
BUILDDIR= build
BINDIR  = bin

TARGET  = $(BINDIR)/NB.exe

# Находим все .c файлы в src/
SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS    = $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Цель по умолчанию
all: $(TARGET)

# ==================== Линковка ====================
$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $^ -o $@ $(LDFLAGS)

# ==================== Компиляция ====================
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ==================== Создание папок ====================
$(BUILDDIR) $(BINDIR):
	mkdir -p $@

# ==================== Очистка ====================
clean:
	rm -rf $(BUILDDIR) 2>/dev/null || \
	del /Q /S $(BUILDDIR)\* 2>nul

.PHONY: all clean