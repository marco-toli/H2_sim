# $Id: GNUmakefile,v 1.2 2003-01-23 15:31:39 maire Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := H2_sim
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

ROOTCFLAGS = `root-config --cflags`
ROOTLIBS = `root-config --nonew --libs`
CPPFLAGS += $(ROOTCFLAGS) 
EXTRALIBS +=  $(ROOTLIBS)

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*
