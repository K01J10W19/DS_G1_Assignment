#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <chrono>   // For timing
#include "Arrays.hpp"
using namespace std;
using namespace std::chrono;

void TransactionToArrays(const string& file_name, TransactionsArray*& array, int& count) {
    int capacity = 0;
    ifstream file(file_name);
    string line;
    getline(file, line); // Ignore header

    while (getline(file, line)) {
        if (count >= capacity) {
            int new_capacity = capacity + 10;
            TransactionsArray* temp = new TransactionsArray[new_capacity];
            for (int i = 0; i < count; ++i) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
            capacity = new_capacity;
        }

        stringstream ss(line);
        string item;

        getline(ss, item, ',');
        array[count].customer_ID = item;
        getline(ss, item, ',');
        array[count].product = item;
        getline(ss, item, ',');
        array[count].category = item;
        getline(ss, item, ',');
        array[count].price = stof(item);
        getline(ss, item, ',');
        array[count].date = item;
        getline(ss, item, ',');
        array[count].payment_method = item;

        ++count;
    }
}

// Helper function to compare dates
bool compareByDate(const TransactionsArray& a, const TransactionsArray& b) {
    int dayA = stoi(a.date.substr(0, 2));
    int monthA = stoi(a.date.substr(3, 2));
    int yearA = stoi(a.date.substr(6, 4));

    int dayB = stoi(b.date.substr(0, 2));
    int monthB = stoi(b.date.substr(3, 2));
    int yearB = stoi(b.date.substr(6, 4));

    if (yearA != yearB)
        return yearA < yearB;
    else if (monthA != monthB)
        return monthA < monthB;
    else
        return dayA < dayB;
}

void merge(TransactionsArray* array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    TransactionsArray* L = new TransactionsArray[n1];
    TransactionsArray* R = new TransactionsArray[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compareByDate(L[i], R[j])) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }

    while (i < n1) array[k++] = L[i++];
    while (j < n2) array[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(TransactionsArray* array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

size_t estimateStringSize(const string& str) {
    // Estimate actual allocated memory: capacity + string object overhead
    return str.capacity(); // Excludes sizeof(string) since object size is constant
}

size_t estimateMemoryUsage(TransactionsArray* array, int count) {
    size_t total = 0;
    for (int i = 0; i < count; ++i) {
        total += sizeof(TransactionsArray); // Object itself
        total += estimateStringSize(array[i].customer_ID);
        total += estimateStringSize(array[i].product);
        total += estimateStringSize(array[i].category);
        total += estimateStringSize(array[i].date);
        total += estimateStringSize(array[i].payment_method);
        total += sizeof(float); // price
    }
    return total;
}


int main() {
    TransactionsArray* transactions = nullptr;
    int transactionCount = 0;

    TransactionToArrays("transactions_cleaned.csv", transactions, transactionCount);

    // Measure time for sorting
    auto start = high_resolution_clock::now();
    mergeSort(transactions, 0, transactionCount - 1);
    auto end = high_resolution_clock::now();

    // Print sorted transactions
    cout << "\nTransactions sorted by date (ascending DD/MM/YYYY):\n";
    for (int i = 0; i < transactionCount; ++i) {
        cout << transactions[i].date << " | " << transactions[i].customer_ID 
            << " | " << transactions[i].product << " | RM" << transactions[i].price << endl;
    }

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Total number of transactions: " << transactionCount << endl;

    cout << "Time taken to sort transactions: " << duration.count() << " milliseconds" << endl;

    size_t memoryUsed = estimateMemoryUsage(transactions, transactionCount);
    cout << "\nEstimated memory used: " << memoryUsed << " bytes" << endl;


    delete[] transactions;
    return 0;
}
