CC=gcc
LD=g++
CXX=g++

TARGET=libexample-plugin-2.so

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
