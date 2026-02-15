CXX = g++
CXXFLAGS = -Wall
TARGET = hello
SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

install:
	cp $(TARGET) $(DESTDIR)/usr/local/bin/

# Проверка зависимостей (компилятора)
check:
	@command -v $(CXX) >/dev/null 2>&1 || { echo "Ошибка: g++ не установлен!"; exit 1; }
	@echo "Компилятор найден"

.PHONY: all clean install check
