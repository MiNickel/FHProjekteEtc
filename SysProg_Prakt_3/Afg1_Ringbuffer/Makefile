######################################################################
##
## Main Target & Install
##
######################################################################

## Führt alle makefiles in den src Unterordnern aus
all:
	make --directory=src/ledanzeige
	make all_libledanzeige
	make --directory=src/ringbuffer
	make --directory=src/temperatur
	

## libaries installieren
.Phony: install
install:
	make install_libledanzeige

######################################################################
##
## Libraries
##
######################################################################

## libledanzeige erstellen
.Phony: all_libledanzeige
all_libledanzeige:
	make lib --directory=src/ledanzeige

## libledanzeige instalieren
.Phony: install_libledanzeige
install_libledanzeige: all_libledanzeige
	mkdir -p lib/
	cp -f --remove-destination src/ledanzeige/libledanzeige.so lib/

## libringbuffer erstellen
.Phony: all_libringbuffer
all_libringbuffer:
	make lib --directory=src/ringbuffer

## libringbuffer installieren
.Phony: install_libringbuffer
install_libringbuffer: all_libringbuffer
	mkdir -p lib/
	cp -f --remove-destination src/ringbuffer/libringbuffer.so lib/


######################################################################
##
## Dokumentation
##
######################################################################

## Generiert Dokumentation mit doxygen
.Phony: genDocs
genDocs:
	doxygen doxygen.cfg

######################################################################
##
## Clean
##
######################################################################

## Führt den clean Befehl der makefiles in den src Unterordnern aus
.Phony: clean
clean:
	make --directory=src/ledanzeige clean
	make --directory=src/studiverwaltung clean
	make --directory=src/pruefungen clean
	make --directory=src/speicherverwaltung clean