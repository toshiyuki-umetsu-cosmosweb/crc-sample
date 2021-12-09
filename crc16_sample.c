#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "misc_functions.h"

#define USE_REVERSE_CALC (1u)

static const uint16_t CRC16_BITS = 0x1021;
//static const uint16_t CRC16_BITS = 0x8408;

/**
 * CRC16 �v�Z�p�e�[�u���B
 *     CRC�X�V���A���݂�CRC�l�̉���8bit�ƍX�V�p�f�[�^�ɂ�茈�܂�萔�Ƃ̉��Z�ɒu����������̂�
 *     256�G���g���̃e�[�u���ɒu���ł���B
 */
static uint16_t CRCPTTable[256u];

static void
make_CRC_LUT(void)
{
    for (uint32_t i = 0u; i < 256u; i++) {
	uint8_t d = i;
	uint16_t crc = (uint16_t)(d) << 8u;
	for (uint32_t bit = 0; bit < 8u; bit++) {
	    if ((crc & 0x8000) != 0u) {
		crc <<= 1;
		crc ^= CRC16_BITS;
	    } else {
		crc <<= 1;
	    }
	}
	printf("[%d]=%04x\n", i, crc);
	CRCPTTable[i] = crc;
    }


    return ;
}


/**
 * CRC���v�Z���� 
 *
 * @param buf CRC32���v�Z����Ώۂ̃f�[�^
 * @param len CRC32���v�Z����Ώۂ̒���
 * @return CRC32�l
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

int32_t
main(int32_t ac, char **av)
{
    make_CRC_LUT();

    for (int32_t i = 1; i < ac; i++) {
	const char *input_str = av[i];
	size_t len = strlen(input_str);
	uint16_t crc = crcPT((const uint8_t*)(input_str), len);

	printf("\'%s\' => 0x%04x\n", input_str, crc);
    }

    return 0;
}
