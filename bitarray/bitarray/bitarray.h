#include <stdio.h>
#include <stdlib.h>
#pragma once


typedef unsigned char byte;


// Хранит size битов, упакованных в байты от старшего к младшему (т.е. сначала добавляется 7-й бит, потом 6-й и т.д.). Поддерживает массив размера capacity байт для избежания перевыделений памяти.

// Неиспользуемые биты заполняются нулями.

struct BitArray {

	byte* data;

	size_t size;

	size_t capacity;

};


// Инициализировать данные нулями до указанной ёмкости

struct BitArray* BitArray_Init(struct BitArray* ba, size_t capacity) {
	ba->data = (byte*)calloc(capacity, sizeof(byte));
	if (ba->data == NULL) {
		return NULL;
	}

	ba->size = 0;
	ba->capacity = capacity;

	
	return ba;
}

// Добавить один байт в конец, возможно перевыделяя память, возвращает текущее количество бит, либо 0, если добавление не удалось

// xxxx xxxx + 1 = 1xxx xxxx (0x80)

// 1xxx xxxx + 0 = 10xx xxxx (0x80)

// 10xx xxxx + 1 = 101x xxxx (0xA0)

size_t BitArray_AddBit(struct BitArray* ba, byte data) {
	if (ba == NULL || ba->data == NULL) {
		return 0;
	}
	if (ba->size >= ba->capacity *8 ) {
		size_t new_capacity = ba->capacity * 2;
		byte* new_data = (byte*)realloc(ba->data, new_capacity);
		if (new_data == NULL) {
			return ba->size;
		}
		ba->data = new_data; 
			ba->capacity = new_capacity;
			memset(ba->data + ba->capacity / 2, 0, ba->capacity / 2);
	}
	size_t index = ba->size / 8;
	size_t bit_index = ba->size % 8;
	ba->data[index] |= (data & 0x01) << (7 - bit_index);
	ba->size++;
	return ba->size;

}


// Добавить в конец n_bits битов из data, возможно перевыделяя память, возвращает текущее количество бит, либо 0, если добавление не удалось

// xxxx xxxx + 101x xxxx = 101x xxxx

// 101x xxxx + 01xx xxxx = 1010 1xxx

// 1010 1xxx + 1xxx xxxx = 1010 11xx

// 1010 11xx + 101x xxxx = 1010 1110 1xxx

size_t BitArray_AddBits(struct BitArray* ba, byte* data, size_t n_bits) {
	for (size_t i = 0; i < n_bits; i++) {
		if (BitArray_AddBit(ba, (data[i / 8] >> (7 - i % 8)) & 0x01) == 0) {
			return 0;
		}
	}
	return ba->size;

}


// Вернуть количество хранимых бит

size_t BitArray_GetSize(struct BitArray* ba) {
	if (ba == NULL || ba->size == 0) {
		return NULL;
	}
	return ba->size;
}


// Получить указатель на данные, NULL если структура не валидна; указатель валиден до следующего вызова AddBit/AddBits

byte* BitArray_GetData(struct BitArray* ba) {
	if (ba == NULL || ba->data == NULL) {
		return NULL;
	}
	return ba->data;
}


// Сбросить данные, возвращает NULL если не удалось выделить память для нового хранилища

struct BitArray* BitArray_Reset(struct BitArray* ba) {
	memset(ba->data, 0, ba->capacity);
	ba->size = 0;
	return ba;
}



// Освободить структуру

void BitArray_Destroy(struct BitArray* ba){
	free(ba->data);
	ba->data = NULL;
	ba->size = 0;
	ba->capacity = 0;
}