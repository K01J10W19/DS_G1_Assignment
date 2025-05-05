#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "Arrays.hpp"
using namespace std;

void ReviewsToArrays(const string& file_name, ReviewsArray*& array, int& count){ 
    int capacity = 0;
    ifstream file(file_name); // input the file
    string line; // variable called line
    getline(file,line); // Ignore header
    while(getline(file, line)){ // read the file line by line
        if(count >= capacity){
            int new_capacity = capacity + 10;
            ReviewsArray* temp = new ReviewsArray[new_capacity];
            for(int i = 0; i < count; ++i){
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
            capacity = new_capacity;
        }
        stringstream ss(line);
        string item;

        getline(ss, item, ','); // attribute 01 product ID (str)
        array[count].product_ID = item;
        getline(ss, item, ','); // attribute 02 Customer ID (str)
        array[count].customer_ID = item;
        getline(ss, item, ','); // attribute 03 Rating (int)
        array[count].rating = stoi(item); 
        getline(ss, item, ','); // attribute 04 Review Text (str)
        array[count].review_text = item;
        ++count;
    }
}

void TransactionToArrays(const string& file_name, TransactionsArray*& array, int& count){
    int capacity = 0;
    ifstream file(file_name); // input the file
    string line; // variable called line
    getline(file,line); // Ignore header
    while(getline(file, line)){ // read the file line by line
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

        getline(ss, item, ','); // attribute 01 customer ID (str)
        array[count].customer_ID = item;
        getline(ss, item, ','); // attribute 02 product (str)
        array[count].product = item;
        getline(ss, item, ','); // attribute 03 category (int)
        array[count].category = item; 
        getline(ss, item, ','); // attribute 04 price (str)
        array[count].price = stof(item);
        getline(ss, item, ','); // attribute 05 date (str)
        array[count].date = item;
        getline(ss, item, ','); // attribute 06 payment method (str)
        array[count].payment_method = item;
        ++count;
    }
}


// // Nang Zhen Ning Tp069063 Q1
string convertDateFormat(const string& date) {
    int day, month, year;
    char ch;
    istringstream iss(date);
    iss >> day >> ch >> month >> ch >> year;

    ostringstream oss;
    oss << year;
    if (month < 10) oss << '0';
    oss << month;
    if (day < 10) oss << '0';
    oss << day;
    return oss.str(); 
}

void heapifyByDate(TransactionsArray* arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && convertDateFormat(arr[l].date) > convertDateFormat(arr[largest].date))
        largest = l;

    if (r < n && convertDateFormat(arr[r].date) > convertDateFormat(arr[largest].date))
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyByDate(arr, n, largest);
    }
}

void heapSortByDate(TransactionsArray* arr, int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapifyByDate(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyByDate(arr, i, 0);
    }
}

