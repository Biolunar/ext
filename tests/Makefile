TARGET   := ./tests
CC       := clang++
FLAGS    := -std=c++14 -pedantic-errors -I../include
WARNINGS := -Weverything -Wno-c++98-compat -Wno-unused-variable
PARAMS   :=

.PHONY: all
all: $(TARGET)

$(TARGET): main.cpp
	@$(CC) $(FLAGS) $(WARNINGS) $(PARAMS) -o $(TARGET) main.cpp

.PHONY: clean
clean:
	@rm -rf $(TARGET)
