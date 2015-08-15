PREFIX := /usr/local

all: tests

clean:
	@$(MAKE) --no-print-directory -C tests clean

tests:
	@$(MAKE) --no-print-directory -C tests

install:
	@echo Installing library to $(PREFIX)/include
	@mkdir -p $(PREFIX)/include
	@cp -r include/ext $(PREFIX)/include

uninstall:
	@echo Uninstalling library from $(PREFIX)/include
	@rm -rf $(PREFIX)/include/ext

.PHONY: all clean tests install uninstall
