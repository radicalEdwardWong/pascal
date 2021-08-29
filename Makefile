CPPGNU = g++ -std=c++0x

SOURCE = src/

TARGET = list

all: $(TARGET)

rebuild: all

$(TARGET) :
	$(CPPGNU) $(SOURCE)$(TARGET).cpp -o $(TARGET)

clean :
	-rm -f $(TARGET)
