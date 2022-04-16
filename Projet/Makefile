CC = gcc 
CFLAGS = -Wall


all : comparaisonExponentiationModulaire testDeclaration testRSA testElection testWinner testBlockchain testOpenSSL graphBlockchain testGenerationClefs


comparaisonExponentiationModulaire : comparaisonExponentiationModulaire.c outilsMathematiques.o outilsMathematiques.h
	$(CC) $(CFLAGS) -o comparaisonExponentiationModulaire outilsMathematiques.o comparaisonExponentiationModulaire.c

generationNbPremier.o : generationNbPremier.c outilsMathematiques.o testMillerRabin.o	generationNbPremier.h outilsMathematiques.h testMillerRabin.h
	$(CC) $(CFLAGS) -c generationNbPremier.c 

outilsMathematiques.o : outilsMathematiques.c outilsMathematiques.h
	$(CC) $(CFLAGS) -c outilsMathematiques.c

testMillerRabin.o : testMillerRabin.c testMillerRabin.h outilsMathematiques.o outilsMathematiques.h
	$(CC) $(CFLAGS) -c testMillerRabin.c 

generationClef.o : generationClef.c generationClef.h outilsMathematiques.h outilsMathematiques.o testMillerRabin.o testMillerRabin.h generationNbPremier.o generationNbPremier.h
	$(CC) $(CFLAGS) -c generationClef.c

testRSA : testRSA.c generationClef.o outilsMathematiques.h outilsMathematiques.o testMillerRabin.o generationNbPremier.o generationNbPremier.h rsa.o rsa.h
	$(CC) $(CFLAGS) -o testRSA testRSA.c generationClef.o testMillerRabin.o outilsMathematiques.o generationNbPremier.o rsa.o -lm
 
rsa.o : rsa.c rsa.h generationClef.o outilsMathematiques.h outilsMathematiques.o testMillerRabin.o generationNbPremier.o generationNbPremier.h
	$(CC) $(CFLAGS) -c rsa.c 

manipulationClefs.o : manipulationClefs.c outilsMathematiques.o generationClef.o generationNbPremier.o testMillerRabin.o rsa.o outilsMathematiques.h generationClef.h generationNbPremier.h testMillerRabin.h rsa.h manipulationClefs.h	
	$(CC) $(CFLAGS) -c manipulationClefs.c 	

signature.o : signature.c outilsMathematiques.o generationClef.o generationNbPremier.o testMillerRabin.o rsa.o outilsMathematiques.h generationClef.h generationNbPremier.h testMillerRabin.h rsa.h manipulationClefs.o manipulationClefs.h	signature.h
	$(CC) $(CFLAGS) -c signature.c 

declaration.o : signature.c signature.h manipulationClefs.c manipulationClefs.h declaration.c declaration.h
	$(CC) $(CFLAGS) -c declaration.c 

testDeclaration : signature.c outilsMathematiques.o generationClef.o generationNbPremier.o testMillerRabin.o rsa.o outilsMathematiques.h generationClef.h generationNbPremier.h testMillerRabin.h rsa.h signature.o signature.h rsa.o rsa.h generationClef.o generationClef.h outilsMathematiques.o outilsMathematiques.h generationNbPremier.o generationNbPremier.h declaration.o declaration.h manipulationClefs.o manipulationClefs.h
	$(CC) $(CFLAGS) -o testDeclaration testDeclaration.c manipulationClefs.o signature.o testMillerRabin.o declaration.o rsa.o generationClef.o outilsMathematiques.o generationNbPremier.o -lm

donneesVote.o : donneesVote.c donneesVote.h manipulationClefs.o manipulationClefs.h declaration.o declaration.h signature.o signature.h
	$(CC) $(CFLAGS) -c donneesVote.c 

listDeclaration.o : listDeclaration.c listDeclaration.h declaration.o declaration.h manipulationClefs.o manipulationClefs.h
	$(CC) $(CFLAGS) -c listDeclaration.c

blockchain.o : blockchain.h blockchain.c listDeclaration.h listDeclaration.o manipulationClefs.h manipulationClefs.o generationClef.o generationClef.h
	$(CC) $(CFLAGS) -c blockchain.c
	
