COMP = g++-5.3.0
#put all your object files here
OBJS = main.o RockPaperScissors.o helperFunctions.o gameStatus.o cell.o
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp #put dependencies here!
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RockPaperScissors.o: RockPaperScissors.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
helperFunctions.o: helperFunctions.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
gameStatus.o: gameStatus.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
cell.o: cell.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
