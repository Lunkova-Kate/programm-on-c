#include "bitarray.h"
#include <assert.h>
void Test_BitArray() {

	// start

	struct BitArray ba;

	assert(BitArray_Init(&ba, 16) != NULL);


	// 1

	byte* data = BitArray_GetData(&ba);

	assert(data[0] == 0);


	// 2 - AddBit

	{

		assert(BitArray_AddBit(&ba, 0x1) == 1);

		data = BitArray_GetData(&ba);

		assert(data[0] == 0x80);


		assert(BitArray_AddBit(&ba, 0x0) == 2);

		data = BitArray_GetData(&ba);

		assert(data[0] == 0x80);


		assert(BitArray_AddBit(&ba, 0x1) == 3);

		data = BitArray_GetData(&ba);

		assert(data[0] == 0xA0);


		assert(BitArray_Reset(&ba) == &ba);

	}


	// 3 - AddBit several

	{

		for (size_t i = 0; i < 26; i++) {

			assert(BitArray_AddBit(&ba, 0x01) == i + 1);

		}


		byte expected_result[] = { 0xFF, 0xFF, 0xFF, 0xC0 };

		assert(BitArray_GetSize(&ba) == 26);

		data = BitArray_GetData(&ba);

		assert(memcmp(expected_result, data, sizeof(expected_result)) == 0);

		assert(BitArray_Reset(&ba) == &ba);

	}


	// 4 - AddBytes - multiple

	{

		byte samples[] = { 0b10100000, 0b01000000, 0b10000000, 0b10100000 };

		assert(BitArray_AddBits(&ba, &samples[0], 3) == 3);

		assert(BitArray_AddBits(&ba, &samples[1], 2) == 5);

		assert(BitArray_AddBits(&ba, &samples[2], 1) == 6);

		assert(BitArray_AddBits(&ba, &samples[3], 3) == 9);


		data = BitArray_GetData(&ba);

		byte expected[] = { 0b10101110, 0b10000000 };

		assert(memcmp(expected, data, sizeof(expected)) == 0);


		assert(BitArray_Reset(&ba) == &ba);

	}


	// 5 - AddBytes with byte border change

	{

		byte payload[] = { 0b11111111, 0b11110000 };

		size_t size = 8 + 4;

		assert(BitArray_AddBits(&ba, payload, size) == size);

		data = BitArray_GetData(&ba);

		assert(memcmp(payload, data, sizeof(payload)) == 0);


		byte payload2[] = { 0b10101010 };

		size_t size2 = 8;

		assert(BitArray_AddBits(&ba, payload2, size2) == size + size2);

		byte final_result[] = { 0b11111111, 0b11111010, 0b10100000 };

		data = BitArray_GetData(&ba);

		assert(memcmp(final_result, data, sizeof(final_result)) == 0);

	}


	// finish

	BitArray_Destroy(&ba);

}

int main() {

	Test_BitArray();
	return 0;
}