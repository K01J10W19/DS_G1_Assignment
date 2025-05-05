#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "LinkedList.hpp"
using namespace std;

void ReviewsToLinkedList(const string& file_name, ReviewsNode*& head, ReviewsNode*& tail) {
    ifstream file(file_name);
    string line;
    head = tail = nullptr;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        string fields[4]; // We expect 4 fields
        string current;
        bool inQuotes = false;
        int fieldIndex = 0;

        for (char c : line) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                if (fieldIndex < 4) {
                    fields[fieldIndex++] = current;
                    current.clear();
                }
            } else {
                current += c;
            }
        }
        if (fieldIndex < 4) {
            fields[fieldIndex] = current; // Final field
        }

        ReviewsNode* newNode = new ReviewsNode();
        newNode->product_ID = fields[0];
        newNode->customer_ID = fields[1];
        newNode->rating = stoi(fields[2]);
        newNode->review_text = fields[3];
        newNode->next = nullptr;
        newNode->prev = tail;

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    file.close();
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
/////////////////////////////////////////////////////////////////////////
// Nang Zhen Ning Q1 Q2 Q3
//////////////////////////////////////////////////////////////////////////
// Nang Zhen Ning Tp069063 Heap sort and Exponental search
// 1.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "LinkedList.hpp" 

using namespace std;

// Function to load Transactions CSV into linked list
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

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
}

// Function to load Reviews CSV into linked list
void ReviewsToLinkedList(const string& file_name, ReviewsNode*& head, ReviewsNode*& tail) {
    ifstream file(file_name);
    string line;
    head = tail = nullptr;

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        ReviewsNode* newNode = new ReviewsNode();

        getline(ss, item, ',');
        newNode->product_ID = item;

        getline(ss, item, ',');
        newNode->customer_ID = item;

        getline(ss, item, ',');
        newNode->rating = stoi(item);

        getline(ss, item, ',');
        newNode->review_text = item;

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
}

