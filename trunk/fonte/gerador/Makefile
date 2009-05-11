CC=g++
FLAGS=-Wall -ansi -ldl -lm
OPENCV= -L/usr/local/lib -lcxcore -lcv -lhighgui -lcvaux -lml -I/usr/local/include/opencv
PLAYERFLAGS=  `pkg-config --cflags playerc++ --libs playerc++` 
NCURSES= -lncurses
GPROOF= -g -pg
CC_OPT= $(FLAGS) $(PLAYERFLAGS)

PROG=gerador_loop

SRC:=$(shell ls ../*.cpp | grep -v principal.cpp && ls *.cpp)
OBJ=$(SRC:.cpp=.o)
DEP=$(OBJ:.o=.d)

$(PROG): $(OBJ)
	@echo "Linkando $(PROG)..." 
	$(CC) $(CC_OPT) $(OBJ) -o ../../$(PROG)
	@echo "Feito."
	@echo "Executando programa..."
	@clear
	@./../../$(PROG)

-include $(DEP)

%.o: %.cpp
	@echo "Compilando $*.cpp..."
	$(CC) $(CC_OPT) -c $*.cpp -o $*.o
	@echo "Gerando dependencias of $*.cpp..."
	$(CC) $(CC_OPT) -MM $*.cpp > $*.d
	@echo "Feito."
 
 

clean:
	@echo "Limpando..."
	@rm -rf ../../$(PROG) *.o *.d *~ *# "#*"
	@make clean2 -C ..
	@echo "Feito."
