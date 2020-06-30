CXX=g++ -std=c++11
CFLAGS=
SRCS=main.cpp

TARGET=cache-sim

OBJS :=$(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET) 

%.o:%.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(TARGET): $(OBJS)
	  $(CXX) $(CFALGS) $^ -o $@

.PHONY=clean
.PHONY=run

run: $(TARGET) 
	     ./$(TARGET) $(ARGS)


clean:
	rm -f $(OBJS) $(TARGET)


