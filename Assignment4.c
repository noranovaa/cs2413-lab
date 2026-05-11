#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int isSorted(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) return 0;
    }
    return 1;
}

// ── Q4: Insertion Sort ───────────────────────────────────────────────────────
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j   = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ── Q5: Selection Sort ───────────────────────────────────────────────────────
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        int temp    = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i]      = temp;
    }
}

// ── Q7.3: Hybrid Merge + Insertion Sort ─────────────────────────────────────
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else               arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void hybridMergeSort(int arr[], int left, int right, int k) {
    if (left >= right) return;

    if (right - left + 1 <= k) {
        insertionSort(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;
    hybridMergeSort(arr, left, mid, k);
    hybridMergeSort(arr, mid + 1, right, k);
    merge(arr, left, mid, right);
}

// ── Helper ───────────────────────────────────────────────────────────────────
void copyArray(int src[], int dst[], int size) {
    for (int i = 0; i < size; i++) dst[i] = src[i];
}

// ── Main ─────────────────────────────────────────────────────────────────────
int main() {
    int original[] = {39, 9, 81, 45, 90, 27, 72, 18};
    int size = sizeof(original) / sizeof(original[0]);
    int arr[size];

    // Q4 — Insertion Sort
    copyArray(original, arr, size);
    printf("Q4 Insertion Sort:\n");
    printf("  Before: "); printArray(arr, size);
    insertionSort(arr, 0, size - 1);
    printf("  After:  "); printArray(arr, size);
    printf("  Result: %s\n\n", isSorted(arr, size) ? "PASS" : "FAIL");

    // Q5 — Selection Sort
    copyArray(original, arr, size);
    printf("Q5 Selection Sort:\n");
    printf("  Before: "); printArray(arr, size);
    selectionSort(arr, size);
    printf("  After:  "); printArray(arr, size);
    printf("  Result: %s\n\n", isSorted(arr, size) ? "PASS" : "FAIL");

    // Q7.3 — Hybrid Merge + Insertion Sort
    copyArray(original, arr, size);
    int k = 3;
    printf("Q7.3 Hybrid Merge+Insertion Sort (k=%d):\n", k);
    printf("  Before: "); printArray(arr, size);
    hybridMergeSort(arr, 0, size - 1, k);
    printf("  After:  "); printArray(arr, size);
    printf("  Result: %s\n\n", isSorted(arr, size) ? "PASS" : "FAIL");

    return 0;
}