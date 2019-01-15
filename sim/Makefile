#
# Makefile
#

# tlm name
TLM := fifo
# cpp names
CPPFILES := main.cpp FifoWriter.cpp

# directories
RTLD := ../rtl
OBJD := obj_dir

# g++ (not used at the moment)
CXX := g++
CXXFLAGS := -Wall 

# verilator
VERILATOR := verilator
VFLAGS := -Wall --trace -cc --exe
VINCLUDE := -y $(RTLD)
VERILATE := $(VERILATOR) $(VFLAGS) $(VINCLUDE)

# sub-make flags
SUBFLAGS := --no-print-directory --directory=$(OBJD)

default: all

.PHONY: all run verilate clean

all: $(OBJD)/V$(TLM)

run:
	@$(OBJD)/V$(TLM)

verilate: $(OBJD)/V$(TLM).mk

$(OBJD)/V$(TLM): $(OBJD)/V$(TLM).mk $(CPPFILES)
	@$(MAKE) $(SUBFLAGS) -f V$(TLM).mk

$(OBJD)/V$(TLM).mk: $(RTLD)/$(TLM).sv $(CPPFILES)
	@$(VERILATE) $< $(CPPFILES)

define	mk-objdir
	@bash -c "if [ ! -e $(OBJDIR) ]; then mkdir -p $(OBJDIR)/; fi"
endef

clean:
	@rm -rf obj_dir