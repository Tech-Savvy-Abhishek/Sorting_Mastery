#include <bits/stdc++.h>
#define N 10000

using namespace std;
using namespace chrono;

void generateRandomVector(vector<int> &v, int n)
{
    // Iterate over the range [0, n)
    for (int i = 0; i < n; ++i)
    {
        // Generate a random integer
        int ele = rand();
        // Add the random integer to the end of the vector
        v.push_back(ele);
    }
}

void generateRandomVector(vector<int> &v, int n, int start, int end)
{
    // Check if the range is valid
    if (end < start)
    {
        cout << "Invalid range\n";
        return;
    }

    // Iterate over the range [0, n)
    for (int i = 0; i < n; ++i)
    {
        // Generate a random integer within the specified range
        int ele = start + rand() % (end - start + 1);
        // Add the random integer to the end of the vector
        v.push_back(ele);
    }
}

void isSorted(vector<int> &v)
{
    // Iterate over the array elements and print them
    for (int i = 1; i < v.size(); ++i)
    {
        if (v[i - 1] > v[i])
        {
            cout << "ALGO IS WRONG!!!\n";
            return;
        }
    }
    cout << "ALGO IS CORRECT\n";
}

class SortStrategy
{
public:
    virtual void sort(vector<int> v, int size) = 0;
};

// Define a class InsertionSort that inherits from the SortStrategy class
class InsertionSort : public SortStrategy
{
    // Override the sort function from the SortStrategy class
    void sort(vector<int> v, int size) override
    {
        // Iterate over each element in the vector starting from the second element
        for (int i = 1; i < size; ++i)
        {
            // Store the current element in a variable
            int curr = v[i];
            // Initialize a pointer to the previous element
            int j = i - 1;
            // Shift elements of the sorted segment forward if they are greater than the current element
            while (j >= 0 && curr < v[j])
            {
                v[j + 1] = v[j];
                --j;
            }
            // Insert the current element in its correct position within the sorted segment
            v[j + 1] = curr;
        }
        // Display the sorted vector
    }
};

// Define a class SelectionSort that inherits from the SortStrategy class
class SelectionSort : public SortStrategy
{
    // Override the sort function from the SortStrategy class
    void sort(vector<int> v, int size) override
    {
        // Iterate over each element in the vector
        for (int i = 0; i < size - 1; i++)
        {
            // Assume the current element is the smallest
            int minEleIdx = i;

            // Iterate over the remaining elements in the vector
            for (int j = i + 1; j < size; j++)
            {
                // If a smaller element is found, update minEleIdx
                if (v[j] < v[minEleIdx])
                {
                    minEleIdx = j;
                }
            }
            // Swap the smallest element found with the current element
            swap(v[i], v[minEleIdx]);
        }
        // Display the sorted vector
    }
};
// BubbleSort class inherits from the SortStrategy class
class BubbleSort : public SortStrategy
{
    // Override the sort function from the SortStrategy class
    void sort(vector<int> v, int size) override
    {
        // Initialize the current array length to the size of the array
        int currArrayLength = size;

        // Continue sorting until the array is fully sorted
        while (currArrayLength > 1)
        {
            // Iterate over the array up to the current length
            for (int i = 1; i < currArrayLength; i++)
            {
                // If the current element is smaller than the previous one
                if (v[i - 1] > v[i])
                {
                    // Swap the current element and the previous one
                    swap(v[i - 1], v[i]);
                }
            }
            // Decrease the current array length for the next iteration
            --currArrayLength;
        }
        // Display the sorted array
    }
};
class MergeSort : public SortStrategy
{
    // Function to merge two sorted subarrays into one sorted array
    void inline merge(vector<int> &v, int l, int mid, int h)
    {
        // Temporary vector to store the merged array
        vector<int> temp(h - l + 1);
        // Starting indices of the first and second subarrays
        int i = l, j = mid + 1, k = 0;

        // Merge the two subarrays into temp until one of them is empty
        while (i <= mid && j <= h)
        {
            if (v[i] <= v[j])
                temp[k++] = v[i++];
            else
                temp[k++] = v[j++];
        }

        // Copy the remaining elements of the first subarray, if there are any
        while (i <= mid)
            temp[k++] = v[i++];

        // Copy the remaining elements of the second subarray, if there are any
        while (j <= h)
            temp[k++] = v[j++];

        // Copy the merged elements from temp back into the original array
        for (i = l; i <= h; i++)
            v[i] = temp[i - l];
    }

