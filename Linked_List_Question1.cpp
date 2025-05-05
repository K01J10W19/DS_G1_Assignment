#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include "LinkedList.hpp"

using namespace std;
using namespace std::chrono;

void TransactionsToLinkedList(const string& file_name, TransactionsNode*& head, TransactionsNode*& tail) {
    ifstream file(file_name);
    string line;

    head = tail = nullptr;
    getline(file, line); // skip header

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
    while (temp) {
        TransactionsNode* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = nullptr;
}

bool compareByDate(const TransactionsNode* a, const TransactionsNode* b) {
    int dayA = stoi(a->date.substr(0, 2));
    int monthA = stoi(a->date.substr(3, 2));
    int yearA = stoi(a->date.substr(6, 4));

    int dayB = stoi(b->date.substr(0, 2));
    int monthB = stoi(b->date.substr(3, 2));
    int yearB = stoi(b->date.substr(6, 4));

    if (yearA != yearB) return yearA < yearB;
    if (monthA != monthB) return monthA < monthB;
    return dayA < dayB;
}

TransactionsNode* split(TransactionsNode* head) {
    TransactionsNode* slow = head;
    TransactionsNode* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    TransactionsNode* mid = slow->next;
    slow->next = nullptr;
    if (mid) mid->prev = nullptr;
    return mid;
}

TransactionsNode* mergeSorted(TransactionsNode* a, TransactionsNode* b) {
    if (!a) return b;
    if (!b) return a;

    if (compareByDate(a, b)) {
        a->next = mergeSorted(a->next, b);
        if (a->next) a->next->prev = a;
        a->prev = nullptr;
        return a;
    } else {
        b->next = mergeSorted(a, b->next);
        if (b->next) b->next->prev = b;
        b->prev = nullptr;
        return b;
    }
}

TransactionsNode* mergeSort(TransactionsNode* head) {
    if (!head || !head->next) return head;
    TransactionsNode* mid = split(head);
    TransactionsNode* left = mergeSort(head);
    TransactionsNode* right = mergeSort(mid);
    return mergeSorted(left, right);
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

    // Load transactions into the linked list
    TransactionsToLinkedList("transactions_cleaned.csv", tHead, tTail);

    // Measure time for sorting
    auto start = high_resolution_clock::now();

    // Sort by date using merge sort
    tHead = mergeSort(tHead);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    // Print sorted list
    TransactionsNode* temp = tHead;
    while (temp) {
        cout << temp->date << " - " << temp->customer_ID << " - RM" << temp->price << endl;
        temp = temp->next;
    }

    cout << "Total Transactions: " << countLinkedList(tHead) << endl;

    cout << "Time taken to sort transactions: " << duration.count() << " milliseconds" << endl;

    size_t memoryUsed = estimateMemoryUsage(tHead);
    cout << "\nEstimated memory used: " << memoryUsed << " bytes" << endl;
    clearLinkedList(tHead);

    // Free memory
    clearLinkedList(tHead);
    return 0;
}
