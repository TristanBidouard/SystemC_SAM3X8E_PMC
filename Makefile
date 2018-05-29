################################################################################
#                                 MAKEFILE                                     #
################################################################################

# Directories
BINDIR 		    = bin
OBJDIR 		    = obj
INCDIR 		    = inc
SRCDIR 		    = src
SYSCDIR         = /home/greensocs/Projects/systemc-2.3.1/release

# Binairy name
TARGET 		    = PMCexe

# Compiling options
CC 		        = g++
CFLAGS 		    = -W -Wall

# Link options
LFLAGS 		    = -L $(SYSCDIR)/lib-linux64 -I $(SYSCDIR)/include/ -lsystemc 

# Variables
BIN             = $(BINDIR)/$(TARGET)
SOURCES        := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES       := $(wildcard $(INCDIR)/*.h)
OBJECTS        := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Rm option
RM 		        = rm -f

############################### COMPILING RULES  ###############################

all : $(BIN)

$(BIN) : $(OBJECTS)
	@$(CC) -o $@ $(OBJECTS) $(LFLAGS)
	@LD_LIBRARY_PATH=$(SYSCDIR)/lib-linux64/ $(BIN)

$(OBJECTS) : $(SOURCES) $(INCLUDES) 
	@$(CC) -o $@ -c $(SOURCES) -I $(INCDIR) $(CFLAGS)

#all :
#	$(LINKER) $(SOURCES) -o $(BIN) $(LFLAGS)
#	LD_LIBRARY_PATH=$(SYSCDIR)/lib-linux64/ $(BIN)
################################### CLEANER ####################################
.PHONY: clean
clean :
	@$(RM) $(OBJECTS)
	@$(RM) $(SRCDIR)/*~
	@$(RM) $(INCDIR)/*~
	@$(RM) *~

clear :
	@$(RM) $(BIN)

################################################################################



