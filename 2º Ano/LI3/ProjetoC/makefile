
CC = gcc
CFLAGS = -Wall -g

prog: ./libs/copia.o ./src/main.o ./src/sgv.o ./src/gestaoFilial.o ./src/faturacao.o ./src/produto.o ./src/cliente.o ./src/view.o ./src/controller.o
	cc ./libs/copia.o ./src/main.o  ./src/sgv.o ./src/gestaoFilial.o ./src/faturacao.o ./src/produto.o ./src/cliente.o ./src/view.o ./src/controller.o -o prog



sgv.o : ./src/sgv.c ./include/interface.h ./include/copia.h 
	cc ./src/sgv.c ./include/interface.h ./include/copia.h  -o sgv

copia.o: ./libs/copia.c ./include/copia.h 
	cc ./libs/copia.c ./include/copia.h -o copia

gestaoFilial.o: ./src/gestaoFilial.c ./include/gestaoFilial.h ./include/copia.h 
	cc ./src/gestaoFilial.c ./include/gestaoFilial.h ./include/copia.h  -o gestaoFilial

faturacao.o: ./src/faturacao.c ./include/faturacao.h ./include/copia.h 
	cc ./src/faturacao.c ./include/faturacao.h ./include/copia.h  -o faturacao

produto.o: ./src/produto.c ./include/produto.h ./include/copia.h 
	cc ./src/produto.c ./include/produto.h ./include/copia.h  -o produto

cliente.o: ./src/cliente.c ./include/cliente.h ./include/copia.h 
	cc ./src/cliente.c ./include/cliente.h ./include/copia.h  -o cliente

controller.o: ./src/controller.c ./include/controller.h
	cc ./src/controller.c ./include/controller.h -o controller 

view.o: ./src/view.c ./include/view.h
	cc ./src/view.c ./include/view.h -o view     

prog.o: ./src/main.c ./include/copia.h ./include/controller.h
	cc ./src/main.c ./include/copia.h ./include/controller.h -o prog

clean:
	rm -f prog ./src/*.o
	rm -f prog ./libs/*.o

