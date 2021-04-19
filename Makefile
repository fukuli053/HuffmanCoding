
INC="./include"
LIB="./lib"
TARGET=main

all: $(TARGET)


$(TARGET): ./lib/libfdr.a $(TARGET).c
	gcc -I$(INC) $(TARGET).c -o $@ -L$(LIB) -lfdr

clean:
	rm -rf $(TARGET)
