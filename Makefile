.SILENT: build clean
build:    #target name
	mkdir -p build
	gcc -o ./build/main ./src/main.c
	echo "Buil to build folder"

buildAndRun: 
	make build
	./build/main

buildAndTest: 
	echo "Not implemented"

clean:
	rm -r build
	echo "Cleaned!"