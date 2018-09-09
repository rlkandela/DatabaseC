CC= gcc

DBLauncher: main.o lecture.o parameters.o List.o Database.o Node.o date.o fdb.o
	$(CC) -o DBLauncher main.o lecture.o parameters.o List.o Database.o Node.o date.o fdb.o

main.o: main.c fdb.h parameters.h lecture.h Database.h DBDefines.h List.h Node.h
	$(CC) -c main.c

lecture.o: lecture.c parameters.h DBDefines.h
	$(CC) -c lecture.c

parameters.o: parameters.c
	$(CC) -c parameters.c

List.o: List.c Node.h DBDefines.h parameters.h
	$(CC) -c List.c

Node.o: Node.c DBDefines.h parameters.h
	$(CC) -c Node.c

date.o: date.c DBDefines.h
	$(CC) -c date.c

Database.o: Database.c List.h date.h Node.h parameters.h DBDefines.h
	$(CC) -c Database.c

fdb.o: fdb.c DBDefines.h lecture.h parameters.h Database.h List.h Node.h
	$(CC) -c fdb.c

clean:
	rm DBLauncher *.o *~
