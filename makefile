CC = g++
CCFLAGS = -Wall
LDFLAGS = -lfreeglut -lopengl32 -lwinmm -L"C:\Program Files\Common Files\freeglut\lib\x64"
IFLAGS = -I"C:\Program Files\Common Files\MinGW\freeglut\include"
TARGET = Pong.exe
OBJFILES = Pong.o ball.o racket.o

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CCFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) $(IFLAGS)
clean:
	 -del -fR $(TARGET) $(OBJFILES) 