all: bin install clean

bin:
	g++ -o hello main.cpp

clean:
	rm -f hello
	
install:
	mkdir -p ../usr/bin
	cp hello ../usr/bin
	chmod +x ../usr/bin/hello
	
