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
