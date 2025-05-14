#pragma once

#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include "types.h"

clock_t time_begin;
clock_t time_end;

void benchmark_begin() {
    time_begin = clock();
}

void benchmark_end() {
    time_end = clock();
    printf("%fs\n", double(time_end - time_begin) / CLOCKS_PER_SEC);
}

void swap(s32* a, s32* b) {
    s32 temp = *a;
    *a = *b;
    *b = temp;
}

void arr_rand(s32* arr, usize len) {
    for (usize i = 0; i < len; i += 1) {
        arr[i] = rand() % len;
    }
}

void arr_copy(s32* out, s32* arr, usize len) {
    for (usize i = 0; i < len; i += 1) {
        out[i] = arr[i];
    }
}

void arr_validate(s32* arr, usize len) {
    for (usize i = 0; i < len - 1; i += 1) {
        assert((arr[i] <= arr[i + 1]) && "Array is not sorted");
    }
}

void arr_print(s32* arr, usize len) {
    for (usize i = 0; i < len; i += 1) {
        printf("%i\t", arr[i]);
    }

    printf("\n");
}

void sort_bubble(s32* arr, usize len) {
    usize last = len;
    usize last_temp = last;

    while (last > 1) {
        for (usize i = 0; i < last - 1; i += 1) {
            if (arr[i] > arr[i + 1]) {
                s32 temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;

                last_temp = i + 1;
            }
        }

        if (last == last_temp) {
            break;
        }

        last = last_temp;
    }
}

void sort_insertion(s32* arr, usize len) {
    for (usize i = 1; i < len; i += 1) {
        s32 k = arr[i];
        usize j = i;

        while (j > 0 && arr[j - 1] > k) {
            arr[j] = arr[j - 1];
            j -= 1;
        }

        arr[j] = k;
    }
}

void sort_merge_half(s32* arr, s32* temp, usize l, usize m, usize r) {
    usize i = l;
    usize j = m;
    usize k = l;

    while (i < m && j < r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i < m) temp[k++] = arr[i++];

    while (j < r) temp[k++] = arr[j++];

    for (usize x = l; x < r; x++) arr[x] = temp[x];
}

void sort_merge_rec(s32* arr, s32* temp, usize l, usize r) {
    if (r - l <= 1) return;

    usize m = l + (r - l) / 2;

    sort_merge_rec(arr, temp, l, m);
    sort_merge_rec(arr, temp, m, r);

    sort_merge_half(arr, temp, l, m, r);
}

void sort_merge(s32* arr, s32* temp, usize len) {
    sort_merge_rec(arr, temp, 0, len);
}

usize partition(s32* arr, usize low, usize high) {
    s32 pivot = arr[high];
    usize i = low - 1;

    for (usize j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

void quicksort(s32* arr, usize low, usize high) {
    if (low < high) {
        usize pi = partition(arr, low, high);

        if (pi > 0) quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void sort_quick(s32* arr, usize len) {
    quicksort(arr, 0, len - 1);
}

#define ARR_LEN 65536

s32 main(s32, char**) {
    srand(time(NULL));

    s32 arr0[ARR_LEN];
    s32 arr1[ARR_LEN];
    s32 temp[ARR_LEN];

    arr_rand(arr0, ARR_LEN);

    printf("Sorting Integers\n");
    printf("Array Size: %zu\n", usize(ARR_LEN));

    printf("Bubble Sort: ");
    arr_copy(arr1, arr0, ARR_LEN);
    benchmark_begin();
    sort_bubble(arr1, ARR_LEN);
    benchmark_end();
    arr_validate(arr1, ARR_LEN);

    printf("Insertion Sort: ");
    arr_copy(arr1, arr0, ARR_LEN);
    benchmark_begin();
    sort_insertion(arr1, ARR_LEN);
    benchmark_end();
    arr_validate(arr1, ARR_LEN);

    printf("Merge Sort: ");
    arr_copy(arr1, arr0, ARR_LEN);
    benchmark_begin();
    sort_merge(arr1, temp, ARR_LEN);
    benchmark_end();
    arr_validate(arr1, ARR_LEN);

    printf("Quick Sort: ");
    arr_copy(arr1, arr0, ARR_LEN);
    benchmark_begin();
    sort_quick(arr1, ARR_LEN);
    benchmark_end();
    arr_validate(arr1, ARR_LEN);

    return 0;
}
