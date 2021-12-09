#include "misc_functions.h"

/**
 * Swap LSB to MSB of input value.
 *
 * @param byte Input data.
 * @return Swapped data.
 */
uint8_t
swap_ui8(uint8_t byte)
{
    uint8_t ret = 0u;

    for (uint32_t bit = 0u; bit < 8u; bit++) {
	if ((byte & (1u << bit)) != 0u) {
	    ret |= (1u << (7u - bit));
	}
    }
    return ret;
}
/**
 * Swap LSB to MSB of input value.
 *
 * @param word Input data.
 * @return Swapped data.
 */
uint16_t
swap_ui16(uint16_t word)
{
    uint16_t ret = 0u;

    for (uint32_t bit = 0u; bit < 16u; bit++) {
	if ((word & (1u << bit)) != 0u) {
	    ret |= (1u << (15u - bit));
	}
    }
    return ret;
}
/**
 * Swap LSB to MSB of input value.
 *
 * @param dword Input data.
 * @return Swapped data.
 */
uint32_t
swap_ui32(uint32_t dword)
{
    uint32_t ret = 0u;

    for (uint32_t bit = 0u; bit < 32u; bit++) {
	if ((dword & (1u << bit)) != 0u) {
	    ret |= (1u << (31u - bit));
	}
    }
    return ret;
}
