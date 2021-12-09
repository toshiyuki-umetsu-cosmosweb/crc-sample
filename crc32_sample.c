#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "misc_functions.h"
#include "crc32.h"

// CRC calculator object.
// Allocate at static RAM in this sample.
static crc32_calculator_t Calculator;

int32_t
main(int32_t ac, char **av)
{
    if (ac <= 1) {
        printf("usage:\n");
        printf("  crc32_sample [options] str1 [str2 [...]]\n");
        printf("options:\n");
        printf("  --initial value# : Specify initial value.\n");
        printf("                     Default is 0xFFFFFFFF.\n");
        printf("  --polynomial polynomial# : Specify polynomial value.\n");
        printf("                             Default is 0x4C11DB7.\n");
        printf("  --final_xor_value value# : Specify final XOR value.\n");
        printf("                             Default is 0xFFFFFFFF.\n");
        printf("  --input_reflected : Specify input reflected.\n");
        printf("  --result_reflected : Specify result reflected.\n");
        return 0;
    }

    // Parse arguments.
    uint32_t initial_value = 0xFFFFFFFFu;
    uint32_t polynomial = 0x4C11DB7u; // CRC32
    uint32_t final_xor_value = 0xFFFFFFFFu;
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
                    initial_value = (uint32_t)(strtoul(
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
                    final_xor_value = (uint32_t)(strtoul(
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
    crc32_calculator_init(&Calculator, initial_value, polynomial,
            final_xor_value, is_input_reflected, is_result_reflected);

    // Calcuating sample.
    while (arg_pos < ac) {
        const char *input_str = av[arg_pos];
        size_t len = strlen(input_str);

        // Reset calcuation value.
        crc32_calculator_reset(&Calculator);
        // Calculate
        uint32_t crc = crc32_calculator_append(&Calculator, input_str, len);
        uint32_t crc_without_lut = crc32_calculate(input_str, len,
                initial_value, polynomial, final_xor_value, 
                is_input_reflected, is_result_reflected);

        // Print results.
        printf("\'%s\' => 0x%08x(UseLut) 0x%08x(UnuseLUT)\n",
                input_str, crc, crc_without_lut);
        arg_pos++;
    }

    return 0;
}
