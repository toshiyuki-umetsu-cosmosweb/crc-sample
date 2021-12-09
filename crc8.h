#ifndef CRC8_H
#define CRC8_H

/*
 * CRC-8  Calculation sample.
 * 
 * Refer : http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

struct crc8_calculator {
    uint8_t initial_value; // Initial value.
    uint8_t final_xor_value; // Final XOR value.
    uint8_t polynomial; // Generator polinomial.
    uint8_t table[256]; // LUT table.
    uint8_t crc; // CRC code.
    bool is_input_reflected; // Swap MSB from LSB of input data.
    bool is_result_reflected; // Swap MSB from LSB of result CRC.
};

typedef struct crc8_calculator crc8_calculator_t;

#ifdef __cplusplus
extern "C" {
#endif

// Use LUT functions.
void crc8_calculator_init(crc8_calculator_t *calculator,
        uint8_t initial_value, uint8_t polinomial, uint8_t final_xor_value,
        bool is_input_reflected, bool is_result_reflected);
void crc8_calculator_reset(crc8_calculator_t *calculator);
uint8_t crc8_calculator_append(crc8_calculator_t *calculator,
        const void *data, size_t len);
uint8_t crc8_calculator_get(const crc8_calculator_t *calculator);

// Unuse LUT function.
uint8_t crc8_calculate(const void *data, size_t len,
        uint8_t initial_value, uint8_t polynomial,
        uint8_t final_xor_value, bool is_input_reflected,
        bool is_result_reflected);

#ifdef __cplusplus
}
#endif


#endif /* CRC8_H */