testElection : testElection.c listDeclaration.o listDeclaration.h listKey.o listKey.h donneesVote.o donneesVote.h winner.o winner.h manipulationClefs.o manipulationClefs.h generationClef.o generationClef.h signature.o signature.h declaration.o declaration.h rsa.o rsa.h outilsMathematiques.o outilsMathematiques.h testMillerRabin.o testMillerRabin.h generationNbPremier.o generationNbPremier.h
	$(CC) $(CFLAGS) -o testElection testElection.c listDeclaration.o listKey.o donneesVote.o winner.o manipulationClefs.o generationClef.o signature.o declaration.o rsa.o outilsMathematiques.o testMillerRabin.o generationNbPremier.o -lm

winner.o : winner.c winner.h listKey.o listKey.h listDeclaration.o listDeclaration.h
	$(CC) $(CFLAGS) -c winner.c

testWinner :  testWinner.c winner.o winner.h listKey.o listKey.h listDeclaration.o listDeclaration.h manipulationClefs.o manipulationClefs.h donneesVote.o donneesVote.h generationClef.o generationClef.h signature.o signature.h declaration.o declaration.h rsa.o rsa.h outilsMathematiques.o outilsMathematiques.h testMillerRabin.o testMillerRabin.h generationNbPremier.o generationNbPremier.h
	$(CC) $(CFLAGS) -o testWinner testWinner.c listDeclaration.o listKey.o donneesVote.o winner.o manipulationClefs.o generationClef.o signature.o declaration.o rsa.o outilsMathematiques.o testMillerRabin.o generationNbPremier.o -lm

testOpenSSL : testOpenSSL.c blockchain.o blockchain.h listDeclaration.o listDeclaration.h manipulationClefs.o manipulationClefs.h donneesVote.o donneesVote.h listKey.o listKey.h generationClef.o generationClef.h donneesVote.o donneesVote.h declaration.o declaration.h generationNbPremier.o generationNbPremier.h rsa.o rsa.h testMillerRabin.o testMillerRabin.h signature.h signature.o outilsMathematiques.o outilsMathematiques.h
	$(CC) $(CFLAGS) -o testOpenSSL testOpenSSL.c blockchain.o listDeclaration.o manipulationClefs.o listKey.o generationClef.o donneesVote.o declaration.o generationNbPremier.o rsa.o testMillerRabin.o signature.o outilsMathematiques.o -lssl -lcrypto -lm

testGenerationClefs : testGenerationClefs.c manipulationClefs.o manipulationClefs.h generationClef.o generationClef.h testMillerRabin.o testMillerRabin.h generationNbPremier.o generationNbPremier.h outilsMathematiques.o outilsMathematiques.h
	$(CC) $(CFLAGS) -o testGenerationClefs testGenerationClefs.c manipulationClefs.o generationClef.o testMillerRabin.o generationNbPremier.o outilsMathematiques.o -lm

testBlockchain : testBlockchain.c blockchain.o blockchain.h listDeclaration.o listDeclaration.h manipulationClefs.o manipulationClefs.h donneesVote.o donneesVote.h listKey.o listKey.h generationClef.o generationClef.h donneesVote.o donneesVote.h declaration.o declaration.h generationNbPremier.o generationNbPremier.h rsa.o rsa.h testMillerRabin.o testMillerRabin.h signature.h signature.o outilsMathematiques.o outilsMathematiques.h
	$(CC) $(CFLAGS) -o testBlockchain testBlockchain.c blockchain.o listDeclaration.o manipulationClefs.o listKey.o generationClef.o donneesVote.o declaration.o generationNbPremier.o rsa.o testMillerRabin.o signature.o outilsMathematiques.o -lssl -lcrypto -lm

graphBlockchain : graphBlockchain.c blockchain.o blockchain.h listDeclaration.o listDeclaration.h manipulationClefs.o manipulationClefs.h donneesVote.o donneesVote.h listKey.o listKey.h generationClef.o generationClef.h declaration.o declaration.h generationNbPremier.o generationNbPremier.h rsa.o rsa.h testMillerRabin.o testMillerRabin.h signature.o signature.h outilsMathematiques.o outilsMathematiques.h
	$(CC) $(CFLAGS) -o graphBlockchain graphBlockchain.c blockchain.o listDeclaration.o manipulationClefs.o listKey.o generationClef.o donneesVote.o declaration.o generationNbPremier.o rsa.o testMillerRabin.o signature.o outilsMathematiques.o -lssl -lcrypto -lm

blockTree.o : blockTree.c blockTree.h blockchain.o blockchain.h
	$(CC) $(CFLAGS) -c blockTree.c

clean :
	rm -rf *.o comparaisonExponentiationModulaire testDeclaration testRSA testElection testWinner testOpenSSL testBlockchain graphBlockchain testGenerationClefs
