#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

int main() {
    cout << setw(12) << "Size" << setw(20) << "Time (ms)" << endl;
    cout << string(35, '-') << endl;

    // Test with exponentially growing sizes
    for (int size = 1000; size <= 32000; size *= 2) {
        vector<int> arr(size);
        
        // Fill array in reverse order (worst case)
        for (int i = 0; i < size; i++) {
            arr[i] = size - i;
        }

        // Measure single execution time (bubble sort is slow enough)
        auto start = high_resolution_clock::now();
        bubbleSort(arr);
        auto stop = high_resolution_clock::now();
        
        auto duration = duration_cast<milliseconds>(stop - start);
        double time_ms = duration.count();

        cout << setw(12) << size << setw(20) << fixed 
             << setprecision(2) << time_ms << endl;
    }
    return 0;
}