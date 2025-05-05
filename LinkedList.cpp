#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "LinkedList.hpp"
using namespace std;

void ReviewsToLinkedList(const string& file_name, ReviewsNode*& head, ReviewsNode*& tail){
    ifstream file(file_name); // input the file
    string line; // variable called line

    head = tail = nullptr; // head and tail of doubly linked list default to nullptr

    getline(file,line); // Ignore header

    while(getline(file, line)){ // read the file line by line
        stringstream ss(line);  
        string item;
        ReviewsNode* newNode = new ReviewsNode(); // set pointer in doubly linked list

        getline(ss, item, ','); // attribute 01 product ID (str)
        newNode -> product_ID = item;
        getline(ss, item, ','); // attribute 02 Customer ID (str)
        newNode -> customer_ID = item;
        getline(ss, item, ','); // attribute 03 Rating (int)
        newNode -> rating = stoi(item);
        getline(ss, item, ','); // attribute 04 Review Text (str)
        newNode -> review_text = item; 

        if(!head){ // if empty means this is a first node
            head = tail = newNode; // head and tail point to newNode
        } else{
            tail-> next = newNode; // link next to the new node
            newNode-> prev = tail; // link prev back to the current tail
            tail = newNode; // update tail to new last node
        }
    }
}
void TransactionsToLinkedList(const string& file_name, TransactionsNode*& head, TransactionsNode*& tail){
    ifstream file(file_name); // input the file
    string line; // variable called line

    head = tail = nullptr; // head and tail of doubly linked list default to nullptr

    getline(file,line); // Ignore header

    while(getline(file, line)){ // read the file line by line
        stringstream ss(line);  
        string item;
        TransactionsNode* newNode = new TransactionsNode(); // set pointer in doubly linked list

        getline(ss, item, ','); // attribute 01 Customer ID (str)
        newNode -> customer_ID = item;
        getline(ss, item, ','); // attribute 02 product (str)
        newNode -> product = item;
        getline(ss, item, ','); // attribute 03 Category (str)
        newNode -> category = item;
        getline(ss, item, ','); // attribute 04 price (double)
        newNode -> price = stof(item); 
        getline(ss, item, ','); // attribute 05 date (str)
        newNode -> date = item;
        getline(ss, item, ','); // attribute 06 payment method (str)
        newNode -> payment_method = item;
        
        if(!head){ // if empty means this is a first node
            head = tail = newNode; // head and tail point to newNode
        } else{
            tail-> next = newNode; // link next to the new node
            newNode-> prev = tail; // link prev back to the current tail
            tail = newNode; // update tail to new last node
        }
    }
}

int countLinkedList(ReviewsNode* head){
    int count = 0;
    ReviewsNode* temp = head;
    while(temp != nullptr){
        count++;
        temp = temp->next;
    }
    return count;
}

int countLinkedList(TransactionsNode* head){
    int count = 0;
    TransactionsNode* temp = head;
    while(temp != nullptr){
        count++;
        temp = temp->next;
    }
    return count;
}

