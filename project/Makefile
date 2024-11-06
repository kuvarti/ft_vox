run: build
	@mkdir -p build
	@cmake --build build
	@./build/bin/Ft_vox ./settings

build:
	@cmake -DCMAKE_BUILD_TYPE=Debug -B build -S .

install:
	@sh ./install.sh

clear:
	rm -rf build

fclean: clear
	rm -rf libs

re: clear build run
