#ifndef PID_UTILS_INCLUDED
#define PID_UTILS_INCLUDED

#include <iostream>
#include <array>

namespace pid
{
//RED
//21 64 107 150 192 234
//43 85 128 171 213 255
const std::array<uint8_t,6> __red = {
	43, 85, 128, 171, 213, 255
};

//GREEN
//18  55  92 128 238 201 237
//37 73 110 146 183 219 255
const std::array<uint8_t,7> __green = {
	37, 73, 110, 146, 183, 219, 255
};

//BLUE
//21 64 107 150 192 234
//43 85 128 171 213 255
const std::array<uint8_t,6> __blue = {
	43, 85, 128, 171, 213, 255
};

/* Get the color pallet index for given color
* @param r The red channel value
* @param g The green channel value
* @param b The blue channel value
* @return The index of the color in the pallet
*/
uint8_t getColorIndex(uint8_t r, uint8_t g, uint8_t b);
} // namespace pid


#endif
