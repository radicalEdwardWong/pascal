CPPGNU = g++ -std=c++0x

SOURCE = src/

TARGET = compact

all: $(TARGET)

rebuild: all

$(TARGET) :
	$(CPPGNU) $(SOURCE)*.cpp -o $(TARGET)

clean :
	-rm -f $(TARGET)
