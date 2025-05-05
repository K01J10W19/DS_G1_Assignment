#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <chrono>  // Added for timing
#include "Arrays.hpp"
using namespace std;
using namespace std::chrono;

void TransactionToArrays(const string& file_name, TransactionsArray*& array, int& count) {
    int capacity = 0;
    ifstream file(file_name); 
    string line; 
    getline(file,line); 
    while(getline(file, line)){ 
        if(count >= capacity){
            int new_capacity = capacity + 10;
            TransactionsArray* temp = new TransactionsArray[new_capacity];
            for(int i = 0; i < count; ++i){
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

float PercentageOfSelectedCategoryAndPayment(TransactionsArray* array, int count, const string& selectedCategory, const string& selectedPayment) {
    int totalCategory = 0;
    int categoryAndPaymentMatch = 0;

    for (int i = 0; i < count; ++i) {
        string category = array[i].category;
        string payment = array[i].payment_method;

        // Normalize to lowercase
        transform(category.begin(), category.end(), category.begin(), ::tolower);
        transform(payment.begin(), payment.end(), payment.begin(), ::tolower);

        if (category == selectedCategory) {
            totalCategory++;
            if (payment == selectedPayment) {
                categoryAndPaymentMatch++;
            }
        }
    }

    if (totalCategory == 0) return 0.0f;

    return (static_cast<float>(categoryAndPaymentMatch) / totalCategory) * 100.0f;
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

    string categoryInput, paymentInput;
    cout << "Enter category you want to search (e.g., Automotive, Beauty, Books, Electronics, Fashion, Furniture, Groceries, Home Appliances, Sports, Toys.): ";
    getline(cin, categoryInput);
    cout << "Enter payment method you want to search (e.g., Credit Card, Cash on Delivery, PayPal, Bank Transfer, Debit Card.): ";
    getline(cin, paymentInput);

    // Normalize user input to lowercase to match the data inside the arrays
    transform(categoryInput.begin(), categoryInput.end(), categoryInput.begin(), ::tolower);
    transform(paymentInput.begin(), paymentInput.end(), paymentInput.begin(), ::tolower);


    // Time the percentage calculation
    auto start = high_resolution_clock::now();

    float percent = PercentageOfSelectedCategoryAndPayment(transactions, transactionCount, categoryInput, paymentInput);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start); // microseconds for finer resolution


    cout << fixed << setprecision(2);
    cout << "\nPercentage of '" << categoryInput << "' purchases made with '" << paymentInput << "': " << percent << "%" << endl;

    cout << "Total number of transactions: " << transactionCount << endl;

    cout << "Time taken for analysis: " << duration.count() << " milliseconds" << endl;

    size_t memoryUsed = estimateMemoryUsage(transactions, transactionCount);
    cout << "\nEstimated memory used: " << memoryUsed << " bytes" << endl;

    delete[] transactions;
    return 0;
}
