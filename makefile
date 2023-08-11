CC = g++

TARGET = YoutubeSort
SRCS = main.cpp window.cpp callback.cpp
OBJS = $(SRCS:.cpp=.o)

RC = windres
RESOURCE = menu.rc
OBJR = $(RESOURCE:.rc=.o)
$(TARGET):
	$(CC) -o $@ $(OBJS) $(OBJR) -lgdi32

$(OBJR): $(RESOURCE)
	$(RC) $(RESOURCE) $(OBJR)

all: clean $(OBJS) $(OBJR) $(TARGET)

clean:
	-rm -f $(OBJS) $(TARGET) *.d
