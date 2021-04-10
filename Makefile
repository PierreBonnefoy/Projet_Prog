TARGET= main
OBJECTS= partie1.o
CC=gcc 
CFLAGS=-g -W -Wall -std=c89 -pedantic -O3 -Wall `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS=`pkg-config --libs-only-l MLV`
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS) $(LDLIBS)
clean:
	-rm -f $(TARGET)
	-rm -f $(OBJECTS)
	-rm -rf *~
