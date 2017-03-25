#
# Copyright 2017 Mahdi Khanalizadeh
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

PREFIX := /usr/local

all: lib tests

clean:
	@$(MAKE) --no-print-directory -C lib clean
	@$(MAKE) --no-print-directory -C tests clean

lib:
	@$(MAKE) --no-print-directory -C lib

test:
	@$(MAKE) --no-print-directory -C tests

install: lib
	@echo Installing library to $(PREFIX)/include and $(PREFIX)/lib
	@mkdir -p $(PREFIX)/include $(PREFIX)/lib
	@cp -r include/ext $(PREFIX)/include
	@cp build/libext.a $(PREFIX)/lib

uninstall:
	@echo Uninstalling library from $(PREFIX)/include and $(PREFIX)/lib
	@rm -rf $(PREFIX)/include/ext
	@rm -rf $(PREFIX)/lib/libext.a

.PHONY: all clean lib tests install uninstall
