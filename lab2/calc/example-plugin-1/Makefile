CC=gcc
LD=gcc
CXX=g++

TARGET=libexample-plugin-1.so

OBJS=calc.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) --shared $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) -DPIC -c $^
	
%.o: %.cpp
	$(CXX) -DPIC -c $^

clean:
	rm -rf $(TARGET) $(OBJS)
