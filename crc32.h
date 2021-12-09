#ifndef CRC32_H
#define CRC32_H

/*
 * CRC-32  Calculation sample.
 * 
 * Refer : http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

struct crc32_calculator {
    uint32_t initial_value; // Initial value.
    uint32_t final_xor_value; // Final XOR value.
    uint32_t polynomial; // Generator polinomial.
    uint32_t table[256]; // LUT table.
    uint32_t crc; // CRC code.
    bool is_input_reflected; // Swap MSB from LSB of input data.
    bool is_result_reflected; // Swap MSB from LSB of result CRC.
};

typedef struct crc32_calculator crc32_calculator_t;

#ifdef __cplusplus
extern "C" {
#endif

// Use LUT functions.
void crc32_calculator_init(crc32_calculator_t *calculator,
        uint32_t initial_value, uint32_t polinomial, uint32_t final_xor_value,
        bool is_input_reflected, bool is_result_reflected);
void crc32_calculator_reset(crc32_calculator_t *calculator);
uint32_t crc32_calculator_append(crc32_calculator_t *calculator,
        const void *data, size_t len);
uint32_t crc32_calculator_get(const crc32_calculator_t *calculator);

// Unuse LUT function.
uint32_t crc32_calculate(const void *data, size_t len,
        uint32_t initial_value, uint32_t polynomial,
        uint32_t final_xor_value, bool is_input_reflected,
        bool is_result_reflected);

#ifdef __cplusplus
}
#endif


#endif /* CRC32_H */
