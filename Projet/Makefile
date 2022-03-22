CC = gcc
CFLAGS = -Wall

all : comparaisonExponentiationModulaire generationClef generationNbPremier testMillerRabin test

comparaisonExponentiationModulaire : comparaisonExponentiationModulaire.c outilsMathematiques.o outilsMathematiques.h
	$(CC) $(CFLAGS) -o comparaisonExponentiationModulaire outilsMathematiques.o comparaisonExponentiationModulaire.c

generationNbPremier.o : generationNbPremier.c outilsMathematiques.o testMillerRabin.o	generationNbPremier.h outilsMathematiques.h testMillerRabin.h
	$(CC) $(CFLAGS) -c generationNbPremier.c outilsMathematiques.o testMillerRabin.o

outilsMathematiques.o : outilsMathematiques.c outilsMathematiques.h
	$(CC) $(CFLAGS) -c outilsMathematiques.c

testMillerRabin.o : testMillerRabin.c outilsMathematiques.h outilsMathematiques.o
	$(CC) $(CFLAGS) -c testMillerRabin.c outilsMathematiques.o

generationClef.o : generationClef.c generationClef.h outilsMathematiques.h outilsMathematiques.o testMillerRabin.o testMillerRabin.h generationNbPremier.o generationNbPremier.h
	$(CC) $(CFLAGS) -c generationClef.c outilsMathematiques.o testMillerRabin.o generationNbPremier.o 

test : test.c generationClef.o outilsMathematiques.h outilsMathematiques.o testMillerRabin.o generationNbPremier.o generationNbPremier.h rsa.o rsa.h
	$(CC) $(CFLAGS) -o test test.c generationClef.o testMillerRabin.o outilsMathematiques.o generationNbPremier.o rsa.o
 
rsa.o : rsa.c rsa.h generationClef.o outilsMathematiques.h outilsMathematiques.o testMillerRabin.o generationNbPremier.o generationNbPremier.h
	$(CC) $(CFLAGS) -c rsa.c generationClef.o testMillerRabin.o outilsMathematiques.o generationNbPremier.o

manipulationClefs.o : manipulationClefs.c outilsMathematiques.o generationClef.o generationNbPremier.o testMillerRabin.o rsa.o outilsMathematiques.h generationClef.h generationNbPremier.h testMillerRabin.h rsa.h manipulationClefs.h	
	$(CC) $(CFLAGS) -c manipulationClefs.c outilsMathematiques.o generationClef.o generationNbPremier.o testMillerRabin.o rsa.o 	

signature.o : signature.c outilsMathematiques.o generationClef.o generationNbPremier.o testMillerRabin.o rsa.o outilsMathematiques.h generationClef.h generationNbPremier.h testMillerRabin.h rsa.h manipulationClefs.h	signature.h
	$(CC) $(CFLAGS) -c signature.c manipulationClefs.o outilsMathematiques.o generationClef.o generationNbPremier.o testMillerRabin.o rsa.o 	

clean :
	rm -rf *.o test generationNbPremier comparaisonExponentiationModulaire