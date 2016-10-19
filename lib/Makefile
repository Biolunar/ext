TARGET      := libext.a
CC          := clang
CXX         := clang++
CFLAGS      := -std=c11 -I ../include -O3 -march=native -DNDEBUG
CXXFLAGS    := -std=c++14 -stdlib=libc++ -I ../include -O3 -march=native -DNDEBUG
CWARNINGS   := -Weverything -Wno-c99-compat
CXXWARNINGS := -Weverything -Wno-c++98-compat

BUILDDIR    := build
TARGETDIR   := ../$(BUILDDIR)

all: ../$(BUILDDIR)/$(TARGET)

$(BUILDDIR)/cores.o: cores.c
	@mkdir -p $(BUILDDIR)
	@$(CC) $(CFLAGS) $(CWARNINGS) $(PARAMS) -c -o $(BUILDDIR)/cores.o cores.c

$(TARGETDIR)/$(TARGET): $(BUILDDIR)/cores.o
	@mkdir -p $(TARGETDIR)
	@ar rcs $(TARGETDIR)/$(TARGET) $(BUILDDIR)/cores.o

clean:
	@rm -rf $(TARGETDIR) $(BUILDDIR)

.PHONY: all clean
