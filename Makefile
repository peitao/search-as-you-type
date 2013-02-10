objects = main.o 

CXXFLAGS = -O2

app:$(objects)
	g++ -O2 -o app $(objects)

main.o:main.cpp *.h


clean:
	rm -f *.o app
