#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
CXX = g++

# locate wx-config (supports Homebrew on Apple Silicon / Intel and standard PATH)
WX_CONFIG := $(shell command -v wx-config 2>/dev/null || command -v /opt/homebrew/bin/wx-config 2>/dev/null || command -v /usr/local/bin/wx-config 2>/dev/null)
WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)

# define any compile-time flags
CXXFLAGS	:= -std=c++17 -Wall -Wextra -g $(WX_CXXFLAGS)

# define library paths in addition to /usr/lib
LFLAGS = $(WX_LIBS)

# define output directory
OUTPUT	:= output

# define source directory
SRC		:= src

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= lib

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d 2>/dev/null)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))

# define the C object files
OBJECTS		:= $(SOURCES:.cpp=.o)

# define the dependency output files
DEPS		:= $(OBJECTS:.o=.d)

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

# include all .d files
-include $(DEPS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -MMD $<  -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	$(RM) $(call FIXPATH,$(DEPS))
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!