    // Function to sort an array using the merge sort algorithm
    void sort(vector<int> v, int size) override
    {
        // Merge subarrays of size 1, 2, 4, etc. until curr_size < size
        for (int curr_size = 1; curr_size <= size - 1; curr_size = 2 * curr_size)
        {
            // For each subarray of the current size
            for (int left_start = 0; left_start < size - 1; left_start += 2 * curr_size)
            {
                // Calculate l, mid, and h such that the subarray [l, h] is within the array bounds
                int mid = min(left_start + curr_size - 1, size - 1);
                int right_end = min(left_start + 2 * curr_size - 1, size - 1);

                // Merge the two halves of the subarray
                merge(v, left_start, mid, right_end);
            }
        }
    }
};

class QuickSort : public SortStrategy
{
    // This function takes last element as pivot, places the pivot element at its correct position
    // in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater
    // elements to right of pivot
    int partition(vector<int> &v, int low, int high)
    {
        int pivot = v[high]; // pivot
        int i = (low - 1);   // Index of smaller element

        for (int j = low; j <= high - 1; j++)
        {
            // If current element is smaller than the pivot
            if (v[j] < pivot)
            {
                i++; // increment index of smaller element
                swap(v[i], v[j]);
            }
        }
        swap(v[i + 1], v[high]);
        return (i + 1);
    }

    // The main function that implements QuickSort using Stack
    void sort(vector<int> v, int n) override
    {
        // Create an auxiliary stack
        stack<int> stk;

        // push initial values in the stack
        stk.push(0);
        stk.push(n - 1);

        // Keep popping elements until stack is not empty
        while (!stk.empty())
        {
            // Pop h and l
            int h = stk.top();
            stk.pop();
            int l = stk.top();
            stk.pop();

            // Set pivot element at its correct position in sorted array
            int p = partition(v, l, h);

            // If there are elements on left side of pivot, then push left side to stack
            if (p - 1 > l)
            {
                stk.push(l);
                stk.push(p - 1);
            }

            // If there are elements on right side of pivot, then push right side to stack
            if (p + 1 < h)
            {
                stk.push(p + 1);
                stk.push(h);
            }
        }
    }
};

// SortContext class
class SortContext
{
    // Private member variable to hold the sorting strategy
    SortStrategy *strategy;

public:
    // Public method to set the sorting strategy
    void setStrategy(SortStrategy *strategy)
    {
        // Assign the provided strategy to the member variable
        this->strategy = strategy;
    }
    // Public method to execute the sorting strategy
    void executeStrategy(vector<int> v, int size)
    {
        // Call the sort method of the strategy
        strategy->sort(v, size);
    }
};

int main()
{
    // Declare an integer vector 'v'
    vector<int> v;

    // Generate a random vector 'v' with N elements
    generateRandomVector(v, N);

    // Get the size of the vector 'v'
    int n = v.size();

    // Create a SortContext object
    SortContext context;

    // Array of sorting strategies
    vector<pair<string, SortStrategy *>> strategies = {
        {"Insertion", new InsertionSort()},
        {"Selection", new SelectionSort()},
        {"Bubble", new BubbleSort()},
        {"Merge", new MergeSort()},
        {"Quick", new QuickSort()}};

    // Number of runs for each sorting strategy
    int num_runs = 100;

    // Measure the time taken by each sorting strategy
    for (auto &strategy : strategies)
    {
        long long total_duration = 0;
        for (int i = 0; i < num_runs; i++)
        {
            auto start = high_resolution_clock::now();
            context.setStrategy(strategy.second); // Set the sorting strategy
            context.executeStrategy(v, n);        // Execute the sorting strategy
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            total_duration += duration.count();
        }
        long long average_duration = total_duration / num_runs;
        cout << "Average time taken by " << strategy.first << " sort: "
             << average_duration << " microseconds" << endl;
    }
    return 0;
}