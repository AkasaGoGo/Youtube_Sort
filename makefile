CC = g++

TARGET = YoutubeSort
SRCS = main.cpp window.cpp callback.cpp
OBJS = $(SRCS:.cpp=.o)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lgdi32

$(OBJS): $(SRCS)
	$(CC) -c $(SRCS)

all: clean $(OBJS) $(TARGET)

clean:
	-rm -f $(OBJS) $(TARGET) *.d
