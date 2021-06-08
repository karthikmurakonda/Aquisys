build: project.o quiz.o admin.o appdata.o login.o nav.o analytics.o
	gcc project.o quiz.o admin.o appdata.o login.o nav.o analytics.o -o run

project.o: 
	gcc -c project.c -o project.o

quiz.o: 
	gcc -c quiz.c -o quiz.o

admin.o: 
	gcc -c admin.c -o admin.o

appdata.o: 
	gcc -c appdata.c -o appdata.o

login.o: 
	gcc -c login.c -o login.o

nav.o: 
	gcc -c nav.c -o nav.o

analytics.o: 
	gcc -c analytics.c -o analytics.o

clean:
	rm -f *.o run

clean-appdata:
	rm -f .appdata.dat