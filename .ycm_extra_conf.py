# Compiler flags for language C
CFLAGS = [
	'-I./include']

# Compiler flags for language C++
CXXFLAGS = [
	'-I./include',
	'-DME_DEBUG',
	'-g',
	'-Wall',
	'-Wextra',
	'-std=c++2b']

# Compiler flags for language Objective C
OBJCFLAGS = [
	'-I./include']

SOURCES = {
	'/home/edvin/Dokument/libme/src/FileSystem.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/Options.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/lexer/Lexer.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/lexer/Token.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/parser/Parser.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/ast/Call.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/ast/Integer.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/ast/Operator.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/ast/String.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/ast/Variable.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/ast/Function.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/ast/Scope.cpp': CXXFLAGS,
	'/home/edvin/Dokument/libme/src/lang/interpreter/Interpreter.cpp': CXXFLAGS
}

def Settings(**kwargs):
	key = kwargs['filename']
	if key in SOURCES:
		return { 'flags': SOURCES[key] }
	else:
		if IsCFile(key):
			return { 'flags': CFLAGS }
		elif IsCXXFile(key):
			return { 'flags': CXXFLAGS }
		elif IsOBJCFile(key):
			return { 'flags': OBJCFLAGS }
	return { 'flags': [ ] }

def IsCXXFile(file):
	CXX_FILES = ['.cpp', '.cxx', '.cc', '.hpp', '.hxx', '.hh']
	for ext in CXX_FILES:
		if file.endswith(ext):
			return True
	return False

def IsCFile(file):
	C_FILES = ['.c', '.h']
	for ext in C_FILES:
		if file.endswith(ext):
			return True
	return False

def IsOBJCFile(file):
	OBJC_FILES = ['.h', '.m', '.mm', '.M']
	for ext in OBJC_FILES:
		if file.endswith(ext):
			return True
	return False

