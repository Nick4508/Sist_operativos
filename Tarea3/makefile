MAIN = main

JAVAC = javac

JAVACFLAGS = -g

JAVA = java

JAVAFLAGS =

all: compile run

compile:
	$(JAVAC) $(JAVACFLAGS) $(MAIN).java

run:
	$(JAVA) $(JAVAFLAGS) $(MAIN)

clean:
	rm -f $(MAIN).class
