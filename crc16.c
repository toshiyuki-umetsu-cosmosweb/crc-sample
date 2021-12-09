#include "crc16.h"

// Use LUT functions.
void crc16_calculator_init(crc16_calculator_t *calculator,
	uint16_t initial_value, uint16_t polinomial, bool is_input_reflected,
	bool is_result_reflected);
void crc16_calculator_reset(crc16_calculator_t *calculator);
uint16_t crc16_calculator_append(const void *data, size_t len);
uint16_t crc16_calculator_get(const crc16_calculator_t *calculator);

// Unuse LUT function.
uint16_t crc16_calculate(uint16_t initial_value, uint16_t polinomial,
	bool is_input_reflected, bool is_result_reflected);

