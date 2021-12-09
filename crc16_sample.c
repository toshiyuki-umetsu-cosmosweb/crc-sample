#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "misc_functions.h"
#include "crc16.h"

#if 0
/**
 * CRCを計算する 
 *
 * @param buf CRC32を計算する対象のデータ
 * @param len CRC32を計算する対象の長さ
 * @return CRC32値
 */
uint32_t
crcPT(const uint8_t *buf, size_t len)
{
    uint16_t crc = 0;

    for (uint32_t i = 0u; i < len; i++) {
#if 0
	// Normal.
	crc ^= (uint16_t)(buf[i]) << 8u;
	for (int32_t i = 0; i < 8; i++) {
	    if ((crc & 0x8000) != 0) {
		crc = (uint16_t)((crc << 1) ^ CRC16_BITS);
	    } else {
		crc <<= 1u;
	    }
	}
#elif 0
	// Reverse.
	uint8_t d = swap_ui8(buf[i]);
	crc ^= (uint16_t)(d) << 8u;
	for (int32_t i = 0; i < 8; i++) {
	    if ((crc & 0x8000) != 0) {
		crc = (uint16_t)((crc << 1) ^ CRC16_BITS);
	    } else {
		crc <<= 1u;
	    }
	}
#else
	//uint8_t d = swap_ui8(buf[i]);
	uint8_t d = (buf[i]);
	uint8_t pos = (uint8_t)((crc >> 8) ^ d);
	crc = (uint16_t)((crc << 8u) ^ (uint16_t)(CRCPTTable[pos]));
#endif
    }
    //return swap_ui16(crc);
    return (crc);
}
#endif

static crc16_calculator_t Calculator;

int32_t
main(int32_t ac, char **av)
{
    if (ac <= 1) {
	printf("usage:\n");
	printf("  crc16_sample [options] str1 [str2 [...]]\n");
	printf("options:\n");
	printf("  --initial value# : Specify initial value.\n");
	printf("                     Default is 0x0000.\n");
	printf("  --polynomial polynomial# : Specify polynomial value.\n");
	printf("                             Default is 0x1021.\n");
	printf("  --final_xor_value value# : Specify final XOR value.\n");
	printf("                             Default is 0x0.\n");
	printf("  --input_reflected : Specify input reflected.\n");
	printf("  --result_reflected : Specify result reflected.\n");
	return 0;
    }

    uint16_t initial_value = 0u;
    uint16_t polynomial = 0x1021; // CRC16 CCIT_ZERO
    uint16_t final_xor_value = 0x0;
    bool is_input_reflected = false;
    bool is_result_reflected = false;
    int32_t arg_pos = 1L;
    while (arg_pos < ac) {
	if (av[arg_pos][0L] == '-') {
	    if (strcmp(av[arg_pos], "--initial") == 0) {
		if ((arg_pos + 1L) >= ac) {
		    fprintf(stderr, "Too few arguments for %s.", av[arg_pos]);
		    return EXIT_FAILURE;
		} else {
		    initial_value = (uint16_t)(strtoul(
			    av[arg_pos + 1L], NULL, 0u));
		    arg_pos++;
		}
	    } else if (strcmp(av[arg_pos], "--polynomial") == 0L) {
		if ((arg_pos + 1L) >= ac) {
		    fprintf(stderr, "Too few arguments for %s.", av[arg_pos]);
		    return EXIT_FAILURE;
		} else {
		    polynomial = strtoul(av[arg_pos + 1], NULL, 0);
		    arg_pos++;
		}
	    } else if (strcmp(av[arg_pos], "--final_xor_value") == 0L) {
		if ((arg_pos + 1L) >= ac) {
		    fprintf(stderr, "Too few arguments for %s.", av[arg_pos]);
		} else {
		    final_xor_value = (uint16_t)(strtoul(
			    av[arg_pos + 1L], NULL, 0u));
		    arg_pos++;
		}
	    } else if (strcmp(av[arg_pos], "--input_reflected") == 0L) {
		is_input_reflected = true;
	    } else if (strcmp(av[arg_pos], "--result_reflected") == 0L) {
		is_result_reflected = true;
	    } else {
		fprintf(stderr, "Unknown option %s\n", av[arg_pos]);
		return EXIT_FAILURE;
	    }
	} else {
	    break;
	}
	arg_pos++;
    }
    crc16_calculator_init(&Calculator, initial_value, polynomial,
	    final_xor_value, is_input_reflected, is_result_reflected);

    while (arg_pos < ac) {
	const char *input_str = av[arg_pos];
	size_t len = strlen(input_str);
#if 0
	uint16_t crc = crcPT((const uint8_t*)(input_str), len);
#else
	crc16_calculator_reset(&Calculator);
	uint16_t crc = crc16_calculator_append(&Calculator, input_str, len);

	uint16_t crc_without_lut = crc16_calculate(input_str, len,
		initial_value, polynomial, final_xor_value, 
		is_input_reflected, is_result_reflected);
#endif

	printf("\'%s\' => 0x%04x(UseLut) 0x%04x(UnuseLUT)\n",
		input_str, crc, crc_without_lut);
	arg_pos++;
    }

    return 0;
}
