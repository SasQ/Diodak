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

$(DIR_BLD)/diodak: $(DIR_OBJ)/main.o
	$(QUIET_LD) $(DIR_BLD)/diodak\n"
	@mkdir -p $(DIR_BLD)
	@$(LD) $(DIR_OBJ)/main.o -o $(DIR_BLD)/diodak $(LDOPTS)
	@echo -e "\n$(COLR_GRN)*** SUCCESSFULLY BUILT ***$(COLR_RST)\n"

$(DIR_OBJ)/main.o: $(DIR_SRC)/main.cc
	$(QUIET_CC) $(DIR_SRC)/main.cc\n"
	@mkdir -p $(DIR_OBJ)
	@$(CC) -c $(DIR_SRC)/main.cc -o $(DIR_OBJ)/main.o $(CCOPTS)

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