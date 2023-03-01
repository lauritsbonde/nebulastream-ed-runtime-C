.SILENT: build clean

main:    #target name
	make clean
	mkdir build
	gcc ./src/*.c -o ./build/EDRuntime -Wall
	echo "Build to build folder"

buildAndRun: 
	make main
	./build/EDRuntime

buildAndRunLogs: 
	make main
	./build/EDRuntime log

buildAndTest: 
	echo "Not implemented"

clean:
	rm -rf build
	echo "Cleaned!"