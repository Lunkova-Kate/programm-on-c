#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}

int delim(int arr[], int left, int right) {
	int pivot = arr[left]; // Выбираем первый элемент в качестве опорного
	int i = left + 1;
	int j = right;

	while (i <= j) {
		while (i <= right && arr[i] < pivot) {
			i++;
		}
		while (j >= left && arr[j] > pivot) {
			j--;
		}
		if (i <= j) {
			swap(&arr[i], &arr[j]);
			i++;
			j--;
		}
	}
	swap(&arr[left], &arr[j]);
	return j;
}


void qs(int arr[], int left, int right) {
	if (left >= right) {
		return;
	}
	
		int pivot = delim(arr, left, right);
		qs(arr, left, pivot );
		qs(arr, pivot + 1, right);
	
}



int main() {
	int num;
	if (!scanf("%d ", &num)) {
		return 0;
	}
	int* arr = (int*)malloc(num * sizeof(int));
	if (!arr) {
		return 0;
	}
	for (int i = 0; i < num; i++) {
		if (!scanf("%d ", &arr[i])) {
			free(arr);
			return 0;
		}
	}
	qs(arr, 0, num - 1);

	for (int j = 0; j < num; j++) {
		printf("%d ", arr[j]);
	}
	printf("\n");

	free(arr);
	return 0;
}
