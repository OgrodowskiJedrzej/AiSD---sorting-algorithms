#include <iostream>
#include <algorithm>
#include <stdlib.h>

void insertion_sort(int *data, int size)
{
    int key, j;
    for (int i = 1; i < size; i++)
    {
        key = data[i];
        j = i - 1;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j = j - 1;
        }
        data[j + 1] = key;
    }
}

long sedgewick_expression(int k)
{
    return std::pow(4, k + 1) + 3 * std::pow(2, k) + 1;
}

std::vector<long> generate_sedgewick_gaps(int k)
{
    std::vector<long> gaps(20);
    for (int i = 0; i < 20; i++)
    {
        gaps[i] = sedgewick_expression(i);
    }
    return gaps;
}
// TODO fix shell sort
void shellSort(int *data, int size, const std::vector<long> &sedgewick_gaps)
{
    int gap_index = 0;

    while (sedgewick_gaps[gap_index] < size / 3)
    {
        gap_index++;
    }

    for (int gap = sedgewick_gaps[gap_index]; gap > 0; gap = sedgewick_gaps[--gap_index])
    {
        for (int i = gap; i < size; i += 1)
        {
            int temp = data[i];
            int j;

            for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
            {
                data[j] = data[j - gap];
            }
            data[j] = temp;
        }
    }
}

void selection_sort(int *data, int size)
{
    int min_idx;
    for (int i = 0; i < size - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < size; j++)
        {
            if (data[j] < data[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            std::swap(data[min_idx], data[i]);
        }
    }
}

int partition_left(int *data, int low, int high)
{
    int pivot = data[low];
    int p = low + 1;
    int q = high;

    while (true)
    {
        while (p <= q && data[p] <= pivot)
            p++;
        while (p <= q && data[q] >= pivot)
            q--;
        if (p <= q)
            std::swap(data[p], data[q]);
        else
            break;
    }

    std::swap(data[low], data[q]);
    return q;
}

void quick_sort_left_pivot(int *data, int low, int high)
{
    if (low < high)
    {
        int pivot = partition_left(data, low, high);
        quick_sort_left_pivot(data, low, pivot - 1);
        quick_sort_left_pivot(data, pivot + 1, high);
    }
}

int partition_random(int *data, int low, int high)
{
    int rand_index = rand() % (high - low + 1) + low;
    std::swap(data[high], data[rand_index]);
    int pivot = data[high];
    int p = low;
    int q = high - 1;

    while (true)
    {
        while (p <= q && data[p] <= pivot)
        {
            p++;
        }
        while (p <= q && data[q] >= pivot)
        {
            q--;
        }
        if (p <= q)
        {
            std::swap(data[p], data[q]);
        }
        else
        {
            break;
        }
    }

    std::swap(data[high], data[p]);
    return p;
}

void quick_sort_random_pivot(int *data, int low, int high)
{
    if (low < high)
    {
        int pivot = partition_random(data, low, high);
        quick_sort_random_pivot(data, low, pivot - 1);
        quick_sort_random_pivot(data, pivot + 1, high);
    }
}

void shift_down(int *data, int i, int upper)
{
    while (true)
    {
        int l = i * 2 + 1;
        int r = i * 2 + 2;

        if (std::max(l, r) < upper)
        {
            if (data[i] >= std::max(data[l], data[r]))
            {
                break;
            }
            else if (data[l] > data[r])
            {
                std::swap(data[i], data[l]);
                i = l;
            }
            else
            {
                std::swap(data[i], data[r]);
                i = r;
            }
        }
        else if (l < upper)
        {
            if (data[l] > data[i])
            {
                std::swap(data[i], data[l]);
                i = l;
            }
            else
            {
                break;
            }
        }
        else if (r < upper)
        {
            if (data[r] > data[i])
            {
                std::swap(data[i], data[r]);
                i = r;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
}

void heap_sort(int *data, int size)
{
    for (int j = (size - 2) / 2; j > -1; j--)
    {
        shift_down(data, j, size);
    }

    for (int end = size - 1; end > 0; end--)
    {
        std::swap(data[0], data[end]);
        shift_down(data, 0, end);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3 || std::string(argv[1]) != "--algorithm")
    {
        std::cout << "Usage: ./main --algorithm <algorithm_number>\n";
        return 1;
    }

    int algorithm_number = std::stoi(argv[2]);

    // Read the maximum integer value from standard input
    int max_int;
    if (!(std::cin >> max_int))
    {
        std::cerr << "Error reading the maximum integer value\n";
        return 1;
    }

    int data[max_int];

    // Read the remaining integers into the array
    int count = 0;
    int num;
    while (std::cin >> num && count < max_int)
    {
        data[count++] = num;
    }

    switch (algorithm_number)
    {
    case 1:
    {
        insertion_sort(data, count);
        break;
    }
    case 2:
    {
        std::vector<long> sedgewick_gaps = generate_sedgewick_gaps(20);
        shellSort(data, count, sedgewick_gaps);
        break;
    }
    case 3:
    {
        selection_sort(data, count);
        break;
    }
    case 4:
    {
        heap_sort(data, count);
        break;
    }
    case 5:
    {
        quick_sort_left_pivot(data, 0, count - 1);
        break;
    }
    case 6:
    {
        quick_sort_random_pivot(data, 0, count - 1);
        break;
    }
    default:
    {
        std::cerr << "Wrong algorithm number"
                  << "\n";
    }

        // Print the sorted data
        std::cout << "Sorted data: ";
        for (int i = 0; i < std::min(10, count); ++i)
        {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";

        return 0;
    }
