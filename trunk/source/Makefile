CC=g++
CC_OPT=-Wall -ansi

PROG=robo2

SRC:=$(shell ls *.cpp)
OBJ=$(SRC:.cpp=.o)
DEP=$(OBJ:.o=.d)

#have_a := $(wildcard $(PROG))

$(PROG): $(OBJ)
	@echo "Linkando $(PROG)..." 
	$(CC) $(CC_OPT) $(OBJ) -o $(PROG)
	@echo "Feito."
	@echo "Executando programa..."
	@./$(PROG)

#ifeq ($(strip $(have_a)),)
# 
#	@echo "we don't have A"
# 
#else
# 
#	@echo "we have A"
#endif

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
