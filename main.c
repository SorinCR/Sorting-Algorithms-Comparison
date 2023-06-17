#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        if(min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}

int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(int arr[], int n, int exp)
{
    int *output = malloc(n * sizeof(int));
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
    free(output);
}

void radixsort(int arr[], int n)
{
    int m = getMax(arr, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

#define MAX_LINE_WIDTH 1024

int main(int argc, char *argv[]) {

    struct timeval start,end;
    double timeUsed;
    int lines = atoi(argv[1]), n = atoi(argv[2]);

    int **v = (int**)malloc(lines * sizeof (int*));

    char path[256] = "./lists/list";
    sprintf(path, "./lists/list_%d_%d.txt", lines, n);

    gettimeofday(&start, NULL);
    FILE* file = fopen(path , "r");
    char *line = malloc(n * 10);

    int lineCount = 0;

    while(fgets(line, n * 10, file)) {
        char *t = strtok(line, " ");
        v[lineCount] = (int*)malloc(n * sizeof (int));
        for(int i = 0; i < n && t; i++) {
            v[lineCount][i] = atoi(t);
            t = strtok(NULL, " ");
        }
        lineCount++;
    }
    fclose(file);

    int **vCopy = (int**)malloc(lines * sizeof(int*));
    for(int i = 0; i < lines; i++) {
        vCopy[i] = (int*)malloc(n * sizeof(int));
        memcpy(vCopy[i], v[i], n * sizeof(int));
    }

    gettimeofday(&end, NULL);
    timeUsed = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000;
    printf("File load: %f seconds\n", timeUsed);

    gettimeofday(&start, NULL);
    for(int i = 0; i < lines; i++) {
        bubbleSort(v[i], n);
    }
    gettimeofday(&end, NULL);
    timeUsed = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000;
    printf("Bubble sort: %f seconds\n", timeUsed);


    for(int i = 0; i < lines; i++) {
        memcpy(v[i], vCopy[i], n * sizeof(int));
    }

    gettimeofday(&start, NULL);
    for(int i = 0; i < lines; i++) {
        insertionSort(v[i], n);
    }
    gettimeofday(&end, NULL);
    timeUsed = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000;
    printf("Insertion sort: %f seconds\n", timeUsed);

    for(int i = 0; i < lines; i++) {
        memcpy(v[i], vCopy[i], n * sizeof(int));
    }

    gettimeofday(&start, NULL);
    for(int i = 0; i < lines; i++) {
        selectionSort(v[i], n);
    }
    gettimeofday(&end, NULL);
    timeUsed = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000;
    printf("Selection sort: %f seconds\n", timeUsed);

    for(int i = 0; i < lines; i++) {
        memcpy(v[i], vCopy[i], n * sizeof(int));
    }

    gettimeofday(&start, NULL);
    for(int i = 0; i < lines; i++) {
        radixsort(v[i], n);
    }
    gettimeofday(&end, NULL);
    timeUsed = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000;
    printf("Radix sort: %f seconds\n", timeUsed);

    for(int i = 0; i < lines; i++) {
        memcpy(v[i], vCopy[i], n * sizeof(int));
    }

    gettimeofday(&start, NULL);
    for(int i = 0; i < lines; i++) {
        mergeSort(v[i], 0, n-1);
    }
    gettimeofday(&end, NULL);
    timeUsed = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000;
    printf("Merge sort: %f seconds\n", timeUsed);

    for(int i = 0; i < lines; i++) {
        memcpy(v[i], vCopy[i], n * sizeof(int));
    }

    gettimeofday(&start, NULL);
    for(int i = 0; i < lines; i++) {
        quickSort(v[i], 0, n-1);
    }
    gettimeofday(&end, NULL);
    timeUsed = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000;
    printf("Quick sort: %f seconds\n", timeUsed);

    for(int i = 0; i < lines; i++) {
        memcpy(v[i], vCopy[i], n * sizeof(int));
        free(vCopy[i]);
    }
    free(vCopy);


    return 0;
}
