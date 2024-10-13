CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
LDFLAGS = -lcryptopp

SRCS = main.cpp password_manager.cpp crypto_utils.cpp file_utils.cpp input_utils.cpp logger.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = password_manager

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

