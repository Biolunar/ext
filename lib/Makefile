TARGET      := libext.a
CC          := clang
CXX         := clang++
CFLAGS      := -std=c11 -I ../include -O3 -march=native
CXXFLAGS    := -std=c++14 -stdlib=libc++ -I ../include -O3 -march=native
CWARNINGS   := -Weverything -Wno-c99-compat
CXXWARNINGS := -Weverything -Wno-c++98-compat

all: $(TARGET)

$(TARGET): cores.o file.o
	@ar rcs $(TARGET) cores.o file.o

cores.o: cores.c
	@$(CC) $(CFLAGS) $(CWARNINGS) $(PARAMS) -c -o cores.o cores.c

file.o: file.cpp
	@$(CXX) $(CXXFLAGS) $(CXXWARNINGS) $(PARAMS) -c -o file.o file.cpp

clean:
	@rm -rf $(TARGET) *.o

.PHONY: all clean
