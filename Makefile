all: bin/testprogram bin/myShell

bin/testprogram: obj/testprogram.o bin
	g++ -o bin/testprogram obj/testprogram.o

bin/myShell: obj/main.o obj/mesinkar1.o obj/mesinkata1.o obj/cd.o obj/eksekusi.o bin
	g++ -o bin/myShell obj/main.o obj/mesinkar1.o obj/mesinkata1.o obj/cd.o obj/eksekusi.o

obj/main.o: src/main.cpp src/cd.h src/mesinkata1.h src/eksekusi.h obj
	g++ -o obj/main.o -c src/main.cpp

obj/mesinkar1.o: src/mesinkar1.c src/mesinkar1.h obj
	gcc -o obj/mesinkar1.o -c src/mesinkar1.c

obj/mesinkata1.o: src/mesinkata1.c src/mesinkata1.h src/mesinkar1.h obj
	gcc -o obj/mesinkata1.o -c src/mesinkata1.c

obj/cd.o: src/cd.cpp src/cd.h obj
	g++ -o obj/cd.o -c src/cd.cpp

obj/testprogram.o: src/testprogram.cpp obj
	g++ -o obj/testprogram.o -c src/testprogram.cpp

obj/eksekusi.o: src/eksekusi.cpp src/eksekusi.h obj
	g++ -o obj/eksekusi.o -c src/eksekusi.cpp

bin:
	mkdir bin

obj:
	mkdir obj
