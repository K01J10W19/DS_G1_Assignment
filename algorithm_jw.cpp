#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

struct ReviewsNode{
    string product_ID;
    string customer_ID;
    int rating;
    string review_text;
    string product;
    string category;
    float price;
    string date;
    string payment_method;
    ReviewsNode* next = nullptr;
    ReviewsNode* prev = nullptr;
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


// 3. Which words are most frequently used in product reviews rated 1-star? 
// (Hint: Extract the most common words, sort them by frequency, and present the results)
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
    
