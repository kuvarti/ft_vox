run:
	@cmake --build build 1>/dev/null
	@./build/bin/Ft_vox

build: install
	@cmake -B build -S .

install:
	@sh ./install.sh

clean:
	rm -rf build

fclean: clean
	rm -rf libs

re: clean build run