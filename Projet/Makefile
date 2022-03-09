CC = gcc
CFLAGS = -Wall

all : comparaisonExponentiationModulaire generationClef generationNbPremier testMillerRabin

comparaisonExponentiationModulaire : comparaisonExponentiationModulaire.c outilsMathematiques.o outilsMathematiques.h
	$(CC) $(CFLAGS) -o comparaisonExponentiationModulaire outilsMathematiques.o comparaisonExponentiationModulaire.c

generationNbPremier : generationNbPremier.c outilsMathematiques.o testMillerRabin.o	generationNbPremier.h outilsMathematiques.h testMillerRabin.h
	$(CC) $(CFLAGS) -o generationNbPremier generationNbPremier.c outilsMathematiques.o testMillerRabin.o

outilsMathematiques.o : outilsMathematiques.c outilsMathematiques.h
	$(CC) $(CFLAGS) -c outilsMathematiques.c

testMillerRabin.o : testMillerRabin.c outilsMathematiques.h outilsMathematiques.o
	$(CC) $(CFLAGS) -c testMillerRabin.c outilsMathematiques.o

generationClef.o : generationClef.c outilsMathematiques.h outilsMathematiques.o testMillerRabin.o generationNbPremier.o generationNbPremier.h
	$(CC) $(CFLAGS) -c generationClef.c outilsMathematiques.o testMillerRabin.o generationNbPremier.o 

 
clean :
	rm -rf *.o