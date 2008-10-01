
CC=g++
CC_OPT=-Wall -ansi

PROG=robo

SRC:=$(shell ls *.cpp)
OBJ=$(SRC:.cpp=.o)
DEP=$(OBJ:.o=.d)

$(PROG): $(OBJ)
	@echo "Linkando $(PROG)..." 
	$(CC) $(CC_OPT) $(OBJ) -o $(PROG)
	@echo "Feito."

-include $(DEP)

%.o: %.cpp
	@echo "Compilando $*.cpp..."
	$(CC) $(CC_OPT) -c $*.cpp -o $*.o
	@echo "Gerando dependencias of $*.cpp..."
	$(CC) $(CC_OPT) -MM $*.cpp > $*.d
	@echo "Feito."

clean:
	@echo "Limpando..."
	@rm -rf $(PROG) *.o *.d *~ *# "#*"
	@echo "Feito."
