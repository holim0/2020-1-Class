CXX=g++
CFLAGS=
SRCS=main.cpp

TARGET=mips_sim

OBJS :=$(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)

%.o:%.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(TARGET): $(OBJS)
	  $(CXX) $(CFALGS) $^ -o $@

.PHONY=clean
.PHONY=run

run: $(TARGET)
	     ./$(TARGET)


clean:
	rm -f $(OBJS) $(TARGET)


