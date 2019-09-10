CC = g++

TARGET = logic

# object file director
BUILDDIR = bin

VPATH = \
src \
src/notation

# source file
SRCS = \
src/notation/node.cpp \
src/notation/nad.cpp \
src/notation/biimplication.cpp \
src/notation/exists.cpp \
src/notation/forall.cpp \
src/notation/implication.cpp \
src/notation/nand.cpp \
src/notation/negation.cpp \
src/notation/or.cpp \
src/notation/statement.cpp \
src/notation/value.cpp \
src/notation/variable.cpp \



# locatio of the python include files and library
PYTHON_INC = /usr/include/python3.6m
PYTHON_LIB = /usr/lib/python3.6m/config

# location of the Boost Python include files and library
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib

# include
INCL = -I.\
-I$(BOOST_INC) \
-I$(PYTHON_INC)

# library
LIB = -L$(BOOST_LIB) \
-L$(PYTHON_LIB)

# flag
CFLAGS = -fPIC $(INCL)
LDFLAGS = -shared -Wl,--export-dynamic $(LIB) -lboost_python3 -lpython3.6m

# Object
OBJS = $(addprefix $(BUILDDIR)/, $(notdir $(SRCS:.cpp=.o)))

.PHONY: default clean

#######################################
# build
#######################################
default: $(TARGET).so
	@echo Done

$(TARGET).so: $(OBJS) $(addprefix $(BUILDDIR)/, $(TARGET:=.o))
	$(CC) $(OBJS) $(addprefix $(BUILDDIR)/,$(notdir $(@:.so=.o))) $(LDFLAGS) -o $@

$(BUILDDIR)/%.o: %.cpp Makefile | $(BUILDDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR):
	@mkdir $@

#######################################
# clean
#######################################
clean:
	rm -rf *.so
	rm -rf $(BUILDDIR)/*.o
