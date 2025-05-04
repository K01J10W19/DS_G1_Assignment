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
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (convertDateFormat(arr[j].date) > convertDateFormat(arr[j + 1].date)) {
                swap(arr[j], arr[j + 1]);
            }
        }
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
