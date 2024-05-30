#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
//#include <Windows.h>

int is_number(const char* str) {
    // ���������, �������� �� ������ ������
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            printf("������������ ����");
        }
    }
    ;
}


float convert_C_to_K(float C) {
    float K;
    K = C + 273.15;
    return K;
}
float convert_C_to_C(float C) {
    return C;
}
float convert_K_to_C(float K) {
    float C;
    C = K - 273.15;
    return C;
}
float convert_C_to_F(float C) {
    float F;
    F = (C * 1.8) + 32;
    return F;
}
float convert_F_to_C(float F) {
    float C;
    C = (F - 32) / 1.8;
    return C;
}

int main() {
    setlocale(LC_ALL, "RUS");

    //SetConsoleOutputCP(CP_UTF8);
    char end[100];
    char value[100], from[3], in[3];
    float value_f;
    float result;

    float(*function1[3]) (float) = {&convert_C_to_C , &convert_K_to_C, &convert_F_to_C}; //0 - ������� �� ���� ,1 - �������� �� ����,2 - ���������� �� ����
    float(*function2[3]) (float) = { &convert_C_to_C, &convert_C_to_K, &convert_C_to_F }; //0 - ������� �� ����� ,1 - �������� �� �����,2 - ���������� �� �����
    int whl = 1;

    while (whl) {
        printf("> ����� ��������� ����������� � ������ ������� ���������!\n");
        printf("> ������ �����������, ������� ������ �������������.\n");
        printf(" <");
        fgets(value, 99, stdin);


        if (sscanf(value, "%f", &value_f) != 1) {
            printf("������������ ��������\n");
            continue;
        }


        printf("> �� ����� ������� ���������  0 - ������� 1 - ������� 2 - ��������� \n");
        printf(" <");
        fgets(from, 3, stdin);
        int from_s = 0;
        sscanf_s(from, "%d", &from_s);
        if (in[0] != '\n') {
            if (from[0] == '0' || from[0] == '1' || from[0] == '2') {
               
                result = function1[from_s](value_f);
            }
            else {
                printf("> � ��� �� ���� ��� ������� ���������\n");
                continue;
            }
           
        }
        //printf("> ��������� %.2f\n", result);
        printf("> � ����� ������� ���������  0 - ������� 1 - ������� 2 - ��������� \n");
        printf(" <");
        fgets(in, 3, stdin);
        int in_s = 0;
        sscanf_s(in, "%d", &in_s);
        if (in[0] != '\n') {
            if (in[0] == '0' || in[0] == '1' || in[0] == '2') {
                result = function2[in_s](result);
            }
            else {
                printf("> � ��� �� ���� ����� ������� ���������\n");
                continue;
            }
        }
        printf("> ���� ��������� %.2f\n", result);
        printf("> �� ������ ����������? 0 - ���������. ����� ������ ������ - ���������� \n");
        printf(" <");
        fgets(end, 98, stdin);
        if (end[0] == '0' && end[1] == '\n') {
            whl = 0;
            break;
        }
        
    }
    return 0;
}



