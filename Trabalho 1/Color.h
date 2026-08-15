#ifndef COLOR_H
#define COLOR_H

#include <cmath>
#include <algorithm>
#include "vec.h"

using Byte = unsigned char;

template<size_t N>
struct Color{ 
	Byte data[N];

	// construtor padrão
	Color() = default; 

	// construtor a partir de uma lista de bytes
	Color(std::initializer_list<Byte> input){ 
		std::copy_n(input.begin(), N, data);
	}

	// construtor a partir de um inteiro
	Color(unsigned long u){
		for(size_t i = 0; i < N; i++){
			data[N-1-i] = (Byte)u;
			u >>= 8;
		}
	}

	// construtor a partir de um vec
	Color(const Vec<N>& vec){
		for(size_t i = 0; i < N; i++)
			data[i] = std::roundf(255*std::clamp(vec[i], 0.0f, 1.0f));
	}

	// operator de conversão de Color para vec
	operator Vec<N>() const{
		Vec<N> vec;
		for(size_t i = 0; i < N; i++)
			vec[i] = data[i]/255.0f;
		return vec;
	}
};
using RGB  = Color<3>;
using RGBA = Color<4>;

const vec3 red     = RGB(0xff0000);
const vec3 white   = RGB(0xffffff);
const vec3 green   = RGB(0x00ff00);
const vec3 blue    = RGB(0x0000ff);
const vec3 black   = RGB(0x000000);
const vec3 cyan    = RGB(0x00ffff);
const vec3 yellow  = RGB(0xffff00);
const vec3 magenta = RGB(0xff00ff);
const vec3 gray    = RGB(0x808080);
const vec3 orange  = RGB(0xffa500);
const vec3 purple  = RGB(0x800080);
const vec3 brown   = RGB(0xa08060);

#endif
