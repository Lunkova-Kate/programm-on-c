#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void maxiheapsort(int arr[], int i, int n) {
    int maxi = i, a;

    while ((a = i * 2 + 1) < n) {
        int b = a + 1;

        if (n > a && arr[a] > arr[maxi]) {
            maxi = a;
        }
        if (n > b && arr[b] > arr[maxi]) {
            maxi = b;
        }

        if (i == maxi)
            break;

        {
            int p = arr[i];
            arr[i] = arr[maxi];
            arr[maxi] = p;

            i = maxi;
        }
    }
}

void heapsort(int arr[], int n) {
    int i = (n / 2) - 1;
    while (i >= 0) {
        maxiheapsort(arr, i, n);
        i = i - 1;
    }
    int j = n - 1;
    while (j > 0) {

        int p = arr[0];
        arr[0] = arr[j];
        arr[j] = p;

        maxiheapsort(arr, 0, j);
        j = j - 1;
    }
}

int main(void) {
    int n = 0, i = 0;

    if (scanf("%d\n", &n) != 1) {
        printf("bad input");
        return 1;
    }

    int* arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("bad input");
        return 1;
    }

    while (i < n) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("bad input");
            free(arr);
            return 1;
        }
        ++i;
    }

    heapsort(arr, n);

    for (i = 0; i < n; ++i)
        printf("%d ", arr[i]);

    free(arr);

    return 0;
}
 