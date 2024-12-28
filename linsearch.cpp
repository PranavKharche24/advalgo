#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

int search(vector<int>& arr, int x) {
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == x)
            return i;
    return -1;
}

int main() {
    // Search for a value that doesn't exist (worst case)
    int x = -1;

    cout << setw(10) << "Size" << setw(15) << "Time (us)" << endl;
    cout << string(30, '-') << endl;

    // Use exponential growth in sizes
    for (int size = 1000; size <= 1000000; size *= 2) {
        vector<int> largeArr(size);
        for (int i = 0; i < size; i++) {
            largeArr[i] = i;
        }

        auto start = high_resolution_clock::now();
        for (int i = 0; i < 1000; i++) {
            int res = search(largeArr, x);
        }
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        double avg_time = duration.count() / 1000.0;  // Average time per search

        cout << setw(10) << size << setw(15) << fixed << setprecision(2) << avg_time << endl;
    }

    return 0;
}