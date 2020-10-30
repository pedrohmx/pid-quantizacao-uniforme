#include <iostream>
#include <array>

#include "pid_utils.hpp"

namespace pid{

uint8_t getColorIndex(uint8_t r, uint8_t g, uint8_t b){
	uint8_t r_index = 0;
	uint8_t g_index = 0;
	uint8_t b_index = 0;

	while (r > __red[r_index]){
		r_index++;
	}

	while (g > __green[g_index]){
		g_index++;
	}

	while (b > __blue[b_index]){
		b_index++;
	}

	uint8_t c_index = 0;

	c_index = b_index + g_index * 6 + r_index * 7 * 6;

	// std::cout << 
	// 	"r index: " << static_cast<uint32_t>(r_index) << std::endl <<
	// 	"g index: " << static_cast<uint32_t>(g_index) << std::endl <<
	// 	"b index: " << static_cast<uint32_t>(b_index) << std::endl <<
	// 	"c index: " << static_cast<uint32_t>(c_index) << std::endl;

	return c_index;
}

}//Namespace pid
