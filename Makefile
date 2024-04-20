CC = g++
CFLAGS = -Wall -Wextra -std=c++11
SRCS = *.cpp
HDRS = *.hpp
OBJS = $(SRCS:.cpp=.o)
OUT = out

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT)

%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)
