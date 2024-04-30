#include <iostream>
#include <omp.h>

using namespace std;

void bubble(int array[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(array[j] > array[j + 1]) swap(array[j], array[j+1]);
        }
    }
}

void pBubble(int array[], int n) {
    for(int i = 0; i < n; i++) {
        #pragma omp for
        for(int j = 1; j < n; j += 2) {
            if(array[j] < array[j-1]) 
                swap(array[j], array[j-1]);
        }

        #pragma omp barrier

        #pragma omp for
        for(int j = 2; j < n; j += 2) {
            if(array[j] < array[j-1]) 
                swap(array[j], array[j-1]);
        }
    }
}

void merge(int array[], int low, int mid, int high) {

    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1];
    int right[n2];

    for(int i = 0; i < n1; i++) left[i] = array[low + i];

    for(int j = 0; j < n2; j++) right[j] = array[mid + 1 + j];

    int i = 0, j= 0, k = low;

    while(i < n1 && j < n2) {
        if(left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        }
        else {
            array[k] = right[j];
            j++;
        }
        k++;
    }
    while(i < n1) {
        array[k] = left[i];
        i++;
        k++;
    }
    while(j < n2) {
        array[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int low, int high) {
    if(low < high) {
        int mid = (low + high) / 2;
        mergeSort(array, low, mid);
        mergeSort(array, mid + 1, high);
        merge(array, low, mid, high);
    }
}

void parallelMergeSort(int array[], int low, int high) {
    if(low < high) {
        int mid = (low + high) / 2;
    
        #pragma omp parallel sections 
        {
            #pragma omp section 
            {
                parallelMergeSort(array, low, mid);
            }

            #pragma omp section 
            {
                parallelMergeSort(array, mid + 1, high);
            }
        }
        merge(array, low, mid, high);
    }
}

void printArray(int array[], int n) {
    for(int i = 0; i < n; i++) 
        cout << array[i] << " ";
    cout << "\n";
}

int main() {
    int n = 10;
    int array[n];
    double start_time, end_time;

    for(int i = 0, j = n; i < n; i++, j--) array[i] = j;

    start_time = omp_get_wtime();
    bubble(array, n);
    end_time = omp_get_wtime();
    cout << "Sequential Bubble Sort took: " << end_time - start_time << " seconds\n";
    printArray(array, n);

    for(int i = 0, j = n; i < n; i++, j--) array[i] = j;

    start_time = omp_get_wtime();
    pBubble(array, n);
    end_time = omp_get_wtime();
    cout << "Parallel Bubble Sort took: " << end_time - start_time << " seconds\n";
    printArray(array, n);

    for(int i = 0, j = n; i < n; i++, j--) array[i] = j;

    start_time = omp_get_wtime();
    mergeSort(array, 0, n - 1);
    end_time = omp_get_wtime();
    cout << "Sequential Merge Sort took: " << end_time - start_time << " seconds\n";
    printArray(array, n);

    for(int i = 0, j = n; i < n; i++, j--) array[i] = j;

    start_time = omp_get_wtime();
    parallelMergeSort(array, 0, n - 1);
    end_time = omp_get_wtime();
    cout << "Parallel Sequential Sort took: " << end_time - start_time << " seconds\n";
    printArray(array, n);
    
}