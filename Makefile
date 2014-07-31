# Toolchain.
CC=g++
LD=g++

# Options.
CCOPTS=`wx-config --cxxflags`
LDOPTS=`wx-config --libs` -O2 -s

# Directories.
DIR_SRC=./src
DIR_LIB=./lib
DIR_OBJ=./obj
DIR_BLD=./build
DIR_RES=$(DIR_SRC)/assets

# ----- Pretty output -----

# Color definitions.
COLR_RED=\033[01;31m
COLR_GRN=\033[01;32m
COLR_YLW=\033[01;33m
COLR_BLU=\033[01;34m
COLR_PNK=\033[01;35m
COLR_CYA=\033[01;36m
COLR_WHT=\033[01;37m
COLR_RST=\033[00m

# Pretty messages.
QUIET_TXT=@echo -n -e "
QUIET_MSG=$(QUIET_TXT)$(COLR_WHT)
QUIET_CC=  $(QUIET_TXT) $(COLR_BLU)Compiling$(COLR_RST)
QUIET_LD=  $(QUIET_TXT) $(COLR_CYA)Linking  $(COLR_RST)


# ----- The actual build recipe -----

$(DIR_BLD)/diodak: $(DIR_OBJ)/Views/Grid.o $(DIR_OBJ)/Views/Circuit.o $(DIR_OBJ)/main.o
	$(QUIET_LD) $(DIR_BLD)/diodak\n"
	@mkdir -p $(DIR_BLD)
	@$(LD) $(DIR_OBJ)/Views/Grid.o $(DIR_OBJ)/Views/Circuit.o $(DIR_OBJ)/main.o -o $(DIR_BLD)/diodak $(LDOPTS)
	@echo -e "\n$(COLR_GRN)*** SUCCESSFULLY BUILT ***$(COLR_RST)\n"

$(DIR_OBJ)/main.o: $(DIR_SRC)/main.cc $(DIR_SRC)/Views/Circuit.hh  $(DIR_RES)/icons/NewCircuit.xpm
	$(QUIET_CC) $(DIR_SRC)/main.cc\n"
	@mkdir -p $(DIR_OBJ)
	@$(CC) -c $(DIR_SRC)/main.cc -o $(DIR_OBJ)/main.o $(CCOPTS)

$(DIR_OBJ)/Views/Circuit.o: $(DIR_SRC)/Views/Circuit.cc $(DIR_SRC)/Views/Circuit.hh $(DIR_SRC)/Views/Grid.hh
	$(QUIET_CC) $(DIR_SRC)/Views/Circuit.cc\n"
	@mkdir -p $(DIR_OBJ)/Views
	@$(CC) -c $(DIR_SRC)/Views/Circuit.cc -o $(DIR_OBJ)/Views/Circuit.o $(CCOPTS)

$(DIR_OBJ)/Views/Grid.o: $(DIR_SRC)/Views/Grid.cc $(DIR_SRC)/Views/Grid.hh
	$(QUIET_CC) $(DIR_SRC)/Views/Grid.cc\n"
	@mkdir -p $(DIR_OBJ)/Views
	@$(CC) -c $(DIR_SRC)/Views/Grid.cc -o $(DIR_OBJ)/Views/Grid.o $(CCOPTS)


.PHONY: clean
clean:
	$(QUIET_MSG) Cleaning up temporary files..."
	@rm -rf $(DIR_OBJ)
	$(QUIET_MSG) $(COLR_GRN)OK$(COLR_RST)\n"

.PHONY: reset
reset: clean
	$(QUIET_MSG) Cleaning up the build directory..."
	@rm -rf $(DIR_BLD)
	$(QUIET_MSG) $(COLR_GRN)OK$(COLR_RST)\n"