int binarySearchByCustomerID(TransactionsArray* arr, int left, int right, const string& target) {
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid].customer_ID == target)
            return mid;
        else if (arr[mid].customer_ID < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int exponentialSearchByCustomerID(TransactionsArray* arr, int size, const string& target) {
    if (arr[0].customer_ID == target)
        return 0;

    int i = 1;
    while (i < size && arr[i].customer_ID <= target)
        i *= 2;

    return binarySearchByCustomerID(arr, i / 2, min(i, size - 1), target);
}

#include "Arrays.hpp"

// int main() {
//     TransactionsArray* transactions = nullptr;
//     int transactionCount = 0;
//     TransactionToArrays("transactions_cleaned.csv", transactions, transactionCount);

//     // Sort using Heap Sort
//     heapSortByDate(transactions, transactionCount);

//     // Display total transactions
//     cout << "Total Transactions: " << transactionCount << endl;

//     // Show first 5 sorted by date
//     cout << "First 5 Transactions (sorted by date):" << endl;
//     for (int i = 0; i < transactionCount; i++) {
//         cout << transactions[i].date << " - "
//              << transactions[i].product << " - "
//              << transactions[i].customer_ID << endl;
//     }

//     // Exponential Search Example
//     string targetID = "CUST9410";
//     int index = exponentialSearchByCustomerID(transactions, transactionCount, targetID);
//     if (index != -1) {
//         cout << "Found " << targetID << " at index " << index << ": "
//              << transactions[index].product << " on " << transactions[index].date << endl;
//     } else {
//         cout << "Customer ID " << targetID << " not found." << endl;
//     }

//     delete[] transactions;
//     return 0;
// }

// Nang Zhen Ning TP069063 Q2
// void heapify(TransactionsArray* arr, int n, int i) {
//     int largest = i; // root
//     int left = 2 * i + 1;
//     int right = 2 * i + 2;

//     // Compare by category
//     if (left < n && arr[left].category > arr[largest].category)
//         largest = left;
//     if (right < n && arr[right].category > arr[largest].category)
//         largest = right;

//     if (largest != i) {
//         swap(arr[i], arr[largest]);
//         heapify(arr, n, largest);
//     }
// }

// void heapSortByCategory(TransactionsArray* arr, int n) {
//     // Build heap
//     for (int i = n / 2 - 1; i >= 0; i--)
//         heapify(arr, n, i);

//     // Extract elements from heap
//     for (int i = n - 1; i >= 0; i--) {
//         swap(arr[0], arr[i]);
//         heapify(arr, i, 0);
//     }
// }

// int binarySearchCategory(TransactionsArray* arr, int left, int right, const string& target) {
//     while (left <= right) {
//         int mid = left + (right - left) / 2;
//         if (arr[mid].category == target)
//             return mid;
//         else if (arr[mid].category < target)
//             left = mid + 1;
//         else
//             right = mid - 1;
//     }
//     return -1;
// }

// int exponentialSearchCategory(TransactionsArray* arr, int n, const string& target) {
//     if (arr[0].category == target)
//         return 0;
    
//     int i = 1;
//     while (i < n && arr[i].category <= target)
//         i *= 2;

//     return binarySearchCategory(arr, i/2, min(i, n-1), target);
// }

// void calculateElectronicsCreditCardPercentage(TransactionsArray* arr, int count) {
//     heapSortByCategory(arr, count);

//     string targetCategory = "Electronics";
//     int index = exponentialSearchCategory(arr, count, targetCategory);

//     if (index == -1) {
//         cout << "No transactions in 'Electronics' category.\n";
//         return;
//     }

//     // Traverse left and right to find all matching entries
//     int start = index;
//     while (start > 0 && arr[start - 1].category == targetCategory)
//         start--;
//     int end = index;
//     while (end < count - 1 && arr[end + 1].category == targetCategory)
//         end++;

//     int total = end - start + 1;
//     int creditCardCount = 0;
//     for (int i = start; i <= end; ++i) {
//         if (arr[i].payment_method == "Credit Card")
//             creditCardCount++;
//     }

//     float percentage = total ? (creditCardCount * 100.0f / total) : 0;
//     cout << "Percentage of 'Electronics' purchases using Credit Card: " << percentage << "%" << endl;
// }

// int main() {
//     TransactionsArray* transactions = nullptr;
//     int transactionCount = 0;
//     TransactionToArrays("transactions_cleaned.csv", transactions, transactionCount);

//     calculateElectronicsCreditCardPercentage(transactions, transactionCount);

//     delete[] transactions;
//     return 0;
// }

// Nang Zhen Ning TP069063 Q3
void heapify(WordFrequency* arr, int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left].count > arr[largest].count)
        largest = left;
    if (right < n && arr[right].count > arr[largest].count)
        largest = right;

    if (largest != i) {
        WordFrequency temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSortWords(WordFrequency* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        WordFrequency temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void countWordsFromOne(ReviewsArray* review, int& count, WordFrequency*& wf, int& wordCount) {
    int capacity = 100;
    wf = new WordFrequency[capacity];
    wordCount = 0;

    for (int i = 0; i < count; ++i) {
        if (review[i].rating == 1) {
            string text = review[i].review_text;
            string word = "";

            for (size_t j = 0; j <= text.length(); ++j) {
                char c = tolower(text[j]);
                if (isalpha(c)) {
                    word += c;
                } else if (!word.empty()) {
                    int index = -1;
                    bool found = false;
                    for (int k = 0; k < wordCount; ++k) {
                        if (wf[k].word == word) {
                            index = k;
                            found = true;
                            break;
                        }
                    }

                    if (found) {
                        wf[index].count++;
                    } else {
                        if (wordCount >= capacity) {
                            int newCapacity = capacity + 100;
                            WordFrequency* temp = new WordFrequency[newCapacity];
                            for (int k = 0; k < wordCount; ++k)
                                temp[k] = wf[k];
                            delete[] wf;
                            wf = temp;
                            capacity = newCapacity;
                        }
                        wf[wordCount].word = word;
                        wf[wordCount].count = 1;
                        wordCount++;
                    }

                    word = "";
                }
            }
        }
    }

    heapSortWords(wf, wordCount);
}

int binarySearchWord(WordFrequency* arr, int left, int right, const string& target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].word == target)
            return mid;
        else if (arr[mid].word < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int exponentialSearchWord(WordFrequency* arr, int n, const string& target) {
    if (arr[0].word == target) return 0;
    int i = 1;
    while (i < n && arr[i].word <= target) i *= 2;
    return binarySearchWord(arr, i/2, min(i, n-1), target);
}

int main() {
    ReviewsArray* reviews = nullptr;
    int reviewCount = 0;
    ReviewsToArrays("reviews_cleaned.csv", reviews, reviewCount);

    WordFrequency* wf = nullptr;
    int wordCount = 0;

    countWordsFromOne(reviews, reviewCount, wf, wordCount);

    cout << "Top 20 most frequent words in 1-star reviews:\n";
    for (int i = 0; i < 20 && i < wordCount; ++i) {
        cout << wf[i].word << " - " << wf[i].count << endl;
    }

    // Extra Function: search for a word
    string searchWord = "quality";
    int index = exponentialSearchWord(wf, wordCount, searchWord);
    if (index != -1)
        cout << "\nWord '" << searchWord << "' found with frequency: " << wf[index].count << endl;
    else
        cout << "\nWord '" << searchWord << "' not found.\n";

    delete[] wf;
    delete[] reviews;
    return 0;
}
