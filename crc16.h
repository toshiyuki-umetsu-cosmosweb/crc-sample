#ifndef CRC16_H
#define CRC16_H

/*
 * CRC-16  Calculation sample.
 * 
 * Refer : http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

struct crc16_calculator {
    uint16_t initial_value; // Initial value.
    uint16_t final_xor_value; // Final XOR value.
    uint16_t polynomial; // Generator polinomial.
    uint16_t table[256]; // LUT table.
    uint16_t crc; // CRC code.
    bool is_input_reflected; // Swap MSB from LSB of input data.
    bool is_result_reflected; // Swap MSB from LSB of result CRC.
};

typedef struct crc16_calculator crc16_calculator_t;

#ifdef __cplusplus
extern "C" {
#endif

// Use LUT functions.
void crc16_calculator_init(crc16_calculator_t *calculator,
        uint16_t initial_value, uint16_t polinomial, uint16_t final_xor_value,
        bool is_input_reflected, bool is_result_reflected);
void crc16_calculator_reset(crc16_calculator_t *calculator);
uint16_t crc16_calculator_append(crc16_calculator_t *calculator,
        const void *data, size_t len);
uint16_t crc16_calculator_get(const crc16_calculator_t *calculator);

// Unuse LUT function.
uint16_t crc16_calculate(const void *data, size_t len,
        uint16_t initial_value, uint16_t polynomial,
        uint16_t final_xor_value, bool is_input_reflected,
        bool is_result_reflected);

#ifdef __cplusplus
}
#endif


#endif /* CRC16_H */
