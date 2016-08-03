# Simple Makefile - August 2, 2016
# Most of it is copied from there
# http://stackoverflow.com/a/22545645

SRC_DIR = src
INC_DIR = includes
CC      = g++ -g
CFLAGS  = -I${INC_DIR}

# Use the following to build the program without
# The normal console printout (MinGW)
# http://stackoverflow.com/a/9619254
#CFLAGS  = -I${INC_DIR} -mwindows

# Note: These will soon get unwieldy.
# The wildcard and patsubt commands will come to your rescue.
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/Copernicus.cpp

# Note: This will soon get unwieldy.
# You will soon want to use an automatic dependency generator.
DEPS = $(INC_DIR)/main.h $(INC_DIR)/Copernicus.h

# Compile, and also specify the include directory
# By using -I we can use headers without the "includes" folder name
all: src/main.cpp
	${CC} ${CFLAGS} -o copernicus.exe ${SRCS} ${DEPS}

clean: 
	$(RM) copernicus.exe