.SILENT: build clean

main:    #target name
	make clean
	mkdir build
	gcc -I/opt/homebrew/Cellar/protobuf-c/1.4.1_1/include -L/opt/homebrew/Cellar/protobuf-c/1.4.1_1/lib -lprotobuf-c ./src/*/*.c ./src/*.c -o ./build/EDRuntime -Wall
	echo "Build to build folder"

# main:    #target name
# 	make clean
# 	mkdir build
# 	gcc -I/opt/homebrew/Cellar/protobuf-c/1.4.1_1/include -L/opt/homebrew/Cellar/protobuf-c/1.4.1_1/lib -lprotobuf-c ./src/*/*.c ./src/*.c -o ./build/EDRuntime -Wall
# 	echo "Build to build folder"

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

mainTest:    #target name
	rm -rf testBuild
	mkdir testBuild
	gcc  -I/opt/homebrew/Cellar/protobuf-c/1.4.1_1/include -L/opt/homebrew/Cellar/protobuf-c/1.4.1_1/lib -lprotobuf-c ./prototest/*.c -o ./testBuild/EDRuntime -Wall
	echo "Build to testBuild folder"

buildAndRunTest: 
	make mainTest
	./testBuild/EDRuntime ulla