TARGET = itree
SRCS = src/*.c
INCLUDES = include/
OBJS = *.o

INSTALL = /usr/bin/install -c -D
BIN_DIR = /bin

CC := gcc
CXX := gcc
CXXFLAGS := -g -Wall -Wextra --pedantic-errors
CCFLAGS += -g -Wall -Wextra --pedantic-errors

all: $(TARGET)

$(OBJS): $(SRCS)
	for SRC in $(SRCS); do \
		$(CC) $(CCFLAGS) -c $$SRC -I $(INCLUDES); \
	done

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

install: $(TARGET)
	@echo "Installing $(BIN_DIR)/$(TARGET) ..."
	$(INSTALL) $(TARGET) "$(BIN_DIR)/$(TARGET)"

clean:
	rm -f $(OBJS) $(TARGET)
