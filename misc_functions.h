#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t swap_ui8(uint8_t byte);
uint16_t swap_ui16(uint16_t word);
uint32_t swap_ui32(uint32_t dword);

#ifdef __cplusplus
}
#endif


#endif /* MISC_FUNCTIONS_H */
