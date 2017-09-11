COMPILADOR=g++
REMOVER=rm -rf
SOURCES=Main.cpp Parque.cpp Carro.cpp Passageiro.cpp
OBJETOS=$(subst .cpp,.o,$(SOURCES))
FLAGS=-std=c++11 -lpthread
DIR_OBJ=OBJ
DIR_INCLUDE=include
BINARIO=ExecParque

all: $(BINARIO)

ExecParque: $(OBJETOS)
	$(COMPILADOR) $(DIR_OBJ)/Main.o $(DIR_OBJ)/Parque.o $(DIR_OBJ)/Carro.o $(DIR_OBJ)/Passageiro.o -o $(BINARIO) $(FLAGS)

Main.o: Main.cpp $(DIR_INCLUDE)/Parque.h $(DIR_INCLUDE)/Carro.h $(DIR_INCLUDE)/Passageiro.h
	[ -d $(DIR_OBJ) ] || mkdir $(DIR_OBJ)
	$(COMPILADOR) -c Main.cpp $(FLAGS) -o $(DIR_OBJ)/Main.o $(FLAGS)

Parque.o: Parque.cpp $(DIR_INCLUDE)/Parque.h $(DIR_INCLUDE)/Passageiro.h
	$(COMPILADOR) -c Parque.cpp -o $(DIR_OBJ)/Parque.o $(FLAGS)

Carro.o: Carro.cpp $(DIR_INCLUDE)/Carro.h $(DIR_INCLUDE)/Parque.h
	$(COMPILADOR) -c Carro.cpp -o $(DIR_OBJ)/Carro.o $(FLAGS)

Passageiro.o: Passageiro.cpp $(DIR_INCLUDE)/Parque.h $(DIR_INCLUDE)/Carro.h $(DIR_INCLUDE)/Passageiro.h
	$(COMPILADOR) -c Passageiro.cpp -o $(DIR_OBJ)/Passageiro.o $(FLAGS)

clean:
	$(REMOVER) $(DIR_OBJ)

distclean: clean
	$(REMOVER) $(BINARIO)
