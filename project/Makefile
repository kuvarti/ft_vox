run: build
	@cmake --build build
	@./build/bin/Ft_vox

build:
	@cmake -DCMAKE_BUILD_TYPE=Debug -B build -S .

install:
	@sh ./install.sh

clean:
	rm -rf build

fclean: clean
	rm -rf libs

re: clean build run