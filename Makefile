CC = g++

CFLAGS = -Wall -g

SRCS = *.cpp

TARGET = main

all: clean $(TARGET) 

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRCS)

clean:
	$(RM) $(TARGET)