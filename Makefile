CC=g++ -std=c++17
SRCDIR=src
OBJDIR=obj
BINDIR=bin
DEPDIR=includes
SRCS=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEP=$(wildcard $(DEPDIR)/*.hpp)
BOOST=-lboost_system -lboost_filesystem
INC= -I$(DEPDIR) -I /usr/local/include/boost
FLAGS=-lm -O4 -L /usr/local/lib

all: bin/main.out

bin/main.out: $(OBJS) $(DEP)
	@echo "Linking objects into main.exe..."
	@$(CC) $(INC) $(FLAGS) -o $(BINDIR)/main $(OBJS) $(BOOST)

obj/%.o : src/%.cpp $(DEP)
	@echo "Creating $(<:src/%.cpp=%) object file..."
	@$(CC) $(INC) $(FLAGS) -c -o $@ $< $(BOOST)

.PHONY:clean 

clean:
	@rm -rf ./obj/*.o ./bin/*.exe .bin/*.out bin/main


	