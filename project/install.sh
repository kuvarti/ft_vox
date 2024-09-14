#!/bin/bash

# Bu script Linux, macOS ve WSL altında SDL2, Vulkan, GLM gibi kütüphaneleri indirip kurar.

# Sistemi tespit etme
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
	OS_NAME=$(cat /etc/os-release | grep ^NAME | awk -F= '{print $2}' | tr -d '"')
	
	if [[ "$OS_NAME" == "Arch Linux" ]]; then
		OS="Arch"
	elif [[ "$OS_NAME" == "Ubuntu" ]]; then
		OS="Ubuntu"
	else
		OS="Linux"
	fi
elif [[ "$OSTYPE" == "darwin"* ]]; then
	OS="macOS"
elif [[ "$OSTYPE" == "cygwin" || "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
	OS="Ubuntu"
else
	echo "Desteklenmeyen işletim sistemi: $OSTYPE"
	exit 1
fi

echo "Sistem tespit edildi: $OS"

# SDL2'yi kurma
install_sdl2() {
	echo "SDL2'yi indirip kuruyoruz..."
	if [[ "$OS" == "Arch" ]]; then
		sudo pacman -S --noconfirm sdl2
	elif [[ "$OS" == "macOS" ]]; then
		brew install sdl2
	elif [[ "$OS" == "Ubuntu" ]]; then
		sudo apt update
		sudo apt install -y libsdl2-dev
	fi
}

# Vulkan SDK kurulumu
install_vulkan() {
	echo "Vulkan SDK kurulumu yapılıyor..."
	if [[ "$OS" == "Arch" ]]; then
		sudo pacman -S --noconfirm vulkan-devel vulkan-icd-loader
	elif [[ "$OS" == "macOS" ]]; then
		# Vulkan macOS için MoltenVK kullanılıyor
		brew install molten-vk
	elif [[ "$OS" == "Ubuntu" ]]; then
		sudo apt install -y vulkan-sdk
	fi
}

# GLM (C++ matematik kütüphanesi) kurulumu
install_glm() {
	echo "GLM kütüphanesi indiriliyor..."
	if [[ ! -d "libs" ]]; then
		mkdir libs
	fi

	git clone https://github.com/g-truc/glm.git libs/glm
}

# CMake kurulumu (projeyi yapılandırmak için)
install_cmake() {
	echo "CMake kuruluyor..."
	if [[ "$OS" == "Arch" ]]; then
		sudo pacman -S --noconfirm cmake
	elif [[ "$OS" == "macOS" ]]; then
		brew install cmake
	elif [[ "$OS" == "Ubuntu" ]]; then
		sudo apt install -y cmake
	fi
}

# SDL2'yi kur
install_sdl2

# Vulkan SDK'yı kur
install_vulkan

# GLM matematik kütüphanesini kur
install_glm

# CMake kurulumunu yap
install_cmake

echo "Tüm kütüphaneler başarıyla kuruldu."
