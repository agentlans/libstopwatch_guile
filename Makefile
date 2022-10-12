GUILE_FLAGS=`pkg-config --cflags --libs guile-3.0`
EXTENSIONS_DIR=`pkg-config guile-3.0 --variable=extensiondir`
SITE_DIR=`guile -c '(display (%site-dir))'`

.PHONY: all clean install

all: libstopwatch_guile.so

libstopwatch_guile.so: libstopwatch.o
	$(CXX) -shared $^ -o $@ $(GUILE_FLAGS)

libstopwatch.o: Stopwatch.cpp Stopwatch.hpp stopwatch.h
	$(CXX) -c -fPIC Stopwatch.cpp -o $@ $(GUILE_FLAGS)

install: libstopwatch_guile.so stopwatch.scm
	cp $^ $(EXTENSIONS_DIR)
	mkdir -p $(SITE_DIR)/extra
	cp stopwatch.scm $(SITE_DIR)/extra

uninstall:
	rm -f $(EXTENSIONS_DIR)/libstopwatch_guile.so
	rm -f $(SITE_DIR)/extra/stopwatch.scm

clean:
	rm -f *.o *.so example
