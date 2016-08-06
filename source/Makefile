# Simple Makefile - August 2, 2016
# Most of it is copied from there
# http://stackoverflow.com/a/22545645
SRC_DIR = src
LIB_DIR = libs
INC_DIR = includes
CC      = g++ -g -std=c++11

# Note we need to disable the 'Dual ABI' used in c++11
# https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_dual_abi.html
# Causes errors with strings
CFLAGS  = -I${INC_DIR} -L${LIB_DIR} -D_GLIBCXX_USE_CXX11_ABI=0


# Use the following to build the program without
# The normal console printout (MinGW)
# http://stackoverflow.com/a/9619254
#CFLAGS  += -mwindows

# Note: These will soon get unwieldy.
# The wildcard and patsubt commands will come to your rescue.
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/copernicus/Copernicus.cpp $(SRC_DIR)/copernicus/MyNetwork.cpp $(SRC_DIR)/happyhttp/happyhttp.cpp

# Note: This will soon get unwieldy.
# You will soon want to use an automatic dependency generator.
DEPS = $(wildcard $(INC_DIR)/*.h)

# Libraries we need to include
# We can static link them here
# Need windows library for sockets
LIBS = -lws2_32

# Compile, and also specify the include directory
# By using -I we can use headers without the "includes" folder name
all: src/main.cpp
	${CC} ${CFLAGS} -o copernicus.exe ${SRCS} ${LIBS}

clean: 
	$(RM) copernicus.exe