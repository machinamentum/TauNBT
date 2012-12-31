TARGET=libtaunbt.a
OBJS= \
	src/NBTTag.o \
	src/NBTStream.o \
	src/NBTInputStream.o \
	src/NBTOutputStream.o

SRC=$(OBJS:.o=.cpp)
LIBS=
LIB_DIR=lib
INC_DIR= -Iinclude

CC=g++
AR=ar
LD=$(CC)
CXXFLAGS=-std=c++11 -stdlib=libstdc++ -g $(INC_DIR)


$(TARGET):$(OBJS)
	$(AR) -r $@ $^

%.o: %.c
	$(CC) $(INC_DIR) -o $@ -c $(CXXFLAGS) $<


clean:
	rm -Rf $(TARGET) $(OBJS)
