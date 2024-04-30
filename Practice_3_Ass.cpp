#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int minx(int arr[], int n) {
    int minval = arr[0];
    #pragma omp parallel for reduction(min: minval) 
    for (int i = 1; i < n; i++) {
        if(arr[i] < minval) 
            minval = arr[i];
    }
    return minval;
} 

int maxp(int arr[], int n) {
    int maxval = arr[0];
    #pragma omp parallel for reduction(max: maxval) 
    for (int i = 1; i < n; i++) {
        if(arr[i] > maxval) 
            maxval = arr[i];
    }
    return maxval;
} 

int sumx(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum) 
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
} 

double average(int arr[], int n) {
    return (double)sumx(arr, n) / n;
}

int main() {
    cout << "Enter the length of array: ";
    int n;
    cin >> n;
    cout << endl;
    int arr[n];

    for(int i = 0; i < n; i++) {
        cout << "Enter the element at index " << i << endl;
        cin >> arr[i];
    }

    cout << "Min: " << minx(arr, n) << endl;
    cout << "Max: " << maxp(arr, n) << endl;
    cout << "Sum: " << sumx(arr, n) << endl;
    cout << "Avg: " << average(arr, n) << endl;
}