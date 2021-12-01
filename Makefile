NAME = libme_2020
VERSION = 2020
OUTPUT = libme

# Directory for the object files
BUILD = ./build

# Compiler for the language C
CC = clang

# Compiler for the language C++
CXXC = clang++

# Compiler for the language Objective C
OBJCC = clang

# Linker
LINKER = clang++

# Compiler and linker flags
FLAGS =

# Compiler flags for language C
CFLAGS = $(FLAGS) -I./include

# Compiler flags for language C++
CXXFLAGS = $(FLAGS) -I./include -DME_DEBUG -Og -g -Wall -Wextra -std=c++20

# Compiler flags for language Objective C
OBJCFLAGS = $(FLAGS) -I./include

# Linker flags
LFLAGS = $(FLAGS)

SOURCES = \
	./src/FileSystem.cpp \
	./src/Options.cpp \
	./src/lang/lexer/Lexer.cpp \
	./src/lang/lexer/Token.cpp \
	./src/lang/parser/Parser.cpp \
	./src/lang/ast/Call.cpp \
	./src/lang/ast/Integer.cpp \
	./src/lang/ast/Operator.cpp \
	./src/lang/ast/String.cpp \
	./src/lang/ast/Variable.cpp \
	./src/lang/ast/Function.cpp \
	./src/lang/ast/Scope.cpp \
	./src/lang/interpreter/Interpreter.cpp
OBJECTS = $(SOURCES:%=$(BUILD)/%.o)
DEPENDS = $(SOURCES:%=$(BUILD)/%.d)

EXTERNALS =

.PHONY: $(NAME)
$(NAME): $(OUTPUT) $(EXTERNALS)

$(OUTPUT): $(OBJECTS)
	ar rcs libme.a $^

-include $(DEPENDS)

$(BUILD)/./src/FileSystem.cpp.o: ./src/FileSystem.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/Options.cpp.o: ./src/Options.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/lexer/Lexer.cpp.o: ./src/lang/lexer/Lexer.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/lexer/Token.cpp.o: ./src/lang/lexer/Token.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/parser/Parser.cpp.o: ./src/lang/parser/Parser.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/ast/Call.cpp.o: ./src/lang/ast/Call.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/ast/Integer.cpp.o: ./src/lang/ast/Integer.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/ast/Operator.cpp.o: ./src/lang/ast/Operator.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/ast/String.cpp.o: ./src/lang/ast/String.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/ast/Variable.cpp.o: ./src/lang/ast/Variable.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/ast/Function.cpp.o: ./src/lang/ast/Function.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/ast/Scope.cpp.o: ./src/lang/ast/Scope.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

$(BUILD)/./src/lang/interpreter/Interpreter.cpp.o: ./src/lang/interpreter/Interpreter.cpp
	@mkdir -p $(dir $@)
	@echo "Building C++ source '$<'"
	@$(CXXC) -c -o $@ $< $(CXXFLAGS) -MMD

.PHONY: install
install:

.PHONY: clean
clean:
	rm -rf $(OUTPUT) $(OBJECTS) $(DEPENDS)
