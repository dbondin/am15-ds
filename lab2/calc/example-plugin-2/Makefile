CC=gcc
LD=g++
CXX=g++

TARGET=libexample-plugin-2.so

OBJS=calc.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) --shared $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) -fPIC -c $^

%.o: %.cpp
	$(CXX) -fPIC -c $^

clean:
	rm -rf $(TARGET) $(OBJS)
