CPP = g++
CPPFLAGS = -I. -std=c++11
DEPS = array.h bmp.h
OBJ = array.o bmp.o main.o

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CPPFLAGS)

PSNRCalculation: $(OBJ)
	$(CPP) -o $@ $^ $(CPPFLAGS)

