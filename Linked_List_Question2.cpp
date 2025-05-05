#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>  // for setprecision
#include <chrono>   // for timing
#include "LinkedList.hpp"  // Assuming it defines TransactionsNode

using namespace std;
using namespace std::chrono;

void TransactionsToLinkedList(const string& file_name, TransactionsNode*& head, TransactionsNode*& tail) {
    ifstream file(file_name);
    string line;

    head = tail = nullptr;
    getline(file, line); // Ignore header

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        TransactionsNode* newNode = new TransactionsNode();

        getline(ss, item, ',');
        newNode->customer_ID = item;
        getline(ss, item, ',');
        newNode->product = item;
        getline(ss, item, ',');
        newNode->category = item;
        getline(ss, item, ',');
        newNode->price = stof(item);
        getline(ss, item, ',');
        newNode->date = item;
        getline(ss, item, ',');
        newNode->payment_method = item;

        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
}

int countLinkedList(TransactionsNode* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

void clearLinkedList(TransactionsNode*& head) {
    TransactionsNode* temp = head;
    while (temp != nullptr) {
        TransactionsNode* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = nullptr;
}

float PercentageOfSelectedCategoryAndPayment(TransactionsNode* head, const string& selectedCategory, const string& selectedPayment) {
    int totalCategory = 0;
    int categoryAndPaymentMatch = 0;

    TransactionsNode* current = head;
    while (current != nullptr) {
        string category = current->category;
        string payment = current->payment_method;

        // Normalize to lowercase
        transform(category.begin(), category.end(), category.begin(), ::tolower);
        transform(payment.begin(), payment.end(), payment.begin(), ::tolower);

        if (category == selectedCategory) {
            totalCategory++;
            if (payment == selectedPayment) {
                categoryAndPaymentMatch++;
            }
        }

        current = current->next;
    }

    if (totalCategory == 0) return 0.0f;

    return (static_cast<float>(categoryAndPaymentMatch) / totalCategory) * 100.0f;
}

size_t estimateStringSize(const string& str) {
    return str.capacity(); // Approximates heap usage for string content
}

size_t estimateMemoryUsage(TransactionsNode* head) {
    size_t total = 0;
    while (head) {
        total += sizeof(TransactionsNode); // base object
        total += estimateStringSize(head->customer_ID);
        total += estimateStringSize(head->product);
        total += estimateStringSize(head->category);
        total += estimateStringSize(head->date);
        total += estimateStringSize(head->payment_method);
        total += sizeof(float); // price
        head = head->next;
    }
    return total;
}

int main() {
    TransactionsNode* tHead = nullptr;
    TransactionsNode* tTail = nullptr;

    TransactionsToLinkedList("transactions_cleaned.csv", tHead, tTail);

    string categoryInput, paymentInput;
    cout << "Enter category you want to search (e.g., Automotive, Beauty, Books, Electronics, Fashion, Furniture, Groceries, Home Appliances, Sports, Toys.): ";
    getline(cin, categoryInput);
    cout << "Enter payment method you want to search (e.g., Credit Card, Cash on Delivery, PayPal, Bank Transfer, Debit Card.): ";
    getline(cin, paymentInput);

    // Normalize user input to lowercase
    transform(categoryInput.begin(), categoryInput.end(), categoryInput.begin(), ::tolower);
    transform(paymentInput.begin(), paymentInput.end(), paymentInput.begin(), ::tolower);

    // Measure execution time of percentage calculation
    auto start = high_resolution_clock::now();

    float percentage = PercentageOfSelectedCategoryAndPayment(tHead, categoryInput, paymentInput);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << fixed << setprecision(2);
    cout << "\nPercentage of '" << categoryInput << "' purchases made with '" << paymentInput << "': " << percentage << "%" << endl;

    cout << "Total Transactions: " << countLinkedList(tHead) << endl;

    cout << "Time taken for analysis: " << duration.count() << " milliseconds" << endl;

    size_t memoryUsed = estimateMemoryUsage(tHead);
    cout << "\nEstimated memory used: " << memoryUsed << " bytes" << endl;
    clearLinkedList(tHead);


    // Free memory
    clearLinkedList(tHead);
}
