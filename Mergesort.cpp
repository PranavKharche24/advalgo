#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>
using namespace std;
using namespace std::chrono;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    
    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while(j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    
    cout << setw(12) << "Size" << setw(20) << "Time (ms)" << endl;
    cout << string(35, '-') << endl;

    // Test with exponentially growing sizes
    for(int size = 10000; size <= 1000000; size *= 2) {
        vector<int> arr(size);
        
        // Fill with random numbers
        uniform_int_distribution<> dis(1, size);
        for(int i = 0; i < size; i++) {
            arr[i] = dis(gen);
        }

        auto start = high_resolution_clock::now();
        mergeSort(arr, 0, size - 1);
        auto stop = high_resolution_clock::now();
        
        auto duration = duration_cast<milliseconds>(stop - start);
        double time_ms = duration.count();

        cout << setw(12) << size << setw(20) << fixed 
             << setprecision(2) << time_ms << endl;
    }
    return 0;
}