// Count nodes in transaction list
int countLinkedList(TransactionsNode* head) {
    int count = 0;
    TransactionsNode* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Count nodes in review list
int countLinkedList(ReviewsNode* head) {
    int count = 0;
    ReviewsNode* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Sort transactions by date (ascending)
void sortTransactionsByDate(TransactionsNode*& head) {
    if (!head || !head->next) return;

    bool swapped;
    do {
        swapped = false;
        TransactionsNode* curr = head;

        while (curr->next) {
            if (curr->date > curr->next->date) {
                swap(curr->customer_ID, curr->next->customer_ID);
                swap(curr->product, curr->next->product);
                swap(curr->category, curr->next->category);
                swap(curr->price, curr->next->price);
                swap(curr->date, curr->next->date);
                swap(curr->payment_method, curr->next->payment_method);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

// Print transactions (for verification)
void printTransactions(TransactionsNode* head) {
    TransactionsNode* current = head;
    while (current) {
        cout << current->date << " - " << current->customer_ID << " bought " << current->product
            << " (" << current->category << ") using " << current->payment_method << endl;
        current = current->next;
    }
}

int main() {
    TransactionsNode* transactionsHead = nullptr;
    TransactionsNode* transactionsTail = nullptr;
    ReviewsNode* reviewsHead = nullptr;
    ReviewsNode* reviewsTail = nullptr;

    // Load the data
    TransactionsToLinkedList("Transaction.csv", transactionsHead, transactionsTail);
    ReviewsToLinkedList("Review.csv", reviewsHead, reviewsTail);

    // Sort transactions by date
    sortTransactionsByDate(transactionsHead);

    // Output sorted transactions (optional)
    cout << "Sorted Transactions by Date:\n";
    printTransactions(transactionsHead);
    cout << endl;

    // Display total counts
    cout << "Total number of transactions: " << countLinkedList(transactionsHead) << endl;
    cout << "Total number of reviews: " << countLinkedList(reviewsHead) << endl;

    return 0;
}

//// U Guys Can Add+ Here below continue
//////////////////////////////////////////////////////////////////////////
// Nang Zhen Ning Tp069063 Heap sort and Exponental search
// 2.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "LinkedList.hpp" 

using namespace std;

// Load transactions from CSV
void TransactionsToLinkedList(const string& file_name, TransactionsNode*& head, TransactionsNode*& tail) {
    ifstream file(file_name);
    string line;
    head = tail = nullptr;

    getline(file, line); // Skip header

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

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
}

// Function to calculate percentage of Electronics paid by Credit Card
void CalculateElectronicsCreditCardPercentage(TransactionsNode* head) {
    int totalElectronics = 0;
    int creditCardElectronics = 0;

    TransactionsNode* temp = head;
    while (temp) {
        // Convert both strings to lowercase for case-insensitive comparison
        string category = temp->category;
        string payment = temp->payment_method;
        transform(category.begin(), category.end(), category.begin(), ::tolower);
        transform(payment.begin(), payment.end(), payment.begin(), ::tolower);

        if (category == "electronics") {
            totalElectronics++;
            if (payment == "credit card") {
                creditCardElectronics++;
            }
        }

        temp = temp->next;
    }

    if (totalElectronics == 0) {
        cout << "No transactions in the 'Electronics' category." << endl;
    } else {
        float percentage = (static_cast<float>(creditCardElectronics) / totalElectronics) * 100;
        cout << fixed << setprecision(2);
        cout << "Percentage of 'Electronics' purchases made using Credit Card: " << percentage << "%" << endl;
    }
}

int main() {
    TransactionsNode* transactionsHead = nullptr;
    TransactionsNode* transactionsTail = nullptr;

    // Load transaction data
    TransactionsToLinkedList("Transaction.csv", transactionsHead, transactionsTail);

    // Calculate and display result
    CalculateElectronicsCreditCardPercentage(transactionsHead);

    return 0;
}

//// U Guys Can Add+ Here below continue
//////////////////////////////////////////////////////////////////////////
// Nang Zhen Ning Tp069063 Heap sort and Exponental search
// 3. 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <algorithm>
#include "LinkedList.hpp" 

using namespace std;

// Load reviews from CSV
void ReviewsToLinkedList(const string& file_name, ReviewsNode*& head, ReviewsNode*& tail) {
    ifstream file(file_name);
    string line;
    head = tail = nullptr;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        ReviewsNode* newNode = new ReviewsNode();

        getline(ss, item, ',');
        newNode->product_ID = item;

        getline(ss, item, ',');
        newNode->customer_ID = item;

        getline(ss, item, ',');
        newNode->rating = stoi(item);

        getline(ss, item, ',');
        newNode->review_text = item;

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
}

// Helper function to convert string to lowercase
string toLowerCase(const string& str) {
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

// Function to get most frequent words in 1-star reviews
void GetTopWordsInOneStarReviews(ReviewsNode* head, int topN = 10) {
    map<string, int> wordFreq;
    regex wordRegex("\\b[a-zA-Z]+\\b");  // Match words (letters only)

    ReviewsNode* current = head;
    while (current) {
        if (current->rating == 1) {
            string review = toLowerCase(current->review_text);
            sregex_iterator it(review.begin(), review.end(), wordRegex);
            sregex_iterator end;

            while (it != end) {
                string word = it->str();
                wordFreq[word]++;
                ++it;
            }
        }
        current = current->next;
    }

    // Move to vector for sorting
    vector<pair<string, int>> sortedWords(wordFreq.begin(), wordFreq.end());
    sort(sortedWords.begin(), sortedWords.end(), [](auto& a, auto& b) {
        return b.second < a.second; // Descending
    });

    cout << "Top " << topN << " most used words in 1-star reviews:\n";
    for (int i = 0; i < min(topN, (int)sortedWords.size()); ++i) {
        cout << sortedWords[i].first << ": " << sortedWords[i].second << " times\n";
    }
}

int main() {
    ReviewsNode* reviewsHead = nullptr;
    ReviewsNode* reviewsTail = nullptr;

    // Load review data
    ReviewsToLinkedList("Review.csv", reviewsHead, reviewsTail);

    // Analyze top words in 1-star reviews
    GetTopWordsInOneStarReviews(reviewsHead, 10); // Top 10 by default

    return 0;
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
void bubbleSortByDateLL(TransactionsNode* head) {
    bool swapped;
    do {
        swapped = false;
        TransactionsNode* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (convertDateFormatll(current->date) > convertDateFormatll(current->next->date)) {
                swap(current->customer_ID, current->next->customer_ID);
                swap(current->product, current->next->product);
                swap(current->category, current->next->category);
                swap(current->price, current->next->price);
                swap(current->date, current->next->date);
                swap(current->payment_method, current->next->payment_method);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
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
TransactionsNode* getNodeAt(TransactionsNode* head, int index) {
    int currentIndex = 0;
    TransactionsNode* current = head;
    while (current != nullptr && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }
    return current;
}

string normalize2(const string& text) {
    string result = text;
    result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
void bubbleSortByCategoryLL(TransactionsNode* head) {
    bool swapped;
    do {
        swapped = false;
        TransactionsNode* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (normalize2(current->category) > normalize2(current->next->category)) {
                // Swap contents
                swap(current->customer_ID, current->next->customer_ID);
                swap(current->product, current->next->product);
                swap(current->category, current->next->category);
                swap(current->price, current->next->price);
                swap(current->date, current->next->date);
                swap(current->payment_method, current->next->payment_method);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

int binarySearchCategoryLL(TransactionsNode* head, int size, const string& target) {
    int low = 0, high = size - 1;
    string tgt = normalize2(target);

    while (low <= high) {
        int mid = (low + high) / 2;
        TransactionsNode* midNode = getNodeAt(head, mid);
        if (!midNode) break;

        string midCat = normalize2(midNode->category);
        if (midCat == tgt) return mid;  // Return index of first match
        else if (midCat < tgt) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
void countElectronicsCreditCardLL_Binary(TransactionsNode* head, int size, int& total, int& creditCard) {
    int index = binarySearchCategoryLL(head, size, "electronics");
    if (index == -1) {
        total = 0;
        creditCard = 0;
        return;
    }

    // Expand left
    int left = index;
    while (left >= 0) {
        TransactionsNode* node = getNodeAt(head, left);
        if (!node || normalize2(node->category) != "electronics") break;
        left--;
    }

    // Expand right
    int right = index;
    while (right < size) {
        TransactionsNode* node = getNodeAt(head, right);
        if (!node || normalize2(node->category) != "electronics") break;
        right++;
    }

    // Count from left+1 to right-1
    total = 0;
    creditCard = 0;
    for (int i = left + 1; i < right; ++i) {
        TransactionsNode* node = getNodeAt(head, i);
        if (node) {
            total++;
            if (normalize2(node->payment_method) == "creditcard") {
                creditCard++;
            }
        }
    }
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

void countWordsFromOneLL(ReviewsNode* head, WordFrequencyll*& wf_head, int& totalWords) {
    wf_head = nullptr;
    totalWords = 0;

    while (head != nullptr) {
        if (head->rating == 1) {
            std::stringstream ss(head->review_text);
            std::string word;

            while (ss >> word) {
                // Clean word: keep only alphabets
                word.erase(remove_if(word.begin(), word.end(), [](char c) {
                    return !isalpha(c);
                }), word.end());
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                if (word.empty()) continue;

                totalWords++;

                // Search manually
                WordFrequencyll* curr = wf_head;
                bool found = false;
                while (curr != nullptr) {
                    if (curr->word == word) {
                        curr->count++;
                        found = true;
                        break;
                    }
                    curr = curr->next;
                }

                // Insert at end if not found
                if (!found) {
                    WordFrequencyll* newNode = new WordFrequencyll{word, 1, nullptr, nullptr};
                    if (!wf_head) {
                        wf_head = newNode;
                    } else {
                        WordFrequencyll* tail = wf_head;
                        while (tail->next) tail = tail->next;
                        tail->next = newNode;
                        newNode->prev = tail;
                    }
                }
            }
        }
        head = head->next;
    }
}

void bubbleSortByFrequencyLL(WordFrequencyll*& head) {
    if (!head) return;
    bool swapped;

    do {
        swapped = false;
        WordFrequencyll* curr = head;

        while (curr && curr->next) {
            if (curr->count < curr->next->count) {
                std::swap(curr->word, curr->next->word);
                std::swap(curr->count, curr->next->count);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

void displayTopWordsLL(WordFrequencyll* head) {
    std::cout << "\nAll Word Frequencies in 1-Star Reviews (Linked List):\n";
    while (head != nullptr) {
        std::cout << head->word << ": " << head->count << " times\n";
        head = head->next;
    }
}
int countTotalWordsInOneStarReviews(ReviewsNode* head) {
    if (head == nullptr) return 0;

    int wordCount = 0;
    if (head->rating == 1) {
        stringstream ss(head->review_text);
        string word;
        while (ss >> word) {
            word.erase(0, word.find_first_not_of(" \t\n\r\f\v"));
            word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1);
            word.erase(remove(word.begin(), word.end(), '\''), word.end());
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
            if (!word.empty()) wordCount++;
        }
    }

    return wordCount + countTotalWordsInOneStarReviews(head->next);
}



