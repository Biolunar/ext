PREFIX := /usr/local

all: lib tests

clean:
	@$(MAKE) --no-print-directory -C lib clean
	@$(MAKE) --no-print-directory -C tests clean

lib:
	@$(MAKE) --no-print-directory -C lib

tests:
	@$(MAKE) --no-print-directory -C tests

install:
	@echo Installing library to $(PREFIX)/include and $(PREFIX)/lib
	@mkdir -p $(PREFIX)/include $(PREFIX)/lib
	@cp -r include/ext $(PREFIX)/include
	@cp lib/libext.a $(PREFIX)/lib

uninstall:
	@echo Uninstalling library from $(PREFIX)/include and $(PREFIX)/lib
	@rm -rf $(PREFIX)/include/ext
	@rm -rf $(PREFIX)/lib/libext.a

.PHONY: all clean lib tests install uninstall
