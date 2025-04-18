#include <iostream>
using namespace std;
// Import csv file to Doubly Linked List 
struct ReviewsNode{
    string product_ID;
    string customer_ID;
    string rating;
    string review_text;
    string product;
    string category;
    string price;
    string date;
    string payment_method;
    ReviewsNode* next = nullptr;
    ReviewsNode* prev = nullptr;
};
// Import csv file to Dynamic Array
struct ReviewsArray{
    string product_ID;
    string customer_ID;
    string rating;
    string review_text;
};
struct TransactionsArray{
    string customer_ID;
    string product;
    string category;
    string price;
    string date;
    string payment_method;
};
// Sorting Algorithms (Quick Sort) && Searching Algorithms (Recursive Search)

// 1. How can you efficiently sort customer transactions by date and display the total number of transactions in both datasets?
    // Array
    int partitionbydate(TransactionsArray* arr, int low, int high){
        string pivot = arr[high].date;
        int i = low - 1;

        for(int j = low; j < high; ++j){
            if(arr[j].date < pivot){
                i++;
                TransactionsArray temp = arr[i];
                arr[i] = arr[i];
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

    void recursiveSearchByCustomerID(TransactionsArray* arr, int index, int size, const string& targetID) {
        if (index >= size) return;
    
        if (arr[index].customer_ID == targetID) {
            cout << arr[index].customer_ID << ", " << arr[index].product << ", " << arr[index].date << endl;
        }
    
        recursiveSearchByCustomerID(arr, index + 1, size, targetID);
    }
    

// 2. What percentage of purchases in the “Electronics” category were made using Credit Card payments? 
// (Hint: Need to search and filter transactions based on category and payment method)



// 3. Which words are most frequently used in product reviews rated 1-star? 
// (Hint: Extract the most common words, sort them by frequency, and present the results)







