CPPGNU = g++ -std=c++0x

SOURCE = src/

TARGET = list

all: $(TARGET)

rebuild: all

$(TARGET) :
	$(CPPGNU) $(SOURCE)*.cpp -o $(TARGET)

clean :
	-rm -f $(TARGET)
