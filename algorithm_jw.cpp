#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

// Import csv file to Doubly Linked List
struct ReviewsNode{
    string product_ID;
    string customer_ID;
    int rating;
    string review_text;
    ReviewsNode* next = nullptr;
    ReviewsNode* prev = nullptr;
};
struct TransactionsNode {
    string customer_ID;
    string product;
    string category;
    float price;
    string date;
    string payment_method;
    TransactionsNode* next = nullptr;
    TransactionsNode* prev = nullptr;
};
struct ReviewFrequencyll{
    string sentence;
    int count;
    ReviewFrequencyll* next = nullptr;
    ReviewFrequencyll* prev = nullptr;
};
// Import csv file to Dynamic Array
struct ReviewsArray{
    string product_ID;
    string customer_ID;
    int rating;
    string review_text;
};
struct TransactionsArray{
    string customer_ID;
    string product;
    string category;
    float price;
    string date;
    string payment_method;
};
struct ReviewFrequency{
    string sentence;
    int count;
};

// Sorting Algorithms (Quick Sort) && Searching Algorithms (Recursive Search)

// 1. How can you efficiently sort customer transactions by date and display the total number of transactions in both datasets?
    // Array
    string convertDateFormat(const string& date){
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
    int partitionbydate(TransactionsArray* arr, int low, int high){
        string pivot = convertDateFormat(arr[high].date);
        int i = low - 1;

        for(int j = low; j < high; ++j){
            if(convertDateFormat(arr[j].date) < pivot){
                i++;
                TransactionsArray temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        TransactionsArray temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        return i + 1;
    }
    void quickSortbydate(TransactionsArray* arr, int low, int high){
        if(low < high){
            int par_by_date = partitionbydate(arr,low,high);
            quickSortbydate(arr, low, par_by_date - 1);
            quickSortbydate(arr,par_by_date + 1, high);
        }
    }
    void recursiveSearchByCustomerID(TransactionsArray* arr, int index, int size, const string& targetID, int num) {
        int qty = num;
        if (index >= size) return;
    
        if (arr[index].customer_ID == targetID) {
            cout << "- - - - -    "<<qty<<"    - - - - -\n";
            cout << "Customer ID: "<<arr[index].customer_ID<<endl;
            cout << "Product: "<<arr[index].product<<endl;
            cout << "Date of Purchase: "<<arr[index].date<<endl;
            qty++;
        }
    
        recursiveSearchByCustomerID(arr, index + 1, size, targetID, qty);
    }  
    // Linked List
    TransactionsNode* partitionbydatell(TransactionsNode* low, TransactionsNode* high) {
        string pivot = convertDateFormat(high->date);
        TransactionsNode* i = low->prev;
    
        for (TransactionsNode* j = low; j != high; j = j->next) {
            if (convertDateFormat(j->date) < pivot) {
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
// 2. What percentage of purchases in the “Electronics” category were made using Credit Card payments? 
// (Hint: Need to search and filter transactions based on category and payment method)
    // Array
    string normalize(string& str){
        string clean;
        for (char& c : str) {
            if (!isspace(c)) clean += tolower(c);
        }
        return clean;
    }    
    int partitionbycategory(TransactionsArray* arr, int low, int high){
        string pivot = arr[high].category;
        int i = low - 1;

        for(int j = low; j < high; ++j){
            if(arr[j].category < pivot){
                ++i;
                TransactionsArray temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        TransactionsArray temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        return i + 1;
    }
    void quickSortbycategory(TransactionsArray* arr, int low, int high){
        if(low < high){
            int par_by_category = partitionbycategory(arr,low,high);
            quickSortbycategory(arr, low, par_by_category - 1);
            quickSortbycategory(arr,par_by_category + 1, high);
        }
    }
    int countElectronics(TransactionsArray* arr, int index, int size){
        if (index >= size) return 0;
        return (normalize(arr[index].category) == "electronics" ? 1 : 0) + countElectronics(arr, index + 1, size);
    }
    int countElectronicsCreditCard(TransactionsArray* arr, int index, int size) {
        if (index >= size) return 0;
        return (normalize(arr[index].category) == "electronics" && normalize(arr[index].payment_method) == "creditcard" ? 1 : 0)
                + countElectronicsCreditCard(arr, index + 1, size);
    }
    // Linked List
    int countElectronicsCredit(TransactionsNode* node) {
        if (node == nullptr) return 0;
    
        string category = normalize(node->category);
        string payment = normalize(node->payment_method);
    
        if (category == "electronics" && payment == "creditcard") {
            return 1 + countElectronicsCredit(node->next);
        }
    
        return countElectronicsCredit(node->next);
    }
    int countElectronicsTotal(TransactionsNode* node) {
        if (node == nullptr) return 0;
    
        string category = normalize(node->category);
        if (category == "electronics") {
            return 1 + countElectronicsTotal(node->next);
        }
    
        return countElectronicsTotal(node->next);
    }
// 3. Which words are most frequently used in product reviews rated 1-star? 
// (Hint: Extract the most common words, sort them by frequency, and present the results)
    // Array
    void show1StarReviews(ReviewsArray* arr, int review_count) {
        int count = 0;
        for (int i = 0; i < review_count; ++i) {
            if (arr[i].rating == 1) {
                cout << "1-star review (" << ++count << "): " << arr[i].review_text << endl;
            }
        }
        cout << "\nTotal 1-star reviews shown: " << count << endl;
    }
    void AddUpdateSentence(ReviewFrequency* arr, int& count, int& capacity, const string& sentence){
        for (int i = 0; i < count; ++i) {
            if (arr[i].sentence == sentence) {
                arr[i].count++;
                return;
            }
        }
        if (count == capacity) {
            int newCapacity = capacity * 2;
            ReviewFrequency* newArray = new ReviewFrequency[newCapacity];
            for (int i = 0; i < count; ++i)
                newArray[i] = arr[i];
            delete[] arr;
            arr = newArray;
            capacity = newCapacity;
        }
    
        arr[count].sentence = sentence;
        arr[count].count = 1;
        count++;
    }
    void extractFrequentSentences(ReviewsArray* arr, int review_count, ReviewFrequency*& freqArr, int& freqcount, int& capacity) {
        for (int i = 0; i < review_count; ++i) {
            if (arr[i].rating == 1) {
                AddUpdateSentence(freqArr, freqcount, capacity, arr[i].review_text);
            }
        }
    }
    int partitionByFrequency(ReviewFrequency* arr, int low, int high) {
        int pivot = arr[high].count;
        int i = low - 1;
    
        for (int j = low; j < high; ++j) {
            if (arr[j].count > pivot) {  // descending order
                ++i;
                ReviewFrequency temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    
        ReviewFrequency temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
    
        return i + 1;
    }    
    void quickSortsentencesbyfrequency(ReviewFrequency* arr, int low, int high) {
        if (low < high) {
            int pi = partitionByFrequency(arr, low, high);
            quickSortsentencesbyfrequency(arr, low, pi - 1);
            quickSortsentencesbyfrequency(arr, pi + 1, high);
        }
    }
    void showTopFrequentSentences(ReviewFrequency* arr, int count, int topN) {
        cout << "\nTop " << topN << " most frequent 1-star review sentences:\n";
        for (int i = 0; i < topN && i < count; ++i) {
            cout << i + 1 << ". \"" << arr[i].sentence << " >>> " << arr[i].count << " times\n";
        }
    }
    // Linked List
    void addUpdateSentencell(ReviewFrequencyll*& head, ReviewFrequencyll*& tail, const string& sentence) {
        ReviewFrequencyll* current = head;
        while (current) {
            if (current->sentence == sentence) {
                current->count++;
                return;
            }
            current = current->next;
        }
    
        ReviewFrequencyll* newNode = new ReviewFrequencyll{sentence, 1, nullptr, tail};
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    void splitIntoSentences(const string& review, ReviewFrequencyll*& sentenceHead, ReviewFrequencyll*& sentenceTail) {
        string sentence = "";
        for (char c : review) {
            
            if (c == '.') {
                int start = 0, end = sentence.size() - 1;
                while (start <= end && isspace(sentence[start])) start++;
                while (end >= start && isspace(sentence[end])) end--;
    
                if (start <= end) {
                    string cleaned = sentence.substr(start, end - start + 1);
                    if (!cleaned.empty()) {
                        addUpdateSentencell(sentenceHead, sentenceTail, cleaned);
                    }
                }
                sentence = "";
            } else {
                sentence += c;
            }
        }
    
        if (!sentence.empty()) {
            int start = 0, end = sentence.size() - 1;
            while (start <= end && isspace(sentence[start])) start++;
            while (end >= start && isspace(sentence[end])) end--;
    
            if (start <= end) {
                string cleaned = sentence.substr(start, end - start + 1);
                if (!cleaned.empty()) {
                    addUpdateSentencell(sentenceHead, sentenceTail, cleaned);
                }
            }
        }
    }
    void extract1StarSentences(ReviewsNode* reviewHead, ReviewFrequencyll*& sentenceHead, ReviewFrequencyll*& sentenceTail) {
        ReviewsNode* curr = reviewHead;
        while (curr != nullptr) {
            if (curr->rating == 1) {
                splitIntoSentences(curr->review_text, sentenceHead, sentenceTail);
            }
            curr = curr->next;
        }
    }
    ReviewFrequencyll* getTail(ReviewFrequencyll* cur) {
        while (cur && cur->next) cur = cur->next;
        return cur;
    }
    ReviewFrequencyll* partition(ReviewFrequencyll* low, ReviewFrequencyll* high) {
        int pivot = high->count;
        ReviewFrequencyll* i = low->prev;
    
        for (ReviewFrequencyll* j = low; j != high; j = j->next) {
            if (j->count >= pivot) {
                i = (i == nullptr) ? low : i->next;
                swap(i->sentence, j->sentence);
                swap(i->count, j->count);
            }
        }
        i = (i == nullptr) ? low : i->next;
        swap(i->sentence, high->sentence);
        swap(i->count, high->count);
        return i;
    }
    void quickSortll(ReviewFrequencyll* low, ReviewFrequencyll* high) {
        if (high != nullptr && low != high && low != high->next) {
            ReviewFrequencyll* p = partition(low, high);
            quickSortll(low, p->prev);
            quickSortll(p->next, high);
        }
    }
    void displayTopSentences(ReviewFrequencyll* head, int topN) {
        int count = 0;
        while (head != nullptr && count < topN) {
            cout << "\"" << head->sentence << " >>> " << head->count << " times\n";
            head = head->next;
            count++;
        }
    }
