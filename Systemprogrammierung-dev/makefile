##
## Haupt Makefile
##
## Author André, Malte, Tim
##
.PHONY: all compile install test run doc clean distclean

##
## macrodefinitions
##

## pfade
SRCLED = cd src/ledanzeige
SRCSTV = cd src/studiverwaltung
SRCPFG = cd src/pruefungen
SRCSPV = cd src/speicherverwaltung
SRCBUF = cd src/ringbuffer
SRCTEP = cd src/temperatur
SRCWET = cd src/wetter
SRCWED = cd src/wetterd

TSTLED = cd tests/ledanzeige
TSTSTV = cd tests/studiverwaltung
TSTPFG = cd tests/pruefungen
TSTSPV = cd tests/speicherverwaltung
TSTBUF = cd tests/ringbuffer
TSTWET = cd tests/wetter

## variablen
MMK = && make
MKALL = $(MMK) all
MKINS = $(MMK) install
MKTST = $(MMK) test
MKRUN = $(MMK) run
MKCLN = $(MMK) clean
MKDYN = $(MMK) all_lib
MKDIN = $(MMK) install_lib
MKDR = mkdir -p
RM = rm -rf

## rules
all: compile

all_libledanzeige:
	$(SRCLED) $(MKDYN)

all_ringbuffer:
	$(SRCBUF) $(MKDYN)

install_libledanzeige: all_libledanzeige
	$(SRCLED) $(MKDIN)

install_ringbuffer: install_libledanzeige all_ringbuffer
	$(SRCBUF) $(MKDIN)

compile: install_ringbuffer
	$(SRCLED) $(MKALL)
	$(SRCSTV) $(MKALL)
	$(SRCPFG) $(MKALL)
	$(SRCSPV) $(MKALL)
	$(SRCBUF) $(MKALL)
	$(SRCTEP) $(MKALL)
	$(SRCWET) $(MKALL)
	$(SRCWED) $(MKALL)

install: install_ringbuffer
	$(MKDR) lib
	$(MKDR) bin

	$(SRCLED) $(MKINS)
	$(SRCSTV) $(MKINS)
	$(SRCPFG) $(MKINS)
	$(SRCSPV) $(MKINS)
	$(SRCBUF) $(MKINS)
	$(SRCTEP) $(MKINS)
	$(SRCWET) $(MKINS)
	$(SRCWED) $(MKINS)

test:
	$(SRCLED) $(MKTST)	
	$(SRCSTV) $(MKTST)
	$(SRCPFG) $(MKTST)
	$(SRCSPV) $(MKTST)
	$(SRCBUF) $(MKTST)
	$(SRCWET) $(MKTST)

run: test install
	$(SRCLED) $(MKRUN)	
	$(SRCSTV) $(MKRUN)
	$(SRCPFG) $(MKRUN)
	$(SRCSPV) $(MKRUN)
	$(SRCBUF) $(MKRUN)
	##$(SRCTEP) $(MKRUN)
	##$(SRCWET) $(MKRUN)
	$(SRCWED) $(MKRUN)

doc:
	$(MKDR) doc
	doxygen config

clean:
	$(SRCLED) $(MKCLN)
	$(TSTLED) $(MKCLN)
	$(SRCSTV) $(MKCLN)
	$(TSTSTV) $(MKCLN)
	$(SRCPFG) $(MKCLN)
	$(TSTPFG) $(MKCLN)
	$(SRCSPV) $(MKCLN)
	$(TSTSPV) $(MKCLN)
	$(SRCBUF) $(MKCLN)
	$(TSTBUF) $(MKCLN)
	$(SRCTEP) $(MKCLN)
	$(SRCWET) $(MKCLN)
	$(TSTWET) $(MKCLN)
	$(SRCWED) $(MKCLN)

distclean: clean
	
	$(RM) bin
	$(RM) lib
	$(RM) doc
