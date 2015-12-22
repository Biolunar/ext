TARGET      := libext.a
CC          := clang
CXX         := clang++
CFLAGS      := -std=c11 -I ../include -O3 -march=native
CXXFLAGS    := -std=c++14 -I ../include -O3 -march=native
CWARNINGS   := -Weverything -Wno-c99-compat
CXXWARNINGS := -Weverything -Wno-c++98-compat

all: $(TARGET)

$(TARGET): cores.o
	@ar rcs $(TARGET) cores.o

cores.o: cores.c
	@$(CC) $(CFLAGS) $(CWARNINGS) $(PARAMS) -c -o cores.o cores.c

clean:
	@rm -rf $(TARGET) *.o

.PHONY: all clean
