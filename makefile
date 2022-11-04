CC = g++
CCFLAGS = -Wall
LDFLAGS = -lfreeglut -lopengl32 -lwinmm
TARGET = Pong.exe
OBJFILES = Pong.o ball.o racket.o

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CCFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	 -del -fR $(TARGET) $(OBJFILES) 