#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cmath>
using namespace std;
using namespace std::chrono;

// Algorithm implementations
void linearSearch(vector<int>& arr) {
    int x = -1; // Worst case: searching for non-existent element
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == x) break;
}

void binarySearch(vector<int>& arr) {
    int x = -1; // Worst case
    int l = 0, r = arr.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x) break;
        if (arr[m] < x) l = m + 1;
        else r = m - 1;
    }
}

void bubbleSort(vector<int>& arr) {
    for (int i = 0; i < arr.size()-1; i++)
        for (int j = 0; j < arr.size()-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        
        vector<int> temp(r - l + 1);
        int i = l, j = m + 1, k = 0;
        
        while (i <= m && j <= r) {
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else temp[k++] = arr[j++];
        }
        while (i <= m) temp[k++] = arr[i++];
        while (j <= r) temp[k++] = arr[j++];
        
        for (i = 0; i < k; i++)
            arr[l + i] = temp[i];
    }
}

double measureTime(void (*func)(vector<int>&), vector<int>& arr) {
    auto start = high_resolution_clock::now();
    func(arr);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

double measureMergeSort(vector<int>& arr) {
    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size()-1);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

void generateGnuplotScript() {
    ofstream script("plot_script.gnu");
    script << "set terminal png size 800,600\n"
           << "set output 'complexity_comparison.png'\n"
           << "set title 'Algorithm Time Complexity Comparison'\n"
           << "set xlabel 'Input Size (log scale)'\n"
           << "set ylabel 'Time (ms)'\n"
           << "set logscale x\n"
           << "set grid\n"
           << "set key left top\n"
           << "plot 'timing_data.txt' using 1:2 title 'Linear Search' with linespoints,\\\n"
           << "     '' using 1:3 title 'Binary Search' with linespoints,\\\n"
           << "     '' using 1:4 title 'Bubble Sort' with linespoints,\\\n"
           << "     '' using 1:5 title 'Merge Sort' with linespoints\n";
    script.close();
}

int main() {
    ofstream data("timing_data.txt");
    data << "#Size LinearSearch BinarySearch BubbleSort MergeSort\n";

    // Test with increasing sizes
    for (int size = 1000; size <= 32000; size *= 2) {
        vector<int> arr(size);
        
        // Linear Search (worst case)
        vector<int> arr1(size);
        for (int i = 0; i < size; i++) arr1[i] = i;
        double linTime = measureTime(linearSearch, arr1);
        
        // Binary Search (worst case on sorted array)
        vector<int> arr2(size);
        for (int i = 0; i < size; i++) arr2[i] = i;
        double binTime = measureTime(binarySearch, arr2);
        
        // Bubble Sort (worst case - reverse sorted)
        vector<int> arr3(size);
        for (int i = 0; i < size; i++) arr3[i] = size-i;
    double bubTime = measureTime(bubbleSort, arr3);
        
        // Merge Sort (worst case - reverse sorted)
        vector<int> arr4(size);
        for (int i = 0; i < size; i++) arr4[i] = size-i;
        double mergeTime = measureMergeSort(arr4);
        
        data << size << " " 
             << linTime << " " 
             << binTime << " "
             << bubTime << " "
             << mergeTime << endl;
    }
    data.close();
    
    generateGnuplotScript();
    system("gnuplot plot_script.gnu");
    
    cout << "Graph has been generated as 'complexity_comparison.png'\n";
    return 0;
}