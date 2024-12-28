#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <climits>
using namespace std;
using namespace std::chrono;

int binarySearch(vector<int>& arr, int x) {
    int l = 0;
    int r = arr.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

int main() {
    // Search for value larger than maximum (worst case)
    int x = INT_MAX;

    cout << setw(12) << "Size" << setw(15) << "Time (ns)" << endl;
    cout << string(30, '-') << endl;

    // Use larger exponential growth
    for (int size = 1000; size <= 10000000; size *= 4) {
        vector<int> arr(size);
        // Create sorted array
        for (int i = 0; i < size; i++) {
            arr[i] = i;
        }

        // Increase iterations for more accurate timing
        const int iterations = 10000;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < iterations; i++) {
            int res = binarySearch(arr, x);
        }
        auto stop = high_resolution_clock::now();

        // Use nanoseconds for more precision
        auto duration = duration_cast<nanoseconds>(stop - start);
        double avg_time = duration.count() / (double)iterations;

        cout << setw(12) << size << setw(15) << fixed << setprecision(2) 
             << avg_time << endl;
    }
    return 0;
}