#include <stdlib.h>
#include <string.h>
#pragma once
typedef unsigned char byte;


struct ByteArray {

	byte* data;

	size_t size;

	size_t capacity;

};

// ���������������� ������ ������ �� ��������� �������
struct ByteArray* ByteArray_Init(struct ByteArray* ba, size_t capacity) {
    ba->data = (byte*)calloc(capacity, sizeof(byte));
    if (ba->data == NULL) {
        return NULL;
    }

    ba->size = 0;
    ba->capacity = capacity;

    return ba;
}
// �������� ���� ���� � �����, �������� ����������� ������, ���������� ������� ���������� ����, ���� 0, ���� ���������� �� �������
size_t ByteArray_AddByte(struct ByteArray* ba, byte b) {
    if (ba == NULL || ba->data == NULL) {
        return 0;
    }

    if (ba->size >= ba->capacity) {
       
        byte* new_data = (byte*)realloc(ba->data, 2 * ba->capacity * sizeof(byte));
        if (new_data == NULL) {
            return 0;
        }

        ba->data = new_data;
        ba->capacity *= 2;
    }

    ba->data[ba->size++] = b;
    return ba->size;
}
// �������� ����� ����, �������� ����������� ������, ���������� ������� ���������� ����, ���� 0, ���� ���������� �� �������
size_t ByteArray_AddBytes(struct ByteArray* ba, const byte* bytes, size_t data_len) {
    while (ba->size + data_len > ba->capacity) {
        size_t new_capacity = ba->capacity * 2;
        byte* new_data = (byte*)realloc(ba->data, new_capacity);
        if (new_data == NULL) {
            return 0;
        }
        ba->data = new_data;
        ba->capacity = new_capacity;
    }
    memcpy(ba->data + ba->size, bytes, data_len);
    ba->size += data_len;
    return ba->size;
}
// �������� ��������� �� ������, NULL ���� ��������� �� �������; ��������� ������� �� ���������� ������
byte* ByteArray_GetData(struct ByteArray* ba) {
    if (ba == NULL || ba->data == NULL) {
        return NULL;
    }
    return ba->data;
}
// �������� ������, ���������� NULL ���� �� ������� �������� ������ ��� ������ ���������
struct ByteArray* ByteArray_Reset(struct ByteArray* ba) {
    if (ba == NULL) {
        return NULL;
    }
    ba->size = 0;
    return ba;
}
// ���������� ���������
void ByteArray_Destroy(struct ByteArray* ba) {
    if (ba == NULL) {
        return;
    }
    free(ba->data);
    ba->data = NULL;
    ba->size = 0;
    ba->capacity = 0;
}