void clearLinkedList(ReviewsNode*& head) {
    ReviewsNode* temp = head;
    while (temp != nullptr) {
        ReviewsNode* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = nullptr; 
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

//////////////////////////////////////////////////////////////////////////
// Koh Chun Wei TP067580 (Quick Sort & Recursion Search)
// 1.
string convertDateFormatll(const string& date){
    int day, month, year;
    char s1,s2;
    istringstream iss(date);
    iss >> day >> s1 >> month >> s2 >> year;
    ostringstream oss;
    oss << year;
    if (month < 10) oss << '0';
    oss << month;
    if (day < 10) oss << '0';
    oss << day;
    return oss.str();
}
TransactionsNode* partitionbydatell(TransactionsNode* low, TransactionsNode* high) {
    string pivot = convertDateFormatll(high->date);
    TransactionsNode* i = low->prev;

    for (TransactionsNode* j = low; j != high; j = j->next) {
        if (convertDateFormatll(j->date) < pivot) {
            i = (i == nullptr) ? low : i->next;
            swap(j->customer_ID, i->customer_ID);
            swap(j->product, i->product);
            swap(j->category, i->category);
            swap(j->price, i->price);
            swap(j->date, i->date);
            swap(j->payment_method, i->payment_method);
        }
    }
    i = (i == nullptr) ? low : i->next;
    swap(i->customer_ID, high->customer_ID);
    swap(i->product, high->product);
    swap(i->category, high->category);
    swap(i->price, high->price);
    swap(i->date, high->date);
    swap(i->payment_method, high->payment_method);

    return i;
}
void quickSortbydatell(TransactionsNode* low, TransactionsNode* high) {
    if (high != nullptr && low != high && low != high->next) {
        TransactionsNode* p = partitionbydatell(low, high);
        quickSortbydatell(low, p->prev);
        quickSortbydatell(p->next, high);
    }
}
void displayTransactions(TransactionsNode* head) {
    while (head) {
        cout << head->customer_ID << ", "
            << head->product << ", "
            << head->date << ", "<<"\n";
        head = head->next;
    }
}
int countTransactions(TransactionsNode* head) {
    if (head == nullptr) return 0;
    return 1 + countTransactions(head->next);
}
//// U Guys Can Add+ Here below continue
//////////////////////////////////////////////////////////////////////////
// Koh Chun Wei TP067580 (Quick Sort & Recursion Search)
// 2.
string normalizell(string& str){
    string clean;
    for (char& c : str) {
        if (!isspace(c)) clean += tolower(c);
    }
    return clean;
}
TransactionsNode* partitionbycategoryll(TransactionsNode* low, TransactionsNode* high) {
    string pivot = high->category;
    TransactionsNode* i = low->prev;

    for (TransactionsNode* j = low; j != high; j = j->next) {
        if (j->category < pivot) {
            i = (i == nullptr) ? low : i->next;
            swap(j->customer_ID, i->customer_ID);
            swap(j->product, i->product);
            swap(j->category, i->category);
            swap(j->price, i->price);
            swap(j->date, i->date);
            swap(j->payment_method, i->payment_method);
        }
    }
    i = (i == nullptr) ? low : i->next;
    swap(i->customer_ID, high->customer_ID);
    swap(i->product, high->product);
    swap(i->category, high->category);
    swap(i->price, high->price);
    swap(i->date, high->date);
    swap(i->payment_method, high->payment_method);

    return i;
}
void quickSortbycategoryll(TransactionsNode* low, TransactionsNode* high) {
    if (high != nullptr && low != high && low != high->next) {
        TransactionsNode* p = partitionbycategoryll(low, high);
        quickSortbycategoryll(low, p->prev);
        quickSortbycategoryll(p->next, high);
    }
}
void displayCategory(TransactionsNode* head) {
    while (head) {
        cout << head->customer_ID << ", "
            << head->product << ", "
            << head->category << ", "<<"\n";
        head = head->next;
    }
}

int countElectronicsCredit(TransactionsNode* node) {
    if (node == nullptr) return 0;

    string category = normalizell(node->category);
    string payment = normalizell(node->payment_method);

    if (category == "electronics" && payment == "creditcard") {
        return 1 + countElectronicsCredit(node->next);
    }

    return countElectronicsCredit(node->next);
}
int countElectronicsTotal(TransactionsNode* node) {
    if (node == nullptr) return 0;

    string category = normalizell(node->category);
    if (category == "electronics") {
        return 1 + countElectronicsTotal(node->next);
    }

    return countElectronicsTotal(node->next);
}
//// U Guys Can Add+ Here below continue
//////////////////////////////////////////////////////////////////////////
// Koh Chun Wei TP067580 (Quick Sort & Recursion Search)
// 3. 
void countWordsFromOnell(ReviewsNode* head, WordFrequencyll*& wf_head, int& totalWords) {
    wf_head = nullptr;
    totalWords = 0;
    ReviewsNode* current = head;

    while (current != nullptr) {
        if (current->rating == 1) {
            stringstream ss(current->review_text);
            string word;

            while (ss >> word) {
                word.erase(0, word.find_first_not_of(" \t\n\r\f\v"));
                word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1);
                word.erase(remove(word.begin(), word.end(), '\''), word.end());
                word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
                for (char& c : word) c = tolower(c);
                if (word.empty()) continue;

                totalWords++;
                WordFrequencyll* wf_curr = wf_head;
                bool found = false;
                while (wf_curr != nullptr) {
                    if (wf_curr->word == word) {
                        wf_curr->count++;
                        found = true;
                        break;
                    }
                    wf_curr = wf_curr->next;
                }

                if (!found) {
                    WordFrequencyll* new_wf_head = new WordFrequencyll{word, 1, nullptr, nullptr};
                    if (wf_head == nullptr) {
                        wf_head = new_wf_head;
                    } else {
                        // Insert at end
                        WordFrequencyll* tail = wf_head;
                        while (tail->next != nullptr) tail = tail->next;
                        tail->next = new_wf_head;
                        new_wf_head->prev = tail;
                    }
                }
            }
        }
        current = current->next;
    }
}
void printWordOccurrences(WordFrequencyll* wf_head) {
    WordFrequencyll* current = wf_head;
    while (current != nullptr) {
        for (int i = 0; i < current->count; ++i) {
            cout << current->word <<"- 1"<< endl;
        }
        current = current->next;
    }
}

void printWordOccurrences2(WordFrequencyll* wf_head) {
    WordFrequencyll* current = wf_head;
    while (current != nullptr) {
        cout << current->word << " : "<<current->count<< endl;
        current = current->next;
    }
}

void sortWordListByFrequency(WordFrequencyll*& head) {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        WordFrequencyll* current = head;

        while (current->next != nullptr) {
            if (current->count < current->next->count) {
                swap(current->word, current->next->word);
                swap(current->count, current->next->count);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}


