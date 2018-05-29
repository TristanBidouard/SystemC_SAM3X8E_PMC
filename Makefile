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
CFLAGS 		    = -W -Wall -I $(SYSCDIR)/include/ -I $(INCDIR)/

# Link options
# LFLAGS 		    = -L $(SYSCDIR)/lib-linux64 -I $(SYSCDIR)/include/ -lsystemc 
LFLAGS                    = -L $(SYSCDIR)/lib-linux64 -lsystemc


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
	$(CC) -o $@ $(OBJECTS) $(LFLAGS)
	@LD_LIBRARY_PATH=$(SYSCDIR)/lib-linux64/ $(BIN)

$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.cpp 
	$(CC) -c $< -o $@ $(CFLAGS)

#	$(CC) -I $(INCDIR) $(CFLAGS) -c $(SOURCES) -o $(OBJDIR)


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



