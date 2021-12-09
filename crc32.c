#include "misc_functions.h"
#include "crc32.h"

static void generate_crc_table(crc32_calculator_t *calculator);

// Use LUT functions.
/**
 * Initialize CRC calculator.
 * This function use for using LUT.
 *
 * @param calculator CRC calculator object.
 * @param initial_value Initial value.
 * @param polynomial Generator polynomial.
 *                  ex) 'x32 + x8 + x3 + 1' indicate 0x0109.
 * @param final_xor_value Final XOR value.
 * @param is_input_reflected Swap LSB from MSB of input byte.
 * @param is_result_reflected Swap LSB from MSB of input byte.
 */
void
crc32_calculator_init(crc32_calculator_t *calculator,
        uint32_t initial_value, uint32_t polynomial, uint32_t final_xor_value,
        bool is_input_reflected, bool is_result_reflected)
{
    if (calculator != NULL) {
        (*calculator).initial_value = initial_value;
        (*calculator).polynomial = polynomial;
        (*calculator).final_xor_value = final_xor_value;
        (*calculator).is_input_reflected = is_input_reflected;
        (*calculator).is_result_reflected = is_result_reflected;
        generate_crc_table(calculator);
        crc32_calculator_reset(calculator);
    }

    return ;
}

/**
 * Generate CRC calculation table.
 */
static void
generate_crc_table(crc32_calculator_t *calculator)
{
    for (uint32_t divident = 0u; divident < 256u; divident++) {
        uint32_t value = (uint32_t)(divident) << 24u;
        for (uint32_t bit = 0u; bit < 8u; bit++) {
            if ((value & 0x80000000) != 0u) {
                value <<= 1u;
                value ^= (*calculator).polynomial;
            } else {
                value <<= 1u;
            }
        }
        calculator->table[divident] = value;
    }

    return ;
}
/**
 * Reset calculation.
 * This function reset crc value to initial value.
 *
 * @param calculator CRC calculator object.
 */
void
crc32_calculator_reset(crc32_calculator_t *calculator)
{
    if (calculator != NULL) {
        calculator->crc = calculator->initial_value;
    }

    return ;
}
/**
 * Calculate CRC value.
 *
 * @param calculator CRC calculator object.
 * @param data Target data.
 * @param len Length in bytes of data.
 * @return Current result returned. (same as crc32_calculator_get())
 */
uint32_t
crc32_calculator_append(crc32_calculator_t *calculator, const void *data, size_t len)
{
    if ((data != NULL) && (len > 0)) {
        const uint8_t *input_data = (const uint8_t*)(data);
        for (uint32_t n = 0u; n < len; n++) {
            uint32_t crc = (*calculator).crc;
            uint8_t d = (*calculator).is_input_reflected
                    ? swap_ui8(input_data[n]) : input_data[n];
            uint8_t pos = (uint8_t)(((crc >> 24u) ^ d) & 0xFFu);
            (*calculator).crc = (crc << 8u) ^ (*calculator).table[pos];
        }
    }

    return crc32_calculator_get(calculator);
}
/**
 * Get CRC result.
 *
 * @param calculator CRC calculator object.
 * @return CRC result.
 */
uint32_t
crc32_calculator_get(const crc32_calculator_t *calculator)
{
    uint32_t retval;

    if (calculator != NULL) {
        uint32_t  value = (*calculator).crc ^ (*calculator).final_xor_value;
        if ((*calculator).is_result_reflected) {
            retval = swap_ui32(value);
        } else {
            retval = value;
        }
    } else {
        retval = 0u;
    }

    return retval;
}

/**
 * Calculate CRC value.
 *
 * @param data Target data.
 * @param len Length in bytes of data.
 * @param initial_value Initial value.
 * @param polynomial Generator polynomial.
 *                  ex) 'x32 + x8 + x3 + 1' indicate 0x0109.
 * @param final_xor_value Final XOR value.
 * @param is_input_reflected Swap LSB from MSB of input byte.
 * @param is_result_reflected Swap LSB from MSB of input byte.
 * @return CRC result.
 */
uint32_t
crc32_calculate(const void *data, size_t len,
        uint32_t initial_value, uint32_t polynomial,
        uint32_t final_xor_value, bool is_input_reflected,
        bool is_result_reflected)
{
    uint32_t crc = initial_value;

    if ((data != NULL) && (len > 0u)) {
        const uint8_t *input_data = (const uint8_t*)(data);

        for (uint32_t n = 0u; n < len; n++) {
            uint8_t d = (is_input_reflected)
                    ? swap_ui8(input_data[n]) : input_data[n];
            crc ^= (uint32_t)(d) << 24u;
            for (int32_t bit = 0u; bit < 8u; bit++) {
                if ((crc & 0x80000000u) != 0u) {
                    crc = (crc << 1u) ^ polynomial;
                } else {
                    crc <<= 1u;
                }
            }
        }
    }

    crc ^= final_xor_value;

    if (is_result_reflected) {
        crc = swap_ui32(crc);
    }

    return crc;
}

