#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include "Arrays.hpp"
using namespace std;

void ReviewsToArrays(const string& file_name, ReviewsArray*& array, int& count) {
    int capacity = 10;
    array = new ReviewsArray[capacity];
    ifstream file(file_name);
    string line;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        // Expand capacity if needed
        if (count >= capacity) {
            int new_capacity = capacity * 2;
            ReviewsArray* temp = new ReviewsArray[new_capacity];
            for (int i = 0; i < count; ++i) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
            capacity = new_capacity;
        }

        // Manual CSV parsing
        string fields[4];
        int fieldIndex = 0;
        bool inQuotes = false;
        string currentField;

        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];
            if (c == '"') {
                inQuotes = !inQuotes; // Toggle quote state
            } else if (c == ',' && !inQuotes) {
                if (fieldIndex < 4) {
                    fields[fieldIndex++] = currentField;
                    currentField.clear();
                }
            } else {
                currentField += c;
            }
        }
        if (fieldIndex < 4) {
            fields[fieldIndex] = currentField; // Add last field
        }

        // Assign to array
        array[count].product_ID = fields[0];
        array[count].customer_ID = fields[1];
        array[count].rating = stoi(fields[2]); // or stof if float
        array[count].review_text = fields[3];
        ++count;
    }

    file.close();
}

void TransactionToArrays(const string& file_name, TransactionsArray*& array, int& count) {
    int capacity = 10;
    array = new TransactionsArray[capacity];
    ifstream file(file_name);
    string line;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (count >= capacity) {
            int new_capacity = capacity * 2;
            TransactionsArray* temp = new TransactionsArray[new_capacity];
            for (int i = 0; i < count; ++i) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
            capacity = new_capacity;
        }

        // Manual field parsing with quote handling
        string fields[6]; // 6 expected fields
        int fieldIndex = 0;
        bool inQuotes = false;
        string currentField;

        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                if (fieldIndex < 6) {
                    fields[fieldIndex++] = currentField;
                    currentField.clear();
                }
            } else {
                currentField += c;
            }
        }
        if (fieldIndex < 6) {
            fields[fieldIndex] = currentField; // Add last field
        }

        // Assign fields to array
        array[count].customer_ID = fields[0];
        array[count].product = fields[1];
        array[count].category = fields[2];
        array[count].price = stof(fields[3]);
        array[count].date = fields[4];
        array[count].payment_method = fields[5];

        count++;
    }

    file.close();
}
/////////////////////////////////////////////////////////////////////////
// Nang Zhen Ning Q1 Q2 Q3
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

// int main() {
//     ReviewsArray* reviews = nullptr;
//     int reviewCount = 0;
//     ReviewsToArrays("reviews_cleaned.csv", reviews, reviewCount);

//     WordFrequency* wf = nullptr;
//     int wordCount = 0;

//     countWordsFromOne(reviews, reviewCount, wf, wordCount);

//     cout << "Top 20 most frequent words in 1-star reviews:\n";
//     for (int i = 0; i < 20 && i < wordCount; ++i) {
//         cout << wf[i].word << " - " << wf[i].count << endl;
//     }

//     // Extra Function: search for a word
//     string searchWord = "quality";
//     int index = exponentialSearchWord(wf, wordCount, searchWord);
//     if (index != -1)
//         cout << "\nWord '" << searchWord << "' found with frequency: " << wf[index].count << endl;
//     else
//         cout << "\nWord '" << searchWord << "' not found.\n";

//     delete[] wf;
//     delete[] reviews;
//     return 0;
// }

//////////////////////////////////////////////////////////////////////////
// Koh Chun Wei TP067580 (Quick Sort & Recursion Search)
// Liew Yi Xian TP068306 (Bubble Sort & Binary Search)
// 1. 
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
void bubbleSortByDate(TransactionsArray* arr, int count) {
    bool swapped;
    for (int i = 0; i < count - 1; ++i) {
        swapped = false;
        for (int j = 0; j < count - i - 1; ++j) {
            auto date1 = convertDateFormat(arr[j].date);
            auto date2 = convertDateFormat(arr[j + 1].date);

            if (date1 > date2) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}


int binarySearchCustomerID(TransactionsArray* arr, int size, const string& customerID) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid].customer_ID == customerID) {
            return mid; // Found one match
        } else if (arr[mid].customer_ID < customerID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Not found
}

void displayAllCustomerTransactions(TransactionsArray* arr, int size, const string& customerID) {
    int index = binarySearchCustomerID(arr, size, customerID);
    if (index == -1) {
        cout << "No transactions found for Customer ID: " << customerID << endl;
        return;
    }

    cout << "Transactions for Customer ID: " << customerID << endl;

    // Expand left
    int left = index - 1;
    while (left >= 0 && arr[left].customer_ID == customerID) {
        left--;
    }

    // Expand right
    int right = index + 1;
    while (right < size && arr[right].customer_ID == customerID) {
        right++;
    }

    // Print all in range
    for (int i = left + 1; i < right; ++i) {
        cout << "- - - - - " << (i - left) << " - - - - -\n";
        cout << "Customer ID: " << arr[i].customer_ID << endl;
        cout << "Product:     " << arr[i].product << endl;
        cout << "Date:        " << arr[i].date << endl;
        cout << "Category:    " << arr[i].category << endl;
        cout << "Payment:     " << arr[i].payment_method << endl;
        cout << "Price:       RM" << arr[i].price << "\n\n";
    }
}
//// U Guys Can Add+ Here below continue
//////////////////////////////////////////////////////////////////////////
// Koh Chun Wei TP067580 (Quick Sort & Recursion Search)
// 2. 
///string normalize(string& str){
///    string clean;
///   for (char& c : str) {
///        if (!isspace(c)) clean += tolower(c);
///    }
///    return clean;
///}    
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
//Yx
string normalize(const string& text) {
    string result = text;
    result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
int binarySearchCategory(TransactionsArray* arr, int size, const string& target) {
    int low = 0, high = size - 1;
    string tgt = normalize(target);

    while (low <= high) {
        int mid = (low + high) / 2;
        string midCat = normalize(arr[mid].category);
        if (midCat == tgt) return mid;
        else if (midCat < tgt) low = mid + 1;
        else high = mid - 1;
    }
    return -1; 
}
void bubbleSortByCategory(TransactionsArray* arr, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (arr[j].category > arr[j + 1].category) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void countElectronicsAndCreditCard_Binary(TransactionsArray* arr, int size, int& total, int& creditCard) {
    int index = binarySearchCategory(arr, size, "electronics");
    if (index == -1) {
        total = 0;
        creditCard = 0;
        return;
    }

    // Expand left
    int left = index - 1;
    while (left >= 0 && normalize(arr[left].category) == "electronics") {
        left--;
    }

    // Expand right
    int right = index + 1;
    while (right < size && normalize(arr[right].category) == "electronics") {
        right++;
    }

    // Count within range
    total = 0;
    creditCard = 0;
    for (int i = left + 1; i < right; ++i) {
        total++;
        if (normalize(arr[i].payment_method) == "creditcard") {
            creditCard++;
        }
    }
}

//// U Guys Can Add+ Here below continue
//////////////////////////////////////////////////////////////////////////
// Koh Chun Wei TP067580 (Quick Sort & Recursion Search)
// 3. 
void countWordsFromOne(ReviewsArray* review, int& count, WordFrequency*& wf, int& wordCount){ 
    int capacity = 10; 
    wf = new WordFrequency[capacity];
    wordCount = 0;
    int test = 0;
    for(int i = 0; i < count; ++i){
        if(review[i].rating == 1){
            cout << "1-Star Review: " << review[i].review_text << endl;
            test+=1;
            cout<<test<<endl;
            stringstream ss(review[i].review_text);
            string word;

            while(ss >> word){
                word.erase(0, word.find_first_not_of(" \t\n\r\f\v"));
                word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1);
                word.erase(remove(word.begin(), word.end(), '\''), word.end());
                word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());


                for(char& c : word) c = tolower(c);

                if(word.empty()) continue;

                bool found = false;
                for (int j = 0; j < wordCount; ++j) {
                    if (wf[j].word == word) {
                        wf[j].count++;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    if (wordCount >= capacity) {
                        capacity *= 2;
                        WordFrequency* temp = new WordFrequency[capacity];
                        for (int k = 0; k < wordCount; ++k)
                            temp[k] = wf[k];
                        delete[] wf;
                        wf = temp;
                    }
                    wf[wordCount].word = word;
                    wf[wordCount].count = 1;
                    wordCount++;
                }
            }
        }
        
    }
}
int partitionbyword(WordFrequency* arr, int low, int high){
    int pivot = arr[high].count;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j].count > pivot) { 
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSortWords(WordFrequency* arr, int low, int high) {
    if (low < high) {
        int pi = partitionbyword(arr, low, high);
        quickSortWords(arr, low, pi - 1);
        quickSortWords(arr, pi + 1, high);
    }
}
bool isWordInArray(WordFrequency* arr, int size, const string& word, int& index) {
    for (int i = 0; i < size; ++i) {
        if (arr[i].word == word) {
            index = i;
            return true;
        }
    }
    return false;
}
//int oneStarCount = 0;
//countWordsInOneStarReviews 
void countWordsFromOne(ReviewsArray* review, int reviewCount, WordFrequency*& wf, int& wordCount) {
    int capacity = 100; // initial capacity
    wf = new WordFrequency[capacity];
    wordCount = 0;
    int raw_not_count = 0;

    for (int i = 0; i < reviewCount; ++i) {
        if (review[i].rating == 1){

            stringstream ss(review[i].review_text);
            string word;
            while (ss >> word) {
                // Normalize the word
                word.erase(remove_if(word.begin(), word.end(), [](char c) {
                    return !isalpha(c); // Keep only letters
                }), word.end());
                
                transform(word.begin(), word.end(), word.begin(), ::tolower);

                if (word.empty()) continue;

                // Check if word already exists
                bool found = false;
                for (int j = 0; j < wordCount; ++j) {
                    if (wf[j].word == word) {
                        wf[j].count++;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    if (wordCount == capacity) {
                        // Resize array
                        capacity *= 2;
                        WordFrequency* temp = new WordFrequency[capacity];
                        for (int k = 0; k < wordCount; ++k) temp[k] = wf[k];
                        delete[] wf;
                        wf = temp;
                    }
                    wf[wordCount++] = {word, 1};
                }
            }
        }
    }

}


void bubbleSortWords(WordFrequency* wf, int wordCount) {
    for (int i = 0; i < wordCount - 1; ++i) {
        for (int j = 0; j < wordCount - i - 1; ++j) {
            if (wf[j].count < wf[j + 1].count) {
                swap(wf[j], wf[j + 1]);
            }
        }
    }
}

void displayTopWords(WordFrequency* arr, int size) {
    std::cout << "\nAll Word Frequencies in 1-Star Reviews:\n";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i].word << ": " << arr[i].count << " times\n";
    }
}
int countTotalWordsInOneStarReviews(ReviewsArray* arr, int index, int size) {
    if (index >= size) return 0;

    int wordCount = 0;
    if (arr[index].rating == 1) {
        stringstream ss(arr[index].review_text);
        string word;
        while (ss >> word) {
            word.erase(0, word.find_first_not_of(" \t\n\r\f\v"));
            word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1);
            word.erase(remove(word.begin(), word.end(), '\''), word.end());
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
            if (!word.empty()) wordCount++;
        }
    }

    return wordCount + countTotalWordsInOneStarReviews(arr, index + 1, size);
}